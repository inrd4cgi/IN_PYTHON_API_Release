//
// Created by 22973 on 2020/12/29.
//

#pragma once

//python api 不要这些接口了

#ifdef INSDRIVER_PYTHON
#else

#include "insdatastructure.h"
#include "insdriver_global.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT MessageInfo GetReviewProjectList(QList<INReviewProject> &reviewProjects);

    INSDRIVER_EXPORT MessageInfo GetReviewTaskList(QList<INReviewTaskList> &t, const GetReviewTaskParam &p);

	INSDRIVER_EXPORT MessageInfo GetTaskReviewFile(QList<INTaskReviewFile> &reviewFileList, const QSet<qint32> &taskIds);

	INSDRIVER_EXPORT MessageInfo PostReviewContent(const INPostReviewParam &postReviewParam);

    INSDRIVER_EXPORT MessageInfo GetTaskReviewComment(QList<INReviewTaskComment> &r, qint32 taskId);

    INSDRIVER_EXPORT MessageInfo GetTaskReviewComment(QList<INReviewTaskComment> &r, const QSet<qint32> &taskIds);
};

#endif
