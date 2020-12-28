#pragma once
#include <QList>
#include <QColor>
#include <QString>

#define FinalINTaskStatusObj INTaskStatus::OnHold
#define GetTaskStatusCount ((int)FinalINTaskStatusObj - (int)INTaskStatus::ToDo + 1)

#define FinalINAssetStatusObj INAssetStatus::noWorkflow
#define GetAssetStatusCount ((int)FinalINAssetStatusObj - (int)INAssetStatus::noWorkflow+1)

#define FinalINProjectStatusObj ProjectStatusEnum::TO_DO
#define GetProjectStatusCount ((int)FinalINProjectStatusObj - (int)ProjectStatusEnum::PASS+1)


#define ToIntAndQstring(taskType) qMakePair((int)(taskType), InTaskStatusOperate::SplitStrByWhiteSpace(QString(#taskType).mid(QString(#taskType).lastIndexOf(":")+1)))

namespace INS
{
enum class INTaskStatus {
    ToDo = 1,
    WorkInProgress = 2,
    PendingApproval = 3,
    PendingPanelReview = 4,
    Reopened = 5,
    PendingValidation = 6,
    Approved = 7,
    Paused = 8,
    Deprecated = 9,
    OnHold = 10
};

class InTaskStatusOperate
{
public:
    static QList<INTaskStatus> GetTaskStatusList()
    {
        int n_count = GetTaskStatusCount;
        QList<INTaskStatus> status;
        for (int i = 1; i <= n_count; ++i)
        {
            ///跳过不需要的PendingPanelReview
            if(4 == i)
                continue;
            status.push_back(INTaskStatus(i));
        }
        return status;
    }

    static QStringList GetTaskStatusStringList()
    {
        static QStringList statusString;
        if(statusString.isEmpty())
        {
            QList<INTaskStatus> statusList = GetTaskStatusList();
            auto taskMap = GetINTaskStatus();
            for(const auto & status : statusList)
                statusString.append(taskMap.value(int(status)).name);
        }
        return statusString;
    }


    class StatusNameAndColor
    {
    public:
        QString name;
        QColor color;
    };
    static QString GetINTaskStausString(INTaskStatus taskState)
    {
        auto taskMap = GetINTaskStatus();
        return taskMap.value(static_cast<int>(taskState)).name;
    }

    static QColor GetINTaskStausColor(INTaskStatus taskState)
    {
        auto taskColorMap = GetINTaskStatus();
        return taskColorMap.value(static_cast<int>(taskState)).color;
    }

    static QString SplitStrByWhiteSpace(QString sourceText)
    {
        for (int i = 0; i < sourceText.size(); ++i)
        {
            if (sourceText.at(i) >= 'A' && sourceText.at(i) <= 'Z')
                sourceText.insert(i++, ' ');
        }
        return sourceText;
    }

    static QMap<qint32, QString> GetINTaskStatusWithoutColor()
    {
        static QMap<int, QString> taskMap;
        if (taskMap.isEmpty())
        {
            auto addToMap = [](const int &statusId, const QString& statusName) {
                taskMap.insert(statusId, statusName);
            };
            addToMap((qint32)(INTaskStatus::ToDo), GetINTaskStausString(INTaskStatus::ToDo));
            addToMap((qint32)(INTaskStatus::WorkInProgress), GetINTaskStausString(INTaskStatus::WorkInProgress));
            addToMap((qint32)(INTaskStatus::PendingApproval), GetINTaskStausString(INTaskStatus::PendingApproval));
            //addToMap((qint32)(INTaskStatus::PendingPanelReview), GetINTaskStausString(INTaskStatus::PendingPanelReview));
            addToMap((qint32)(INTaskStatus::Reopened), GetINTaskStausString(INTaskStatus::Reopened));
            addToMap((qint32)(INTaskStatus::PendingValidation), GetINTaskStausString(INTaskStatus::PendingValidation));
            addToMap((qint32)(INTaskStatus::Approved), GetINTaskStausString(INTaskStatus::Approved));
            addToMap((qint32)(INTaskStatus::Paused),"Paused by System");
            addToMap((qint32)(INTaskStatus::Deprecated), GetINTaskStausString(INTaskStatus::Deprecated));
            addToMap((qint32)(INTaskStatus::OnHold), GetINTaskStausString(INTaskStatus::OnHold));
        }
        return taskMap;
    }

private:
    static QMap<int, StatusNameAndColor> GetINTaskStatus()
    {
        static QMap<int, StatusNameAndColor> taskMap;
        if (taskMap.isEmpty())
        {
            auto addToMap = [](const QPair<int, QString>& taskType, const QColor& typeColor) {
                taskMap.insert(taskType.first, {taskType.second, typeColor});
            };
            addToMap(ToIntAndQstring(INTaskStatus::ToDo), QColor("#5eceff"));
            addToMap(ToIntAndQstring(INTaskStatus::WorkInProgress), QColor("#2888F7"));
            addToMap(ToIntAndQstring(INTaskStatus::PendingApproval), QColor("#ffaa40"));
            addToMap(ToIntAndQstring(INTaskStatus::PendingPanelReview), QColor("#ffb75d"));
            addToMap(ToIntAndQstring(INTaskStatus::Reopened), QColor("#f23333"));
            addToMap(ToIntAndQstring(INTaskStatus::PendingValidation), QColor("#cc7ee0"));
            addToMap(ToIntAndQstring(INTaskStatus::Approved), QColor("#7ad975"));
            addToMap(qMakePair(int(INTaskStatus::Paused),QString("Paused by System")), QColor("#B15EFF"));
            addToMap(ToIntAndQstring(INTaskStatus::Deprecated), QColor("#8b8b8b"));
            addToMap(ToIntAndQstring(INTaskStatus::OnHold), QColor("#8080C0"));
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
        int n_count = GetAssetStatusCount;
        QList<INAssetStatus> status;
        for (int i = 0; i < n_count; ++i)
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
        int n_count = GetProjectStatusCount;
        QList<ProjectStatusEnum> status;
        for (int i = 0; i < n_count; ++i)
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

