#pragma once
#include "insfiletransfer.h"

namespace INS
{
	struct INSDataUploadComment
	{
		enum class enumCommentType
		{
            ct_audio, ct_general
		};

		QString name;
		qint32 taskId{ 0 };
		enumCommentType commentType;
		QString absolutePath;
	};


    /*!
     * \brief The INSUpLoadSourceReferenceFile class 上传资产或镜头的参考文件 类
     */
    class INSDRIVER_EXPORT INSUpLoadSourceReferenceFile : public INSUpLoad
    {
        Q_OBJECT
    public:
        INSUpLoadSourceReferenceFile(qint32 sourceId, const FileVO & filebase, const QString & absolutePath, bool isAssetFlag);
        ~INSUpLoadSourceReferenceFile(){};

        void AddExtendData(QVariantMap& varMap) override;

        qint32 m_sourceId{0};
        bool m_IsAssetFlag{false};
    };


	/*!
	 * \brief The INSUpLoadPlaceHolders class 上传PlaceHolders文件 类
	 */
    class INSDRIVER_EXPORT INSUploadPlaceHolders : public INSUpLoad
	{
		Q_OBJECT
	public:
        INSUploadPlaceHolders(const FileVO & file, const QString & absolutePath);
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
		INSUploadCommentFile(const FileVO & file, const INSDataUploadComment& commentData);

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
		INSUploadRequiredFile(const FileVO& fileBase, qint32 taskId, const QString& absolutePath);

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
		INSUploadReferenceFile(const FileVO& fileBase, qint32 taskId, const QString& absolutePath);
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
		INSUploadOutputFile(const FileVO& fileBase, qint32 taskId, const QString& absolutePath);
	};

	/*!
	 * \class INSUploadSequenceTaskFile
	 * \ingroup businessAPI_fileModule
     * \brief 上传sequence file的类
	 */
	class INSDRIVER_EXPORT INSUploadSequenceTaskFile : public INSUploadRequiredFile {
		Q_OBJECT;

	public:
		INSUploadSequenceTaskFile(const FileVO& fileBase, qint32 taskId, const QString& absolutePath);
	};
};
