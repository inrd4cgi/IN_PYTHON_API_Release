#include "insdllgetsysversion.h"

namespace INS
{
	INSDLLGetSysVersion::INSDLLGetSysVersion(QString& version)
	{
		*mp_out << qint32(112) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}
	
	INSDLLGetSysVersion::~INSDLLGetSysVersion(){
	}

	void INSDLLGetSysVersion::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_reply_code >> m_ver;
		if (118 == m_reply_code)
		{
			m_return_value = m_reply_code;
		}
		m_finished = true;
		return;
	}
};