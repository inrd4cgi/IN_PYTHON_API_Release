#pragma once
#include "insrequest.h"

namespace INS
{
	class INSGetTask : public INSRequest
	{
	public:
		INSGetTask(qint32 isneed, INTaskSeachCondition& condition);
		~INSGetTask() {};

		qint32 m_return_value = 0;
		QList<INTask> m_tasklist;
		INTaskSeachCondition m_condition;
		void Process(const QByteArray&);
	};

	class INSCreateTask : public INSRequest
	{
	public:
		INSCreateTask(INTask& newtask);
		~INSCreateTask() {};

		qint32 m_return_value = 0;
		INTask m_newtask;
		void Process(const QByteArray&);
	};

	class INSEditTask : public INSRequest
	{
	public:
		INSEditTask(INTask& etask);
		~INSEditTask() {};

		qint32 m_return_value = 0;
		INTask m_etask;
		void Process(const QByteArray&);
	};

	class INSAddRecordToTaskFiles : public INSRequest
	{
	public:
		INSAddRecordToTaskFiles(int taskId, int fileId, int filetype, int isauto);
		~INSAddRecordToTaskFiles() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSCleanFileRecordBytask : public INSRequest
	{
	public:
		INSCleanFileRecordBytask(int taskId);
		~INSCleanFileRecordBytask() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSEditOutputFile : public INSRequest
	{
	public:
		INSEditOutputFile(int taskId);
		~INSEditOutputFile() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	class INSGetTaskComments : public INSRequest
	{
	public:
		INSGetTaskComments(int taskId, qint32 taskStateId);
		~INSGetTaskComments() { ; }

		qint32 m_return_value;
		QList<INTaskComment> m_taskComments;
		void Process(const QByteArray&);
	};

	class INSGetTaskListPersonal : public INSRequest
	{
	public:
		INSGetTaskListPersonal(int personId);
		~INSGetTaskListPersonal() {}

		qint32 m_return_value;
		QList<INTask> m_tasklist;
		void Process(const QByteArray&);
	};

	class INSGetAppendTask : public INSRequest
	{
	public:
		INSGetAppendTask(int pId);
		~INSGetAppendTask() {};

		qint32 m_return_value = 0;
		QList<INTask> m_tasklist;
		void Process(const QByteArray&);
	};


	class INSDeleteTask : public INSRequest
	{
	public:
		INSDeleteTask(int taskId);

		qint32 m_return_value{ 0 };
		void Process(const QByteArray&);
	};
}


