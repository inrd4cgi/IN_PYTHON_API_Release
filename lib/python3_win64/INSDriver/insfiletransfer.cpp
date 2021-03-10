#include "insfiletransfer.h"
#include "CFileOperateBase.h"
#include "inssetting.h"
#include "insdriver_global.h"

#include <QCoreApplication>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QFileInfo>
#include <QTimer>

#ifdef Q_OS_WIN
#include <Windows.h>
#else
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#endif

#define ReqSucceed 9999
#define ReqFileSysError 8888
#define ReqParamError 1000
#define ReqPermissionFailed 1001
#define ReqServerOverload 1002
#define ReqFileServerMemInsufficient 1003

#define RETSTATUSERROR 404
#define RETSTATUSSUCCEEDED 200
#define RETSTATUSSUCCEEDEDOTHER 206

static QString TEMP_TRANS_RECORD_DIRECTORY = QDir::tempPath() + "/insDriver/Record";
static int WAITFORRESPONTIMEOUT = 20 * 1000;

static const char* strInterfaceInitUploadInfo{ "/api/initUpload" };
static const char* strInterfaceGetUploadState{ "/api/checkMeta" };
static const char* strInterfaceUploadChunk{ "/api/uploadChunk" };
static const char* strInterfaceCancelUpload{ "/api/abortUpload" };
static const char* strInterfaceDownloadFile{ "/api/download" };
static const char* strInterfaceUploadTinyFile{ "/api/upload" };

namespace INS
{
	/*!
	 * \class FileTransferRecorder
	 * \ingroup
	 * \brief 上传下载时，记录传输过程的数据。
	 */
	class FileTransferRecorder : public QObject
	{
	public:
		explicit FileTransferRecorder(const QString& filePath, QObject* parent = nullptr)
			:QObject(parent), m_strTargetFilePath(filePath)
		{
			QString recordFilePath(GenerateRecordFileNameAndCreateFolder(filePath));
			qInfo() << "generate record obj, name: " << recordFilePath;

			m_recordFile = new QSettings(recordFilePath, QSettings::IniFormat);
		}

		~FileTransferRecorder() override
		{
			if (m_recordFile)
			{
				if (m_deleteRecordFile)
					RemoveRecordFile();

				m_recordFile->deleteLater();
				m_recordFile = nullptr;
			}
		}

		void RemoveRecordFile()
		{
			QString recordFilePath(m_recordFile->fileName());
			if (QFile::exists(recordFilePath))
			{
				bool bResult = QFile::remove(recordFilePath);
				qDebug() << "remove record file. name : " << recordFilePath << " . result : " << bResult;
			}
		}

		bool isRecordFileExist() {
			return QFile::exists(m_recordFile->fileName());
		}

		/*!
		 * \brief 本地有文件存在的时候可以使用这个函数，有些需要记录的数值可以直接通过本地文件获取
		 * \details
		 * \param[in] transferType 传输业务的类型。
		 * \param[in] md5Value 传输文件的md5的值
		 * \return
		 */
		void InitRecordFileByLocalFile(quint32 transferType, QString md5Value)
		{
			QFileInfo targetFileInfo(m_strTargetFilePath);
			InitRecordFile(targetFileInfo.size(), targetFileInfo.lastModified(), transferType, md5Value);
		}

		void SetValue(const char* strKey, const QVariant& var, bool bSync = false)
		{
			if (m_recordFile)
			{
				m_recordFile->setValue(strKey, var);
				if (bSync)
					m_recordFile->sync();
			}
		}

		QVariant GetValue(const char* strKey)
		{
			if (m_recordFile)
				return m_recordFile->value(strKey);
			return QVariant();
		}

		void InitRecordFile(qint64 fileSize, const QDateTime& modifiedDate, qint64 transferType, QString md5Value)
		{
			SetValue(m_strFileSize, fileSize);
			SetValue(m_strModifiedTime, modifiedDate);
			SetValue(m_strTransType, transferType);
			SetValue(m_strMd5, md5Value, true);
		}

		/*!
		 * \brief 生成记录文件的文件名，并创建记录文件需要存放的目录。
		 * \details
		 * \param[in] filePath 需要传输的文件的路径。
		 * \return
		 */
		QString GenerateRecordFileNameAndCreateFolder(QString filePath)
		{
			//创建文件夹记录文件的文件夹
			QString folderName(TEMP_TRANS_RECORD_DIRECTORY);
			QDir tempFolder(folderName);
			tempFolder.mkpath(folderName);

			//拼接记录文件的文件名
			int n_index = filePath.lastIndexOf("/");
			QString fileName = filePath.mid(n_index);
			fileName.remove(".");
			fileName.append("Recorder");

			return folderName + fileName;
		}

		bool isTheFileSameAsTheOld(QFile* p_file)
		{
			assert(m_recordFile);
			QFileInfo fileInfo(*p_file);
			QVariant strModifiedTime = m_recordFile->value(m_strModifiedTime);
			QVariant strFileSize = m_recordFile->value(m_strFileSize);

			if (strModifiedTime.isValid() && strFileSize.isValid())
			{
				if (strModifiedTime.toDateTime() == fileInfo.lastModified() && strFileSize.toLongLong() == fileInfo.size())
					return true;
			}
			return false;
		}

		void SetFileId(QString fileId)
		{
			SetValue(m_strFIleId, fileId, true);
		}


		QString GetFileId()
		{
			return m_recordFile->value(m_strFIleId).toString();
		}

		bool isTransTypeEnqual(quint32 transferType)
		{
			assert(m_recordFile);
			QVariant var = m_recordFile->value(m_strTransType);
			if (!var.isValid())
				return false;

			quint32 recordType = var.toUInt();
			return recordType == transferType;
		}

		void SetRecordFileDeleted(bool deleteNow = false)
		{
			m_deleteRecordFile = true;
			RemoveRecordFile();
		}

		qint64 GetTransLength()
		{
			return m_recordFile->value(m_strTransLength).toLongLong();
		}

		void SetTransLength(qint64 dataLength)
		{
			SetValue(m_strTransLength, dataLength, true);
		}

		QString GetTransFileMd5()
		{
			return m_recordFile->value(m_strMd5).toString();
		}

	protected:
		QSettings* m_recordFile;
		QString m_strTargetFilePath;
		bool m_deleteRecordFile{ false };

		const char* m_strModifiedTime{ "modifiedTime" };
		const char* m_strFileSize{ "fileSize" };
		const char* m_strTransLength{ "transLength" };
		const char* m_strTransType{ "transfType" };
		const char* m_strFIleId{ "fileId" };
		const char* m_strMd5{ "md5" };
	};



	/*************************************************************************************************
	Description: 传输文件[file],[root_dir]为文件根路径。
	*************************************************************************************************/
	INSFileTransfer::INSFileTransfer(const FileVO & file, const QString & rootDir, const QString& absolutePath)
		:m_file(file), m_fileAbsolutePath(absolutePath), m_rootDir(rootDir), m_step(INSFileTransferStep::enumRecvRepoInfo)
	{
        qDebug() << "rootDir ==" << rootDir;
        qDebug() << "absolutePath == " << absolutePath;
	    qDebug() << "m_fileAbsolutePath == " << m_fileAbsolutePath;
	    qDebug() << "m_rootDir" << m_rootDir;
		//上传下载业务不需要加锁，将基类锁解锁。
		m_lock.unlock();
	}

	INSFileTransfer::~INSFileTransfer()
	{
		qDebug() << "DELETE TRANSFER OBJ";
		if (m_fileHandle.isOpen())
			m_fileHandle.close();

		if (m_fileRecorder)
			delete m_fileRecorder;
	}

	void INSFileTransfer::Process(const QByteArray & data)
	{
		m_data = data;
		RunStepFunc();
	}

	void INSFileTransfer::RunStepFunc(INSFileTransferStep transferStep)
	{
		m_step = transferStep;
		auto p_stepFunc = m_stepFunc.value(m_step, nullptr);
		if (p_stepFunc)
			p_stepFunc();
	}

	void INSFileTransfer::RunStepFunc()
	{
		RunStepFunc(m_step);
	}

	/*************************************************************************************************
	Description: 获取主机的内存消耗量
	*************************************************************************************************/
	int INSFileTransfer::GetSysMemory()
	{
#ifdef Q_OS_WIN
		MEMORYSTATUSEX memerystatus;
		memerystatus.dwLength = sizeof(memerystatus);
		//如果获取系统内存信息不成功，就直接返回
		if (!GlobalMemoryStatusEx(&memerystatus))
			return 100;
		//获取未使用的内存总量,浮点型，主要为了后面的除法运算。
		float memeryfree = memerystatus.ullAvailPhys / (1024.0*1024.0);
		float memerytotal = memerystatus.ullTotalPhys / (1024.0*1024.0);
		float memeryused = memerytotal - memeryfree;
		//返回已用除以总数。
		return round(100.0 * (memeryused / memerytotal));//返回值是占用比：0 - 100
#else
		int error;
		struct sysinfo s_info;
		error = sysinfo(&s_info);
		return qRound(100.0 * (s_info.freeswap / s_info.totalram));
#endif
	}


	/*!
	* \details 计算传输文件的md5值。如果文件在本地不存在，则不做计算。
	* \param[in] tmpFileHandle 传入文件的句柄，这个句柄传入前，需要用文件路径初始化。
	* \return 返回值为包含md5计算结果的QByteArray，如果文件不存在，则返回空的QByteArray。
	*/
	QString INSFileTransfer::GetFileMd5(QFile* tmpFileHandle)
	{
		//如果记录文件存在md5值，则从记录文件获取。
		if (isTheFileSameAsTheOld())
			return m_fileRecorder->GetTransFileMd5();

		//记录文件不存在md5值，计算文件的md5值。
		if (!tmpFileHandle->exists())
			return QByteArray();

		if (!tmpFileHandle->isOpen())
			tmpFileHandle->open(m_fileHandleOpenMode);

		QCryptographicHash hashObj(QCryptographicHash::Md5);
		hashObj.addData(tmpFileHandle);
		return QString(hashObj.result().toHex());
	}

	bool INSFileTransfer::InitFileHandle(bool bCreateIfNotExist)
	{
		InitFileAbsolutePath();
		m_fileHandle.setFileName(m_fileAbsolutePath);
		if (!m_fileHandle.exists())
		{
			if (!bCreateIfNotExist)
				return false;

			QDir folderPath(m_rootDir + m_file.directory + "/");
			auto aa = folderPath.path();
			if (!folderPath.exists())
				folderPath.mkpath(folderPath.path());
		}

		if ((m_fileHandleOpenMode & QIODevice::WriteOnly) && !(m_fileHandle.permissions() & QFileDevice::WriteOther))
		    m_fileHandle.setPermissions(m_fileHandle.permissions() | QFileDevice::WriteOther);
        return m_fileHandle.open(m_fileHandleOpenMode);
    }

	void INSFileTransfer::InitFileAbsolutePath()
	{
		
		if (m_fileAbsolutePath.isEmpty())
		{
			m_fileAbsolutePath = m_rootDir + m_file.directory + "/" + m_file.name;
			qInfo() << "InitFileAbsolutePath. fileName: " << m_fileAbsolutePath;
		}
	}

    void INSFileTransfer::mkdirFolder()
    {
        QString absolutePath = m_rootDir + m_file.directory + "/";
        QDir dir(absolutePath);
        if(!dir.exists())
            dir.mkpath(absolutePath);
    }

	bool INSFileTransfer::isTheFileSameAsTheOld()
	{
		if (!m_fileRecorder->isTransTypeEnqual(m_transferType))
			return false;
		return m_fileRecorder->isTheFileSameAsTheOld(&m_fileHandle);
	}

	bool INSFileTransfer::GetDataFromFile(QByteArray & dataBuf, qint64 n_max, qint64 n_seek)
	{
		if (!m_fileHandle.seek(n_seek))
			return false;

		QDataStream dt(&dataBuf, QIODevice::ReadWrite);
		if (n_max >= 0)
			dt << m_fileHandle.read(n_max);
		else
			dt << m_fileHandle.readAll();

		dataBuf.remove(0, 4);
		return true;
	}

	QPair<qint32, QString> INSFileTransfer::GetValidJsonFromByteArray(const QByteArray & dataBuf, QJsonObject& jsonObj)
	{
		QJsonParseError parseError;
		auto jsonDoc = QJsonDocument::fromJson(dataBuf, &parseError);
		if (parseError.error != QJsonParseError::NoError)
		{
			return qMakePair((int)parseError.error, QString("QJsonParseError:%1").arg(parseError.error));
		}

		jsonObj = jsonDoc.object();
		if (!jsonObj.isEmpty())
		{
			auto codeValue = jsonObj.value("retcode");
			if (codeValue.toInt() != ReqSucceed)
				return qMakePair(jsonObj.value("retcode").toInt(), jsonObj.value("retmsg").toString());
		}
		return qMakePair(0, QString("succeeded"));
	}

	void INSFileTransfer::WaitAppServerResponse()
	{
		StopResponseTimer();

		//第二次从应用服务器接收数据，需要QDataStream指0的位置。
		mp_in->device()->seek(0);
		QByteArray jsonStr;
		*mp_in >> jsonStr;
		JsonMessageUtils::jsonArrayBinaryDataToData(jsonStr, m_responFromAppSever, m_fileRepoInfo);

		m_file = m_fileRepoInfo.clientInfo;
		SetFinished(m_responFromAppSever.code, m_responFromAppSever.message);
		m_step = INSFileTransferStep::enumNone;
		qInfo() << "App Server response again. code: " << m_responFromAppSever.code << " . msg: " << m_responFromAppSever.message;
	}

	void INSFileTransfer::SetFinished(qint32 msgCode, const QString& strMsg)
    {
        ///检查msgCode,若为202，则意味着此操作为下载文件夹操作，直接在本地创建一个文件夹。
        if(msgCode == 202)
        {
            mkdirFolder();
            msgCode = 1;
        }

		m_transFinished = true;
		emit SigEventFinishedForPy(msgCode, strMsg);
		emit SigEventFinished(qMakePair(msgCode, strMsg));
		qInfo() << "transferType " << m_transferType << " msgCode: " << msgCode << " Msg: " << strMsg;
	}


	void INSFileTransfer::RegistStepFunc()
	{
		m_stepFunc.insert(INSFileTransferStep::enumRecvRepoInfo, std::bind(&INSFileTransfer::ReceiveFileRepoInfo, this));
		m_stepFunc.insert(INSFileTransferStep::enumJudgeLastTransferComplete, std::bind(&INSFileTransfer::BeginFileTransferStep, this));
		m_stepFunc.insert(INSFileTransferStep::enumWaitForRespon, std::bind(&INSFileTransfer::WaitAppServerResponse, this));
	}

	void INSFileTransfer::ReceiveFileRepoInfo()
	{
	    QByteArray jsonStr;
		*mp_in >> jsonStr;
		JsonMessageUtils::jsonArrayBinaryDataToData(jsonStr, m_responFromAppSever, m_fileRepoInfo);

		if (m_responFromAppSever.code == 1)
			RunStepFunc(INSFileTransferStep::enumJudgeLastTransferComplete);
		else
			ReceivedFileRepoInfoAbnormalStatus();
	}

	void INSFileTransfer::ReceivedFileRepoInfoAbnormalStatus()
	{
		qWarning() << "get permission failed. code: " << m_responFromAppSever.code << " . msg: " << m_responFromAppSever.message;

		switch (m_responFromAppSever.code)
		{
		case 200:
			m_step = INSFileTransferStep::enumNone;
			m_file = m_fileRepoInfo.clientInfo;
			emit SigTransLength(m_fileRepoInfo.size);
			m_responFromAppSever.code = 1;
			break;
		case 201:
			m_step = INSFileTransferStep::enumNone;
			m_file = m_fileRepoInfo.clientInfo;
			break;
		case 202:
			m_step = INSFileTransferStep::enumNone;
			break;
		default:
			m_step = INSFileTransferStep::enumNone;
			break;
		}

		SetFinished(m_responFromAppSever.code, m_responFromAppSever.message);
	}

	void INSFileTransfer::StartWaitForResponTimer()
	{
		if (m_waitFotResponTimer.isNull())
		{
			m_waitFotResponTimer = QSharedPointer<QTimer>(new QTimer);
			m_waitFotResponTimer->setSingleShot(true);
			connect(m_waitFotResponTimer.data(), &QTimer::timeout, this, &INSFileTransfer::AppServerResponTimeout, Qt::DirectConnection);
		}
		m_waitFotResponTimer->start(WAITFORRESPONTIMEOUT);
	}

	void INSFileTransfer::AppServerResponTimeout()
	{
		SetFinished((int)(ClientTransMsg::enumInfoTimeout), "Can not receive the response.");
	}

	void INSFileTransfer::StopResponseTimer()
	{
		if (!m_waitFotResponTimer.isNull())
		{
			if (m_waitFotResponTimer->isActive())
				m_waitFotResponTimer->stop();
		}
	}

	/*!
	 * \brief 上传文件业务的构造函数。
	 * \details
	 * \param[in] file 需要上传的文件的结构体，包含文件的信息，必须填写file的文件名。
	 * \param[in] strLocalFilePath 本地文件的路径。
	 * \return
	 */
	INSUpLoad::INSUpLoad(const FileVO& file, const QString& rootDir, const QString& absolutePath)
		:INSFileTransfer(file, rootDir, absolutePath)
	{
		m_transferType = 0x00010000;
		m_fileHandleOpenMode = QIODevice::ReadOnly;

		RegistStepFunc();

		//上传之前，需要先初始化文件句柄，并更新m_file的某些信息。
		InitFileHandle();
		m_file.size = QFileInfo(m_fileAbsolutePath).size();
	}


	/*!
	 * \brief 开始上传。业务结束后，调用者需要手动删除掉上传对象。
	 * \details
	 * \return 返回值为布尔值
	 - true : 表示发送数据到应用服务器成功。如果开始失败。
	 - false : 原因通常是网络连接出错！
	 */
	bool INSUpLoad::Start()
	{
		if (!QFile::exists(m_fileAbsolutePath))
		{
			SetFinished((int)(ClientTransMsg::enumFileIsNotExist), "file is not exist.");
			return false;
		}

		if (m_fileRecorder == nullptr)
			m_fileRecorder = new FileTransferRecorder(m_fileAbsolutePath);

		QVariantMap transferInfo;
		transferInfo.insert(QString("type"), m_transferType);

		if (m_file.folderId > 0)
			transferInfo.insert(QString("folderId"), m_file.folderId);
		else
			transferInfo.insert(QString("directory"), m_file.directory);

		if (m_file.fileId <= 0 && m_file.name.isEmpty())
		{
			SetFinished((int)(ClientTransMsg::enumFileIsNotExist), "file is not exist.");
			return false;
		}

		if (m_file.fileId > 0)
			transferInfo.insert(QString("fileId"), m_file.fileId);
		else
			transferInfo.insert(QString("name"), m_file.name);

		m_file.checkCode = GetFileMd5(&m_fileHandle);
		transferInfo.insert(QString("checkCode"), m_file.checkCode);

		//添加延申的数据，方便传输其他类型的文件拓展
		AddExtendData(transferInfo);

		qDebug() << "md5 " << m_file.checkCode;
		QByteArray jsonStr = JsonMessageUtils::dataToJsonArrayBinaryData(transferInfo);
		*mp_out << qint32(304) << m_request_id << jsonStr;
		return INSNETWORK->SendDataToAppServer(m_senddata);
	}

	void INSUpLoad::CancelTransfer()
	{
		RunStepFunc(INSFileTransferStep::enumCancelTransfer);
		m_step = INSFileTransferStep::enumNone;
		m_fileRecorder->SetRecordFileDeleted(true);
	}

	void INSUpLoad::RegistStepFunc()
	{
		INSFileTransfer::RegistStepFunc();

		m_stepFunc.insert(INSFileTransferStep::enumInitFileInfo, std::bind(&INSUpLoad::InitUploadFile, this));
		m_stepFunc.insert(INSFileTransferStep::enumCheckFileState, std::bind(&INSUpLoad::CheckUploadStateBeforeTransfer, this));
		m_stepFunc.insert(INSFileTransferStep::enumTransferData, std::bind(&INSUpLoad::UploadFileToFileServer, this));
		m_stepFunc.insert(INSFileTransferStep::enumCancelTransfer, std::bind(&INSUpLoad::AbortUpload, this));
	}

	void INSUpLoad::BeginFileTransferStep()
	{
		if (m_file.size <= m_tinyUploadSize)
		{
			TinyUpload();
			return;
		}

		if (m_fileRecorder->isRecordFileExist() && isTheFileSameAsTheOld())
		{
			//非初次上传，查询文件状态
			m_fileInfoInFileServer.m_fileId = m_fileRecorder->GetFileId();
			RunStepFunc(INSFileTransferStep::enumCheckFileState);
		}
		else
		{
			//初次上传，初始化记录文件
			m_fileRecorder->InitRecordFileByLocalFile(m_transferType, m_file.checkCode);
			RunStepFunc(INSFileTransferStep::enumInitFileInfo);
		}
	}

	void INSUpLoad::InitUploadFile()
	{
		InitUploadInfoOperator* p_operator = new InitUploadInfoOperator(this, this);
		p_operator->RunRequest();
	}

	void INSUpLoad::CheckUploadStateBeforeTransfer()
	{
		CheckFileStateOperator* p_operator = new CheckFileStateOperator(this, this);
		p_operator->RunRequest();
	}

	void INSUpLoad::UploadFileToFileServer()
	{
		UploadFileOperator* p_operator = new UploadFileOperator(this, this);
		p_operator->RunRequest();
	}

	void INSUpLoad::AbortUpload()
	{
		if (!m_uploadTinyOperator.isNull())
		{
			m_step = INSFileTransferStep::enumNone;
            m_uploadTinyOperator->ManuaAbortNetworkReply();
			m_fileHandle.close();
			m_fileRecorder->SetRecordFileDeleted(true);
			SetFinished((int)(ClientTransMsg::enumInfoAbort), "trans abort.");

			return;
		}

		CancelTransferOperator* p_operator = new CancelTransferOperator(this, this);
		p_operator->RunRequest();
		SetFinished((int)(ClientTransMsg::enumInfoAbort), "trans abort.");
	}

	void INSUpLoad::TinyUpload()
	{
		m_uploadTinyOperator = new UploadTinyFileOperator(this, this);
		m_uploadTinyOperator->RunRequest();
	}



	/**************************************************************************************************
	Description:服务器返回数据[data]处理函数。按步骤进行文件上传。
	//使用该接口需要注意如果返回了失败结果需要及时删除指针，否则将会无法连接文件服务器
	**************************************************************************************************/
	INSDownLoad::INSDownLoad(const FileVO& file, const QString& rootDir)
		:INSFileTransfer(file, rootDir) {
		m_transferType = 0x00020000;
		RegistStepFunc();
	}

	/*************************************************************************************************
	Description: 开始下载。如果开始失败，返回false,原因通常是网络连接出错！此后下载请求失效，调用者需要删除掉
	下载对象。
	*************************************************************************************************/
	bool INSDownLoad::Start()
	{
		QVariantMap transferInfo;
		transferInfo.insert(QString("type"), m_transferType);

		assert(m_file.fileId > 0);
		transferInfo.insert(QString("fileId"), m_file.fileId);

		if (m_file.currentVersion > 0)
			transferInfo.insert(QString("version"), m_file.currentVersion);
		QByteArray jsonStr;
		jsonStr = JsonMessageUtils::dataToJsonArrayBinaryData(transferInfo);
		*mp_out << qint32(304) << m_request_id << jsonStr;
		return INSNETWORK->SendDataToAppServer(m_senddata);
	}

	void INSDownLoad::CancelTransfer()
	{
		if (!m_downloadOperator.isNull())
            m_downloadOperator->ManuaAbortNetworkReply();

        m_step = INSFileTransferStep::enumNone;
        m_fileHandle.close();
        m_fileHandle.remove();

        if (m_fileRecorder)
            m_fileRecorder->SetRecordFileDeleted(true);
        
		SetFinished((int)(ClientTransMsg::enumInfoAbort), "trans abort.");
	}

	void INSDownLoad::RegistStepFunc()
	{
		INSFileTransfer::RegistStepFunc();
		m_stepFunc.insert(INSFileTransferStep::enumTransferData, std::bind(&INSDownLoad::DownloadFileFromServer, this));
	}

	void INSDownLoad::DownloadFileFromServer()
	{
		m_file = m_fileRepoInfo.clientInfo;
		m_downloadOperator = new DownloadFileOperator(this, this);
		m_downloadOperator->RunRequest();
	}


	void INSDownLoad::BeginFileTransferStep()
	{
		if (m_file.directory.isEmpty())
			m_file.directory = m_fileRepoInfo.clientInfo.directory;
		if (m_file.name.isEmpty())
			m_file.name = m_fileRepoInfo.clientInfo.name;

		if (!InitFileHandle(true))
		{
			SetFinished((int)(ClientTransMsg::enumInfoFileOpenFailed), "Open file failed.");
			return;
		}

		if (m_fileRecorder == nullptr)
			m_fileRecorder = new FileTransferRecorder(m_fileAbsolutePath);

		if (!m_fileRecorder->isRecordFileExist())
			m_fileRecorder->InitRecordFile(m_file.size, m_file.lastModifyTime, m_transferType, m_file.checkCode);
		RunStepFunc(INSFileTransferStep::enumTransferData);
	}


	//INSCheckIn
	//***************************************************************************************************
	INSCheckIn::INSCheckIn(const FileVO & file, const QString & rootDir, const QString& absolutePath)
		:INSUpLoad(file, rootDir, absolutePath)
	{
		m_transferType = 0x00010003;
	}


	INSCheckOut::INSCheckOut(const FileVO & file, const QString & rootDir)
		:INSDownLoad(file, rootDir)
	{
		RegistStepFunc();
	}

	void INSCheckOut::RegistStepFunc()
	{
        INS::INSDownLoad::RegistStepFunc();
		m_stepFunc.insert(INSFileTransferStep::enumSecondReqToAppServer, std::bind(&INSCheckOut::SendCheckOutReqToAppServer, this));
	}

	void INSCheckOut::DownloadFileFromServer()
	{
		m_file = m_fileRepoInfo.clientInfo;
		m_downloadOperator = new DownloadFileOperator(this, this);
		m_downloadOperator->m_nextStep = INSFileTransferStep::enumSecondReqToAppServer;
		m_downloadOperator->RunRequest();
	}

	void INSCheckOut::SendCheckOutReqToAppServer()
	{
		qInfo() << "send checkout request to app server";

		m_transferType = 0x00020003;
		QVariantMap varMap;
		varMap.insert("type", m_transferType);
		varMap.insert("fileId", m_file.fileId);

		QByteArray jsonStr = JsonMessageUtils::dataToJsonArrayBinaryData(varMap);
		m_senddata.clear();
		mp_out->device()->seek(0);
		*mp_out << qint32(304) << m_request_id << jsonStr;
		INSNETWORK->SendDataToAppServer(m_senddata);

		StartWaitForResponTimer();
		m_step = INSFileTransferStep::enumWaitForRespon;
	}


	//INSUploadTinyFile
	INSUploadTinyFile::INSUploadTinyFile(const FileVO & file, const QString & rootDir, const QString & absolutePath)
		:INSFileTransfer(file, rootDir, absolutePath)
	{
		m_transferType = 0x00010000;
		m_fileHandleOpenMode = QIODevice::ReadOnly;

		RegistStepFunc();

		//上传之前，需要先初始化文件句柄，并更新m_file的某些信息。
		InitFileHandle();
		m_file.size = QFileInfo(m_fileAbsolutePath).size();
	}

	bool INSUploadTinyFile::Start()
	{
		assert(QFile::exists(m_fileAbsolutePath));
		if (m_fileRecorder == nullptr)
			m_fileRecorder = new FileTransferRecorder(m_fileAbsolutePath);

		QVariantMap transferInfo;
		transferInfo.insert(QString("type"), m_transferType);

		if (m_file.folderId > 0)
			transferInfo.insert(QString("folderId"), m_file.folderId);
		else
			transferInfo.insert(QString("directory"), m_file.directory);

		assert(m_file.fileId > 0 || !m_file.name.isEmpty());
		if (m_file.fileId > 0)
			transferInfo.insert(QString("fileId"), m_file.fileId);
		else
			transferInfo.insert(QString("name"), m_file.name);

		m_file.checkCode = GetFileMd5(&m_fileHandle);
		transferInfo.insert(QString("checkCode"), m_file.checkCode);

		//添加延申的数据，方便传输其他类型的文件拓展
		AddExtendData(transferInfo);

		qDebug() << "md5  " << m_file.checkCode;
		QByteArray jsonStr = JsonMessageUtils::dataToJsonArrayBinaryData(transferInfo);
		*mp_out << qint32(304) << m_request_id << jsonStr;
		
		return INSNETWORK->SendDataToAppServer(m_senddata);
	}

	void INSUploadTinyFile::CancelTransfer()
	{
		if (!m_uploadOperator.isNull())
		{
            m_uploadOperator->ManuaAbortNetworkReply();

			m_step = INSFileTransferStep::enumNone;
			m_fileHandle.close();
			m_fileRecorder->SetRecordFileDeleted(true);
		}

		SetFinished((int)(ClientTransMsg::enumInfoAbort), "trans abort.");
	}

	void INSUploadTinyFile::BeginFileTransferStep()
	{
		m_uploadOperator = new UploadTinyFileOperator(this, this);
		m_uploadOperator->RunRequest();
	}


	///INSUploadUserAvatar
	INSUpLoadUserAvatar::INSUpLoadUserAvatar(const FileVO &file, const QString &absolutePath)
		:INSUploadTinyFile(file, QString(), absolutePath)
	{
		m_transferType = 0x00010001;
	}

	//INSUploadLibraryFile
	//*************************************************************************************************
	INSUploadLibraryFile::INSUploadLibraryFile(const FileVO & fileBase, const QString & absolutePath)
		: INSUpLoad(fileBase, QString(), absolutePath)
	{
		m_transferType = 0x00010007;
	}


	//TransferOperatorAbstract
	//*************************************************************************************************
	TransferOperatorAbstract::TransferOperatorAbstract(INSFileTransfer * p_transfer, QObject * parent)
		:m_transferObj(p_transfer), INSHttpRequest(parent)
	{
	}

	void TransferOperatorAbstract::SlotRequestError(QNetworkReply::NetworkError netError)
	{
		qWarning() << "Http request error. error type: " << netError;
		qWarning() << "error code: " << m_errorMsg.first << " error msg: " << m_errorMsg.second;
	}


	void TransferOperatorAbstract::SlotRequestFinished()
	{
	    deleteLater();
		qInfo() << "Http request finished.";
	}

	void TransferOperatorAbstract::GenerateTransPostRequestWithJson(const QJsonObject & jsonObj, const QString & reqPath)
	{
		INSHttpRequest::CreatePostRequestWithJson(m_transferObj->m_fileRepoInfo.ip, QString::number(m_transferObj->m_fileRepoInfo.port), reqPath, QJsonDocument(jsonObj).toJson(), true);
	}

	void TransferOperatorAbstract::FinishedOperator(INS::INSFileTransferStep finishedStep, bool deleteRecord)
	{
		m_transferObj->m_fileRecorder->SetRecordFileDeleted(deleteRecord);
		m_transferObj->m_step = finishedStep;
	}

	void TransferOperatorAbstract::ManuaAbortNetworkReply()
	{
		if (!m_netReply.isNull() && !m_netReply->isFinished())
			m_netReply->abort();
	}


	//InitUploadInfoOperator
	//*************************************************************************************************
	InitUploadInfoOperator::InitUploadInfoOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent)
	{
	}

	void InitUploadInfoOperator::RunRequest()
	{
		QJsonObject reqParam{ { QString("token"),m_transferObj->m_fileRepoInfo.token },
		{ QString("filename"),m_transferObj->m_file.name },
		{ QString("filesize"),m_transferObj->m_fileHandle.size() },
		{ QString("checkcode"),m_transferObj->m_file.checkCode } };

		TransferOperatorAbstract::GenerateTransPostRequestWithJson(reqParam, strInterfaceInitUploadInfo);
	}

	void InitUploadInfoOperator::SlotReadyread(QByteArray & byteArray)
	{
	    if (m_transferObj.isNull())
            return;

		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);
		if (retResult.first == 0)
		{
			assert(jsonObj.contains("retdata"));
			m_transferObj->m_fileInfoInFileServer.m_fileId = jsonObj.value("retdata").toString();

			m_transferObj->m_fileRecorder->SetFileId(m_transferObj->m_fileInfoInFileServer.m_fileId);

			m_transferObj->RunStepFunc(INSFileTransferStep::enumCheckFileState);
		}
		else
		{
			qWarning() << "init upload error." << " code: " << retResult.first << " message: " << retResult.second;
		}
	}


	//CheckFileStateOperator
	//***********************************************************************************************************
	CheckFileStateOperator::CheckFileStateOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent)
	{
	}

	void CheckFileStateOperator::RunRequest()
	{
		QJsonObject reqParam{ { QString("token"), m_transferObj->m_fileRepoInfo.token },
			{ QString("fileid"), m_transferObj->m_fileInfoInFileServer.m_fileId} };

		TransferOperatorAbstract::GenerateTransPostRequestWithJson(reqParam, strInterfaceGetUploadState);
	}

	void CheckFileStateOperator::SlotReadyread(QByteArray & byteArray)
	{
	    if (m_transferObj.isNull())
            return;

		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);
		if (retResult.first == 0)
		{
			QJsonObject dataJson = jsonObj.value("retdata").toObject();
			assert(dataJson.contains("status"));

			qint32 fileStatus = dataJson.value("status").toInt();
			m_transferObj->m_fileInfoInFileServer.m_receivedLength = dataJson.value("received").toVariant().value<qint64>();
			RunCheckedStatus(fileStatus);
		}
		else
		{
			m_transferObj->SetFinished(retResult.first, retResult.second);
			qWarning() << "check upload state error. code: " << retResult.first << " msg: " << retResult.second;
		}
	}

	void CheckFileStateOperator::RunCheckedStatus(qint32 fileStatus)
	{
		switch (fileStatus)
		{
		case 0:
			qInfo() << "check status: 0. mean: uploading. url: " << m_netReply->url();
			m_transferObj->RunStepFunc(INSFileTransferStep::enumTransferData);
			break;
		case 1:
			qInfo() << "check status: 1. mean: finished. url: " << m_netReply->url();
			m_transferObj->StartWaitForResponTimer();
			m_transferObj->RunStepFunc(INSFileTransferStep::enumWaitForRespon);
			break;
		case -1:
			qWarning() << "check status: 1. mean: failed. url: " << m_netReply->url();
			m_transferObj->RunStepFunc(INSFileTransferStep::enumInitFileInfo);
			break;
		}
	}


	//TransferDataOperator
	//***********************************************************************************************************
	UploadFileOperator::UploadFileOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent)
	{
	}

	void UploadFileOperator::RunRequest()
	{
		QStringList reqParam;
		reqParam += QString("token=%1").arg(m_transferObj->m_fileRepoInfo.token);
		reqParam += QString("fileid=%1").arg(m_transferObj->m_fileInfoInFileServer.m_fileId);
		QString strUrl{ INSHttpRequest::GenerateHttpUrl(m_transferObj->m_fileRepoInfo.ip, QString::number(m_transferObj->m_fileRepoInfo.port), strInterfaceUploadChunk, reqParam) };

		QHttpPart dataPart;
		dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data;name=\"file\";filename=\"%1\"").arg(m_transferObj->m_file.name)));

		QByteArray fileData;
		bool readResult = m_transferObj->GetDataFromFile(fileData, m_transferObj->m_fileChunkSize, m_transferObj->m_fileInfoInFileServer.m_receivedLength);
		if (!readResult)
		{
			qWarning() << "get file data failed.";
			return;
		}
		dataPart.setBody(fileData);

		auto multiPart = new QHttpMultiPart(this);
		multiPart->setBoundary("helloJim");
		multiPart->append(dataPart);

		QNetworkRequest netReq(strUrl);
		netReq.setRawHeader("Content-Type", "multipart/form-data;boundary=helloJim");
		qint64 n_beginPos = m_transferObj->m_fileInfoInFileServer.m_receivedLength;
		QByteArray contentRange;
		contentRange += QString("bytes %1-%2/%3").arg(QString::number(n_beginPos), QString::number(n_beginPos + fileData.size() - 1), QString::number(m_transferObj->m_fileHandle.size()));
		netReq.setRawHeader("Content-Range", contentRange);
		qInfo() << "file range: " << contentRange;

		m_netReply = INSNETWORKHTTP->post(netReq, multiPart);

		ConnectReplySlot(m_netReply);
	}

	void UploadFileOperator::SlotReadyread(QByteArray & byteArray)
	{
		if(byteArray.size() <= 0 || m_transferObj.isNull())
			return;

		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);
		if (retResult.first == 0)
		{
			QJsonObject dataJson = jsonObj.value("retdata").toObject();
			m_transferObj->m_fileInfoInFileServer.m_receivedLength = dataJson.value("received").toVariant().value<qint64>();

			emit m_transferObj->SigTransLength(m_transferObj->m_fileInfoInFileServer.m_receivedLength);
			qInfo() << "send length : " << m_transferObj->m_fileInfoInFileServer.m_receivedLength;

			qint32 fileStatus = dataJson.value("status").toInt();
			RunCheckedStatus(fileStatus);
		}
		else
		{
			m_transferObj->SetFinished(retResult.first, retResult.second);
			qWarning() << "upload failed. code: " << retResult.first << " msg: " << retResult.second;
		}
	}

	void UploadFileOperator::RunCheckedStatus(qint32 fileStatus)
	{
		switch (fileStatus)
		{
		case 0:
			qInfo() << "uploading. status: 0. url: " << m_netReply->url();
			m_transferObj->RunStepFunc();
			break;
		case 1:
			qInfo() << "upload finished. status: 1. url: " << m_netReply->url();
				m_transferObj->StartWaitForResponTimer();
				FinishedOperator();
			break;
		case -1:
			qWarning() << "upload failed. status: -1. url: " << m_netReply->url();
				FinishedOperator();
			break;
		}
	}


	//CancelTransferOperator
	//************************************************************************************
	CancelTransferOperator::CancelTransferOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent)
	{
	}

	void CancelTransferOperator::RunRequest()
	{
		QJsonObject reqParam{ { QString("token"),m_transferObj->m_fileRepoInfo.token },
		{ QString("fileid"),m_transferObj->m_fileInfoInFileServer.m_fileId} };

		TransferOperatorAbstract::GenerateTransPostRequestWithJson(reqParam, strInterfaceCancelUpload);
	}

	void CancelTransferOperator::SlotReadyread(QByteArray & byteArray)
	{
        if (m_transferObj.isNull())
            return;

		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);
		if (retResult.first == 0)
		{
			qInfo() << "Cancel upload succeeded. code: " << retResult.first << " msg: " << retResult.second;
		}
		else
		{
			qWarning() << "Cancel upload failed. code: " << retResult.first << " msg: " << retResult.second;
		}
	}



	//DownloadFileOperator
	//************************************************************************************
	DownloadFileOperator::DownloadFileOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent), m_nextStep(INSFileTransferStep::enumNone)
	{
	}

	void DownloadFileOperator::RunRequest()
	{
		QJsonObject reqParam{ { QString("token"),m_transferObj->m_fileRepoInfo.token },
		{ QString("filepath"),m_transferObj->m_fileRepoInfo.path},
		{ QString("filename"), m_transferObj->m_fileRepoInfo.name} };

		QString strUrl{ INSHttpRequest::GenerateHttpUrl(m_transferObj->m_fileRepoInfo.ip, QString::number(m_transferObj->m_fileRepoInfo.port), strInterfaceDownloadFile) };
		QNetworkRequest netReq(strUrl);
		netReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

		qint64 receivedLength{ GetReceivedLength() };
		InitFileState(receivedLength);

		QByteArray contentRange{ GenerateContentRange(receivedLength) };
		if (!contentRange.isEmpty())
			netReq.setRawHeader("Range", contentRange);

		m_netReply = INSNETWORKHTTP->post(netReq, QJsonDocument(reqParam).toJson());

		ConnectReplySlot(m_netReply);

		qInfo() << "http request download file. file name: " << m_transferObj->m_fileAbsolutePath << "range: " << contentRange;
	}

	void DownloadFileOperator::SlotReadyread(QByteArray & byteArray)
	{
		if (m_transferObj.isNull() || m_transferObj->isFinished())
			return;

		int retStatus = m_netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
		if (retStatus == RETSTATUSSUCCEEDED || RETSTATUSSUCCEEDEDOTHER == retStatus)
			SaveFileData(byteArray);
		else
		{
			qWarning() << "download error . http status: " << retStatus;
			ParseAndReturnError(retStatus, byteArray);
		}
	}

	void DownloadFileOperator::SaveFileData(QByteArray &byteArray)
	{
		auto receivedLength = m_transferObj->m_fileHandle.write(byteArray);
		if (receivedLength == -1)
			return;

		m_transferObj->m_fileInfoInFileServer.m_receivedLength += receivedLength;

		if(receivedLength > 0)
            m_transferObj->m_fileRecorder->SetTransLength(m_transferObj->m_fileInfoInFileServer.m_receivedLength);

		if (m_transferObj->m_fileInfoInFileServer.m_receivedLength >= m_transferObj->m_fileRepoInfo.size)
		{
			m_transferObj->m_fileHandle.setFileTime(m_transferObj->m_file.lastModifyTime, QFileDevice::FileModificationTime);
			m_transferObj->m_fileHandle.setFileTime(m_transferObj->m_file.createTime, QFileDevice::FileBirthTime);

			m_transferObj->m_fileRecorder->SetRecordFileDeleted(true);
			if (m_nextStep == INSFileTransferStep::enumNone)
			{
				FinishedOperator(INSFileTransferStep::enumNone, true);
				m_transferObj->SetFinished(1, "download finished. type: succeeded");
			}
			else
				m_transferObj->RunStepFunc(m_nextStep);
		}
		else
			emit m_transferObj->SigTransLength(m_transferObj->m_fileInfoInFileServer.m_receivedLength);
	}

	void DownloadFileOperator::ParseAndReturnError(int errorStatus, QByteArray &byteArray)
	{
		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);

		FinishedOperator(INSFileTransferStep::enumNone, false);
		m_transferObj->SetFinished(retResult.first, retResult.second);
	}

	qint64 DownloadFileOperator::GetReceivedLength()
	{
		if (!m_transferObj->m_fileRecorder->isTransTypeEnqual(m_transferObj->m_transferType))
			return 0;

		qint64 fileSizeInRecord = m_transferObj->m_fileRecorder->GetTransLength();
        return fileSizeInRecord == m_transferObj->m_fileHandle.size() ? fileSizeInRecord : 0;
	}

	void DownloadFileOperator::InitFileState(qint64 n_seek)
	{
		m_transferObj->m_fileHandle.resize(n_seek);
		m_transferObj->m_fileHandle.seek(n_seek);
		m_transferObj->m_fileInfoInFileServer.m_receivedLength = n_seek;
	}

	QByteArray DownloadFileOperator::GenerateContentRange(qint64 n_received)
	{
		if (n_received == 0)
			return QByteArray();

		QString contentRange("bytes=");
		contentRange.append(QString::number(n_received) + "-");
		return contentRange.toStdString().c_str();
	}

	void DownloadFileOperator::SlotRequestFinished()
	{
        if (m_transferObj.isNull())
            return;

        m_transferObj->m_fileHandle.close();
		TransferOperatorAbstract::SlotRequestFinished();
	}


	//UploadTinyFileOperator
	//***************************************************************************************************
	UploadTinyFileOperator::UploadTinyFileOperator(INSFileTransfer * p_transfer, QObject * parent)
		:TransferOperatorAbstract(p_transfer, parent)
	{
	}

	void UploadTinyFileOperator::RunRequest()
	{
		QStringList reqParam;
		reqParam += QString("token=%1").arg(m_transferObj->m_fileRepoInfo.token);
		reqParam += QString("filename=%1").arg(QString(QUrl::toPercentEncoding(m_transferObj->m_file.name)));
		reqParam += QString("filesize=%1").arg(m_transferObj->m_file.size);
		reqParam += QString("checkcode=%1").arg(m_transferObj->m_file.checkCode);
		QString strUrl{ INSHttpRequest::GenerateHttpUrl(m_transferObj->m_fileRepoInfo.ip, QString::number(m_transferObj->m_fileRepoInfo.port), strInterfaceUploadTinyFile, reqParam) };

		QHttpPart dataPart;
		dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data;name=\"file\";filename=\"%1\"").arg(m_transferObj->m_file.name)));

		QByteArray fileData;
		bool readResult = m_transferObj->GetDataFromFile(fileData);
		if (!readResult)
		{
			qWarning() << "get file data failed.";
			return;
		}
		dataPart.setBody(fileData);

		auto multiPart = new QHttpMultiPart(this);
		multiPart->setBoundary("helloJim");
		multiPart->append(dataPart);

		QNetworkRequest netReq(strUrl);
		netReq.setRawHeader("Content-Type", "multipart/form-data;boundary=helloJim");
		m_netReply = INSNETWORKHTTP->post(netReq, multiPart);

		ConnectReplySlot(m_netReply);
	}

	void UploadTinyFileOperator::SlotReadyread(QByteArray & byteArray)
	{
		if(byteArray.size() <= 0 || m_transferObj.isNull())
			return;

		QJsonObject jsonObj;
		auto retResult = m_transferObj->GetValidJsonFromByteArray(byteArray, jsonObj);
		if (retResult.first == 0)
		{
			QJsonObject dataJson = jsonObj.value("retdata").toObject();
			m_transferObj->m_fileInfoInFileServer.m_receivedLength = dataJson.value("received").toVariant().value<qint64>();

			qInfo() << "send length : " << m_transferObj->m_fileInfoInFileServer.m_receivedLength;

			qint32 fileStatus = dataJson.value("status").toInt();
			RunCheckedStatus(fileStatus);
		}
		else
		{
			m_transferObj->SetFinished(retResult.first, retResult.second);
			qWarning() << "upload failed. code: " << retResult.first << " msg: " << retResult.second;
		}
	}

	void UploadTinyFileOperator::RunCheckedStatus(qint32 fileStatus)
	{
		switch (fileStatus)
		{
		case 1:
			qInfo() << "upload finished. status: 1. url: " << m_netReply->url();
			break;
		case -1:
			qWarning() << "upload failed. status: -1. url: " << m_netReply->url();
			break;
		}
		m_transferObj->StartWaitForResponTimer();
        FinishedOperator(INSFileTransferStep::enumWaitForRespon, true);
    }


}

