#include "insasset.h"

namespace INS
{
	//获取资产
	INSGetAsset::INSGetAsset(qint32 isneed, INAssetSeachCondition& condition)
	{
		if (isneed)
		{
			*mp_out << qint32(541) << m_request_id << isneed << condition;
		}
		else
		{
			*mp_out << qint32(541) << m_request_id << isneed;
		}

		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSGetAsset::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_assetlist;
		m_finished = true;
	}

	//创建资产
	INSCreateAsset::INSCreateAsset(INAsset& newasset, QList<TagParam> taglist)
	{
		*mp_out << qint32(542) << m_request_id << newasset << taglist;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSCreateAsset::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_newasset;
		m_finished = true;
	}

	//修改资产
	INSEditAsset::INSEditAsset(INAsset& easset)
	{
		*mp_out << qint32(543) << m_request_id << easset;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSEditAsset::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		if (0 == m_return_value)
			*mp_in >> m_easset;
		m_finished = true;
	}

	//删除资产
	INSDeleteAsset::INSDeleteAsset(int assetId)
	{
		*mp_out << qint32(544) << m_request_id << assetId;
		if (!INSNETWORK->SendDataToAppServer(m_senddata))
		{
			m_return_value = -999;
			m_lock.unlock();
		}
	}

	void INSDeleteAsset::Process(const QByteArray& data)
	{
		m_data = data;
		mp_in->device()->seek(0);
		*mp_in >> m_return_value;
		m_finished = true;
	}
}
