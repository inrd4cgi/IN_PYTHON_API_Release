#pragma once

#include "insdriver_global.h"
#include "insdatastructure.h"
#include "InTaskStatus.h"


namespace INS_INTERFACE
{
	INSDRIVER_EXPORT MessageInfo GetTaskSequenceFile(QMap<QString, QList<SequenceFileSetVO>>& sequenceFileInfos, qint32 taskId, qint32 type);

	INSDRIVER_EXPORT MessageInfo SaveTaskSequenceFile(const SequenceFileParam& param);

	INSDRIVER_EXPORT MessageInfo GetAffectedTaskInfo(AffectedObjectInfoVO& affectedInfos, qint32 taskId, const QDateTime& dueTime);

	INSDRIVER_EXPORT MessageInfo GetTaskFileUsageRecord(QList<FileTaskVO>& fileTaskVOs, qint32 taskId, qint32 projectId, qint32 taskType);

	//根据筛选条件获取任务信息
	INSDRIVER_EXPORT qint32 GetTasksByConditions(QList<INTask>& tasks, TaskFilterParam& params);

	//查询获取任务关联文件的接口，taskId必填，类型不填为全部
	INSDRIVER_EXPORT MessageInfo GetTaskRelatedFiles(QMap<qint32, TaskFileVO>& taskFileVOs, qint32 taskId, FileTypeEnum fileType = FileTypeEnum::ALL);

	/*!
	 * \brief 编辑任务关联文件的接口
	 * \details
	 * \param taskFileRelationEditParams
	 * 若是添加模板文件,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path ={ "/proj1/aa/bb","a.txt"} fileId 为模板文件的id
	 * 若是添加路径,必填字段为: fileType=FileTypeEnum::OUTPUT_FILE,path={"/proj1/aa/bb",""}
	 * 若是删除路径，必填字段为：fileType=FileTypeEnum::OUTPUT_FILE，folderId=路径id
	 * \return
	 */
	INSDRIVER_EXPORT MessageInfo EditTaskFileRelatedFiles(const QList<TaskFileRelationEditParam>& taskFileRelationEditParams);

	/*!
	 * \brief 通过参数，从服务器获取一个新的taskId。
	 * \details
	 * \param[in]option 获取pipeline step的参数
	 * \return
	 */
	INSDRIVER_EXPORT MessageInfo GetNewTaskId(const InstanceTaskRequest& option);

	////获取任务所绑定的团队，key--任务id value--团队id
	//INSDRIVER_EXPORT MessageInfo GetTaskBindedTeamList(QMap<qint32, qint32>& taskBindTeams);

	//获取下一个可显示的状态
	INSDRIVER_EXPORT MessageInfo GetTaskNextAvailableStatus(QList<qint32>& taskStatus, int taskId);

	//获取下一个可显示的状态
	INSDRIVER_EXPORT MessageInfo GetTasksNextAvailableStatus(QList<qint32>& taskStatus,const QSet<qint32>& taskIds);

	//获取pannelView的人员 584
	INSDRIVER_EXPORT MessageInfo GetPannelViewPersons(QList<PersonRoleDTO>& personRoles, int projectId, int taskId);

	//获取人员的会议列表 585
	INSDRIVER_EXPORT MessageInfo GetPannelViewList(QList<PanelReviewVO>& panelViews, int projectId = 0);

	//创建或者修改pannel review的列表 586
	INSDRIVER_EXPORT MessageInfo CreatePannelReviewOrModify(PanelReviewVO& panelView);

	//获取文件服务器placeholder列表
	INSDRIVER_EXPORT qint32 GetPlaceHolderList(QList<FileVO>& placeholderlist);

	//创建任务
	INSDRIVER_EXPORT MessageInfo CreateTask(INTask& newtask);

	//编辑任务信息
    INSDRIVER_EXPORT MessageInfo EditTask(INTask& etask);

    //批量设置任务的时间，参数：任务id集合，任务开始时间，任务结束时间
    INSDRIVER_EXPORT MessageInfo EditTaskTime(const QSet<qint32> &, const QDateTime &, const QDateTime &);

    //批量设置任务的assignee，taskIds:任务的id集合，
    INSDRIVER_EXPORT MessageInfo EditTaskAssignee(const QSet<qint32> &taskIds, qint32 assignee, QMap<QString, QString> &failTasks);

    //编辑任务审批流程信息
    INSDRIVER_EXPORT MessageInfo EditTaskApproval(QList<TaskApproval> &approvalList);

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

    INSDRIVER_EXPORT MessageInfo setBatchTaskApprovalList(TaskApprovalWorkFlow& taskApprovalWorkFlow);


    /*!
     * \brief getTaskApprovalList 根据任务ID获取任务审批流程。
     * \param taskId
     * \param approvalList
     * \return
     */
    INSDRIVER_EXPORT MessageInfo getTaskApprovalList(qint32 taskId, QList<TaskApproval> &approvalList);

    //获取任务状态列表
	INSDRIVER_EXPORT QList<INTaskStatus> GetTaskStatusList();

	INSDRIVER_EXPORT QString GetTaskStateString(INTaskStatus taskState);

    /*!
     * \brief UpdateTaskStatus 改变任务状态
     * \param taskId
     * \param status
     * \param isRequiredFirstApproved 是否需要重新开始审批任务
     * \return
     */
    INSDRIVER_EXPORT MessageInfo UpdateTaskStatus(qint32 taskId, qint32 status, bool isRequiredFirstApproved = false);

	//根据任务ID找任务状态
	INSDRIVER_EXPORT qint32 FindTaskStatus(TaskDurationProgress& progress, qint32 taskId);

	//获取当前任务文件历史表
	INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QList<FileVO>& filehistorylist);

	INSDRIVER_EXPORT qint32 SubmitComment(INTaskComment& taskComment);

	INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QList<INTaskComment>& taskComments, qint32 taskStateId = 0);

	INSDRIVER_EXPORT qint32 GetTaskListPersonal(qint32 personId, QList<INTask>& tasklist);

	//根据ID获取整个task结构体
	INSDRIVER_EXPORT qint32 GetTaskFromID(qint32 taskId, INTask& task);

	INSDRIVER_EXPORT qint32 GetAppendTask(qint32 pId, QList<INTask>& tasklist);

	//删除task，返回值为0，删除task成功。
	INSDRIVER_EXPORT qint32 DeleteTask(qint32 taskId);

    INSDRIVER_EXPORT MessageInfo saveTaskRelationFile(const TaskRelationFileRequest& request);
	INSDRIVER_EXPORT MessageInfo GetTaskOutputFileComment(qint32 taskId, QList<FileComment>& fileComments);
	INSDRIVER_EXPORT MessageInfo GetTaskDefaultOutputPath(qint32 taskId, QString& path);
	INSDRIVER_EXPORT MessageInfo getOutputFiles(const OutputFileRequest& request, OutputFileResponse& response);
	INSDRIVER_EXPORT MessageInfo getRequiredFiles(qint32 taskId, QList<OutputFileResponse>& responseList);

};