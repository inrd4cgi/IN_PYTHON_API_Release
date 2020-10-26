#include "inslogin.h"
#include "insdriver.h"

#include <QCryptographicHash>
#include <QTimer>
#include <QCoreApplication>

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
	INSLogin::INSLogin(const QString & username, const QString & password, const QString & type)
	{
		QString password_encrypted = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5).toHex();
		SaveCurrentLoginInfo(username, password, type);

		*mp_out << qint32(108) << m_request_id << username << password_encrypted << type;
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
		*mp_in >> m_reply_code;
		if (m_reply_code == 110)
		{
			m_return_value = 1;
			qint32 isactived = 1;

			*mp_in >> isactived >> m_normalRole;
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
		if (!INSNETWORK->ReqReConnectToAppServerHost())
        {
            QTimer::singleShot(RECONNECT_MSEC, &INSLogin::ReConnectThenLogin);
            return;
        }

		m_reloginFirstTime = QDateTime::currentDateTime();
		ReLoginForever();
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
		auto currentDt(QDateTime::currentDateTime());
		if (m_reloginFirstTime.secsTo(currentDt) > m_reloginTimeout)
		{
			qDebug()<<"Relogin timeout";
			qApp->exit(0);
			return;;
		}

        qint32 loginRet = INSLogin::ReLogin();
        if (loginRet == 1)
        {
            qInfo() << "ReConnect succeeded. And login succeeded.";
            if (LoginStatusCallback)
                LoginStatusCallback(true);
            return;
        }

        qCritical() << "ReConnect succeeded . But login failed";
        QTimer::singleShot(RELOGIN_MSEC, &INSLogin::ReLoginForever);
    }

    /**************************************************************************************************
    Description:激活账号。
    **************************************************************************************************/
	INSActivateAccount::INSActivateAccount(const QString & username, const QString & password)
		:INSLogin(username, password)
	{
		QString password_encrypted = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5).toHex();
		SaveCurrentLoginInfo(username, password);

		*mp_out << qint32(111) << m_request_id << username << password_encrypted;
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
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}
};