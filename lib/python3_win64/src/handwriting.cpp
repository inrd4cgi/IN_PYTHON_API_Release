
#include "handwriting.h"
#include "insproject.h"
#include "inspersonhandle.h"
#include "insrecycle.h"
#include "insfolder.h"
#include "insnotification.h"
#include "insasset.h"
#include "insshot.h"
#include "insrecyclebin.h"
#include "inspermission.h"
#include "insdepartmenthandle.h"
#include "insdllteamhandle.h"
#include "inscommitment.h"
#include "insdatastructure.h"

using namespace INS;

namespace INS_INTERFACE
{
    INSDRIVER_EXPORT QCoreApplication *initApp() {
        QCoreApplication *pApplication = qApp;
        if(!pApplication) {
            qint32 argc = 0;
            pApplication = new QCoreApplication(argc, nullptr);
        }
        return pApplication;
    }

    inline static QVariantMap convertTagParam(const TagParam &tag) {
        QVariantMap searchMap;
        searchMap["tagGroupId"] = tag.tagGroupId;
        searchMap["tagObjectId"] = tag.tagObjectId;
        searchMap["tagName"] = tag.tagName;
        if ( tag.resourceEntryId != 0 ) {
            searchMap["resourceEntryId"] = tag.resourceEntryId;
        }
        if ( tag.resourceId != 0 ) {
            searchMap["resourceId"] = tag.resourceId;
        }
        return searchMap;
    }


    //日志业务 通过查询参数查询日志
    INSDRIVER_EXPORT INQRespondInfo GetLogs(QListINQLogInfo &logs, INQGetLogBusParams &logParams) {
        INSCommonRequest<QList<INQLogInfo>, INQGetLogBusParams> commonRequest(99, logParams);
        commonRequest.WaitForFinished();
        logs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取文件结构模板列表
    INSDRIVER_EXPORT INQRespondInfo GetFileStructTempls(QListINFileStructTemplate &fileStructTempls) {
        INSCommonRequest<QList<INFileStructTemplate>> commonRequest(503, 0);
        commonRequest.WaitForFinished();
        fileStructTempls = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetInboxList(QListSelectInboxEntity &reInlist) {
        INSInboxList getinboxlist;
        getinboxlist.WaitForFinished();
        reInlist = getinboxlist.m_inboxList;
        return getinboxlist.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetOutboxList(QMapqintSelectSendboxEntity &reoutlist) {
        INSOutboxList getoutboxlist;
        getoutboxlist.WaitForFinished();
        reoutlist = getoutboxlist.m_sentboxList;
        return getoutboxlist.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, QListSimpleWorklog &worklogs) {
        INVariadicRequest<0, QList<SimpleWorklog>, qint32> commonRequest(700, publisherId);
        commonRequest.WaitForFinished();
        worklogs = commonRequest.retData;
        return commonRequest.m_return_value;
    }


    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, const QDateTime &startTime,
                                            const QDateTime &endTime, QListSimpleWorklog &worklogs) {
        INVariadicRequest<0, QList<SimpleWorklog>, qint32, QDateTime, QDateTime> request(701,
                                                                                         publisherId, startTime,endTime);
        request.WaitForFinished();
        worklogs = request.retData;
        return request.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetInboxNofitication(qint32 recipient_id, qint32 beg, qint32 offset,
                                                                        QListNotification &nos) {
        INVariadicRequest<0, QList<Notification>, qint32, qint32, qint32> request(761,
                                                                                  recipient_id,
                                                                                  beg, offset);
        request.WaitForFinished();
        nos = request.retData;
        return request.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetAssetsByCondition(QListINAsset& assets, const AssetFilterParam& assetFilterParam) {
    INSCommonRequest<QList<INAsset>, AssetFilterParam> commonRequest(541, assetFilterParam);
    commonRequest.WaitForFinished();
    assets = commonRequest.retData;
    return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetShotsByCondition(QListINShot& shots, const ShotFilterParam& shotFilterParam) {
    INSCommonRequest<QList<INShot>, ShotFilterParam> commonRequest(561, shotFilterParam);
    commonRequest.WaitForFinished();
    shots = commonRequest.retData;
    return commonRequest.m_return_value.code;
    }

    //创建资产
    INSDRIVER_EXPORT qint32 CreateAsset(INAsset &newasset, QListTagParam &taglist) {
    INSCreateAsset newassetobj(newasset, taglist.unWrap());
    newassetobj.WaitForFinished();
    newasset = newassetobj.m_newasset;
    return newassetobj.m_return_value;
    }

    //获取资产状态列表
    INSDRIVER_EXPORT qint32 GetAssetStatusList(QListINAssetStatus assetStatusList) {
    assetStatusList = INAssetStatusOperate::GetAssetStatusList();
    return 0;
    }

    //获取当前任务文件历史表
    INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QListINFileBase &filehistorylist) {
        QMapqintTaskFileVO taskFileVOs;
        qint32 type_id = (qint32)INS::FileTypeEnum::OUTPUT_FILE;
        auto ret= GetTaskRelatedFiles(taskFileVOs, taskId, type_id);
        for (auto& tf : taskFileVOs.unWrap()) {
            filehistorylist.value.append(tf.files);
            for (auto& sf:tf.sequenceFiles) {
                filehistorylist.value.append(sf.files);
            }
        }
        return ret.code;
    }

    //获取特定权限的人员列表
    INSDRIVER_EXPORT INQRespondInfo  GetPersonsInAction(QListtag_CIdName &persons, PersonInActionParam param) {
        INSCommonRequest<QSet<QPair<qint32, QString>>, PersonInActionParam> commonRequest(213, param);
        commonRequest.WaitForFinished();
        QSet<QPair<qint32, QString>> ret = commonRequest.retData;
        for(auto &item : ret) {
            tag_CIdName person(item.first, item.second);
            persons.value.append(person);
        }
            return commonRequest.m_return_value;
    }

    //创建镜头
    INSDRIVER_EXPORT qint32 CreateShot(INShot &newshot, QListTagParam taglist) {
        INSCreateShot newshotobj(newshot, taglist.unWrap());
        newshotobj.WaitForFinished();
        newshot = newshotobj.m_newshot;
        return newshotobj.m_return_value;
    }

    //获取场景列表
    INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMapqintQString &scenelist) {
        INSGetSceneList getscenelistobj(projectId);
        getscenelistobj.WaitForFinished();
        scenelist = getscenelistobj.m_scenelist;
        return getscenelistobj.m_return_value;
    }

    //获取回收站列表
    INSDRIVER_EXPORT qint32 GetBusRecycleBinList(QListDeleteInfo &recyclebinList) {
    INSGetBusRecycleList getlistobj(recyclebinList.unWrap());
    getlistobj.WaitForFinished();
    recyclebinList = getlistobj.m_delInfoList;
    return getlistobj.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetPermissionTemps(const qint32 &prj_id, QListINQProjectPermissionVO &temps) {
        INSGetPermissionTempS prjTemps(prj_id);
        prjTemps.WaitForFinished();
        temps = prjTemps.m_temps;
        return prjTemps.m_response;
    }

    INSDRIVER_EXPORT INQRespondInfo GetPersonPermissionTemps(QListINQPersonTemplateVO &temps, const qint32 &prjId,
    const qint32 &teamId, const qint32 &tempId) {
    INSGetPersonPermissionTemps personTemps(prjId, teamId, tempId);
    personTemps.WaitForFinished();
    temps = personTemps.m_temps;
    return personTemps.m_response;
    }

    INSDRIVER_EXPORT INQRespondInfo ModifyPersonPermissionTemp(const INQPersonTemplateVO &temp,
                                                               QListINQPersonTemplateVO &temps) {
        INSModifyPersonPermissionTemp personTemp(temp);
        personTemp.WaitForFinished();
        temps = personTemp.m_temps;
        return personTemp.m_response;
    }

    INSDRIVER_EXPORT qint32 GetJobList(QListtag_CIdName &idNames) {
        INSGetJobList jobList;
        jobList.WaitForFinished();
        idNames = jobList.idNames;
        return jobList.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetDepartments(QListDepartment &departments, qint32 filter) {
    INSGetDepartmentList getdepartments(filter);
    getdepartments.WaitForFinished();
    departments = getdepartments.m_departments;
    return getdepartments.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTeams(QListTeamInfomation &teams, const qint32 &department_id, qint32 projectId) {
    INSGetTeams getteams(department_id, projectId);
    getteams.WaitForFinished();
    teams = getteams.m_teams;
    return getteams.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetPersonList(QListPerson &personlist, const qint32 &department_id,
    const qint32 &team_id, qint32 fileter) {
    INSGetPersonList getpersonlist(department_id, team_id, fileter);
    getpersonlist.WaitForFinished();
    personlist = getpersonlist.m_personlist;
    return getpersonlist.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetStorageInfos(QListStorageInfo& storageInfos,
    const StorageInfoSearchParam& params) {
    INSCommonRequest< QList<StorageInfo>, StorageInfoSearchParam> commonRequest(301, params);
    commonRequest.WaitForFinished();
    storageInfos = commonRequest.retData;
    return commonRequest.m_return_value;
    }


    //里程碑
    INSDRIVER_EXPORT INQRespondInfo ModifyProjectMilestones(QListProjectMilestone &ms,
    int projectId) {
    INSCommonRequest<int, QPair<int, QList<ProjectMilestone>>>
    commonRequest(594, qMakePair(projectId, ms.unWrap()));

    commonRequest.WaitForFinished();
    return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetTagInfo(QListTagInfoVO &tagInfos, QVariantMap &searchMap) {
        INSCommonRequest<QList<TagInfoVO>, QVariantMap> commonRequest(601, searchMap);
        commonRequest.WaitForFinished();
        tagInfos = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetTagResource(QListTagResourceVO &tagResources, QVariantMap &searchMap) {
        INSCommonRequest<QList<TagResourceVO>, QVariantMap> commonRequest(602, searchMap);
        commonRequest.WaitForFinished();
        tagResources = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //批量修改人员的项目权限[每一项的人员id,项目id和模板id均不为空]
    INSDRIVER_EXPORT INQRespondInfo
    UpdatePersonProjectTemplates(QListINQPersonTemplateVO &personTemplates) {
        INSCommonRequest<qint32, QList<INQPersonTemplateVO>>commonRequest(211,
                                                                          personTemplates.unWrap());
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetProjects(QListINQProjectVO &projects, INQGetPrjBusinessFilter &prjFilter) {
        INSCommonRequest<QList<INQProjectVO>, INQGetPrjBusinessFilter> commonRequest(508, prjFilter);
        commonRequest.WaitForFinished();
        projects = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo GetTaskFileUsageRecord(QListFileTaskVO& fileTaskVOs, qint32 taskId, qint32 projectId, qint32 taskType) {
        INSCommonRequest<QList<FileTaskVO>, QPair<qint32,QPair<qint32,qint32>>> commonRequest(5203, qMakePair(taskId,qMakePair(projectId, taskType)));
        commonRequest.WaitForFinished();
        fileTaskVOs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTasksByConditions(QListINTask& tasks, TaskFilterParam& params) {
        INSCommonRequest<QList<INTask>, TaskFilterParam> commonRequest(5202, params);
        commonRequest.WaitForFinished();
        tasks = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT INQRespondInfo
    GetTaskRelatedFiles(QMapqintTaskFileVO& taskFileVOs, qint32 &taskId, qint32 &fileType) {
        INSCommonRequest<QMap<qint32, TaskFileVO>, QPair<qint32, qint32>>
                commonRequest(5200, qMakePair(taskId, fileType));
        commonRequest.WaitForFinished();
        taskFileVOs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT INQRespondInfo EditTaskFileRelatedFiles(QList<TaskFileRelationEditParam*> taskFileRelationEditParams) {
        QList<TaskFileRelationEditParam> tmp;
        for (auto item : taskFileRelationEditParams) {
            tmp.append(*item);
        }
        INSCommonRequest<qint32, QList<TaskFileRelationEditParam> > commonRequest(5201, tmp);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //获取下一个可显示的状态
    INSDRIVER_EXPORT INQRespondInfo GetTaskNextAvailableStatus(QListqint &taskStatus, int taskId) {
        INSCommonRequest<QList<qint32>, int> commonRequest(587, taskId);
        commonRequest.WaitForFinished();
        taskStatus = commonRequest.retData;
        return commonRequest.m_return_value;
    }


    //获取pannelView的人员 584
    INSDRIVER_EXPORT INQRespondInfo GetPannelViewPersons(QListPersonRoleDTO &personRoles, int projectId, int taskId) {
        INSCommonRequest<QList<PersonRoleDTO>, QPair<int, int>> commonRequest(584, qMakePair(projectId, taskId));
        commonRequest.WaitForFinished();
        personRoles = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取人员的会议列表 585
    INSDRIVER_EXPORT INQRespondInfo GetPannelViewList(QListPanelReviewVO &panelViews, int projectId) {
        INSCommonRequest<QList<PanelReviewVO>, int> commonRequest(585, projectId);
        commonRequest.WaitForFinished();
        panelViews = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取文件服务器placeholder列表
    INSDRIVER_EXPORT qint32 GetPlaceHolderList(QListINFileBase &placeholderlist) {
        INSCommonRequest<QList<INS::INFileBase>> phRequest(351, 0);
        phRequest.WaitForFinished();
        placeholderlist = phRequest.retData;
        return phRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetTaskStatusList(QListINTaskStatus &taskStatusList) {
        taskStatusList = InTaskStatusOperate::GetTaskStatusList();
        return 0;
    }

    INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QListINTaskComment &taskComments, qint32 taskStateId) {
        INSGetTaskComments getComment(taskId, taskStateId);
        getComment.WaitForFinished();
        taskComments = getComment.m_taskComments;
        return getComment.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTaskListPersonal(qint32 personId, QListINTask &tasklist) {
        TaskFilterParam params;
        params.assigneeId= personId;
        return GetTasksByConditions(tasklist, params);
    }

    INSDRIVER_EXPORT qint32 GetAppendTask(qint32 pId, QListINTask &tasklist) {
        TaskFilterParam params;
        params.supervisorId = pId;
        params.status = (qint32)INS::INTaskStatus::PendingApproval;
        return GetTasksByConditions(tasklist, params);
    }

    //获取workFlow列表
    INSDRIVER_EXPORT INQRespondInfo
    GetWorkFlowTempls(QListINQWorkFlowVO &workFlowVOs, qint32 projectId, qint32 pipelineType) {
    INSCommonRequest<QList<INQWorkFlowVO>, QPair<qint32, qint32>> commonRequest(5517,
                                                                                qMakePair(projectId, pipelineType));
    commonRequest.WaitForFinished(-1);
    workFlowVOs = commonRequest.retData;
    return commonRequest.m_return_value;
    }

    //根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
    INSDRIVER_EXPORT INQRespondInfo
    GetPipelineSteps(QListINPipelineStep &pipelineSteps, qint32 pipelineType, qint32 projectId) {
    INSCommonRequest<QList<INPipelineStep>, QPair<qint32, qint32>> commonRequest(5112, qMakePair(pipelineType,
                                                                                                 projectId));
    commonRequest.WaitForFinished();
    pipelineSteps = commonRequest.retData;
    return commonRequest.m_return_value;
    }

    //批量修改pipeline step 的 surpervisor
    INSDRIVER_EXPORT INQRespondInfo updatePipelineStepSupervisor(qint32 personId, QListqint pipelineSteps) {
    QPair<int, QList<qint32>> param;
    param = qMakePair(personId, pipelineSteps.unWrap());
    INSCommonRequest<qint32, QPair<int, QList<qint32>>> commonRequest(5114, param);
    commonRequest.WaitForFinished();
    return commonRequest.m_return_value;
    }

    //批量修改pipeline step 的 coordinator
    INSDRIVER_EXPORT INQRespondInfo updatePipelineStepCoordinator(qint32 personId, QListqint pipelineSteps) {
    QPair<int, QList<qint32>> param;
    param = qMakePair(personId, pipelineSteps.unWrap());
    INSCommonRequest<qint32, QPair<int, QList<qint32>>> commonRequest(5115, param);
    commonRequest.WaitForFinished();
    return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetServerRootDirs(QListINFileServerRoot &root_dirs) {
    INSGetRootDirs getrootdirs;
    getrootdirs.WaitForFinished();
    root_dirs = getrootdirs.m_root_dirs;
    return getrootdirs.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetProjectFiles(QListINProjectFile &projects) {
    INSCommonRequest<QList<INProjectFile>, int> commonRequest(312, 0);
    commonRequest.WaitForFinished();
    projects = commonRequest.retData;
    return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetFolder(INFolderBase &folderbase, QMapqintINFileBase &files) {
    FolderParam param;
    param.folderId = folderbase.id;
    auto ret = GetFolderByParams(folderbase, param);
    files = folderbase.files;
    return ret.code;
    }

    INSDRIVER_EXPORT qint32 GetFileHistory(INFileBase &filebase, QListINFileHistory &file_histories) {
    auto ret = GetFileFromId(filebase, filebase.id);
    file_histories = filebase.version_list;
    return ret;
    }

    INSDRIVER_EXPORT qint32 DeleteRecycles(const qint32 &project_id, QListqint &recycles, qint32 &code, qint32 &amount_files) {
        INSDeleteRecycles delete_recycles(project_id, recycles.unWrap());
        delete_recycles.WaitForFinished();
        code = delete_recycles.m_code;
        amount_files = delete_recycles.m_amount_files;
        return delete_recycles.m_return_value;
    }

    INSDRIVER_EXPORT qint32 RenameFolder(INFolderBase &folder, QMapqintINFileBase &files) {
    INSRenameFolder rename_folder(folder);
    rename_folder.WaitForFinished();
    folder = rename_folder.m_folder;
    files = rename_folder.m_files;
    return rename_folder.m_return_value;
    }

    INSDRIVER_EXPORT qint32 SendFilesToRecycleBin(QListINFileBase &files) {
    INSSendFilesToRecycleBin send_file_to_recyclebin(files.unWrap());
    send_file_to_recyclebin.WaitForFinished();
    return send_file_to_recyclebin.m_return_value;
    }

    INSDRIVER_EXPORT qint32 SendFoldersToRecycleBin(QListINFolderBase &folders) {
    INSSendFoldersToRecycleBin send_folders_to_recyclebin(folders.unWrap());
    send_folders_to_recyclebin.WaitForFinished();
    return send_folders_to_recyclebin.m_return_value;
    }

    INSDRIVER_EXPORT qint32 RestoreRecycleBin(const qint32 &project_id, QListqint &items_id, QListINFileBase &files, qint32 &code) {
        INSRestoreRecycleBin restore_recycle_bin(project_id, items_id.unWrap());
        restore_recycle_bin.WaitForFinished();
        files = restore_recycle_bin.m_files;
        code = restore_recycle_bin.m_code;
        return restore_recycle_bin.m_return_value;
    }

    INSDRIVER_EXPORT qint32 ReplaceFiles(const qint32 &code, const qint32 &exit, QListINFileBase &files) {
        INSReplaceFiles replace_file(code, exit, files.unWrap());
        replace_file.WaitForFinished();
        return replace_file.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetRecycleBin(const qint32 &project_id, QMapqintINRecycleBinInfo &recycle_bins) {
        INSGetRecycleBin get_recycle_bins(project_id);
        get_recycle_bins.WaitForFinished();
        recycle_bins = get_recycle_bins.m_recycle_bins;
        return get_recycle_bins.m_return_value;
    }
};