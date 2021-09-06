#pragma once

#include "insdriver_global.h"
#include "insrequest.h"
#include "sfc_msg.h"
#include "insnetwork.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QPair>

struct QJsonParseError;
class QTimer;

namespace INS
{
	class FileTransferRecorder;
    class DownloadFileOperator;

	enum class INSFileTransferStep
	{
		enumNone,
		enumRecvRepoInfo,
		enumJudgeLastTransferComplete,
		enumInitFileInfo,
		enumCheckFileState,
		enumTransferData,
		enumWaitForRespon,
		enumCancelTransfer,
		enumSecondReqToAppServer
	};

	/*!
	 * \struct FileInfoInFileServer
	 * \ingroup businessAPI_fileModule
	 * \brief 和文件服务器通信用的结构体，保存需要和文件服务器交互的一些信息
	 */
	struct FileInfoInFileServer
	{
		QString m_fileId;	//文件存放在文件服务器的id
		qint64 m_receivedLength{ 0 };	//文件传输过程中，已经传输并被接收的文件数据长度。
	};


	/*!
	 * \class INSFileTransfer
	 * \ingroup businessAPI_fileModule
	 * \brief 文件传输业务的基类。封装一些文件句柄的操作或传输过程中的各种公共函数。
	 */
	class INSDRIVER_EXPORT INSFileTransfer :public QObject, public INSRequest
	{
		Q_OBJECT;
	public:

		enum class ClientTransMsg
		{
			enumInfoAbort = 10000,
			enumInfoTimeout = 20000, enumInfoFileOpenFailed, enumFileIsNotExist,
			enumNetworkError = 30000
		};

		friend class TransferOperatorAbstract;
		friend class InitUploadInfoOperator;
		friend class CheckFileStateOperator;
		friend class UploadFileOperator;
		friend class CancelTransferOperator;
		friend class DownloadFileOperator;
		friend class UploadTinyFileOperator;

		INSFileTransfer(const FileVO& file, const QString& rootDir, const QString& absolutePath = QString());
		~INSFileTransfer() override;

		FileVO m_file;	//客户端输入的文件结构体对象。包含客户端输入的文件数据。

		bool isTransFinished() { return m_transFinished; }

		void Process(const QByteArray&) override;	//接收应用服务器的请求，并分析业务的函数。
		virtual bool Start() = 0;

		quint32 m_transferType{ 0x00000000 };	//传输业务的类型，
		QString m_rootDir;
		QString m_fileAbsolutePath;	//文件的绝对路径
		QFile m_fileHandle;	//文件的句柄
		INSFileTransferStep m_step;	//记录传输业务当前的执行步骤
		FileTransferInfo m_fileRepoInfo;	//应用服务器返回的，对于当前文件在文件服务器的对应信息。
		FileInfoInFileServer m_fileInfoInFileServer;	//和文件服务器交互，需要暂时保存供交互使用的信息。
		QMap<INSFileTransferStep, std::function<void()>> m_stepFunc;	//装载文件传输执行步骤的对应函数的容器。
		const qint64 m_fileChunkSize{ 4 * 1024 * 1024 - 500 };	//一次读取文件最大的数据大小。
		FileTransferRecorder* m_fileRecorder{ nullptr };	//文件传输过程中，记录传输过程的对象。该对象会生成一份文件，并将信息存储在该文件中。
		bool  m_transFinished{ false };
		MessageInfo m_responFromAppSever;	//应用服务器返回的业务结果。
		QIODevice::OpenMode m_fileHandleOpenMode{ QIODevice::ReadWrite };
		QSharedPointer<QTimer> m_waitFotResponTimer {nullptr};
		QPair<qint32, QString> m_finishedResult;
		qint32 m_fileCurrentVersion {0};

		/*!
		 * \brief 注册文件传输步骤的函数。需要更改传输步骤和对应的执行函数时，要重载该函数。该函数需要手动调用。
		 * \details
		 * \param
		 * \return
		 */
		virtual void RegistStepFunc();

		/*!
		 * \brief 默认的接收应用服务器发过来关于需要传输的文件在文件服务器的对应信息。
		 * \details
		 * \param
		 * \return
		 */
		virtual void ReceiveFileRepoInfo();

		/*!
		 * \brief 接收文件仓库信息的异常状态处理。ReceiveFileRepoInfo函数接收m_responFromAppSever内容的code非成功的时候调用。
		 * \details
		 * \param
		 * \return
		 */
		virtual void ReceivedFileRepoInfoAbnormalStatus();

		/*!
		 * \brief 用指定的步骤调用对应的执行函数。
		 * \details
		 * \param[in] transferStep 需要执行的步骤。
		 * \return
		 */
		void RunStepFunc(INSFileTransferStep transferStep);

		/*!
		 * \brief  用指定的步骤调用对应的执行函数。执行步骤为m_step的步骤。
		 * \details
		 * \param
		 * \return
		 */
		void RunStepFunc();


		int GetSysMemory();

		/*!
		 * \brief 计算文件的MD5值。
		 * \details
		 * \param[in] tmpFileHandle 被计算的文件的句柄。
		 * \return 返回装有md5值的QByteArray对象。
		 */
		QString GetFileMd5(QFile* tmpFileHandle);

		/*!
		 * \brief 用已有的数据，初始化m_fileHanlde的函数。
		 * \details
		 * \param[in] bCreateInfoExist 如果为true，则文件初始化过程中，文件m_fileAbsolutePath不存在，则创建。否则直接返回false。
		 * \return
		 */
		bool InitFileHandle(bool bCreateIfNotExist = false);

		/*!
		 * \brief 用已有的数据初始化m_fileAbsolutePath。m_fileAbsolutePath为文件的绝对路径。
		 * \details
		 * \param
		 * \return
		 */
        void InitFileAbsolutePath();

        /*!
         * \brief mkdirFolder 用已有的数据创建目录路径，若目录不存在则创建
         */
        void mkdirFolder();

		/*!
		 * \brief 通过事先记录到的文件的大小和最后的修改时间，判断m_fileAbsolutePath指定的文件是否已经被修改。
		 * \details
		 * \param
		 * \return
		 - true 文件和上次传输时候的一样
		 - false 文件和上次传输的时候不一样。
		 */
		bool isTheFileSameAsTheOld();

		/*!
		 * \brief 从文件中读取数据
		 * \details
		 * \param[out] dataBuf 读取文件的数据，并存入到当前的对象中。
		 * \param[in] n_max 一次读取的最大的数据长度，如果n_max为负数则全部读取。
		 * \param[in] n_seek 文件读取数据的起始点。
		 * \return	读取文件失败则返回false。
		 */
		bool GetDataFromFile(QByteArray& dataBuf, qint64 n_max = -1, qint64 n_seek = 0);

		/*!
		 * \brief 从QByteArray中获取有效的json数据，并返回。
		 * \details
		 * \param[in] dataBuf 原本存放json数据的字节数据。
		 * \param[out] jsonObj 返回的json对象。
		 * \return 返回QPair<qint32, QString>的qint32为结果的代码，QString为结果的信息。
		 */
		QPair<qint32, QString> GetValidJsonFromByteArray(const QByteArray& dataBuf, QJsonObject& jsonObj);

		/*!
		 * \brief 启动定时器，这个定时器专门为了等待应用服务器回复时使用
		 * \details
		 * \param
		 * \return
		 */
		void StartWaitForResponTimer();

		/*!
		 * \brief 等待服务器回复超时，该函数会调用结束函数，结束文件传输
		 * \details
		 * \param
		 * \return
		 */
		void AppServerResponTimeout();

		/*!
		 * \brief 停止等待回复的定时器。
		 * \details
		 * \param
		 * \return
		 */
		void StopResponseTimer();

		void SetFinished(qint32 msgCode, const QString& strMsg);

		QPair<qint32, QString> GetFinishedResult();

		virtual void BeginFileTransferStep() {}
		virtual void WaitAppServerResponse();

		/*!
		 * \brief 添加拓展的数据，主要是为了方便后面的传输类型的拓展，需要添加额外的参数。
		 * \details
		 * \param[out] varMap 取得所有
		 * \return
		 */
		virtual void AddExtendData(QVariantMap& varMap) {}
		
	signals:
		/*!
		 * \brief 业务结束信号，发出结束的状态。
		 * \details
		 * \param finishedMsg first为业务的状态，second为业务的信息。
		 * \return
		 */

        void SigEventFinished(QPair<qint32, QString>);

        void SigEventFinishedForPy(qint32, QString);

		/*!
		 * \brief 文件传输长度信号。
		 * \details
		 * \param qint64 为文件的总接收或总发送的长度。
		 * \return
		 */
        void SigTransLength(qint64);

        /*!
         * \brief 请求取消传输的信号，触发该信号，会调用取消函数
         * \details
         * \param
         * \return
         */
        void SigReqCancelTransfer();

	protected:
		virtual void CancelTransfer() = 0;
	};


	//上传文件
	class UploadTinyFileOperator;
	class INSDRIVER_EXPORT INSUpLoad : public INSFileTransfer
	{
		Q_OBJECT;
	public:
		INSUpLoad(const FileVO& file, const QString& rootDir, const QString& absolutePath = QString());

		bool Start() override;

	protected:
	    qint64 m_tinyUploadSize = 32 * 1024 * 1024 - 500;

		QPointer<UploadTinyFileOperator> m_uploadTinyOperator{ nullptr };

		void RegistStepFunc() override;
		void BeginFileTransferStep() override;
		void CancelTransfer() override;

		/*!
		 * \brief 封装上传文件到文件服务器的具体操作。
		 * \details
		 * \param
		 * \return
		 */
		virtual void UploadFileToFileServer();

		/*!
		 * \brief 初始化需要上传的文件信息
		 * \details
		 * \param
		 * \return
		 */
		void InitUploadFile();

		/*!
		 * \brief 查询被上传的文件的传输状态
		 * \details
		 * \param
		 * \return
		 */
		void CheckUploadStateBeforeTransfer();

		/*!
		 * \brief 取消上传文件的函数。
		 * \details
		 * \param
		 * \return
		 */
		void AbortUpload();

		void TinyUpload();

	};


	//下载文件。
	class INSDRIVER_EXPORT INSDownLoad : public INSFileTransfer
	{
		Q_OBJECT;
	public:
		INSDownLoad(const FileVO& file, const QString&rootDir);

		bool Start() override;

	protected:
		void CancelTransfer() override;


	protected:
        QSharedPointer<DownloadFileOperator> m_downloadOperator{ nullptr };		//下载文件的具体操作对象

		void RegistStepFunc() override;

		/*!
		 * \brief 从文件服务器下载文件的函数
		 * \details
		 * \param
		 * \return
		 */
        virtual void DownloadFileFromServer();

		void BeginFileTransferStep() override;
	};


	//check in文件
	class INSDRIVER_EXPORT INSCheckIn : public INSUpLoad
	{
		Q_OBJECT;
	public:
		INSCheckIn(const FileVO& file, const QString& rootDir, const QString& absolutePath = QString());

	};

	//check out 文件
	class INSDRIVER_EXPORT INSCheckOut : public INSDownLoad
	{
		Q_OBJECT;
	public:
		INSCheckOut(const FileVO& file, const QString& rootDir);

	protected:
		void RegistStepFunc() override;
		void DownloadFileFromServer() override;

		/*!
		 * \brief 向应用服务器请求checkout操作。
		 * \details
		 * \param
		 * \return
		 */
		void SendCheckOutReqToAppServer();
	};

	/*!
	 * \class INSUploadTinyFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传小文件的类。文件大小不超过32MB
	 */
	class UploadTinyFileOperator;
	class INSDRIVER_EXPORT INSUploadTinyFile : public INSFileTransfer
	{
		Q_OBJECT;
	public:
		INSUploadTinyFile(const FileVO& file, const QString& rootDir, const QString& absolutePath = QString());

		bool Start() override;

	protected:
		void BeginFileTransferStep() override;
		void CancelTransfer() override;


		QPointer<UploadTinyFileOperator> m_uploadOperator{ nullptr };
	};

	/*!
	 * \brief The INSUpLoadUserAvatar class 上传用户头像文件 类。上传的文件最大不能超过32MB。
	 */
	class INSDRIVER_EXPORT INSUpLoadUserAvatar : public INSUploadTinyFile
	{
		Q_OBJECT
	public:
		INSUpLoadUserAvatar(const FileVO & file, const QString & absolutePath);
		~INSUpLoadUserAvatar() {};

	};


	/*!
	 * \class INSUploadOutputFile
	 * \ingroup businessAPI_fileModule
	 * \brief 上传output file的类。
	 */
	class INSDRIVER_EXPORT INSUploadLibraryFile : public INSUpLoad
	{
		Q_OBJECT;
	public:
		INSUploadLibraryFile(const FileVO& fileBase, const QString& absolutePath);
	};


	/*!
	 * \class TransferOperatorAbstract
	 * \ingroup businessAPI_fileModule
	 * \brief 文件传输步骤的基类。
	 */
	class TransferOperatorAbstract : public INSHttpRequest
	{
		Q_OBJECT;
	public:
        explicit TransferOperatorAbstract(INSFileTransfer* p_transfer, QObject* parent = nullptr);

		/*!
		 * \brief 关闭QNetworkReply对象，关闭后，直接结束传输操作，需要手动删除传输中的文件和记录文件。
		 * \details
		 * \param
		 * \return
		 */
		virtual void ManuaAbortNetworkReply();
	protected:
		QPointer<INSFileTransfer> m_transferObj;
		QPair<qint32, QString> m_errorMsg;

		void SlotRequestError(QNetworkReply::NetworkError netError) override;
		void SlotRequestFinished() override;

		/*!
		 * \brief  使用成员数据和传入的参数，发出post请求。
		 * \details
		 * \param[in] QJsonObject 需要放入报文体发送给文件服务器的参数。
		 * \param[in] reqPath 请求的路径
		 * \return
		 */
		void GenerateTransPostRequestWithJson(const QJsonObject& jsonObj, const QString& reqPath);

		/*!
		 * \brief 结束文件传输操作，关闭传输套接字，设置step的状态并且选择删除记录文件
		 * \details
		 * \param[in] finishedStep 设置下一步的操作状态
		 * \param[in] deleteRecord 指定是否删除传输的记录文件
		 * \return
		 */

		void FinishedOperator(INSFileTransferStep finishedStep = INSFileTransferStep::enumWaitForRespon, bool deleteRecord = true);
	};

	/*!
	 * \class InitUploadInfoOperator
	 * \ingroup businessAPI_fileModule
	 * \brief 初始化上传业务状态的具体操作类。
	 */
	class InitUploadInfoOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;

	public:
		InitUploadInfoOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);

		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;
	};


	/*!
	 * \class CheckFileStateOperator
	 * \ingroup businessAPI_fileModule
	 * \brief 检查文件上传状态的具体操作类。
	 */
	class CheckFileStateOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;
	public:
		CheckFileStateOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);
		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;

		/*!
		 * \brief 分析文件的上传状态，并执行对应的操作步骤
		 * \details
		 * \param[in] fileStatus 文件的传输状态
		 * \return
		 */
		void RunCheckedStatus(qint32 fileStatus);
	};


	/*!
	 * \class UploadFileOperator
	 * \ingroup businessAPI_fileModule
	 * \brief 上传文件的具体操作类。
	 */
	class UploadFileOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;
	public:
		explicit UploadFileOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);
		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;

		/*!
		 * \brief 检查发送数据到文件服务器后，文件服务器返回来的状态。并执行对应的操作。
		 * \details
		 * \param[in] fileStatus 文件服务器返回的当前文件状态。
		 * \return
		 */
		void RunCheckedStatus(qint32 fileStatus);
	};


	/*!
	 * \class CancelTransferOperator
	 * \ingroup businessAPI_fileModule
	 * \brief 取消上传文件的具体操作类。
	 */
	class CancelTransferOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;
	public:
		CancelTransferOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);
		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;
	};


	/*!
	 * \class DownloadFileOperator
	 * \ingroup businessAPI_fileModule
	 * \brief 从文件服务器下载文件的具体操作类。
	 */
	class DownloadFileOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;
	public:
		INSFileTransferStep m_nextStep;

		explicit DownloadFileOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);
		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;
        void ConnectReplySlot(QNetworkReply *netReply) override;
		void SaveFileData(QByteArray& byteArray);
		void UpdateTransData();

		void ParseAndReturnError(int errorStatus, QByteArray& byteArray);

		/*!
		 * \brief 检查本地的配置文件，获取已经接收的文件数据的长度
		 * \details
		 * \param
		 * \return 返回已经接收的文件数据的长度。
		 */
		qint64 GetReceivedLength();

		/*!
		 * \brief 初始化文件传输的位置和接收长度的变量数据
		 * \details
		 * \param[in]
		 * \return
		 */
		void InitTransState();

		/*!
		 * \brief 按照特定的格式，生成当前文件已经接收的数据长度的字符串。
		 * \details
		 * \param[in] n_received 文件已经接收的长度。
		 * \return
		 */
		QByteArray GenerateContentRange(qint64 n_received);

	};

	class UploadTinyFileOperator : public TransferOperatorAbstract
	{
		Q_OBJECT;
	public:
		UploadTinyFileOperator(INSFileTransfer* p_transfer, QObject* parent = nullptr);
		void RunRequest() override;
		void SlotReadyread(QByteArray& byteArray) override;

		/*!
		 * \brief 检查发送数据到文件服务器后，文件服务器返回来的状态。并执行对应的操作。
		 * \details
		 * \param[in] fileStatus 文件服务器返回的当前文件状态。
		 * \return
		 */
		void RunCheckedStatus(qint32 fileStatus);
	};

}

