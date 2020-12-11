#include "instasktransfer.h"

namespace INS
{

    ///资源的参考文件传输业务
    INSUpLoadSourceReferenceFile::INSUpLoadSourceReferenceFile(qint32 sourceId, const FileVO &filebase, const QString &absolutePath,bool isAssetFlag)
        :INSUpLoad(filebase,QString(),absolutePath),m_sourceId(sourceId),m_IsAssetFlag(isAssetFlag)
    {

    }

    void INSUpLoadSourceReferenceFile::AddExtendData(QVariantMap &varMap)
    {
        QString idValue = (m_IsAssetFlag) ? "assetId" : "shotId";
        varMap.insert(idValue, m_sourceId);
    }



	///INSUploadPlaceHolders
	INSUploadPlaceHolders::INSUploadPlaceHolders(const FileVO & file, const QString & absolutePath)
		:INSUpLoad(file, QString(), absolutePath)
	{
        m_transferType = 0x00010002;
    }



	INSUploadCommentFile::INSUploadCommentFile(const FileVO & file, const INSDataUploadComment & commentData)
		:INSUpLoad(file, QString(), commentData.absolutePath), m_commentData(commentData)
	{
		m_transferType = 0x00010008;
	}

	void INSUploadCommentFile::AddExtendData(QVariantMap & varMap)
	{
		varMap.insert("taskId", m_commentData.taskId);
		varMap.insert("commentType", static_cast<int>(m_commentData.commentType));
	}


	INSUploadRequiredFile::INSUploadRequiredFile(const FileVO & fileBase, qint32 taskId, const QString & absolutePath)
		:INSUpLoad(fileBase, QString(), absolutePath), m_taskId(taskId)
	{
		m_transferType = 0x00010005;
	}

	void INSUploadRequiredFile::AddExtendData(QVariantMap & varMap)
	{
		varMap.insert("taskId", m_taskId);
	}


	INSUploadReferenceFile::INSUploadReferenceFile(const FileVO & fileBase, qint32 taskId, const QString & absolutePath)
		:INSUploadRequiredFile(fileBase, taskId, absolutePath)
	{
		m_transferType = 0x00010004;
	}

	INSUploadOutputFile::INSUploadOutputFile(const FileVO & fileBase, qint32 taskId, const QString & absolutePath)
		: INSUploadRequiredFile(fileBase, taskId, absolutePath)
	{
		m_transferType = 0x00010006;
    }

	INSUploadSequenceTaskFile::INSUploadSequenceTaskFile(const FileVO & fileBase, qint32 taskId, const QString & absolutePath)
		: INSUploadRequiredFile(fileBase, taskId, absolutePath) {
		m_transferType = 0x00010009;
	}
};
