//
// Created by 22973 on 2020/12/29.
//

#ifdef INSDRIVER_PYTHON
#else

#include "insdriverreviewinterface.h"
#include "inscommonhandle.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT MessageInfo GetReviewProjectList(QList<INReviewProject> &reviewProjects)
	{
		INSCommonRequest<QList<INReviewProject>> commonRequest(281, 0);
		commonRequest.WaitForFinished();
		reviewProjects = commonRequest.getRecvData();
		return  commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo
    GetReviewTaskList(QList<INReviewTaskList> &reviewTasks, const GetReviewTaskParam &getReviewTaskParam) {

        INSCommonRequest<QList<INReviewTaskList>> commonRequest(282, getReviewTaskParam);
        commonRequest.WaitForFinished();
        reviewTasks = commonRequest.getRecvData();
        return  commonRequest.getRetValue();
	}

	INSDRIVER_EXPORT MessageInfo 
	GetTaskReviewFile(QList<INTaskReviewFile> &reviewFileList, const QSet<qint32> &taskIds) {

		INSCommonRequest<QList<INTaskReviewFile>> commonRequest(283, taskIds);
		commonRequest.WaitForFinished();
		reviewFileList = commonRequest.getRecvData();
		return  commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo
    PostReviewContent(const INPostReviewParam &postReviewParam,INReviewTaskComment & reviewTaskComment) {

        INSCommonRequest<INReviewTaskComment> commonRequest(284, postReviewParam);
        commonRequest.WaitForFinished();
        reviewTaskComment = commonRequest.getRecvData();
        return  commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo
    GetTaskReviewComment(QList<INReviewTaskComment> &reviewTaskComment, qint32 taskId) {

        INSCommonRequest<QList<INReviewTaskComment>> commonRequest(285, taskId);
        commonRequest.WaitForFinished();
        reviewTaskComment = commonRequest.getRecvData();
        return  commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo
    GetTaskReviewComment(QList<INReviewTaskComment> &reviewTaskComment, const QSet<qint32> &taskIds) {

        INSCommonRequest<QList<INReviewTaskComment>> commonRequest(286, taskIds);
        commonRequest.WaitForFinished();
        reviewTaskComment = commonRequest.getRecvData();
        return  commonRequest.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo
    GetReviewContentByCommentId(QString &reviewContent, qint32 commentId) {

        INSCommonRequest<QString> commonRequest(287, commentId);
        commonRequest.WaitForFinished();
        reviewContent = commonRequest.getRecvData();
        return  commonRequest.getRetValue();
	}
};

#endif
