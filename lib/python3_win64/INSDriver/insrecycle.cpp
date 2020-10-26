#include "insrecycle.h"

namespace INS
{
	/**************************************************************************************************
	Description:请求删除项目[project_id]中的回收站条目[recycles]。
	**************************************************************************************************/
	INSDeleteRecycles::INSDeleteRecycles(const qint32 & project_id, const QList<qint32>& recycles)
	{
		*mp_out << qint32(308) << m_request_id << project_id << recycles;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==服务器方的删除工作以及准备好，等待提交确认;0==权限不足;
	-1==修改失败。
	**************************************************************************************************/
	void INSDeleteRecycles::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (1 == m_return_value)
			*mp_in >> m_code >> m_amount_files;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:回复是否确认删除回收站中的内容。ok==1:确认删除，其余为取消删除。先发送[code]再发送[ok]。
	注意：后台对这个回复将不再回复。因此，直接退出就可以了。
	**************************************************************************************************/
	INSComfirmDelete::INSComfirmDelete(const qint32 & ok, const qint32 & code)
	{
		*mp_out << qint32(317) << code << ok;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		if (ok == 0)
		{
			m_return_value = -1;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==删除成功;0==删除失败。
	**************************************************************************************************/
	void INSComfirmDelete::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:将文件[files]放入回收站。
	**************************************************************************************************/
	INSSendFilesToRecycleBin::INSSendFilesToRecycleBin(const QList<INFileBase>& files)
	{
		*mp_out << qint32(320) << m_request_id << files;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==放入回收站成功;0==权限不足;-1==数据出错。
	**************************************************************************************************/
	void INSSendFilesToRecycleBin::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:将文件夹[folders]放入回收站。
	**************************************************************************************************/
	INSSendFoldersToRecycleBin::INSSendFoldersToRecycleBin(const QList<INFolderBase>& folders)
	{
		*mp_out << qint32(321) << m_request_id << folders;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==放入回收站成功;0==权限不足;-1==数据出错。
	**************************************************************************************************/
	void INSSendFoldersToRecycleBin::Process(const QByteArray & data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:恢复回收站中的内容。
	**************************************************************************************************/
	INSRestoreRecycleBin::INSRestoreRecycleBin(const qint32 & project_id, const QList<qint32>& items_id)
	{
		*mp_out << qint32(322) << m_request_id << project_id << items_id;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==恢复成功;0==权限不足;-1==恢复的文件有冲突;-2==数据出错。
	**************************************************************************************************/
	void INSRestoreRecycleBin::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (-1 == m_return_value)
			*mp_in >> m_code >> m_files;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:恢复回收站中的内容。
	**************************************************************************************************/
	INSReplaceFiles::INSReplaceFiles(const qint32 & code, const qint32 & exit, const QList<INFileBase>& files)
	{
		*mp_out << qint32(323) << m_request_id << code << exit << files;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
		if (exit)
		{
			m_return_value = 0;
			m_lock.unlock();
		}
		return;
	}

	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。1==恢复成功;0==恢复失败。
	**************************************************************************************************/
	void INSReplaceFiles::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
		return;
	}

	/**************************************************************************************************
	Description:获取项目[project_id]的回收站中的内容。
	**************************************************************************************************/
	INSGetRecycleBin::INSGetRecycleBin(const qint32 & project_id)
	{
		*mp_out << qint32(324) << m_request_id << project_id;
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
	void INSGetRecycleBin::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (m_return_value == 1)
			*mp_in >> m_recycle_bins;
		m_finished = true;
		return;
	}
}