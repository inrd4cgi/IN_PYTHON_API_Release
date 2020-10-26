#pragma once
#include "insfiletransfer.h"

namespace INS
{
	struct INSDataUploadComment
	{
		enum class enumCommentType
		{
			ct_audio, ct_video
		};

		QString name;
		qint32 taskId{ 0 };
		enumCommentType commentType;
		QString absolutePath;
	};

	/*!
	 * \brief The INSUpLoadPlaceHolders class 上传PlaceHolders文件 类
	 */
    class INSDRIVER_EXPORT INSUploadPlaceHolders : public INSUpLoad
	{
		Q_OBJECT
	public:
        INSUploadPlaceHolders(const INFileBase & file, const QString & absolutePath);
        ~INSUploadPlaceHolders() {};

	};

	/*!
	 * \class INSUploadCommentFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传评论文件类
	 */
	class INSDRIVER_EXPORT INSUploadCommentFile : public INSUpLoad
	{
		Q_OBJECT;

	public:
		INSUploadCommentFile(const INFileBase & file, const INSDataUploadComment& commentData);

	protected:
		INSDataUploadComment m_commentData;

		void AddExtendData(QVariantMap& varMap) override;
	};

	/*!
	 * \class INSUploadRequiredFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传required file的类
	 */
	class INSDRIVER_EXPORT INSUploadRequiredFile : public INSUpLoad
	{
		Q_OBJECT;

	public:
		INSUploadRequiredFile(const INFileBase& fileBase, qint32 taskId, const QString& absolutePath);

	protected:
		qint32 m_taskId;

		void AddExtendData(QVariantMap& varMap) override;
	};


	/*!
	 * \class INSUploadReferenceFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传reference file的类。
	 */
	class INSDRIVER_EXPORT INSUploadReferenceFile : public INSUploadRequiredFile
	{
		Q_OBJECT;

	public:
		INSUploadReferenceFile(const INFileBase& fileBase, qint32 taskId, const QString& absolutePath);
	};


	/*!
	 * \class INSUploadOutputFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传output file的类。
	 */
	class INSDRIVER_EXPORT INSUploadOutputFile : public INSUploadRequiredFile
	{
		Q_OBJECT;
	public:
		INSUploadOutputFile(const INFileBase& fileBase, qint32 taskId, const QString& absolutePath);
	};

};
