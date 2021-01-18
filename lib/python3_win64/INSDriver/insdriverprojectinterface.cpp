#include "insdriverprojectinterface.h"
#include "inscommonhandle.h"

namespace INS_INTERFACE
{
    INSDRIVER_EXPORT MessageInfo
    GetStorageInfos(QList<StorageInfo> &storageInfos, const StorageInfoSearchParam &params)
    {
        INSCommonRequest<QList<StorageInfo>> commonRequest(301, params);
        commonRequest.WaitForFinished();
        storageInfos = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }


    //里程碑
    INSDRIVER_EXPORT MessageInfo ModifyProjectMilestones(const QList<ProjectMilestone> &ms, int projectId)
    {
        INSCommonRequest<int> commonRequest(594, projectId, ms);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo InsertProjectMilestone(ProjectMilestone &ret)
    {
        INSCommonRequest<ProjectMilestone> commonRequest(590, ret);
        commonRequest.WaitForFinished();
        ret = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo
    FindProjectMilestones(QMap<qint32, QList<ProjectMilestone>> &ret, QList<qint32> projectIds)
    {
        INSCommonRequest<QMap<int, QList<ProjectMilestone>>> commonRequest(591, projectIds);
        commonRequest.WaitForFinished();
        ret = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo UpdateProjectMilestone(ProjectMilestone &ret)
    {
        INSCommonRequest<int> commonRequest(592, ret);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo DeleteProjectMilestone(int milestoneId)
    {
        INSCommonRequest<int> commonRequest(593, milestoneId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }


    //标签
    INSDRIVER_EXPORT MessageInfo GetTagInfo(QList<TagInfoVO> &tagInfos, QVariantMap searchMap)
    {
        INSCommonRequest<QList<TagInfoVO>> commonRequest(601, searchMap);
        commonRequest.WaitForFinished();
        tagInfos = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetTagResource(QList<TagResourceVO> &tagResources, QVariantMap searchMap)
    {
        INSCommonRequest<QList<TagResourceVO>> commonRequest(602, searchMap);
        commonRequest.WaitForFinished();
        tagResources = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //插入标签
    INSDRIVER_EXPORT MessageInfo MakeTag(int &tagId, const TagParam &tagParam)
    {
        INSCommonRequest<int> commonRequest(603, tagParam);
        commonRequest.WaitForFinished();
        tagId = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

	INSDRIVER_EXPORT MessageInfo BatchMakeTags(const QList<TagParam>& tagParams) {
		INSCommonRequest<int> commonRequest(606, tagParams);
		commonRequest.WaitForFinished();
		return commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo GetTagByCondition(QList<TagInfoVO> &tagInfoVOs, const SearchTagParam &searchTagParam) {
        INSCommonRequest<QList<TagInfoVO>> commonRequest(607, searchTagParam);
        commonRequest.WaitForFinished();
        tagInfoVOs = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //移除标签
    INSDRIVER_EXPORT MessageInfo RemoveTag(const TagParam &tagParam)
    {
        INSCommonRequest<int> commonRequest(604, tagParam);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo AddPersonToProject(qint32 prjId, QList<qint32> personList)
    {
        INSCommonRequest<qint32> commonRequest(580, prjId, std::move(personList));
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }
    //将人员移除出项目:projectId和personId不为空
    INSDRIVER_EXPORT MessageInfo RemovePersonFromProject(qint32 projectId, qint32 personId)
    {
        INSCommonRequest<qint32> commonRequest(581, projectId, personId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    //批量修改人员的项目权限[每一项的人员id,项目id和模板id均不为空]
    INSDRIVER_EXPORT MessageInfo UpdatePersonProjectTemplates(QList<INQPersonTemplateVO> &personTemplates)
    {
        INSCommonRequest<qint32> commonRequest(211, personTemplates);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    //创建项目--项目名,服务器信息的id,部门id,项目Root,文件结构模板id均不能为空
    INSDRIVER_EXPORT MessageInfo CreateProject(INQProjectVO &project)
    {
        INSCommonRequest<INQProjectVO> commonRequest(506, project);
        commonRequest.WaitForFinished();
        project = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //编辑项目--项目名,项目id不为空
    INSDRIVER_EXPORT MessageInfo EditProject(INQProjectVO &project)
    {
        INSCommonRequest<INQProjectVO> commonRequest(509, project);
        commonRequest.WaitForFinished();
        project = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //通过项目id查询项目:项目id不能为空
    INSDRIVER_EXPORT MessageInfo GetProject(INQProjectVO &project)
    {
        INSCommonRequest<INQProjectVO> commonRequest(507, project.projectId);
        commonRequest.WaitForFinished();
        project = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetProjects(QList<INQProjectVO> &projects, INQGetPrjBusinessFilter prjFilter)
    {
        INSCommonRequest<QList<INQProjectVO>> commonRequest(508, prjFilter);
        commonRequest.WaitForFinished();
        projects = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT QString GetProjectStateString(ProjectStatusEnum prjState)
    {
        return INProjectStatusOperate::GetProjectStatusString(prjState);
    }

    INSDRIVER_EXPORT MessageInfo DeleteProject(qint32 projectId)
    {
        INSCommonRequest<qint32> commonRequest(511, projectId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    //type: 1是团队，2是资产，3是镜头, 4是sequence
    INSDRIVER_EXPORT MessageInfo
    getProjectStatisticsData(ProjectStatisticsData &projectStatisticsData, qint32 type, qint32 projectId)
    {

        INSCommonRequest<ProjectStatisticsData> commonRequest(510, type, projectId);
        commonRequest.WaitForFinished();
        projectStatisticsData = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }
};