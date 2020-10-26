#pragma once
#include "insrequest.h"

namespace INS
{
	class INSGetAvatarInfo : public INSRequest
	{
	public:
		INSGetAvatarInfo(Avatar& avatar);
		~INSGetAvatarInfo() {};

		qint32 m_return_value = 0;
		Avatar m_avatar;
		void Process(const QByteArray&);
	};

	class INSInsertAvatarInfo : public INSRequest
	{
	public:
		INSInsertAvatarInfo(const Avatar Iavatar);
		~INSInsertAvatarInfo() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSUpdateAvatarInfo : public INSRequest
	{
	public:
		INSUpdateAvatarInfo(const Avatar Uavatar);
		~INSUpdateAvatarInfo() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSGetTaskInfo : public INSRequest
	{
	public:
		INSGetTaskInfo(ProjectTaskInfo & pti);
		~INSGetTaskInfo() {};

		qint32 m_return_value = 0;
		ProjectTaskInfo m_pti;
		void Process(const QByteArray&);
	};

	class INSGetTaskStatus : public INSRequest
	{
	public:
		INSGetTaskStatus(ProjectTaskInfo & pti);
		~INSGetTaskStatus() {};

		qint32 m_return_value = 0;
		ProjectTaskInfo m_pti;
		void Process(const QByteArray&);
	};

	class INSGetTeamInfo : public INSRequest
	{
	public:
		INSGetTeamInfo(ProjectTaskInfo & pti);
		~INSGetTeamInfo() {};

		qint32 m_return_value = 0;
		ProjectTaskInfo m_pti;
		void Process(const QByteArray&);
	};

	class INSGetMen : public INSRequest
	{
	public:
		INSGetMen(ProjectTaskInfo & pti);
		~INSGetMen() {};

		qint32 m_return_value = 0;
		ProjectTaskInfo m_pti;
		void Process(const QByteArray&);
	};

}
