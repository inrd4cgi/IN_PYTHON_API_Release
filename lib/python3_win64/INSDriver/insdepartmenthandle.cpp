#include "insdepartmenthandle.h"

namespace INS
{
	/**************************************************************************************************
	Description:获取系统中所有部门列表[departments]。
	**************************************************************************************************/
	INSGetDepartmentList::INSGetDepartmentList(qint32 filter)
	{
		*mp_out << qint32(121) << m_request_id << filter;
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
	void INSGetDepartmentList::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
			*mp_in >> m_departments;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端请求创建一个部门[department]。
	**************************************************************************************************/
	INSCreateDepartment::INSCreateDepartment(ProjectGroup& department)
	{
		*mp_out << qint32(123) << m_request_id << department;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	INSCreateDepartment::~INSCreateDepartment() {
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足。-1==已经存在同名项目组。-2==未知
	**************************************************************************************************/
	void INSCreateDepartment::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;

		//部门创建成功
		if (1 == m_return_value)
			*mp_in >> m_department;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:客户端删除一个部门,参数[departmentid]为要删除的部门id。
	**************************************************************************************************/
	INSDeleteDepartment::INSDeleteDepartment(const qint32 & departmentid)
	{
		*mp_out << qint32(128) << m_request_id << departmentid;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==删除成功;0==权限不足。-1==数据出错。
	**************************************************************************************************/
	void INSDeleteDepartment::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:修改部门[department].可修改的内容有：部门名，部门所拥有的团队。
	**************************************************************************************************/
	INSModifyDepartment::INSModifyDepartment(const Department & department)
	{
		*mp_out << qint32(130) << m_request_id << department;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==修改成功;0==权限不足。-1==数据出错。
	**************************************************************************************************/
	void INSModifyDepartment::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value >> m_department;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:获取一个指定id的部门[department]。
	**************************************************************************************************/
	INSGetDepartment::INSGetDepartment(const Department & department)
	{
		*mp_out << qint32(132) << m_request_id << department;
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
	void INSGetDepartment::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value >> m_department;
		m_finished = true;
		return;
	}
}