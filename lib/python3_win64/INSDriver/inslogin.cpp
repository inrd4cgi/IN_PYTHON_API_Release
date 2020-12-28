#include "inslogin.h"
#include "insdriver.h"

#include <QCryptographicHash>
#include <QTimer>
#include <QCoreApplication>
#include <QtConcurrentRun>
#include <QtCore/qabstracteventdispatcher.h>

#define RECONNECT_MSEC 1000
const int RELOGIN_MSEC = 5 * 1000;

#ifdef INSDRIVER_PYTHON
using namespace INS_INTERFACE;
#endif

namespace INS
{
	QString INSLogin::m_currentName = nullptr;
	QString INSLogin::m_currentPassword = nullptr;
	QString INSLogin::m_currentType = nullptr;
	int INSLogin::m_reloginTimeout = 0;
	QDateTime INSLogin::m_reloginFirstTime;
	std::function<void(bool)> INSLogin::LoginStatusCallback = nullptr;

	/**************************************************************************************************
	Description:构造函数。用户名[username]和密码[password]。密码在这里用md5加密。[type]为登录类型，例如：
	INSJIM,INSMAYA,INSUE4
	**************************************************************************************************/
	INSLogin::INSLogin(const QString & username, const QString & password, const QString & typ)
	{
		const static QString type = INS_CLIENT_PREFIX + QString(":") + typ;//加个前缀，你江哥加的
		QString password_encrypted = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5).toHex();
		SaveCurrentLoginInfo(username, password, type);
        QString jsonStr = JsonMessageUtils::dataToJson(username, password_encrypted, type);
		*mp_out << qint32(108) << m_request_id << jsonStr;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSLogin::~INSLogin() {
	}

	/**************************************************************************************************
	Description:分析回复数据，此过程在一个独立的线程中进行。回复代码：110：登录成功。109：账号密码错误。108：
	该账户已在其他地方登录。
	**************************************************************************************************/
	void INSLogin::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		QString jsonStr;
        qint32 isactived = 1;

        *mp_in >> jsonStr;
        JsonMessageUtils::jsonToData(jsonStr, m_reply_code, isactived, m_normalRole);

		if (m_reply_code == 110)
		{
			m_return_value = 1;
			if (!isactived)
				m_return_value = -1;
		}
		if (m_reply_code == 109)
			m_return_value = 0;
		if (m_reply_code == 108)
			m_return_value = -2;
		m_finished = true;

		qDebug()<<"reply code"<<m_reply_code<<" return value"<<m_return_value;
	}

	qint32 INSLogin::ReLogin()
	{
		assert(!m_currentName.isEmpty() && !m_currentPassword.isEmpty() && !m_currentType.isEmpty());

		bool bNormal;
		return Login(m_currentName, m_currentPassword, bNormal, m_currentType);
	}

	void INSLogin::ReConnectThenLogin()
	{
        auto threadFunc = [](){
            while (!INSNETWORK->ReqReConnectToAppServerHost())
                QThread::msleep(RECONNECT_MSEC);

            m_reloginFirstTime = QDateTime::currentDateTime();
            ReLoginForever();
        };
        QtConcurrent::run(threadFunc);
	}

	INSLogin::INSLogin(const QString & username, const QString & password)
	{
		m_currentName = username;
		m_currentPassword = password;
	}

	void INSLogin::SaveCurrentLoginInfo(const QString & userName, const QString & password, const QString & type)
	{
		m_currentName = userName;
		m_currentPassword = password;

		if (!type.isEmpty())
			m_currentType = type;
	}

    void INSLogin::ReLoginForever()
    {
        while (true)
        {
            auto currentDt(QDateTime::currentDateTime());
            if (m_reloginFirstTime.secsTo(currentDt) > m_reloginTimeout)
            {
                qDebug()<<"Relogin timeout";
                qApp->exit(0);
                return;
            }

            qint32 loginRet = INSLogin::ReLogin();
            if (loginRet == 1)
            {
                qInfo() << "ReConnect succeeded. And login succeeded.";
                if (LoginStatusCallback)
                    LoginStatusCallback(true);
                return;
            }

            qApp->processEvents();
            QThread::msleep(RELOGIN_MSEC);
            qCritical() << "ReConnect succeeded . But login failed";
        }
    }

    /**************************************************************************************************
    Description:激活账号。
    **************************************************************************************************/
	INSActivateAccount::INSActivateAccount(const QString & username, const QString & password)
		:INSLogin(username, password)
	{
		QString password_encrypted = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5).toHex();
		SaveCurrentLoginInfo(username, password);
		QString jsonStr = JsonMessageUtils::dataToJson(username, password_encrypted);
		*mp_out << qint32(111) << m_request_id << jsonStr;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSActivateAccount::~INSActivateAccount() {
	}

	void INSActivateAccount::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		QString jsonStr;
		*mp_in >> jsonStr;
        JsonMessageUtils::jsonToData(jsonStr, m_return_value);
		m_finished = true;
		return;
	}


	//INSLoginConflictListener
	//**************************************************************************************
	INSLoginConflictListener::INSLoginConflictListener()
			: INSRequest(-1011){
		m_lock.unlock();
	}

	void INSLoginConflictListener::SetCallbackFunc(std::function<void(QString)> p_func) {
		m_loginConflictCallback = p_func;
	}

	void INSLoginConflictListener::Process(const QByteArray &byteArray) {
		//在python api下，这个成员可能为空。
		if (m_loginConflictCallback) {
			m_data = byteArray;
			mp_in->device()->seek(0);
			QString jsonStr;
			*mp_in >> jsonStr;

			QString msg;
			JsonMessageUtils::jsonToData(jsonStr, msg);
			m_loginConflictCallback(msg);
		}
	}
};