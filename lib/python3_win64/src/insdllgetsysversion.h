#pragma once
#include "insrequest.h"

namespace INS
{
	class INSDLLGetSysVersion : public INSRequest
	{
	public:
		INSDLLGetSysVersion(QString& version);
		~INSDLLGetSysVersion();

		qint32 m_return_value;
		QString m_ver;
		void Process(const QByteArray&);
	};
};
