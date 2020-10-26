#include "insproject.h"

namespace INS
{
	/**************************************************************************************************
	Description:获取文件服务器上存放项目的根路径列表。
	**************************************************************************************************/
	INSGetRootDirs::INSGetRootDirs()
	{
		*mp_out << qint32(301) << m_request_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取成功;0==没有权限;-1==数据出错。
	**************************************************************************************************/
	void INSGetRootDirs::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_root_dirs;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:获取项目列表。
	**************************************************************************************************/
	INSGetProjectFiles::INSGetProjectFiles()
	{
		*mp_out << qint32(312) << m_request_id;
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
	void INSGetProjectFiles::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_projects;
		m_finished = true;
		return;
	}
};