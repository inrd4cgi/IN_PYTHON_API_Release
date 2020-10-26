#include "insdrivertaskinterface.h"
#include "inspersonhandle.h"
#include "inscommitment.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT INQRespondInfo GetAffectedTaskInfo(AffectedObjectInfoVO& affectedInfos, qint32 taskId, const QDateTime& dueTime) {
		INSCommonRequest<AffectedObjectInfoVO, QPair<qint32, QDateTime>> commonRequest(5204, qMakePair(taskId, dueTime));
		commonRequest.WaitForFinished();
		affectedInfos = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetTaskFileUsageRecord(QList<FileTaskVO>& fileTaskVOs, qint32 taskId, qint32 projectId, qint32 taskType) {
		INSCommonRequest<QList<FileTaskVO>, QPair<qint32,QPair<qint32,qint32>>> commonRequest(5203, qMakePair(taskId,qMakePair(projectId, taskType)));
		commonRequest.WaitForFinished();
		fileTaskVOs = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTasksByConditions(QList<INTask>& tasks, TaskFilterParam& params) {
		INSCommonRequest<QList<INTask>, TaskFilterParam> commonRequest(5202, params);
		commonRequest.WaitForFinished();
		tasks = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	INSDRIVER_EXPORT INQRespondInfo GetTaskRelatedFiles(QMap<qint32, TaskFileVO>& taskFileVOs, qint32 taskId, FileTypeEnum fileType) {
		INSCommonRequest<QMap<qint32, TaskFileVO>, QPair<qint32, qint32>> commonRequest(5200, qMakePair(taskId, (qint32)fileType));
		commonRequest.WaitForFinished();
		taskFileVOs = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo EditTaskFileRelatedFiles(const QList<TaskFileRelationEditParam>& taskFileRelationEditParams) {
		INSCommonRequest<qint32, QList<TaskFileRelationEditParam> > commonRequest(5201, taskFileRelationEditParams);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//INSDRIVER_EXPORT INQRespondInfo GetTaskBindedTeamList(QMap<qint32, qint32> &taskBindTeams) {
	//	INSCommonRequest<QMap<qint32, qint32>, int> commonRequest(588, 0);
	//	commonRequest.WaitForFinished();
	//	taskBindTeams = commonRequest.retData;
	//	return commonRequest.m_return_value;
	//}

	//获取下一个可显示的状态
	INSDRIVER_EXPORT INQRespondInfo GetTaskNextAvailableStatus(QList<qint32> &taskStatus, int taskId) {
		INSCommonRequest<QList<qint32>, int> commonRequest(587, taskId);
		commonRequest.WaitForFinished();
		taskStatus = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	//获取pannelView的人员 584
	INSDRIVER_EXPORT INQRespondInfo GetPannelViewPersons(QList<PersonRoleDTO> &personRoles, int projectId, int taskId) {
		INSCommonRequest<QList<PersonRoleDTO>, QPair<int, int>> commonRequest(584, qMakePair(projectId, taskId));
		commonRequest.WaitForFinished();
		personRoles = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//获取人员的会议列表 585
	INSDRIVER_EXPORT INQRespondInfo GetPannelViewList(QList<PanelReviewVO> &panelViews, int projectId) {
		INSCommonRequest<QList<PanelReviewVO>, int> commonRequest(585, projectId);
		commonRequest.WaitForFinished();
		panelViews = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//创建或者修改pannel review的列表 586
	INSDRIVER_EXPORT INQRespondInfo CreatePannelReviewOrModify(PanelReviewVO &panelView) {
		INSCommonRequest<PanelReviewVO, PanelReviewVO> commonRequest(586, panelView);
		commonRequest.WaitForFinished();
		panelView = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//获取文件服务器placeholder列表
	INSDRIVER_EXPORT qint32 GetPlaceHolderList(QList<INFileBase> &placeholderlist) {
		INSCommonRequest<QList<INS::INFileBase>> phRequest(351, 0);
		phRequest.WaitForFinished();
		placeholderlist = phRequest.retData;
		return phRequest.m_return_value.code;
	}

	//创建任务
	INSDRIVER_EXPORT qint32 CreateTask(INTask &newtask) {
		INSCreateTask newtaskobj(newtask);
		newtaskobj.WaitForFinished();
		return newtaskobj.m_return_value;
	}

	//编辑任务信息
	INSDRIVER_EXPORT INQRespondInfo EditTask(INTask &etask) {
		INSCommonRequest<INTask, INTask> commonRequest(523, etask);
		commonRequest.WaitForFinished();
		etask = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT QList<INTaskStatus> GetTaskStatusList() {
		return InTaskStatusOperate::GetTaskStatusList();
	}

	INSDRIVER_EXPORT QString GetTaskStateString(INTaskStatus taskState) {
		return InTaskStatusOperate::GetINTaskStausString(taskState);
	}

	//改变任务状态
	INSDRIVER_EXPORT INQRespondInfo UpdateTaskStatus(qint32 taskId, qint32 status) {
		INSCommonRequest<qint32, QPair<qint32, qint32>> commonRequest(525, qMakePair(taskId, status));

		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//根据任务ID找任务状态
	INSDRIVER_EXPORT qint32 FindTaskStatus(INQTaskStatus &taskStatus, qint32 taskId) {
		INSCommonRequest<INQTaskStatus, qint32> commonRequest(526, taskId);
		commonRequest.WaitForFinished();
		taskStatus = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	//添加文件记录到taskFiles表
	INSDRIVER_EXPORT qint32 AddRecordToTaskFiles(int taskId, int fileId, int filetype, int isauto) {
		INSAddRecordToTaskFiles addrecordtotaskobj(taskId, fileId, filetype, isauto);
		addrecordtotaskobj.WaitForFinished();
		return addrecordtotaskobj.m_return_value;
	}

	INSDRIVER_EXPORT qint32 SubmitComment(INTaskComment &taskComment) {
		INSCommonRequestRetInt<INTaskComment, INTaskComment> commonRequest(531, taskComment, 0);
		commonRequest.WaitForFinished();
		taskComment = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTaskComment(qint32 taskId, QList<INTaskComment> &taskComments, qint32 taskStateId) {
		INSGetTaskComments getComment(taskId, taskStateId);
		getComment.WaitForFinished();
		taskComments = getComment.m_taskComments;
		return getComment.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTaskListPersonal(qint32 personId, QList<INTask> &tasklist) {
		TaskFilterParam params;
		params.assigneeId= personId;
		return GetTasksByConditions(tasklist, params);
	}

	//获取当前任务文件历史表
	INSDRIVER_EXPORT qint32 GetFileHistoryList(int taskId, QList<INFileBase> &filehistorylist) {
		QMap<qint32, TaskFileVO> taskFileVOs;
		auto ret= INS_INTERFACE::GetTaskRelatedFiles(taskFileVOs, taskId,INS::FileTypeEnum::OUTPUT_FILE);
		for (auto& tf : taskFileVOs) {
			filehistorylist.append(tf.files);
			for (auto& sf:tf.sequenceFiles) {
				filehistorylist.append(sf.files);
			}
		}
		return ret.code;
	}

	INSDRIVER_EXPORT qint32 GetTaskFromID(qint32 taskId, INTask &task) {
		QList<INTask> tasks;
		TaskFilterParam params;
		params.taskIds = { taskId };
		auto ret = GetTasksByConditions(tasks, params);
		task = tasks.isEmpty() ? INTask() : tasks[0];
		return ret;
		//INVariadicRequest<0, INTask, qint32> request(534, taskId);
		//request.WaitForFinished();
		//task = request.retData;
		//return request.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetAppendTask(qint32 pId, QList<INTask> &tasklist) {
		TaskFilterParam params;
		params.supervisorId = pId;
		params.status = (qint32)INS::INTaskStatus::PendingApproval;
		return GetTasksByConditions(tasklist, params);
		//INSGetAppendTask getappobj(pId);
		//getappobj.WaitForFinished();
		//tasklist = getappobj.m_tasklist;
		//return getappobj.m_return_value;
	}

	//INSDRIVER_EXPORT qint32
	//	FilterTasks(qint32 project_id, qint32 team_id, QMap<qint16, QVariant> &specs, QList<INTask> &tasks) {
	//	
	// <0, QList<INTask>, qint32, qint32, QMap<qint16, QVariant>> request(750, project_id, team_id,
	//		specs);
	//	request.WaitForFinished();
	//	tasks = request.retData;
	//	return request.m_return_value;
	//}

	INSDRIVER_EXPORT qint32 DeleteTask(qint32 taskId)
	{
		INSDeleteTask delTask(taskId);
		delTask.WaitForFinished();
		return delTask.m_return_value;
	}
};