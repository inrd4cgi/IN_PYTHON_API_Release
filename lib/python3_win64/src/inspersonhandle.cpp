#include "inspersonhandle.h"

namespace INS
{
	/************************************************************/
	//获取职位列表
	INSGetJobList::INSGetJobList() {
		*mp_out << qint32(134) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}
	void INSGetJobList::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
		{
			*mp_in >> idNames;
		}
		m_finished = true;
		return;
	}

	//创建IN-admin账号
	INSCreateAdmin::INSCreateAdmin(QString& account) {
		*mp_out << qint32(135) << m_request_id << account;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSCreateAdmin::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
			*mp_in >> person;
		m_finished = true;
		return;
	}

	//移除人员
	INSRemovePerson::INSRemovePerson(qint32 personId) {
		*mp_out << qint32(136) << m_request_id << personId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSRemovePerson::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}
	//删除人员
	INSDeletePerson::INSDeletePerson(qint32 personId) {
		*mp_out << qint32(137) << m_request_id << personId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSDeletePerson::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	//重设密码
	INSResetPassword::INSResetPassword(qint32 personId) {
		*mp_out << qint32(138) << m_request_id << personId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSResetPassword::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}
	/***********************************************************/
	/**************************************************************************************************
	Description:在系统中创建一个用户。
	**************************************************************************************************/
	INSCreatePerson::INSCreatePerson(Person& person)
	{
		*mp_out << qint32(113) << m_request_id << person;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSCreatePerson::~INSCreatePerson() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==创建成功;0==创建失败;-1表示权限不足。
	**************************************************************************************************/
	void INSCreatePerson::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
			*mp_in >> m_person;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:构造函数。通过[person]的id获取指定的person.
	**************************************************************************************************/
	INSGetPerson::INSGetPerson(Person& person)
	{
		*mp_out << qint32(118) << m_request_id << person;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSGetPerson::~INSGetPerson() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取成功，0==获取失败。
	**************************************************************************************************/
	void INSGetPerson::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
		{
			*mp_in >> m_person;
		}
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:修改人员[person]的信息。参数中的person为修改后的状态。
	**************************************************************************************************/
	INSModifyPerson::INSModifyPerson(Person& person)
	{
		*mp_out << qint32(117) << m_request_id << person;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSModifyPerson::~INSModifyPerson() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==修改成功;0==权限不足;1==数据有误。
	**************************************************************************************************/
	void INSModifyPerson::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value >> m_person;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:人员列表[personlist],部门id[department_id]和团队id[team_id]为筛选条件。
	**************************************************************************************************/
	INSGetPersonList::INSGetPersonList(const qint32& department_id, const qint32& team_id, qint32 fileter)
	{
		*mp_out << qint32(125) << m_request_id << department_id << team_id << fileter;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:析构函数。
	**************************************************************************************************/
	INSGetPersonList::~INSGetPersonList() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取人员列表成功;0==获取失败。
	**************************************************************************************************/
	void INSGetPersonList::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_personlist;
		m_finished = true;
		return;
	}
	
	/**************************************************************************************************
	Description:获取个人信息[person]。
	**************************************************************************************************/
	INSGetOneself::INSGetOneself()
	{
		*mp_out << qint32(133) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}
	
	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取成功;0==获取失败。
	**************************************************************************************************/
	void INSGetOneself::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_person;
		m_finished = true;
		return;
	}

	ReCreateJsonPH::ReCreateJsonPH(qint32 jsonid, qint32 proid, qint32 taskId)
	{
		*mp_out << qint32(352) << m_request_id << jsonid << proid << taskId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	void ReCreateJsonPH::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}
}