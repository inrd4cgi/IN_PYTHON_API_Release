#pragma once
#include "insrequest.h"
#include "insdriver_global.h"

#include <QObject>
#include <functional>

namespace INS
{
	class INSLogin : public INSRequest
	{
	public:
		INSLogin(const QString & username, const QString & password, const QString & type);
		~INSLogin() override;
		
		qint32 m_return_value = 0;
		void Process(const QByteArray&) override;
		bool m_normalRole = false;

		static int m_reloginTimeout;
		static std::function<void(bool)> LoginStatusCallback;

		/*! 
		 * \brief 再次登录函数，该函数只能在程序运行后，在登录过一次之后才能开始调用。程序启动后，未登录过账号，就直接调用该函数则无效。
		 * \details 
		 * \param 
		 * \return
		 */
		static qint32 ReLogin();

		/*! 
		 * \brief 重新连接网络并且再次登录的函数，可在网络断开连接后使用。
		 * \details 
		 * \param 
		 * \return
		 */
		static void ReConnectThenLogin();

	protected:
		static QString m_currentName;
		static QString m_currentPassword;
		static QString m_currentType;
		static QDateTime m_reloginFirstTime;

		INSLogin(const QString & username, const QString & password);

		void SaveCurrentLoginInfo(const QString& userName, const QString& password, const QString& type = QString());

    private:
	    static void ReLoginForever();
	};

	class INSActivateAccount : public INSLogin
	{
	public:
		INSActivateAccount(const QString & username, const QString & password);
		~INSActivateAccount();

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};


	//INSLoginConflictListener
	//**************************************************************************************
	class INSLoginConflictListener : public INSRequest
	{
	public:

		/*!
         * \brief 设置登录冲突通知的回调函数，如果之前已经设置过回调函数，那么新的函数会覆盖掉旧的函数。
         * \details
         * \param[in] p_func 回调函数的函数指针
         * \return
         */
		void SetCallbackFunc(std::function<void(QString)> p_func);

		void Process(const QByteArray &) override;

		static INSLoginConflictListener *GetInstance();
	protected:
		std::function<void(QString)> m_loginConflictCallback{nullptr};

    private:
        INSLoginConflictListener();
	};

	class INSDRIVER_EXPORT INSPythonNotifier : public QObject
	{
        Q_OBJECT

	public:

        static INSPythonNotifier *GetInstance();
        void LogOff(QString);
        void Disconnected();
	
    signals:
	    void EventLogOff(QString);
        void EventDisconnected();

    private slots:
        void SlotAppServerSocketStatus(bool);
    private:
        INSPythonNotifier(QObject *parent = 0);
	};
};
