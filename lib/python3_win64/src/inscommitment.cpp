#include "inscommitment.h"

namespace INS
{
	//获取任务
	INSGetTask::INSGetTask(qint32 isneed, INTaskSeachCondition& condition)
	{
		if (isneed)
		{
			*mp_out << qint32(521) << m_request_id << isneed << condition;
		}
		else
		{
			*mp_out << qint32(521) << m_request_id << isneed;
		}
		
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetTask::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_tasklist;
		m_finished = true;
	}

	//创建任务
	INSCreateTask::INSCreateTask(INTask& newtask)
	{
		*mp_out << qint32(522) << m_request_id << newtask;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSCreateTask::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_newtask;
		m_finished = true;
	}

	//修改任务
	INSEditTask::INSEditTask(INTask& etask)
	{
		*mp_out << qint32(523) << m_request_id << etask;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSEditTask::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_etask;
		m_finished = true;
	}

	INSAddRecordToTaskFiles::INSAddRecordToTaskFiles(int taskId, int fileId, int filetype, int isauto)
	{
		*mp_out << qint32(528) << m_request_id << taskId << fileId << filetype << isauto;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSAddRecordToTaskFiles::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}
	INSCleanFileRecordBytask::INSCleanFileRecordBytask(int taskId)
	{
		*mp_out << qint32(529) << m_request_id << taskId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSCleanFileRecordBytask::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}
	INSEditOutputFile::INSEditOutputFile(int taskId)
	{
		*mp_out << qint32(530) << m_request_id << taskId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSEditOutputFile::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}


	INSGetTaskComments::INSGetTaskComments(int taskId, qint32 taskStateId)
	{
		*mp_out << qint32(532) << m_request_id << taskId << taskStateId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}
	void INSGetTaskComments::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_taskComments;
		m_finished = true;
	}

	INSGetTaskListPersonal::INSGetTaskListPersonal(int personId)
	{
		*mp_out << qint32(533) << m_request_id << personId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetTaskListPersonal::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_tasklist;
		m_finished = true;
	}
	
	INSGetAppendTask::INSGetAppendTask(int pId)
	{
		*mp_out << qint32(536) << m_request_id << pId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetAppendTask::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_tasklist;
		m_finished = true;
	}

	INSDeleteTask::INSDeleteTask(int taskId)
	{
		*mp_out << qint32(524) << m_request_id << taskId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSDeleteTask::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}
}