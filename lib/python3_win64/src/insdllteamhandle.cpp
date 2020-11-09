#include "insdllteamhandle.h"


namespace INS
{
	/**************************************************************************************************
	Description:获取团队列表。部门id[department_id]为筛选条件。
	**************************************************************************************************/
	INSGetTeams::INSGetTeams(const qint32& department_id, qint32 projectId)
	{
		*mp_out << qint32(122) << m_request_id << department_id << projectId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSGetTeams::~INSGetTeams() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取成功;0==获取失败。
	**************************************************************************************************/
	void INSGetTeams::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_teams;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端请求创建一个团队[teaminfo]
	**************************************************************************************************/
	INSCreateTeam::INSCreateTeam(TeamInfomation& teaminfo)
	{
		*mp_out << qint32(124) << m_request_id << teaminfo;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSCreateTeam::~INSCreateTeam() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==创建成功;0==没有权限,-1==部门名已被占用,-2==数据出错。
	**************************************************************************************************/
	void INSCreateTeam::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;

		//创建团队成功
		if (1 == m_return_value)
			*mp_in >> m_teaminfo;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端请求删除一个团队。[teamid]为要删除的团队id。
	**************************************************************************************************/
	INSDeleteTeam::INSDeleteTeam(const qint32& teamid)
	{
		*mp_out << qint32(127) << m_request_id << teamid;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSDeleteTeam::~INSDeleteTeam() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==删除成功;0==没有权限。
	**************************************************************************************************/
	void INSDeleteTeam::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端请求修改一个团队[team]。
	**************************************************************************************************/
	INSModifyTeam::INSModifyTeam(const TeamInfomation & team)
	{
		*mp_out << qint32(129) << m_request_id << team;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==修改成功;0==没有权限;-1==数据出错。
	**************************************************************************************************/
	void INSModifyTeam::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value >> m_team;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端请求获取一个团队[team]。
	**************************************************************************************************/
	INSGetTeam::INSGetTeam(TeamInfomation& team)
	{
		*mp_out << qint32(131) << m_request_id << team;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSGetTeam::~INSGetTeam() {
	}

	/**************************************************************************************************
	Description:客户端请求获取一个团队[team]。
	**************************************************************************************************/
	void INSGetTeam::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value >> m_team;
		m_finished = true;
		return;
	}
};
