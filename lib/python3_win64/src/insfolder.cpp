#include "insfolder.h"

namespace INS
{
	/**************************************************************************************************
	Description:获取指定id的文件夹信息。。
	**************************************************************************************************/
	INSGetFolder::INSGetFolder(INFolderBase &folderbase)
	{
		*mp_out << qint32(303) << m_request_id << folderbase.id << folderbase.project_id;
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
	void INSGetFolder::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_folder >> m_files;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:请求创建文件夹[folder]
	**************************************************************************************************/
	INSCreateFolder::INSCreateFolder(const INFolderBase & folder)
	{
		*mp_out << qint32(309) << m_request_id << folder;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==创建成功;0==没有权限;-1==数据出错。
	**************************************************************************************************/
	void INSCreateFolder::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_folder;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:重命名文件夹[folder]。
	**************************************************************************************************/
	INSRenameFolder::INSRenameFolder(const INFolderBase & folder)
	{
		*mp_out << qint32(310) << m_request_id << folder;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==重命名成功;0==没有权限;-1==数据出错。
	**************************************************************************************************/
	void INSRenameFolder::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_folder >> m_files;
		m_finished = true;
		return;
	}
};