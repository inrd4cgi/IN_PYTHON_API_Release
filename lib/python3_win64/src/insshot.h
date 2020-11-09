#pragma once
#include "insrequest.h"

namespace INS
{
	class INSGetShot : public INSRequest
	{
	public:
		INSGetShot(qint32 isneed, INShotSeachCondition& condition);
		~INSGetShot() {};

		qint32 m_return_value = 0;
		QList<INShot> m_shotlist;
		INShotSeachCondition m_condition;
		void Process(const QByteArray&);
	};

	class INSCreateShot : public INSRequest
	{
	public:
		INSCreateShot(INShot& newshot, QList<TagParam> taglist);
		~INSCreateShot() {};

		qint32 m_return_value = 0;
		INShot m_newshot;
		void Process(const QByteArray&);
	};

	class INSEditShot : public INSRequest
	{
	public:
		INSEditShot(INShot& eshot);
		~INSEditShot() {};

		qint32 m_return_value = 0;
		INShot m_eshot;
		void Process(const QByteArray&);
	};

	class INSDeleteShot : public INSRequest
	{
	public:
		INSDeleteShot(int shotId);
		~INSDeleteShot() {};

        INQRespondInfo m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSGetSceneList : public INSRequest
	{
	public:
		INSGetSceneList(int projectId);
		~INSGetSceneList() {};

		qint32 m_return_value = 0;
		QMap<qint32, QString> m_scenelist;
		void Process(const QByteArray&);
	};

	class INSCreateScene : public INSRequest
	{
	public:
		INSCreateScene(QString sceneName, quint32 projectId);
		~INSCreateScene() {};

		qint32 m_return_value = 0;
		qint32 m_sceneId = 0;
		void Process(const QByteArray&);
	};

}
