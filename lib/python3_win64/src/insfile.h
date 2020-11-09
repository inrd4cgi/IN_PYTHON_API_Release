#pragma once
#include "insrequest.h"

namespace INS
{
	//获取文件的历史版本信息。
	class INSGetFileHistory :public INSRequest
	{
	public:
		INSGetFileHistory(const INFileBase&);
		~INSGetFileHistory() {};

		INFileBase m_file;
		QList<INFileHistory> m_histories;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};
	
	//修改文件状态
	class INSModifyFileStatus :public INSRequest
	{
	public:
		INSModifyFileStatus(const INFileBase&);
		~INSModifyFileStatus() {};

		INFileBase m_file;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};
};
