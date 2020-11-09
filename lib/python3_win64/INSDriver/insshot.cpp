#include "insshot.h"

namespace INS
{
	//获取镜头
	INSGetShot::INSGetShot(qint32 isneed, INShotSeachCondition& condition)
	{
		if (isneed)
		{
			*mp_out << qint32(561) << m_request_id << isneed << condition;
		}
		else
		{
			*mp_out << qint32(561) << m_request_id << isneed;
		}
		
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetShot::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_shotlist;
		m_finished = true;
	}

	//创建镜头
	INSCreateShot::INSCreateShot(INShot& newshot, QList<TagParam> taglist)
	{
		*mp_out << qint32(562) << m_request_id << newshot << taglist;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSCreateShot::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_newshot;
		m_finished = true;
	}

	//修改镜头
	INSEditShot::INSEditShot(INShot& eshot)
	{
		*mp_out << qint32(563) << m_request_id << eshot;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSEditShot::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_eshot;
		m_finished = true;
	}

	//删除镜头
	INSDeleteShot::INSDeleteShot(int shotId)
	{
		*mp_out << qint32(564) << m_request_id << shotId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSDeleteShot::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}

	//获取场景列表
	INSGetSceneList::INSGetSceneList(int projectId)
	{
		*mp_out << qint32(565) << m_request_id << projectId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetSceneList::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_scenelist;
		m_finished = true;
	}

	//创建场景
	INSCreateScene::INSCreateScene(QString sceneName, quint32 projectId)
	{
		*mp_out << quint32(566) << m_request_id << sceneName << projectId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSCreateScene::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_sceneId;
		m_finished = true;
	}
}
