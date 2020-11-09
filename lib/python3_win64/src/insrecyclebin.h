#pragma once
#include "insrequest.h"

namespace INS
{
	class INSGetBusRecycleList : public INSRequest
	{
	public:
		INSGetBusRecycleList(QList<DeleteInfo> &recyclebinList);
		~INSGetBusRecycleList() {};
		QList<DeleteInfo> m_delInfoList;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSDeleteObjInRecordBin : public INSRequest
	{
	public:
		INSDeleteObjInRecordBin(int recordId);
		~INSDeleteObjInRecordBin() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSRestoreObjInRecordBin : public INSRequest
	{
	public:
		INSRestoreObjInRecordBin(int recordId);
		~INSRestoreObjInRecordBin() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};
}