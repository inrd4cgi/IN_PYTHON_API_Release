#pragma once

#include "insdriver_global.h"
#include "insdatastructure.h"
#include "InTaskStatus.h"


namespace INS_INTERFACE
{

	/*!
	 * \brief 获取文件服务器所有的存储信息
	 * \details
	 * \param[out] storageInfos 文件服务器信息列表
	 * \param[int] params 查询参数,projectId为0表示查询所有,否则表示查询项目的
	 * \return
	 */
	INSDRIVER_EXPORT MessageInfo GetStorageInfos(QList<StorageInfo>& storageInfos, const StorageInfoSearchParam& params);



	//里程碑
	INSDRIVER_EXPORT MessageInfo ModifyProjectMilestones(const QList<ProjectMilestone>& ms, int projectId);

	INSDRIVER_EXPORT MessageInfo InsertProjectMilestone(ProjectMilestone& ret);

	INSDRIVER_EXPORT MessageInfo FindProjectMilestones(QMap<qint32, QList<ProjectMilestone>>& ret, QList<qint32> projectIds);

	INSDRIVER_EXPORT MessageInfo UpdateProjectMilestone(ProjectMilestone& ret);

	INSDRIVER_EXPORT MessageInfo DeleteProjectMilestone(int milestoneId);


	//通过搜索map获取标签信息
	//searchMap:参数说明
	//a)resourceId:资源id, 比如资产的id
	//b)tagName：标签名称
	//b1)若类型为QString, 则表示查询单个标签。默认加入模糊搜索
	//b2)若类型为QList<QVariant>, 则表示同时包含这些标签信息的内容，这种类型不支持模糊查询
	//c)tagObjectId：标签实体id，表示要搜索资产类型或者特定类型的标签
	//d)tagGroupId:标签组id，表示要搜索某个集合中的标签, 比如搜索项目标签组，则出来的内容是所有与项目相关的内容，包括资产和镜头等信息。
	INSDRIVER_EXPORT MessageInfo GetTagInfo(QList<TagInfoVO>& tagInfos, QVariantMap searchMap);

	INSDRIVER_EXPORT MessageInfo GetTagResource(QList<TagResourceVO>& tagResources, QVariantMap searchMap);

	//插入标签
	INSDRIVER_EXPORT MessageInfo MakeTag(int& tagId, const TagParam& tagParam);

	//插入标签
	INSDRIVER_EXPORT MessageInfo BatchMakeTags(const QList<TagParam>& tagParams);

	//根据条件获取标签
	INSDRIVER_EXPORT MessageInfo GetTagByCondition(QList<TagInfoVO> &tagInfoVOs, const SearchTagParam &searchTagParam);

	//移除标签
	INSDRIVER_EXPORT MessageInfo RemoveTag(const TagParam& tagParam);


	//批量修改人员的项目权限[每一项的人员id,项目id和模板id均不为空]
	INSDRIVER_EXPORT MessageInfo UpdatePersonProjectTemplates(QList<INQPersonTemplateVO>& personTemplates);

	INSDRIVER_EXPORT MessageInfo AddPersonToProject(qint32 prjId, QList<qint32> personList);

	//将人员移除出项目:projectId和personId不为空
	INSDRIVER_EXPORT MessageInfo RemovePersonFromProject(qint32 projectId, qint32 personId);

	//创建项目--项目名,服务器信息的id,部门id,项目Root,文件结构模板id均不能为空
	INSDRIVER_EXPORT MessageInfo CreateProject(INQProjectVO& project);

	//编辑项目--项目名,项目id不为空
	INSDRIVER_EXPORT MessageInfo EditProject(INQProjectVO& project);

	//通过项目id查询项目:项目id不能为空
	INSDRIVER_EXPORT MessageInfo GetProject(INQProjectVO& project);

	//获取项目列表，prjFilter为过滤参数，不需要过滤可不填
	INSDRIVER_EXPORT MessageInfo GetProjects(QList<INQProjectVO>& projects, INQGetPrjBusinessFilter prjFilter = INQGetPrjBusinessFilter());

	INSDRIVER_EXPORT QString GetProjectStateString(ProjectStatusEnum prjState);

	INSDRIVER_EXPORT MessageInfo DeleteProject(qint32 projectId);

    INSDRIVER_EXPORT MessageInfo getProjectStatisticsData(ProjectStatisticsData &projectStatisticsData, qint32 type, qint32 projectId);
};