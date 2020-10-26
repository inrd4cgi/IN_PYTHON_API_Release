#include "insdashboard.h"

namespace INS
{
	INSGetAvatarInfo::INSGetAvatarInfo(Avatar& avatar)
	{
	
		*mp_out << qint32(651) << m_request_id << avatar.personId;
	
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetAvatarInfo::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_avatar;
		m_finished = true;
	}


	INSInsertAvatarInfo::INSInsertAvatarInfo(const Avatar Iavatar)
	{
		*mp_out << qint32(652) << m_request_id << Iavatar;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSInsertAvatarInfo::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}


	INSUpdateAvatarInfo::INSUpdateAvatarInfo(const Avatar Uavatar)
	{
		*mp_out << qint32(653) << m_request_id << Uavatar;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSUpdateAvatarInfo::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}

	INSGetTaskInfo::INSGetTaskInfo(ProjectTaskInfo & pti)
	{
		*mp_out << qint32(654) << m_request_id << pti;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetTaskInfo::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_pti;
		m_finished = true;
	}




	INSGetTaskStatus::INSGetTaskStatus(ProjectTaskInfo & pti)
	{
		*mp_out << qint32(655) << m_request_id << pti;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetTaskStatus::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_pti;
		m_finished = true;
	}




	INSGetTeamInfo::INSGetTeamInfo(ProjectTaskInfo & pti)
	{
		*mp_out << qint32(656) << m_request_id << pti;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetTeamInfo::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_pti;
		m_finished = true;
	}





	INSGetMen::INSGetMen(ProjectTaskInfo & pti)
	{
		*mp_out << qint32(657) << m_request_id << pti;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetMen::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_pti;
		m_finished = true;
	}

}
