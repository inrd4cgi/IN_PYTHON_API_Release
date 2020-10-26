#pragma once
#include "insrequest.h"

namespace INS
{
	class INSGetAsset : public INSRequest
	{
	public:
		INSGetAsset(qint32 isneed, INAssetSeachCondition& condition);
		~INSGetAsset() {};

		qint32 m_return_value = 0;
		QList<INAsset> m_assetlist;
		INAssetSeachCondition m_condition;
		void Process(const QByteArray&);
	};

	class INSCreateAsset : public INSRequest
	{
	public:
		INSCreateAsset(INAsset& newasset, QList<TagParam> taglist);
		~INSCreateAsset() {};

		qint32 m_return_value = 0;
		INAsset m_newasset;
		void Process(const QByteArray&);
	};

	class INSEditAsset : public INSRequest
	{
	public:
		INSEditAsset(INAsset& easset);
		~INSEditAsset() {};

		qint32 m_return_value = 0;
		INAsset m_easset;
		void Process(const QByteArray&);
	};

	class INSDeleteAsset : public INSRequest
	{
	public:
		INSDeleteAsset(int assetId);
		~INSDeleteAsset() {};

		INQRespondInfo m_return_value;
		void Process(const QByteArray&);
	};
}
