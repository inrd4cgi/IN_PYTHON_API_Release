#pragma once
#include "insrequest.h"

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
};
