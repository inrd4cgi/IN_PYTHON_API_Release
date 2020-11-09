#include "insfile.h"

namespace INS
{
	/**************************************************************************************************
	Description:获取文件的历史版本信息。
	**************************************************************************************************/
	INSGetFileHistory::INSGetFileHistory(const INFileBase& file_base)
	{
		*mp_out << qint32(306) << m_request_id << file_base;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==获取成功;0==获取失败;
	**************************************************************************************************/
	void INSGetFileHistory::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_histories;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:修改文件[file]的状态
	**************************************************************************************************/
	INSModifyFileStatus::INSModifyFileStatus(const INFileBase & file)
	{
		*mp_out << m_request_id << file;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==修改成功;0==权限不足;-1==修改失败。
	**************************************************************************************************/
	void INSModifyFileStatus::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_file;
		m_finished = true;
		return;
	}
};
