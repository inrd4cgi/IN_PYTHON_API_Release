#pragma once
#include "insrequest.h"

namespace INS
{
	//客户端请求获取团队列表
	class INSGetTeams : public INSRequest
	{
	public:
		INSGetTeams(const qint32& department_id,qint32 projectId);
		~INSGetTeams();

		qint32 m_return_value = 0;
		QList<TeamInfomation> m_teams;
		void Process(const QByteArray&);
	};

	//客户端请求创建一个团队
	class INSCreateTeam : public INSRequest
	{
	public:
		INSCreateTeam(TeamInfomation& teaminfo);
		~INSCreateTeam();

		qint32 m_return_value = 0;
		TeamInfomation m_teaminfo;
		void Process(const QByteArray&);
	};

	//客户端请求删除一个团队
	class INSDeleteTeam : public INSRequest
	{
	public:
		INSDeleteTeam(const qint32& teamid);
		~INSDeleteTeam();

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//客户端请求修改团队信息
	class INSModifyTeam: public INSRequest
	{
	public:
		INSModifyTeam(const TeamInfomation& team);
		~INSModifyTeam() {};

		qint32 m_return_value = 0;
		TeamInfomation m_team;
		void Process(const QByteArray&);
	};

	//客户端请求获取指定团队信息。
	class INSGetTeam : public INSRequest
	{
	public:
		INSGetTeam(TeamInfomation& team);
		~INSGetTeam();

		qint32 m_return_value = 0;
		TeamInfomation m_team;
		void Process(const QByteArray&);
	};
};
