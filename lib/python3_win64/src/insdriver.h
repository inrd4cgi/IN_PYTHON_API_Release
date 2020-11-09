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
#include "insdriver_global.h"
#include "insdatastructure.h"
#include "InTaskStatus.h"
#include "insfiletransfer.h"
#include "instasktransfer.h"
using namespace INS;
namespace INI
{    INSDRIVER_EXPORT INQRespondInfo GetClientUpdateServerPath(QString& path);


	INSDRIVER_EXPORT void SetNotificationCallback(std::function<void(const QByteArray&)> p_callback);



	/*文件结构模板篇*/
	INSDRIVER_EXPORT INQRespondInfo CreateFileStructTempl(INFileStructTemplate& fileStructTempl);

	INSDRIVER_EXPORT INQRespondInfo GetFileStructTempl(INFileStructTemplate& fileStructTempl);


	INSDRIVER_EXPORT INQRespondInfo UpdateFileStructTempl(INFileStructTemplate& fileStructTempl);


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


	INSDRIVER_EXPORT INQRespondInfo CreateHolidayTemplate(INQHolidayTemplate& holidayTemplate);

	INSDRIVER_EXPORT INQRespondInfo EditHolidayTemplate(INQHolidayTemplate& holidayTemplate);



	INSDRIVER_EXPORT INQRespondInfo DeleteHolidayTemplate(qint32 templateId);
    INSDRIVER_EXPORT QCoreApplication *initApp();

    INSDRIVER_EXPORT INQRespondInfo GetLogs(QListINQLogInfo& logs, INQGetLogBusParams& logParams);

    INSDRIVER_EXPORT INQRespondInfo GetFileStructTempls(QListINFileStructTemplate& fileStructTempls);

    INSDRIVER_EXPORT qint32 GetInboxList(QListSelectInboxEntity& reInlist);

    INSDRIVER_EXPORT qint32 GetOutboxList(QMapqintSelectSendboxEntity& reoutlist);

    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, QListSimpleWorklog& worklogs);

    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, const QDateTime& startTime, const QDateTime& endTime, QListSimpleWorklog& worklogs);

    INSDRIVER_EXPORT qint32 GetInboxNofitication(qint32 recipient_id, qint32 beg, qint32 offset, QListNotification& nos);



    INSDRIVER_EXPORT qint32 GetAssetsByCondition(QListINAsset& assets,const AssetFilterParam& assetFilterParam);

    INSDRIVER_EXPORT qint32 GetShotsByCondition(QListINShot& shots, const ShotFilterParam& shotFilterParam);

    INSDRIVER_EXPORT qint32 CreateAsset(INAsset& newasset, QListTagParam &taglist);

    INSDRIVER_EXPORT qint32 GetAssetStatusList(QListINAssetStatus);

    INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QListINFileBase& filehistorylist);

    INSDRIVER_EXPORT qint32 CreateShot(INShot& newshot, QListTagParam taglist);

    INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMapqintQString& scenelist);

    INSDRIVER_EXPORT qint32 GetBusRecycleBinList(QListDeleteInfo &recyclebinList);



    INSDRIVER_EXPORT INQRespondInfo GetPermissionTemps(const qint32& prj_id, QListINQProjectPermissionVO& temps);

    INSDRIVER_EXPORT INQRespondInfo GetPersonPermissionTemps(QListINQPersonTemplateVO& temps, const qint32& prjId = 0, const qint32& teamId = 0, const qint32& tempId = 0);

    INSDRIVER_EXPORT INQRespondInfo ModifyPersonPermissionTemp(const INQPersonTemplateVO& temp, QListINQPersonTemplateVO& temps);



    INSDRIVER_EXPORT qint32 GetJobList(QListtag_CIdName& idNames);

    INSDRIVER_EXPORT qint32 GetDepartments(QListDepartment& departments, qint32 filter = 0);

    INSDRIVER_EXPORT qint32 GetPersonList(QListPerson& personlist, const qint32& department_id = 0, const qint32& team_id = 0, qint32 fileter = 0);

    INSDRIVER_EXPORT qint32 GetTeams(QListTeamInfomation& teams, const qint32& department_id = 0, qint32 projectId = 0);




    INSDRIVER_EXPORT INQRespondInfo GetStorageInfos(QListStorageInfo& storageInfos, const StorageInfoSearchParam& params);

    INSDRIVER_EXPORT INQRespondInfo ModifyProjectMilestones(QListProjectMilestone& ms, int projectId);

    INSDRIVER_EXPORT INQRespondInfo GetTagInfo(QListTagInfoVO &tagInfos, QVariantMap &searchParam);

    INSDRIVER_EXPORT INQRespondInfo GetTagResource(QListTagResourceVO& tagResources, QVariantMap &searchParam);

    INSDRIVER_EXPORT INQRespondInfo UpdatePersonProjectTemplates(QListINQPersonTemplateVO& personTemplates);

    INSDRIVER_EXPORT INQRespondInfo GetProjects(QListINQProjectVO& projects, INQGetPrjBusinessFilter &filter);



    INSDRIVER_EXPORT INQRespondInfo GetTaskFileUsageRecord(QListFileTaskVO& fileTaskVOs, qint32 taskId, qint32 projectId, qint32 taskType);

    INSDRIVER_EXPORT qint32 GetTasksByConditions(QListINTask& tasks, TaskFilterParam& params);

    INSDRIVER_EXPORT INQRespondInfo GetTaskRelatedFiles(QMapqintTaskFileVO& taskFileVOs, qint32 &taskId, qint32 &fileType);

    //INSDRIVER_EXPORT INQRespondInfo EditTaskFileRelatedFiles(QListTaskFileRelationEditParam& taskFileRelationEditParams);

    INSDRIVER_EXPORT INQRespondInfo EditTaskFileRelatedFiles(QList<TaskFileRelationEditParam*> taskFileRelationEditParams);

    INSDRIVER_EXPORT INQRespondInfo GetTaskNextAvailableStatus(QListqint& taskStatus, int taskId);

    INSDRIVER_EXPORT INQRespondInfo GetPannelViewPersons(QListPersonRoleDTO& personRoles, int projectId, int taskId);

    INSDRIVER_EXPORT INQRespondInfo GetPannelViewList(QListPanelReviewVO& panelViews, int projectId = 0);

    INSDRIVER_EXPORT qint32 GetPlaceHolderList(QListINFileBase& placeholderlist);

    INSDRIVER_EXPORT qint32 GetTaskStatusList(QListINTaskStatus &);

    INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QListINTaskComment& taskComments, qint32 taskStateId = 0);

    INSDRIVER_EXPORT qint32 GetTaskListPersonal(qint32 personId, QListINTask& tasklist);

    INSDRIVER_EXPORT qint32 GetAppendTask(qint32 pId, QListINTask& tasklist);

    //handwriting here
    //获取文件服务器上存放项目的根路径列表[server_roots]。
    //返回说明：1==获取成功;0==权限不足,-1==数据出错;
    INSDRIVER_EXPORT qint32 GetServerRootDirs(QListINFileServerRoot& root_dirs);

    //获取项目文件列表[projects]。
    //返回说明：1==获取成功;0==获取失败。
    INSDRIVER_EXPORT qint32 GetProjectFiles(QListINProjectFile& projects);

    //获取一个指定id的文件夹。要求[folderbase]中有项目id和文件夹id。[files]为文件夹下的文件列表。
    //返回说明：1==创建成功;0==权限不足;
    INSDRIVER_EXPORT qint32 GetFolder(INFolderBase &folderbase, QMapqintINFileBase &files);

    //获取指定文件的历史版本列表。要求[filebase]中有文件id
    //返回说明：1==获取成功;0==获取失败;
    INSDRIVER_EXPORT qint32 GetFileHistory(INFileBase &filebase, QListINFileHistory &file_histories);

    //删除回收站中的条目。要指明项目id[project_id]和回收站条目id列表[recycles]。参数[code]为业务id,执行成功时，会返回一个值。
    //返回说明：1==请求删除成功,这里还需要进一步确认,调用函数ComfirmDelete(),参数为对应的[code];0==没有权限;-1==数据出错。
    INSDRIVER_EXPORT qint32 DeleteRecycles(const qint32& project_id, QListqint& recycles, qint32& code, qint32& amount_files);

    //修改文件夹[folder]名。要求[folder]有项目id，文件夹id，新的文件夹名。[files]为文件列表，用以接收文件夹返回的文件。
    //返回说明：1==修改成功;0==没有权限;-1==数据出错。
    INSDRIVER_EXPORT qint32 RenameFolder(INFolderBase & folder, QMapqintINFileBase &files);

    //将文件[files]放入回收站。可以是多个，但要求是在同一个文件夹下。[files]中条目要求有文件id，文件夹id，项目id。
    //返回说明：1==成功放入回收站;0==权限不足;-1==数据出错。
    INSDRIVER_EXPORT qint32 SendFilesToRecycleBin(QListINFileBase& files);

    //将文件夹[folders]放入回收站。可以是多个，但要求是在同一个父级文件夹下。[folders]中条目要求有文件夹id，项目id。
    //返回说明：1==成功放入回收站;0==权限不足;-1==数据出错。
    INSDRIVER_EXPORT qint32 SendFoldersToRecycleBin(QListINFolderBase& folders);

    //从项目[project_id]的回收站中恢复回收站条目[items_id]。[files]用来接收冲突文件。当恢复后文件有冲突时，[code]会有一个值
    //此时[files]列出所有冲突的文件。此时客户端需要调用ReplaceFiles函数来决定跳过的文件。
    //返回说明：1==恢复成功;0==权限不足;-1==恢复的文件有冲突，需要客户端做replace/skip的选择;-2==数据出错。
    INSDRIVER_EXPORT qint32 RestoreRecycleBin(const qint32& project_id, QListqint& items_id, QListINFileBase& files, qint32& code);

    //回复服务器要替换的文件列表.[code]为调用RestoreRecycleBin时产生的业务关联码。[exit]为是否放弃恢复。
    //[files]为要replace掉的文件,即删除掉当前文件，选用回收站中的文件。
    //返回说明：1==恢复成功;0==恢复失败。
    INSDRIVER_EXPORT qint32 ReplaceFiles(const qint32& code, const qint32& exit, QListINFileBase& files);

    //获取项目[project_id]的回收站中的内容[recycle_bins]
    //返回说明：1==获取成功;0==获取失败。
    INSDRIVER_EXPORT qint32 GetRecycleBin(const qint32& project_id, QMapqintINRecycleBinInfo& recycle_bins);
    //handwriting end

    INSDRIVER_EXPORT INQRespondInfo GetWorkFlowTempls(QListINQWorkFlowVO& workFlowVOs, qint32 projectId, qint32 pipelineType);

    INSDRIVER_EXPORT INQRespondInfo GetPipelineSteps(QListINPipelineStep& pipelineSteps, qint32 pipelineType = 0, qint32 projectId = 0);

    INSDRIVER_EXPORT INQRespondInfo updatePipelineStepSupervisor(qint32 personId, QListqint pipelineSteps);

    INSDRIVER_EXPORT INQRespondInfo updatePipelineStepCoordinator(qint32 personId, QListqint pipelineSteps);






	INSDRIVER_EXPORT qint32 EditAsset(INAsset& easset);

    INSDRIVER_EXPORT INQRespondInfo DeleteAsset(int assetId);


	INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState);

	INSDRIVER_EXPORT INQRespondInfo GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param);

    INSDRIVER_EXPORT qint32 GetAssetInfo(INAsset& assetinfo);


	INSDRIVER_EXPORT qint32 EditShot(INShot& eshot);

    INSDRIVER_EXPORT INQRespondInfo DeleteShot(int shotId);


	INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int& sceneId);

	INSDRIVER_EXPORT qint32 GetShotInfo(INShot& shotinfo);


    INSDRIVER_EXPORT qint32 DeleteObjectInRecordBin(qint32 recordId);

    INSDRIVER_EXPORT qint32 RestoreObjectInRecordBin(qint32 recordId);

	INSDRIVER_EXPORT INQRespondInfo GetOneselfPermissionInfo(PersonPermissionVO& ret);

	INSDRIVER_EXPORT INQRespondInfo GetPermissionTemp(INQProjectPermissionVO& temp);


	INSDRIVER_EXPORT INQRespondInfo CreatePermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT INQRespondInfo ModifyPermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT INQRespondInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId);



	INSDRIVER_EXPORT INQRespondInfo GetOneSelfAdminTemp(INQAdministrationPermissionVO& temp);


	extern "C" INSDRIVER_EXPORT qint32 CreateAdmin(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 RemovePerson(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 DeletePerson(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 ResetPassword(qint32 personId);

	extern "C" INSDRIVER_EXPORT qint32 CreateTeam(TeamInfomation& teaminfo);

	extern "C" INSDRIVER_EXPORT qint32 DeleteTeam(const qint32& teamid);

	extern "C" INSDRIVER_EXPORT qint32 GetTeam(TeamInfomation& team);

	extern "C" INSDRIVER_EXPORT qint32 DeleteDepartment(const qint32& departmentid);

	extern "C" INSDRIVER_EXPORT qint32 CreateDepartment(Department& department);




	extern "C" INSDRIVER_EXPORT qint32 ModifyPerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 GetPerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 CreatePerson(Person& person);

	extern "C" INSDRIVER_EXPORT qint32 ModifyTeam(TeamInfomation& team);

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




	INSDRIVER_EXPORT INQRespondInfo InsertProjectMilestone(ProjectMilestone& ret);


	INSDRIVER_EXPORT INQRespondInfo UpdateProjectMilestone(ProjectMilestone& ret);

	INSDRIVER_EXPORT INQRespondInfo DeleteProjectMilestone(int milestoneId);




	INSDRIVER_EXPORT INQRespondInfo MakeTag(int& tagId, const TagParam& tagParam);

	INSDRIVER_EXPORT INQRespondInfo RemoveTag(const TagParam& tagParam);



	INSDRIVER_EXPORT INQRespondInfo AddPersonToProject(INQPersonTemplateVO& personTemplate);

	INSDRIVER_EXPORT INQRespondInfo RemovePersonFromProject(qint32 projectId, qint32 personId);



	INSDRIVER_EXPORT INQRespondInfo CreateProject(INQProjectVO& project);

	INSDRIVER_EXPORT INQRespondInfo EditProject(INQProjectVO& project);

	INSDRIVER_EXPORT INQRespondInfo GetProject(INQProjectVO& project);


	INSDRIVER_EXPORT QString GetProjectStateString(ProjectStatusEnum prjState);

	INSDRIVER_EXPORT INQRespondInfo DeleteProject(qint32 projectId);


	INSDRIVER_EXPORT INQRespondInfo GetAffectedTaskInfo(AffectedObjectInfoVO& affectedInfos, qint32 taskId, const QDateTime& dueTime);




	/*!
	 * \brief 编辑任务关联文件的接口
	 * \details
	 * \param taskFileRelationEditParams
	 * 若是添加模板文件,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path ={ "/proj1/aa/bb","a.txt"} fileId 为模板文件的id
	 * 若是添加路径,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path={"/proj1/aa/bb",""}
	 * 若是删除路径，必填字段为：fileType=FileTypeEnum::OUTPUT_FILE，folderId=路径id
	 * \return
	 */





	INSDRIVER_EXPORT INQRespondInfo CreatePannelReviewOrModify(PanelReviewVO& panelView);


	INSDRIVER_EXPORT qint32 CreateTask(INTask& newtask);

	INSDRIVER_EXPORT INQRespondInfo EditTask(INTask& etask);


	INSDRIVER_EXPORT QString GetTaskStateString(INTaskStatus taskState);

	INSDRIVER_EXPORT INQRespondInfo UpdateTaskStatus(qint32 taskId, qint32 status);

	INSDRIVER_EXPORT qint32 FindTaskStatus(INQTaskStatus& taskStatus, qint32 taskId);


	INSDRIVER_EXPORT qint32 SubmitComment(INTaskComment& taskComment);



	INSDRIVER_EXPORT qint32 GetTaskFromID(qint32 taskId, INTask& task);


	INSDRIVER_EXPORT qint32 DeleteTask(qint32 taskId);

	INSDRIVER_EXPORT qint32 GetFileFromId(INFileBase& fileBase, qint32 fileId);

	INSDRIVER_EXPORT qint32 GetFilePathFromId(const qint32 fileId, QString& filePath);



    INSDRIVER_EXPORT INQRespondInfo	GetFolderByParams(INFolderBase &folderbase, FolderParam &param);



	extern "C" INSDRIVER_EXPORT qint32 ModifyFileStatus(INFileBase &filebase);


	extern "C" INSDRIVER_EXPORT qint32 ComfirmDelete(const qint32& ok, const qint32& code);

	extern "C" INSDRIVER_EXPORT qint32 CreateFolder(INFolderBase & folder);

	INSDRIVER_EXPORT INQRespondInfo CreateFolderOrEdit(INFolderBase & folder);








	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 从文件服务器下载文件到本地
	 * \details
	 * \param[in] file 文件的id必填。其余可不填。
	 * \param[in] rootDir 下载的文件的文件夹路径
	 * \return INSDownload指针对象，通过该对象调用start函数启动下载业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSDownLoad* DownLoad(const INFileBase& file, const QString& rootDir);


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
	extern "C" INSDRIVER_EXPORT INSUpLoad* UpLoad(const INFileBase& file, const QString& rootDir, const QString& AbsolutePath = QString());

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
	extern "C" INSDRIVER_EXPORT INSCheckIn* CheckIn(const INFileBase& file, const QString& rootDir, const QString& AbsolutePath = QString());

	extern "C" INSDRIVER_EXPORT INSCheckOut* CheckOut(const INFileBase& file, const QString& rootDir);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传PlaceHolders文件
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadPlaceHolders *UploadPlaceHolders(const INFileBase &file, const QString &AbsolutePath);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 更新用户头像,需要用户头像文件信息和路径信息。
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUpLoadUserAvatar *UploadUserAvatar(const INFileBase &file, const QString &AbsolutePath);

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




	INSDRIVER_EXPORT INQRespondInfo CreateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowTempl(INQWorkFlowVO& workFlowVO);


	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT INQRespondInfo DeleteWorkFlowTempl(qint32 workFlowId);

	INSDRIVER_EXPORT INQRespondInfo CreatePrivateUseWorkFlow(INQWorkFlowVO& workFlowVO, qint32 workFlowId);

	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowInstance(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowInstance(INQWorkFlowVO &workFlowVO);

	INSDRIVER_EXPORT INQRespondInfo CreatePipelineStep(INPipelineStep& pipelineStep, QVector<INWorkPath> &workPath);

	INSDRIVER_EXPORT INQRespondInfo UpdatePipelineStep(INPipelineStep& pipelineStep, QVector<INWorkPath> &workPath);


	INSDRIVER_EXPORT INQRespondInfo DeletePipelineStep(qint32 pipelineId);

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

    /*!
     * \brief GetPipelineStepWorkPath 根据PipelineStepTemplate的ID，获取此PipelineStep下的输出文件路径列表
     * \param pipelineId
     * \param workPath
     * \return
     */
    INSDRIVER_EXPORT INQRespondInfo GetPipelineStepWorkPath(qint32 pipelineId, QVector<INWorkPath> &workPath);




};