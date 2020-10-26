#pragma once

#include "insdatastructure.h"
#include "PyWrapperUtils.h"
#include "InTaskStatus.h"

namespace INS {

	PyWrapper(QListINQLogInfo,QList<INQLogInfo>,QList<INQLogInfo*>);
	PyWrapper(QListINFileStructTemplate,QList<INFileStructTemplate>,QList<INFileStructTemplate*>);
	PyWrapper(QListSelectInboxEntity,QList<SelectInboxEntity>,QList<SelectInboxEntity*>);
	PyWrapper(QListSimpleWorklog,QList<SimpleWorklog>,QList<SimpleWorklog*>);
	PyWrapper(QListNotification,QList<Notification>,QList<Notification*>);
	PyWrapper(QListINQHolidayTemplate,QList<INQHolidayTemplate>,QList<INQHolidayTemplate*>);
	PyWrapper(QListINAsset,QList<INAsset>,QList<INAsset*>);
	PyWrapper(QListINTask,QList<INTask>,QList<INTask*>);
	PyWrapper(QListINShot,QList<INShot>,QList<INShot*>);
	PyWrapper(QListTagParam,QList<TagParam>,QList<TagParam*>);
	PyWrapper(QListINAssetStatus,QList<INAssetStatus>,QList<INAssetStatus*>);
	PyWrapper(QListDeleteInfo,QList<DeleteInfo>,QList<DeleteInfo*>);
	PyWrapper(QListINQProjectPermissionVO,QList<INQProjectPermissionVO>,QList<INQProjectPermissionVO*>);
	PyWrapper(QListINQPersonTemplateVO,QList<INQPersonTemplateVO>,QList<INQPersonTemplateVO*>);
	PyWrapper(QListtag_CIdName,QList<tag_CIdName>,QList<tag_CIdName*>);
	PyWrapper(QListDepartment,QList<Department>,QList<Department*>);
	PyWrapper(QListPerson,QList<Person>,QList<Person*>);
	PyWrapper(QListTeamInfomation,QList<TeamInfomation>,QList<TeamInfomation*>);
	PyWrapper(QListStorageInfo,QList<StorageInfo>,QList<StorageInfo*>);
	PyWrapper(QListProjectMilestone,QList<ProjectMilestone>,QList<ProjectMilestone*>);
	PyWrapper(QListqint,QList<qint32>,QList<qint32>);
	PyWrapper(QListTagInfoVO,QList<TagInfoVO>,QList<TagInfoVO*>);
	PyWrapper(QListTagResourceVO,QList<TagResourceVO>,QList<TagResourceVO*>);
	PyWrapper(QListINQProjectVO,QList<INQProjectVO>,QList<INQProjectVO*>);
	PyWrapper(QListFileTaskVO,QList<FileTaskVO>,QList<FileTaskVO*>);
	PyWrapper(QListTaskFileRelationEditParam,QList<TaskFileRelationEditParam>,QList<TaskFileRelationEditParam*>);
	PyWrapper(QListPersonRoleDTO,QList<PersonRoleDTO>,QList<PersonRoleDTO*>);
	PyWrapper(QListPanelReviewVO,QList<PanelReviewVO>,QList<PanelReviewVO*>);
	PyWrapper(QListINFileBase,QList<INFileBase>,QList<INFileBase*>);
	PyWrapper(QListINTaskStatus,QList<INTaskStatus>,QList<INTaskStatus*>);
	PyWrapper(QListINTaskComment,QList<INTaskComment>,QList<INTaskComment*>);
	PyWrapper(QListINFileServerRoot,QList<INFileServerRoot>,QList<INFileServerRoot*>);
	PyWrapper(QListINProjectFile,QList<INProjectFile>,QList<INProjectFile*>);
	PyWrapper(QListINFileHistory,QList<INFileHistory>,QList<INFileHistory*>);
	PyWrapper(QListINFolderBase,QList<INFolderBase>,QList<INFolderBase*>);
	PyWrapper(QListINQWorkFlowVO,QList<INQWorkFlowVO>,QList<INQWorkFlowVO*>);
	PyWrapper(QListINPipelineStep,QList<INPipelineStep>,QList<INPipelineStep*>);
	PyWrapper(QListWorkFlowDetlFile,QList<WorkFlowDetlFile>,QList<WorkFlowDetlFile*>);
	typedef QMap<qint32,SelectSendboxEntity> qmapqintselectsendboxentitya;
	typedef QMap<qint32,SelectSendboxEntity*> qmapqintselectsendboxentityb;
	PyWrapper(QMapqintSelectSendboxEntity, qmapqintselectsendboxentitya, qmapqintselectsendboxentityb);
	typedef QMap<qint32,QListINTask> qmapqintqlistintaska;
	typedef QMap<qint32,QListINTask*> qmapqintqlistintaskb;
	PyWrapper(QMapqintQListINTask, qmapqintqlistintaska, qmapqintqlistintaskb);
	typedef QMap<qint32,QString> qmapqintqstringa;
	typedef QMap<qint32,QString> qmapqintqstringb;
	PyWrapper(QMapqintQString, qmapqintqstringa, qmapqintqstringb);
	typedef QMap<qint32,QListProjectMilestone> qmapqintqlistprojectmilestonea;
	typedef QMap<qint32,QListProjectMilestone*> qmapqintqlistprojectmilestoneb;
	PyWrapper(QMapqintQListProjectMilestone, qmapqintqlistprojectmilestonea, qmapqintqlistprojectmilestoneb);
	typedef QMap<qint32,TaskFileVO> qmapqinttaskfilevoa;
	typedef QMap<qint32,TaskFileVO*> qmapqinttaskfilevob;
	PyWrapper(QMapqintTaskFileVO, qmapqinttaskfilevoa, qmapqinttaskfilevob);
	typedef QMap<qint32,INFileBase> qmapqintinfilebasea;
	typedef QMap<qint32,INFileBase*> qmapqintinfilebaseb;
	PyWrapper(QMapqintINFileBase, qmapqintinfilebasea, qmapqintinfilebaseb);
	typedef QMap<qint32,INRecycleBinInfo> qmapqintinrecyclebininfoa;
	typedef QMap<qint32,INRecycleBinInfo*> qmapqintinrecyclebininfob;
	PyWrapper(QMapqintINRecycleBinInfo, qmapqintinrecyclebininfoa, qmapqintinrecyclebininfob);
};