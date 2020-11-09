#include "insrecycle.h"
#include "insrecyclebin.h"

namespace INS
{
	INSGetBusRecycleList::INSGetBusRecycleList(QList<DeleteInfo> &recyclebinList)
	{
		*mp_out << qint32(800) << m_request_id << recyclebinList;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetBusRecycleList::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_delInfoList;
		m_finished = true;
	}

	INSDeleteObjInRecordBin::INSDeleteObjInRecordBin(int recordId)
	{
		*mp_out << qint32(801) << m_request_id << recordId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSDeleteObjInRecordBin::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}

	INSRestoreObjInRecordBin::INSRestoreObjInRecordBin(int recordId)
	{
		*mp_out << qint32(802) << m_request_id << recordId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSRestoreObjInRecordBin::Process(const QByteArray &data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}
}