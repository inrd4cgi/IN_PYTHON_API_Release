#include "insdriverprojectinterface.h"
#include "inspersonhandle.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT INQRespondInfo GetStorageInfos(QList<StorageInfo>& storageInfos, const StorageInfoSearchParam& params) {
		INSCommonRequest< QList<StorageInfo>, StorageInfoSearchParam> commonRequest(301, params);
		commonRequest.WaitForFinished();
		storageInfos = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	//里程碑
	INSDRIVER_EXPORT INQRespondInfo ModifyProjectMilestones(const QList<ProjectMilestone> &ms, int projectId) {
		INSCommonRequest<int, QPair<int, QList<ProjectMilestone>>> commonRequest(594, qMakePair(projectId, ms));
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo InsertProjectMilestone(ProjectMilestone &ret) {
		INSCommonRequest<ProjectMilestone, ProjectMilestone> commonRequest(590, ret);
		commonRequest.WaitForFinished();
		ret = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo FindProjectMilestones(QMap<qint32, QList<ProjectMilestone>> &ret, QList<qint32> projectIds) {
		INSCommonRequest<QMap<int, QList<ProjectMilestone>>, QList<int>> commonRequest(591, projectIds);
		commonRequest.WaitForFinished();
		ret = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo UpdateProjectMilestone(ProjectMilestone &ret) {
		INSCommonRequest<int, ProjectMilestone> commonRequest(592, ret);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo DeleteProjectMilestone(int milestoneId) {
		INSCommonRequest<int, int> commonRequest(593, milestoneId);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}
	

	//标签
	INSDRIVER_EXPORT INQRespondInfo GetTagInfo(QList<TagInfoVO> &tagInfos, QVariantMap searchMap) {
		INSCommonRequest<QList<TagInfoVO>, QVariantMap> commonRequest(601, searchMap);
		commonRequest.WaitForFinished();
		tagInfos = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetTagResource(QList<TagResourceVO> &tagResources, QVariantMap searchMap) {
		INSCommonRequest<QList<TagResourceVO>, QVariantMap> commonRequest(602, searchMap);
		commonRequest.WaitForFinished();
		tagResources = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//插入标签
	INSDRIVER_EXPORT INQRespondInfo MakeTag(int &tagId, const TagParam &tagParam) {
		INSCommonRequest<int, TagParam> commonRequest(603, tagParam);
		commonRequest.WaitForFinished();
		tagId = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//移除标签
	INSDRIVER_EXPORT INQRespondInfo RemoveTag(const TagParam &tagParam) {
		INSCommonRequest<int, TagParam> commonRequest(604, tagParam);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}



	//将人员添加进入项目中:项目id，人员id，不为空[若模板id不为空,则添加之后为普通权限,否则为特殊的模板]
	INSDRIVER_EXPORT INQRespondInfo AddPersonToProject(INQPersonTemplateVO &personTemplate) {
		INSCommonRequest<qint32, INQPersonTemplateVO> commonRequest(580, personTemplate);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}
	//将人员移除出项目:projectId和personId不为空
	INSDRIVER_EXPORT INQRespondInfo RemovePersonFromProject(qint32 projectId, qint32 personId) {
		INSCommonRequest<qint32, QPair<qint32, qint32>> commonRequest(581, qMakePair(projectId, personId));
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//批量修改人员的项目权限[每一项的人员id,项目id和模板id均不为空]
	INSDRIVER_EXPORT INQRespondInfo UpdatePersonProjectTemplates(QList<INQPersonTemplateVO> &personTemplates) {
		INSCommonRequest<qint32, QList<INQPersonTemplateVO>> commonRequest(211, personTemplates);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//创建项目--项目名,服务器信息的id,部门id,项目Root,文件结构模板id均不能为空
	INSDRIVER_EXPORT INQRespondInfo CreateProject(INQProjectVO &project) {
		INSCommonRequest<INQProjectVO, INQProjectVO> commonRequest(506, project);
		commonRequest.WaitForFinished();
		project = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//编辑项目--项目名,项目id不为空
	INSDRIVER_EXPORT INQRespondInfo EditProject(INQProjectVO &project) {
		INSCommonRequest<INQProjectVO, INQProjectVO> commonRequest(509, project);
		commonRequest.WaitForFinished();
		project = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//通过项目id查询项目:项目id不能为空
	INSDRIVER_EXPORT INQRespondInfo GetProject(INQProjectVO &project) {
		INSCommonRequest<INQProjectVO, qint32> commonRequest(507, project.projectId);
		commonRequest.WaitForFinished();
		project = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetProjects(QList<INQProjectVO> &projects, INQGetPrjBusinessFilter prjFilter) {
		INSCommonRequest<QList<INQProjectVO>, INQGetPrjBusinessFilter> commonRequest(508, prjFilter);
		commonRequest.WaitForFinished();
		projects = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT QString GetProjectStateString(ProjectStatusEnum prjState) {
		return INProjectStatusOperate::GetProjectStatusString(prjState);
	}

	INSDRIVER_EXPORT INQRespondInfo DeleteProject(qint32 projectId) {
		INSCommonRequest<qint32, qint32> commonRequest(583, projectId);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}
};