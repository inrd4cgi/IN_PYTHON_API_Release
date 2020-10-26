
#include "handwriting.h"
#include "insnotification.h"
#include "insdatastructure.h"
#include "inscommonhandle.h"

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
    INSDRIVER_EXPORT MessageInfo GetLogs(QListLogInfoVO &logs, LogBusParams &logParams) {
        INSCommonRequest<QList<LogInfoVO>, LogBusParams> commonRequest(99, logParams);
        commonRequest.WaitForFinished();
        logs = commonRequest.retData;
        return commonRequest.m_return_value;
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

    //获取资产状态列表
    INSDRIVER_EXPORT qint32 GetAssetStatusList(QListINAssetStatus assetStatusList) {
        assetStatusList = INAssetStatusOperate::GetAssetStatusList();
        return 0;
    }

    //获取当前任务文件历史表
    INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QListFileVO &filehistorylist) {
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

    //获取场景列表
    INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMapqintQString &scenelist) {
        INSCommonRequestRetInt<QMap<qint32, QString>, int> commonRequest(565, projectId);
        commonRequest.WaitForFinished();
        scenelist = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetStorageInfos(QListStorageInfo& storageInfos,
        const StorageInfoSearchParam& params) {
        INSCommonRequest< QList<StorageInfo>, StorageInfoSearchParam> commonRequest(301, params);
        commonRequest.WaitForFinished();
        storageInfos = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetTagInfo(QListTagInfoVO &tagInfos, QVariantMap &searchMap) {
        INSCommonRequest<QList<TagInfoVO>, QVariantMap> commonRequest(601, searchMap);
        commonRequest.WaitForFinished();
        tagInfos = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetTagResource(QListTagResourceVO &tagResources, QVariantMap &searchMap) {
        INSCommonRequest<QList<TagResourceVO>, QVariantMap> commonRequest(602, searchMap);
        commonRequest.WaitForFinished();
        tagResources = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetProjects(QListINQProjectVO &projects, INQGetPrjBusinessFilter &prjFilter) {
        INSCommonRequest<QList<INQProjectVO>, INQGetPrjBusinessFilter> commonRequest(508, prjFilter);
        commonRequest.WaitForFinished();
        projects = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTasksByConditions(QListINTask& tasks, TaskFilterParam& params) {
        INSCommonRequest<QList<INTask>, TaskFilterParam> commonRequest(5202, params);
        commonRequest.WaitForFinished();
        tasks = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT MessageInfo
    GetTaskRelatedFiles(QMapqintTaskFileVO& taskFileVOs, qint32 &taskId, qint32 &fileType) {
        INSCommonRequest<QMap<qint32, TaskFileVO>, qint32, qint32> commonRequest(5200, taskId, fileType);
        commonRequest.WaitForFinished();
        taskFileVOs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo EditTaskFileRelatedFiles(QList<TaskFileRelationEditParam*> taskFileRelationEditParams) {
        QList<TaskFileRelationEditParam> tmp;
        for (auto item : taskFileRelationEditParams) {
            tmp.append(*item);
        }
        INSCommonRequest<qint32, QList<TaskFileRelationEditParam> > commonRequest(5201, tmp);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //获取下一个可显示的状态
    INSDRIVER_EXPORT MessageInfo GetTaskNextAvailableStatus(QListqint &taskStatus, int taskId) {
        INSCommonRequest<QList<qint32>, int> commonRequest(587, taskId);
        commonRequest.WaitForFinished();
        taskStatus = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取文件服务器placeholder列表
    INSDRIVER_EXPORT qint32 GetPlaceHolderList(QListFileVO &placeholderlist) {
        INSCommonRequest<QList<FileVO>, qint32> phRequest(351, 0);
        phRequest.WaitForFinished();
        placeholderlist = phRequest.retData;
        return phRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetTaskStatusList(QListINTaskStatus &taskStatusList) {
        taskStatusList = InTaskStatusOperate::GetTaskStatusList();
        return 0;
    }

    INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QListINTaskComment &taskComments, qint32 taskStateId) {
        INSCommonRequestRetInt<QList<INTaskComment>, qint32, qint32> commonRequest(531, taskId, taskStateId);
        commonRequest.WaitForFinished();
        taskComments = commonRequest.retData;
        return commonRequest.m_return_value;
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
    INSDRIVER_EXPORT MessageInfo
    GetWorkFlowTempls(QListINQWorkFlowVO &workFlowVOs, qint32 projectId, qint32 pipelineType) {
        INSCommonRequest<QList<INQWorkFlowVO>, qint32, qint32> commonRequest(5517, projectId, pipelineType);
        commonRequest.WaitForFinished(-1);
        workFlowVOs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
    INSDRIVER_EXPORT MessageInfo
    GetPipelineSteps(QListINPipelineStep &pipelineSteps, qint32 pipelineType, qint32 projectId) {
        INSCommonRequest<QList<INPipelineStep>, qint32, qint32> commonRequest(5112, pipelineType, projectId);
        commonRequest.WaitForFinished();
        pipelineSteps = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetProjectFiles(QListProjectRootFolderVO &projects) {
        INSCommonRequest<QList<ProjectRootFolderVO>, int> commonRequest(312, 0);
        commonRequest.WaitForFinished();
        projects = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetFolder(FolderVO &folderbase, QMapqintFileVO &files) {
        FolderSearchParam param;
        param.folderId = folderbase.folderId;
        auto ret = GetFolderByParams(folderbase, param);
        files = folderbase.files;
        return ret.code;
    }

    INSDRIVER_EXPORT qint32 GetFileHistory(FileVO &filebase, QListFileVersionVO &file_histories) {
        auto ret = GetFileFromId(filebase, filebase.fileId);
        file_histories = filebase.fileVersions.values();
        return ret;
    }
};