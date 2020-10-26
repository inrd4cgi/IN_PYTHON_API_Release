#pragma once
#include <QList>

#define FinalINTaskStatusObj INTaskStatus::Deprecated
#define GetTaskStatusCount ((int)FinalINTaskStatusObj - (int)INTaskStatus::None + 1)

#define FinalINAssetStatusObj INAssetStatus::noWorkflow
#define GetAssetStatusCount ((int)FinalINAssetStatusObj - (int)INAssetStatus::noWorkflow+1)

#define FinalINProjectStatusObj ProjectStatusEnum::TO_DO
#define GetProjectStatusCount ((int)FinalINProjectStatusObj - (int)ProjectStatusEnum::PASS+1)

#define ToIntAndQstring(taskType) qMakePair((int)(taskType),QString(#taskType).mid(QString(#taskType).lastIndexOf(":")+1))

namespace INS
{
	enum class INTaskStatus {
		None = 0,
		ToDo = 1,
		WorkInProgress = 2,
		PendingApproval = 3,
		PendingPanelReview = 4,
		Reopened = 5,
		PendingValidation = 6,
		Approved = 7,
		Paused = 8,
		Deprecated = 9
	};

	class InTaskStatusOperate
	{
	public:
		static QList<INTaskStatus> GetTaskStatusList()
		{
			int n_count = GetTaskStatusCount;
			QList<INTaskStatus> status;
			for (int i = 0; i < n_count; ++i)
				status.push_back(INTaskStatus((int)INTaskStatus::ToDo + i));
			return status;
		}

		static QString GetINTaskStausString(INTaskStatus taskState)
		{
			auto taskMap = GetINTaskStatus();
			return taskMap.value(static_cast<int>(taskState));
		}

	private:	
		static QMap<int, QString> GetINTaskStatus()
		{
			static QMap<int, QString> taskMap;
			if (taskMap.isEmpty())
			{
				auto addToMap = [](const QPair<int, QString>& taskType) {
					taskMap.insert(taskType.first, taskType.second);
				};
				addToMap(ToIntAndQstring(INTaskStatus::None));
				addToMap(ToIntAndQstring(INTaskStatus::ToDo));
				addToMap(ToIntAndQstring(INTaskStatus::WorkInProgress));
				addToMap(ToIntAndQstring(INTaskStatus::PendingApproval));
				addToMap(ToIntAndQstring(INTaskStatus::PendingPanelReview));
				addToMap(ToIntAndQstring(INTaskStatus::Reopened));
				addToMap(ToIntAndQstring(INTaskStatus::PendingValidation));
				addToMap(ToIntAndQstring(INTaskStatus::Approved));
				addToMap(ToIntAndQstring(INTaskStatus::Paused));
				addToMap(ToIntAndQstring(INTaskStatus::Deprecated));
			}
			return taskMap;
		}
	};


	enum class INAssetStatus
	{
		All = 0, Schedule, Unschedule, noWorkflow
	};

	class INAssetStatusOperate
	{
	public:
		static QList<INAssetStatus> GetAssetStatusList()
		{
			int n_cout = GetAssetStatusCount;
			QList<INAssetStatus> status;
			for (int i = 0; i < n_cout; ++i)
				status.push_back(INAssetStatus((int)INAssetStatus::All + i));
			return status;
		}

		static QString GetINAssetStatusString(INAssetStatus assetState)
		{
			auto assetStatus = GetAssetStatus();
			return assetStatus.value(static_cast<int>(assetState));
		}

	private:
		static  QMap<int, QString> GetAssetStatus()
		{
			static QMap<int, QString> assetStatus;
			if (assetStatus.isEmpty())
			{
				auto addToMap = [](const QPair<int, QString>& type) {
					assetStatus.insert(type.first, type.second);
				};
				addToMap(ToIntAndQstring(INAssetStatus::All));
				addToMap(ToIntAndQstring(INAssetStatus::Schedule));
				addToMap(ToIntAndQstring(INAssetStatus::Unschedule));
				addToMap(ToIntAndQstring(INAssetStatus::noWorkflow));
			}
			
			return assetStatus;
		}
	};


	enum class ProjectStatusEnum {
		PASS = 1,//项目通过[项目中全部任务都为approve状态了]
		UNSCHEDULED = 2,//项目还未安排时间[项目还没指定开始时间]
		WORK_IN_PROGRESS = 3,//项目进行中[项目中有一个任务是正在进行中]
		TO_DO = 4//项目待办中[项目中全部任务都是待办状态]
	};

	class INProjectStatusOperate
	{
	public:
		static QList<ProjectStatusEnum> GetProjectStatusList()
		{
			int n_cout = GetProjectStatusCount;
			QList<ProjectStatusEnum> status;
			for (int i = 0; i < n_cout; ++i)
				status.push_back(ProjectStatusEnum((int)ProjectStatusEnum::PASS + i));
			return status;
		}

		static QString GetProjectStatusString(ProjectStatusEnum prjType)
		{
			auto projectStatus = RegistShotStatus();
			return projectStatus.value(static_cast<int>(prjType));
		}

	private:
		static QMap<int, QString> RegistShotStatus()
		{
			static QMap<int, QString> projectStatus;
			if (projectStatus.isEmpty())
			{
				auto addToMap = [](const QPair<int, QString>& type) {
					projectStatus.insert(type.first, type.second);
				};
				addToMap(ToIntAndQstring(ProjectStatusEnum::PASS));
				addToMap(ToIntAndQstring(ProjectStatusEnum::UNSCHEDULED));
				addToMap(ToIntAndQstring(ProjectStatusEnum::WORK_IN_PROGRESS));
				addToMap(ToIntAndQstring(ProjectStatusEnum::TO_DO));
			}
			return projectStatus;
		}
	};
};

