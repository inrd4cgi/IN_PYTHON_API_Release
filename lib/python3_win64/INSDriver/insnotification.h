#pragma once
#include "insrequest.h"
#include "sfc_msg.h"

namespace INS
{ 
	//请求获取接收通知列表
	class INSInboxList : public INSRequest
	{
	public:
		INSInboxList();
		~INSInboxList() {};
		
		qint32 m_return_value = 0;
		QList<SelectInboxEntity> m_inboxList;
		void Process(const QByteArray&);
	};

	//请求获取发送通知列表
	class INSOutboxList : public INSRequest
	{
	public:
		INSOutboxList();
		~INSOutboxList() {};

		qint32 m_return_value = 0;
		QMap<qint32, SelectSendboxEntity> m_sentboxList;
		void Process(const QByteArray&);
	};

	//请求获取接收通知
	class INSSelect1inMsg : public INSRequest
	{
	public:
		INSSelect1inMsg(qint32 mailId);
		~INSSelect1inMsg() {};

		qint32 m_return_value = 0;
		MailobjEntity m_inmailobj;
		void Process(const QByteArray&);
	};

	//请求获取发送通知
	class INSSelect1outMsg : public INSRequest
	{
	public:
		INSSelect1outMsg(qint32 mailId);
		~INSSelect1outMsg() {};

		qint32 m_return_value = 0;
		MailobjEntity m_sentmailobj;
		void Process(const QByteArray&);
	};

	//请求发送通知
	class INSSendMsg : public INSRequest
	{
	public:
		INSSendMsg(const MailobjEntity& mailobj);
		~INSSendMsg() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//请求删除通知
	class INSDeleteMsg : public INSRequest
	{
	public:
		INSDeleteMsg(const MailListEntity& delmaillist);
		~INSDeleteMsg() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSNotificationListener : public INSRequest
	{
	public:
		INSNotificationListener();

		/*! 
		 * \brief 设置通知的回调函数，如果之前已经设置过回调函数，那么新的函数会覆盖掉旧的函数。
		 * \details 
		 * \param[in] p_func 回调函数的函数指针
		 * \return
		 */
		void SetCallbackFunc(std::function<void(const QByteArray&)> p_func);

		void Process(const QByteArray&) override;

	protected:
		std::function<void(const QByteArray&)> m_notificationCallback{ nullptr };
	};
}