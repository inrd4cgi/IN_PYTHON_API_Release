#pragma once

#include "insdatastructure.h"
#include "PyWrapperUtils.h"
#include "InTaskStatus.h"

namespace INS {

	PyWrapper(QListLogInfoVO,QList<LogInfoVO>,QList<LogInfoVO*>);
	PyWrapper(QListSelectInboxEntity,QList<SelectInboxEntity>,QList<SelectInboxEntity*>);
	PyWrapper(QListSimpleWorklog,QList<SimpleWorklog>,QList<SimpleWorklog*>);
	PyWrapper(QListNotification,QList<Notification>,QList<Notification*>);
	PyWrapper(QListINQHolidayTemplate,QList<INQHolidayTemplate>,QList<INQHolidayTemplate*>);
	PyWrapper(QListVariantEditParam,QList<VariantEditParam>,QList<VariantEditParam*>);
	PyWrapper(QListVariantVO,QList<VariantVO>,QList<VariantVO*>);
	PyWrapper(QListVariantRecordVO,QList<VariantRecordVO>,QList<VariantRecordVO*>);
	PyWrapper(QListINAsset,QList<INAsset>,QList<INAsset*>);
	PyWrapper(QListINTask,QList<INTask>,QList<INTask*>);
	PyWrapper(QListINShot,QList<INShot>,QList<INShot*>);
	PyWrapper(QListTagParam,QList<TagParam>,QList<TagParam*>);
	PyWrapper(QListINAssetStatus,QList<INAssetStatus>,QList<INAssetStatus*>);
	PyWrapper(QListRecycleInfo,QList<RecycleInfo>,QList<RecycleInfo*>);
	PyWrapper(QListINQProjectPermissionVO,QList<INQProjectPermissionVO>,QList<INQProjectPermissionVO*>);
	PyWrapper(QListINQPersonTemplateVO,QList<INQPersonTemplateVO>,QList<INQPersonTemplateVO*>);
	PyWrapper(QListIdName,QList<IdName>,QList<IdName*>);
	PyWrapper(QListDataAuthVO,QList<DataAuthVO>,QList<DataAuthVO*>);
	PyWrapper(QListDepartment,QList<Department>,QList<Department*>);
	PyWrapper(QListPerson,QList<Person>,QList<Person*>);
	PyWrapper(QListTeam,QList<Team>,QList<Team*>);
	PyWrapper(QListStorageInfo,QList<StorageInfo>,QList<StorageInfo*>);
	PyWrapper(QListProjectMilestone,QList<ProjectMilestone>,QList<ProjectMilestone*>);
	PyWrapper(QListqint,QList<qint32>,QList<qint32>);
	PyWrapper(QListTagInfoVO,QList<TagInfoVO>,QList<TagInfoVO*>);
	PyWrapper(QListTagResourceVO,QList<TagResourceVO>,QList<TagResourceVO*>);
	PyWrapper(QListINQProjectVO,QList<INQProjectVO>,QList<INQProjectVO*>);
	PyWrapper(QListSequenceFileSetVO,QList<SequenceFileSetVO>,QList<SequenceFileSetVO*>);
	PyWrapper(QListFileTaskVO,QList<FileTaskVO>,QList<FileTaskVO*>);
	PyWrapper(QListTaskFileRelationEditParam,QList<TaskFileRelationEditParam>,QList<TaskFileRelationEditParam*>);
	PyWrapper(QListPersonRoleDTO,QList<PersonRoleDTO>,QList<PersonRoleDTO*>);
	PyWrapper(QListPanelReviewVO,QList<PanelReviewVO>,QList<PanelReviewVO*>);
	PyWrapper(QListFileVO,QList<FileVO>,QList<FileVO*>);
	PyWrapper(QListTaskApproval,QList<TaskApproval>,QList<TaskApproval*>);
	PyWrapper(QListINTaskStatus,QList<INTaskStatus>,QList<INTaskStatus*>);
	PyWrapper(QListINTaskComment,QList<INTaskComment>,QList<INTaskComment*>);
	PyWrapper(QListProjectRootFolderVO,QList<ProjectRootFolderVO>,QList<ProjectRootFolderVO*>);
	PyWrapper(QListFileVersionVO,QList<FileVersionVO>,QList<FileVersionVO*>);
	PyWrapper(QListFolderVO,QList<FolderVO>,QList<FolderVO*>);
	PyWrapper(QListINQWorkFlowVO,QList<INQWorkFlowVO>,QList<INQWorkFlowVO*>);
	PyWrapper(QListINPipelineStep,QList<INPipelineStep>,QList<INPipelineStep*>);
	PyWrapper(QListWorkFlowDetlFile,QList<WorkFlowDetlFile>,QList<WorkFlowDetlFile*>);
	typedef QMap<qint32,SelectSendboxEntity> qmapqintselectsendboxentitya;
	typedef QMap<qint32,SelectSendboxEntity*> qmapqintselectsendboxentityb;
	PyWrapper(QMapqintSelectSendboxEntity, qmapqintselectsendboxentitya, qmapqintselectsendboxentityb);
	typedef QMap<qint32,INRecycleBinInfo> qmapqintinrecyclebininfoa;
	typedef QMap<qint32,INRecycleBinInfo*> qmapqintinrecyclebininfob;
	PyWrapper(QMapqintINRecycleBinInfo, qmapqintinrecyclebininfoa, qmapqintinrecyclebininfob);
	typedef QMap<qint32,QString> qmapqintqstringa;
	typedef QMap<qint32,QString> qmapqintqstringb;
	PyWrapper(QMapqintQString, qmapqintqstringa, qmapqintqstringb);
	typedef QMap<qint32,TaskFileVO> qmapqinttaskfilevoa;
	typedef QMap<qint32,TaskFileVO*> qmapqinttaskfilevob;
	PyWrapper(QMapqintTaskFileVO, qmapqinttaskfilevoa, qmapqinttaskfilevob);
	typedef QMap<qint32,QListProjectMilestone> qmapqintqlistprojectmilestonea;
	typedef QMap<qint32,QListProjectMilestone*> qmapqintqlistprojectmilestoneb;
	PyWrapper(QMapqintQListProjectMilestone, qmapqintqlistprojectmilestonea, qmapqintqlistprojectmilestoneb);
	typedef QMap<qint32,FileVO> qmapqintfilevoa;
	typedef QMap<qint32,FileVO*> qmapqintfilevob;
	PyWrapper(QMapqintFileVO, qmapqintfilevoa, qmapqintfilevob);
	typedef QMap<qint32,QListINTask> qmapqintqlistintaska;
	typedef QMap<qint32,QListINTask*> qmapqintqlistintaskb;
	PyWrapper(QMapqintQListINTask, qmapqintqlistintaska, qmapqintqlistintaskb);
	typedef QMap<QString,QListSequenceFileSetVO> qmapqstringqlistsequencefilesetvoa;
	typedef QMap<QString*,QListSequenceFileSetVO*> qmapqstringqlistsequencefilesetvob;
	PyWrapper(QMapQStringQListSequenceFileSetVO, qmapqstringqlistsequencefilesetvoa, qmapqstringqlistsequencefilesetvob);
};