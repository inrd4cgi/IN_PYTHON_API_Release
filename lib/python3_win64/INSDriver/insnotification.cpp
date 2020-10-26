#include "insnotification.h"


namespace INS
{
	INSInboxList::INSInboxList()
	{
		*mp_out << qint32(401) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSInboxList::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_inboxList;
		m_finished = true;
	}

	//**************************************************************************************************
	INSOutboxList::INSOutboxList()
	{
		*mp_out << qint32(402) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSOutboxList::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_sentboxList;
		m_finished = true;
	}

	//**************************************************************************************************
	INSSelect1inMsg::INSSelect1inMsg(qint32 mailId)
	{
		*mp_out << qint32(403) << m_request_id << mailId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSSelect1inMsg::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_inmailobj;
		m_finished = true;
	}

	//**************************************************************************************************
	INSSelect1outMsg::INSSelect1outMsg(qint32 mailId)
	{
		*mp_out << qint32(404) << m_request_id << mailId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSSelect1outMsg::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_sentmailobj;
		m_finished = true;
	}

	//**************************************************************************************************
	INSSendMsg::INSSendMsg(const MailobjEntity& mailobj)
	{
		*mp_out << qint32(405) << m_request_id << mailobj;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSSendMsg::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		/*if (1 == m_return_value)
			*mp_in >> m_senddata;*/
		m_finished = true;
	}

	//**************************************************************************************************
	INSDeleteMsg::INSDeleteMsg(const MailListEntity& delmaillist)
	{
		*mp_out << qint32(406) << m_request_id << delmaillist;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSDeleteMsg::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		/*if (1 == m_return_value)
			*mp_in >> m_senddata;*/
		m_finished = true;
	}


	//**************************************************************************************************
	INSNotificationListener::INSNotificationListener()
		:INSRequest(-1010)
	{
		m_lock.unlock();
	}

	void INSNotificationListener::SetCallbackFunc(std::function<void(const QByteArray&)> p_func)
	{
		m_notificationCallback = p_func;
	}

	void INSNotificationListener::Process(const QByteArray & byteArray)
	{
	    //在python api下，这个成员可能为空。
	    if (m_notificationCallback) {
            m_notificationCallback(byteArray);
	    }
	}
}
