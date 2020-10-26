#pragma once

#include "insdriver_global.h"
#include "insdriverworkflowinterface.h"
#include "insdriverassetshotinterface.h"
#include "insdriverprojectinterface.h"
#include "insdriverpermissioninterface.h"
#include "insdrivertaskinterface.h"
#include "insdrivertransinterface.h"
#include "insdriverpersoninterface.h"
#include "PyContainerWapper.h"
#include "insdatastructure.h"
#include <QCoreApplication>
#include <QtWidgets/QApplication>
//文件格式固定为：LF utf-8 bom。不得修改
#include "InTaskStatus.h"
#include "insfiletransfer.h"
#include "instasktransfer.h"
using namespace INS;
namespace INI
{    INSDRIVER_EXPORT QString jsonRequest(int serviceId, QString &queryParam);

    INSDRIVER_EXPORT MessageInfo GetClientUpdateServerPath(QString& path);


	INSDRIVER_EXPORT void SetNotificationCallback(std::function<void(const QByteArray&)> p_callback);



	INSDRIVER_EXPORT qint32 GetAvatarInfo(Avatar& avatar);

	INSDRIVER_EXPORT qint32 InsertAvatarInfo(const Avatar Iavatar);

	INSDRIVER_EXPORT qint32 UpdateAvatarInfo(const Avatar Uavatar);

	INSDRIVER_EXPORT qint32 GetTaskInfoFromProID(ProjectTaskInfo& pti);

	INSDRIVER_EXPORT qint32 GetTaskStatusFromProID(ProjectTaskInfo& pti);

	INSDRIVER_EXPORT qint32 GetTeamInfoFromProID(ProjectTaskInfo& pti);

	INSDRIVER_EXPORT qint32 GetMenFormProID(ProjectTaskInfo& pti);


	extern "C" INSDRIVER_EXPORT bool ConnectToServer(const QString&, const qint32& = 0);

	extern "C" INSDRIVER_EXPORT void SetReconnectAndReLoginEnable(bool bEnable, int secNum);

	extern "C" INSDRIVER_EXPORT void SetAppServerNetworkStatusSig(std::function<void(bool)> callbackSig);

    extern "C" INSDRIVER_EXPORT qint32 Login(const QString& username, const QString& password, bool &normalRole, const QString& type = "JIMC");

	extern "C" INSDRIVER_EXPORT qint32 ActivateAccount(const QString& username, const QString& password);

	extern "C" INSDRIVER_EXPORT qint32 GetSysVersion(QString& version);

    INSDRIVER_EXPORT qint32 Logout();



	INSDRIVER_EXPORT qint32 GetInMsg(const qint32 msgID, MailobjEntity& remsg);

	INSDRIVER_EXPORT qint32 GetSentMsg(const qint32 msgID, MailobjEntity& remsg);

	INSDRIVER_EXPORT qint32 SentMsg(const MailobjEntity& mail);

	INSDRIVER_EXPORT qint32 DeleteMsg(const MailListEntity& maillist);


	INSDRIVER_EXPORT qint32 CreateWorklog(SimpleWorklog& worklog);

	INSDRIVER_EXPORT qint32 UpdateWorklog(SimpleWorklog& worklog);

	

	INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id, Notification& no);

	INSDRIVER_EXPORT qint32 SendUserNofitication(Notification& no);


	INSDRIVER_EXPORT MessageInfo CreateHolidayTemplate(INQHolidayTemplate& holidayTemplate);

	INSDRIVER_EXPORT MessageInfo EditHolidayTemplate(INQHolidayTemplate& holidayTemplate);



	INSDRIVER_EXPORT MessageInfo DeleteHolidayTemplate(qint32 templateId);
    INSDRIVER_EXPORT QCoreApplication *initApp();

    INSDRIVER_EXPORT MessageInfo GetLogs(QListLogInfoVO& logs, LogBusParams& logParams);

    INSDRIVER_EXPORT qint32 GetAssetsByCondition(QListINAsset& assets,const AssetFilterParam& assetFilterParam);

    INSDRIVER_EXPORT qint32 GetShotsByCondition(QListINShot& shots, const ShotFilterParam& shotFilterParam);

    INSDRIVER_EXPORT qint32 GetAssetStatusList(QListINAssetStatus);

    INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QListFileVO& filehistorylist);

    INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMapqintQString& scenelist);


    INSDRIVER_EXPORT MessageInfo GetStorageInfos(QListStorageInfo& storageInfos, const StorageInfoSearchParam& params);

    INSDRIVER_EXPORT MessageInfo GetTagInfo(QListTagInfoVO &tagInfos, QVariantMap &searchParam);

    INSDRIVER_EXPORT MessageInfo GetTagResource(QListTagResourceVO& tagResources, QVariantMap &searchParam);

    INSDRIVER_EXPORT MessageInfo GetProjects(QListINQProjectVO& projects, INQGetPrjBusinessFilter &filter);


    INSDRIVER_EXPORT qint32 GetTasksByConditions(QListINTask& tasks, TaskFilterParam& params);

    INSDRIVER_EXPORT MessageInfo GetTaskRelatedFiles(QMapqintTaskFileVO& taskFileVOs, qint32 &taskId, qint32 &fileType);

    //INSDRIVER_EXPORT MessageInfo EditTaskFileRelatedFiles(QListTaskFileRelationEditParam& taskFileRelationEditParams);

    INSDRIVER_EXPORT MessageInfo EditTaskFileRelatedFiles(QList<TaskFileRelationEditParam*> taskFileRelationEditParams);

    INSDRIVER_EXPORT MessageInfo GetTaskNextAvailableStatus(QListqint& taskStatus, int taskId);

    INSDRIVER_EXPORT qint32 GetPlaceHolderList(QListFileVO& placeholderlist);

    INSDRIVER_EXPORT qint32 GetTaskStatusList(QListINTaskStatus &);

    INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QListINTaskComment& taskComments, qint32 taskStateId = 0);

    INSDRIVER_EXPORT qint32 GetTaskListPersonal(qint32 personId, QListINTask& tasklist);

    INSDRIVER_EXPORT qint32 GetAppendTask(qint32 pId, QListINTask& tasklist);

    //获取项目文件列表[projects]。
    //返回说明：1==获取成功;0==获取失败。
    INSDRIVER_EXPORT qint32 GetProjectFiles(QListProjectRootFolderVO& projects);

    //获取一个指定id的文件夹。要求[folderbase]中有项目id和文件夹id。[files]为文件夹下的文件列表。
    //返回说明：1==创建成功;0==权限不足;
    INSDRIVER_EXPORT qint32 GetFolder(FolderVO &folderbase, QMapqintFileVO &files);

    //获取指定文件的历史版本列表。要求[filebase]中有文件id
    //返回说明：1==获取成功;0==获取失败;
    INSDRIVER_EXPORT qint32 GetFileHistory(FileVO &filebase, QListFileVersionVO &file_histories);

    INSDRIVER_EXPORT MessageInfo GetWorkFlowTempls(QListINQWorkFlowVO& workFlowVOs, qint32 projectId, qint32 pipelineType);

    INSDRIVER_EXPORT MessageInfo GetPipelineSteps(QListINPipelineStep& pipelineSteps, qint32 pipelineType = 0, qint32 projectId = 0);


	INSDRIVER_EXPORT MessageInfo GetAssetOrShotReferenceFiles(QMap<qint32,FileVO>& files, qint32 objectId, bool isAsset = true);


	INSDRIVER_EXPORT MessageInfo EditVariant(qint32 assetId, const VariantEditParam &variantEditParam);

	INSDRIVER_EXPORT MessageInfo CreateVariant(qint32 assetId, const VariantEditParam &variantEditParam);

	INSDRIVER_EXPORT MessageInfo DeleteVariantById(qint32 variantId);








    INSDRIVER_EXPORT MessageInfo EditAsset(INAsset& easset);

    INSDRIVER_EXPORT MessageInfo DeleteAsset(int assetId);


	INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState);

	INSDRIVER_EXPORT MessageInfo GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param);

    INSDRIVER_EXPORT qint32 GetAssetInfo(INAsset& assetinfo);


    INSDRIVER_EXPORT MessageInfo EditShot(INShot& eshot);

    INSDRIVER_EXPORT MessageInfo DeleteShot(int shotId);


	INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int& sceneId);

	INSDRIVER_EXPORT qint32 GetShotInfo(INShot& shotinfo);


    INSDRIVER_EXPORT qint32 DeleteObjectInRecordBin(qint32 recordId);

    INSDRIVER_EXPORT qint32 RestoreObjectInRecordBin(qint32 recordId);

	INSDRIVER_EXPORT MessageInfo GetOneselfPermissionInfo(PersonPermissionVO& ret);

	INSDRIVER_EXPORT MessageInfo GetPermissionTemp(INQProjectPermissionVO& temp);


	INSDRIVER_EXPORT MessageInfo CreatePermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT MessageInfo ModifyPermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT MessageInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId);



	INSDRIVER_EXPORT MessageInfo GetOneSelfAdminTemp(INQAdministrationPermissionVO& temp);



    /*!
     * \brief 更新可看的资产和镜头
     * \details
     * \param[in]roleId 模板id。
     * \param[in]assets 模板资产列表。
     * \param[in]DataAuthVO.roleId 模板id,必填。
     * \param[in]DataAuthVO.actionId 权限id,必填。
     * \param[in]DataAuthVO.resourceId 资产或镜头id,必填。
     * \return
     */



    /*!
     * \brief 查询当前人员是否审批类型，如果是，并获取审批类型
     * \details
     * \param[out]approvalType 审批人员的类型，0为普通人员，1为普通批员，2为默认审批员
     * \param[in]personId 被查询的人员id
     * \param[in]prjId 查询的项目id。0表示所有项目
     * \return
     */

	INSDRIVER_EXPORT MessageInfo GetPersonApprovalInfo(qint32& approvalType, qint32 personId, qint32 prjId = 0);



	extern "C" INSDRIVER_EXPORT qint32 CreateAdmin(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 RemovePerson(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 DeletePerson(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 ResetPassword(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 CreateTeam(Team& teaminfo);

	extern "C" INSDRIVER_EXPORT qint32 DeleteTeam(const qint32& teamid);

	extern "C" INSDRIVER_EXPORT qint32 GetTeam(Team& team);

	extern "C" INSDRIVER_EXPORT qint32 DeleteDepartment(const qint32& departmentid);

	extern "C" INSDRIVER_EXPORT qint32 CreateDepartment(Department& department);




	extern "C" INSDRIVER_EXPORT qint32 ModifyPerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 GetPerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 CreatePerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 ModifyTeam(Team& team);

	extern "C" INSDRIVER_EXPORT qint32 ModifyDepartment(Department& department);

	extern "C" INSDRIVER_EXPORT qint32 GetDepartment(Department& department);

	extern "C" INSDRIVER_EXPORT qint32 GetOneself(Person& person);

	/*!
	 * \brief 获取文件服务器所有的存储信息
	 * \details
	 * \param[out] storageInfos 文件服务器信息列表
	 * \param[int] params 查询参数,projectId为0表示查询所有,否则表示查询项目的
	 * \return
	 */




	INSDRIVER_EXPORT MessageInfo InsertProjectMilestone(ProjectMilestone& ret);


	INSDRIVER_EXPORT MessageInfo UpdateProjectMilestone(ProjectMilestone& ret);

	INSDRIVER_EXPORT MessageInfo DeleteProjectMilestone(int milestoneId);




	INSDRIVER_EXPORT MessageInfo MakeTag(int& tagId, const TagParam& tagParam);

	INSDRIVER_EXPORT MessageInfo RemoveTag(const TagParam& tagParam);



	INSDRIVER_EXPORT MessageInfo AddPersonToProject(INQPersonTemplateVO& personTemplate);

	INSDRIVER_EXPORT MessageInfo RemovePersonFromProject(qint32 projectId, qint32 personId);

	INSDRIVER_EXPORT MessageInfo CreateProject(INQProjectVO& project);

	INSDRIVER_EXPORT MessageInfo EditProject(INQProjectVO& project);

	INSDRIVER_EXPORT MessageInfo GetProject(INQProjectVO& project);


	INSDRIVER_EXPORT QString GetProjectStateString(ProjectStatusEnum prjState);

	INSDRIVER_EXPORT MessageInfo DeleteProject(qint32 projectId);

    INSDRIVER_EXPORT MessageInfo getProjectStatisticsData(ProjectStatisticsData &projectStatisticsData, qint32 type, qint32 projectId);

	INSDRIVER_EXPORT MessageInfo SaveTaskSequenceFile(const SequenceFileParam& param);

	INSDRIVER_EXPORT MessageInfo GetAffectedTaskInfo(AffectedObjectInfoVO& affectedInfos, qint32 taskId, const QDateTime& dueTime);




	/*!
	 * \brief 编辑任务关联文件的接口
	 * \details
	 * \param taskFileRelationEditParams
	 * 若是添加模板文件,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path ={ "/proj1/aa/bb","a.txt"} fileId 为模板文件的id
	 * 若是添加路径,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path={"/proj1/aa/bb",""}
	 * 若是删除路径，必填字段为：fileType=FileTypeEnum::OUTPUT_FILE，folderId=路径id
	 * \return
	 */





	INSDRIVER_EXPORT MessageInfo CreatePannelReviewOrModify(PanelReviewVO& panelView);


	INSDRIVER_EXPORT qint32 CreateTask(INTask& newtask);

    INSDRIVER_EXPORT MessageInfo EditTask(INTask& etask);


    /*!
     * \brief approveTaskApprovalStatus 执行任务审批操作
     * \param taskId 任务id
     * \param direction 审批行为。[0] : send to prev \n
     *                          [1] : send to next
     * \return
     */
    INSDRIVER_EXPORT MessageInfo approveTaskApprovalStatus(qint32 taskId, qint32 direction);

    /*!
     * \brief setTaskApprovalToUrgent 设置任务审批加急，将一个具有审批权限的人员指定为加急审批此任务的人。
     * \param taskId 任务id
     * \param approverID 审批人id
     * \return
     */
    INSDRIVER_EXPORT MessageInfo setTaskApprovalToUrgent(qint32 taskId, qint32 approverID);

    /*!
     * \brief getTaskApprovalList 根据任务ID获取任务审批流程。
     * \param taskId
     * \param approvalList
     * \return
     */


	INSDRIVER_EXPORT QString GetTaskStateString(INTaskStatus taskState);

    /*!
     * \brief UpdateTaskStatus 改变任务状态
     * \param taskId
     * \param status
     * \param isRequiredFirstApproved 是否需要重新开始审批任务
     * \return
     */
    INSDRIVER_EXPORT MessageInfo UpdateTaskStatus(qint32 taskId, qint32 status, bool isRequiredFirstApproved = false);

	INSDRIVER_EXPORT qint32 FindTaskStatus(TaskDurationProgress& progress, qint32 taskId);


	INSDRIVER_EXPORT qint32 SubmitComment(INTaskComment& taskComment);



	INSDRIVER_EXPORT qint32 GetTaskFromID(qint32 taskId, INTask& task);


	INSDRIVER_EXPORT qint32 DeleteTask(qint32 taskId);

	INSDRIVER_EXPORT qint32 GetFileFromId(FileVO& fileBase, qint32 fileId);

	INSDRIVER_EXPORT qint32 GetFilePathFromId(const qint32 fileId, QString& filePath);


    INSDRIVER_EXPORT MessageInfo	GetFolderByParams(FolderVO &folderbase, FolderSearchParam &param);



	extern "C" INSDRIVER_EXPORT qint32 ModifyFileStatus(FileVO &filebase);


	extern "C" INSDRIVER_EXPORT qint32 ComfirmDelete(const qint32& ok, const qint32& code);

	extern "C" INSDRIVER_EXPORT qint32 CreateFolder(FolderVO & folder);

	INSDRIVER_EXPORT MessageInfo CreateFolderOrEdit(FolderVO & folder);








	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 从文件服务器下载文件到本地
	 * \details
	 * \param[in] file 文件的id必填。其余可不填。
	 * \param[in] rootDir 下载的文件的文件夹路径
	 * \return INSDownload指针对象，通过该对象调用start函数启动下载业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSDownLoad* DownLoad(const FileVO& file, const QString& rootDir);


	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传文件到文件服务器
	 * \details
	 * \param[in] file 存放文件信息的类。\n
	 *            - 文件并非初次上传时，需要填写文件id。
	 *            - file中的 name 是必填项。
	 *            - 其他参数看rootDir和AbsolutePath的填写情况。
	 * \param[in] rootDir 存放文件目录的根路径。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 - 为空 参数rootDir必填，参数file的filename和directory字段必填。
	 - 不为空 file对象只需要folderID和directory选一个填写就好
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUpLoad* UpLoad(const FileVO& file, const QString& rootDir, const QString& AbsolutePath = QString());

		/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传小文件到文件服务器，小文件的定义是文件大小不超过32MB的文件。
	 * \details
	 * \param[in] filename 需要记录在应用服务器的文件名。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUploadTinyFile指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadTinyFile* UpLoadTinyFile(const QString &filename, const QString& absolutePath);

	/*!
	 * \brief 上传文件到文件服务器
	 * \details
	 * \param[in] file 存放文件信息的类。文件并非初次上传时，需要填写文件id。其他参数看rootDir和AbsolutePath的填写情况。
	 * \param[in] rootDir 存放文件目录的根路径。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 - 为空 参数rootDir必填，参数file的filename和directory字段必填。
	 - 不为空 file对象只需要folderID和directory选一个填写就好
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSCheckIn* CheckIn(const FileVO& file, const QString& rootDir, const QString& AbsolutePath = QString());

	extern "C" INSDRIVER_EXPORT INSCheckOut* CheckOut(const FileVO& file, const QString& rootDir);

    /*!
     * \ingroup businessAPI_fileModule
     * \brief 上传资源文件的参考文件
     * \details
     * \param[in] sourceId 资产ID或者镜头ID
     * \param[in] AbsolutePath 被上传的文件的绝对路径。
     * \param[in] isAssetFlag 资产标志位，传入的sourceId是资产则置位true,镜头置位false。
     * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
     */

    extern "C" INSDRIVER_EXPORT INSUpLoadSourceReferenceFile *UploadSourceReferenceFile(qint32 sourceId,const QString &absolutePath,bool isAssetFlag);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传PlaceHolders文件
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadPlaceHolders *UploadPlaceHolders(const FileVO &file, const QString &AbsolutePath);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 更新用户头像,需要用户头像文件信息和路径信息。
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUpLoadUserAvatar *UploadUserAvatar(const FileVO &file, const QString &AbsolutePath);

	/*!
	 * \brief 上传评论文件的函数。所有参数都要正确填写
	 * \details
	 * \param[in] commentData 评论文件的数据
	 * \return 返回INSUploadCommentFile对象,调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadCommentFile *UploadCommentFile(const INSDataUploadComment &commentData);

	/*!
	 * \brief 上传required file的函数
	 * \details
	 * \param[in] filename 为该文件被记录的名字
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadRequiredFile对象，调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadRequiredFile *UploadRequiredFile(const QString &filename, qint32 taskId, const QString& absolutePath);

	/*!
	 * \brief 上传reference file的函数
	 * \details
	 * \param[in] filename 为该文件被记录的名字
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadReferenceFile对象，调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadReferenceFile *UploadReferenceFile(const QString &filename, qint32 taskId, const QString& absolutePath);

	/*!
	 * \brief 上传output file的函数
	 * \details
	 * \param[in] fileName 为需要记录的文件名
	 * \param[in] strDirectory 为相对项目的相对路径，需要确保路径在服务器存在，否则会报错
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadOutputFile对象，调用start启动上传业务，业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadOutputFile *UploadOutputFile(const QString &filename, const QString& strDirectory, qint32 taskId, const QString& absolutePath);

	/*! 
	 * \brief 上传library文件的函数
	 * \details 
	 * \param[in] filename 需要记录在应用服务器的文件名 
	 * \param[in] strDirectory 相对项目的相对路径，文件的存放路径，如果路径不存在，则会自动在应用服务器创建改路径。
	 * \return 返回INSUploadOutputFile对象，调用start启动上传业务，业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadLibraryFile *UploadLibraryFile(const QString &filename, const QString& strDirectory, const QString& absolutePath);




	INSDRIVER_EXPORT MessageInfo CreateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT MessageInfo GetWorkFlowTempl(INQWorkFlowVO& workFlowVO);


	INSDRIVER_EXPORT MessageInfo UpdateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT MessageInfo DeleteWorkFlowTempl(qint32 workFlowId);

	INSDRIVER_EXPORT MessageInfo CreatePrivateUseWorkFlow(INQWorkFlowVO& workFlowVO, qint32 workFlowId);

	INSDRIVER_EXPORT MessageInfo GetWorkFlowInstance(TaskWorkflow& taskWorkflow, qint32 objectID, qint32 objectType);

	INSDRIVER_EXPORT MessageInfo UpdateWorkFlowInstance(TaskWorkflow & taskWorkflow);

    INSDRIVER_EXPORT MessageInfo CreatePipelineStep(INPipelineStep& pipelineStep);

    INSDRIVER_EXPORT MessageInfo UpdatePipelineStep(INPipelineStep& pipelineStep);


	INSDRIVER_EXPORT MessageInfo DeletePipelineStep(qint32 pipelineId);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief updatePipelineStepSupervisor 批量修改PipelineStep的Supervisor
	 * \param personId Supervisor人员ID,必填。
	 * \param pipelineStep 被修改的PipelineStep ID 列表
	 * \return 业务操作结果
	 */

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief updatePipelineStepCoordinator 批量修改PipelineStep的Coordinator
	 * \param personId Coordinator人员ID,必填。
	 * \param pipelineStep 被修改的PipelineStep ID 列表
	 * \return 业务操作结果
	 */




};