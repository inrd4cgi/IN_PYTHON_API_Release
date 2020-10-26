#include "instasktransfer.h"

namespace INS
{
	///INSUploadPlaceHolders
	INSUploadPlaceHolders::INSUploadPlaceHolders(const INFileBase & file, const QString & absolutePath)
		:INSUpLoad(file, QString(), absolutePath)
	{
		m_transferType = 0x00010002;
	}



	INSUploadCommentFile::INSUploadCommentFile(const INFileBase & file, const INSDataUploadComment & commentData)
		:INSUpLoad(file, QString(), commentData.absolutePath), m_commentData(commentData)
	{
		m_transferType = 0x00010008;
	}

	void INSUploadCommentFile::AddExtendData(QVariantMap & varMap)
	{
		varMap.insert("taskId", m_commentData.taskId);
		varMap.insert("commentType", static_cast<int>(m_commentData.commentType));
	}


	INSUploadRequiredFile::INSUploadRequiredFile(const INFileBase & fileBase, qint32 taskId, const QString & absolutePath)
		:INSUpLoad(fileBase, QString(), absolutePath), m_taskId(taskId)
	{
		m_transferType = 0x00010005;
	}

	void INSUploadRequiredFile::AddExtendData(QVariantMap & varMap)
	{
		varMap.insert("taskId", m_taskId);
	}


	INSUploadReferenceFile::INSUploadReferenceFile(const INFileBase & fileBase, qint32 taskId, const QString & absolutePath)
		:INSUploadRequiredFile(fileBase, taskId, absolutePath)
	{
		m_transferType = 0x00010004;
	}

	INSUploadOutputFile::INSUploadOutputFile(const INFileBase & fileBase, qint32 taskId, const QString & absolutePath)
		: INSUploadRequiredFile(fileBase, taskId, absolutePath)
	{
		m_transferType = 0x00010006;
	}
};