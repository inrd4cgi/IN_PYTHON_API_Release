#include "insdrivertransinterface.h"

#include "inscommonhandle.h"
#include "insfiletransfer.h"
#include "insdatastructure.h"
#include "insdriver_global.h"

#include "insfiletransfer.h"
#include "instasktransfer.h"

namespace INS_INTERFACE {
    INSDRIVER_EXPORT qint32 GetFileFromId(FileVO &fileBase, qint32 fileId) {
        INSCommonRequest<FileVO> commonRequest(325, fileId);
        commonRequest.WaitForFinished();
        fileBase = commonRequest.getRecvData();
        return commonRequest.getRetValue().code;
    }

    INSDRIVER_EXPORT qint32 GetFilePathFromId(const qint32 fileId, QString &filePath) {
        FileVO file;
        if (1 != GetFileFromId(file, fileId)) {
            return 0;
        }
        filePath = file.directory;
        return 1;
    }

    INSDRIVER_EXPORT qint32 GetProjectFiles(QList<ProjectRootFolderVO> &projects) {
        INSCommonRequest<QList<ProjectRootFolderVO>> commonRequest(312, 0);
        commonRequest.WaitForFinished();
        projects = commonRequest.getRecvData();
        return commonRequest.getRetValue().code;
    }

    INSDRIVER_EXPORT MessageInfo GetFolderByParams(FolderVO &folderbase, FolderSearchParam &param) {
        INSCommonRequest<FolderVO> commonRequest(303, param);
        commonRequest.WaitForFinished();
        folderbase = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT qint32 GetFolder(FolderVO &folderbase, QMap<qint32, FileVO> &files) {
        FolderSearchParam param;
        param.folderId = folderbase.folderId;
        auto ret = GetFolderByParams(folderbase, param);
        files = folderbase.files;
        return ret.code;
    }

    INSDRIVER_EXPORT qint32 GetFileHistory(FileVO &filebase, QList<FileVersionVO> &file_histories) {
        auto ret = GetFileFromId(filebase, filebase.fileId);
        file_histories = filebase.fileVersions.values();
        return ret;
    }

    INSDRIVER_EXPORT qint32 ModifyFileStatus(FileVO &filebase) { return 0; }

    INSDRIVER_EXPORT qint32
    DeleteRecycles(const qint32 &project_id, const QList<qint32> &recycles, qint32 &code, qint32 &amount_files) { return 0; }

    INSDRIVER_EXPORT qint32 ComfirmDelete(const qint32 &ok, const qint32 &code) { return 0; }

    INSDRIVER_EXPORT MessageInfo CreateFolderOrEdit(FolderVO &folder) {
        INSCommonRequest<FolderVO> commonRequest(309, folder.parentId, folder.folderName);
        commonRequest.WaitForFinished();
        folder = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT qint32 CreateFolder(FolderVO &folder) {
        return CreateFolderOrEdit(folder).code;
    }

    INSDRIVER_EXPORT qint32 RenameFolder(FolderVO &folder, QMap<qint32, FileVO> &files) { return 0; }


    INSDRIVER_EXPORT qint32 SendFilesToRecycleBin(const QList<FileVO> &files) { return 0; }

    INSDRIVER_EXPORT qint32 SendFoldersToRecycleBin(const QList<FolderVO> &folders) { return 0; }

    INSDRIVER_EXPORT qint32
    RestoreRecycleBin(const qint32 &project_id, const QList<qint32> &items_id, QList<FileVO> &files,
                      qint32 &code) { return 0; }

    INSDRIVER_EXPORT qint32 ReplaceFiles(const qint32 &code, const qint32 &exit, const QList<FileVO> &files) { return 0; }

    INSDRIVER_EXPORT qint32 GetRecycleBin(const qint32 &project_id, QMap<qint32, INRecycleBinInfo> &recycle_bins) { return 0; }

    INSDRIVER_EXPORT INSDownLoad *DownLoad(const FileVO &file, const QString &rootDir) {
        return new INSDownLoad(file, rootDir);
    }

    INSDRIVER_EXPORT INSUpLoad *UpLoad(const FileVO &file, const QString &rootDir, const QString &AbsolutePath) {
        return new INSUpLoad(file, rootDir, AbsolutePath);
    }

    INSDRIVER_EXPORT INSUploadTinyFile *UpLoadTinyFile(const QString &filename, const QString &absolutePath) {
        FileVO fileBase;
        fileBase.name = filename;
        return new INSUploadTinyFile(fileBase, QString(), absolutePath);
    }

    INSDRIVER_EXPORT INSCheckIn *CheckIn(const FileVO &file, const QString &rootDir, const QString &AbsolutePath) {
        qDebug() << "rootDir == " << rootDir;
        qDebug() << "AbsolutePath == " << AbsolutePath;
        return new INSCheckIn(file, rootDir);
    }

    INSDRIVER_EXPORT INSCheckOut *CheckOut(const FileVO &file, const QString &rootDir) {
        return new INSCheckOut(file, rootDir);
    }


    INSUpLoadSourceReferenceFile *UploadSourceReferenceFile(qint32 sourceId, const QString &absolutePath, bool isAssetFlag)
    {
        FileVO fileBase;
        QFileInfo fileinfo(absolutePath);
        fileBase.name = fileinfo.fileName();
        return new INSUpLoadSourceReferenceFile(sourceId,fileBase,absolutePath,isAssetFlag);
    }

    INSDRIVER_EXPORT INSUploadPlaceHolders *UploadPlaceHolders(const FileVO &file, const QString &AbsolutePath) {
        return new INSUploadPlaceHolders(file, AbsolutePath);
    }

    INSDRIVER_EXPORT INSUpLoadUserAvatar *UploadUserAvatar(const FileVO &file, const QString &AbsolutePath) {
        return new INSUpLoadUserAvatar(file, AbsolutePath);
    }

    INSDRIVER_EXPORT INSUploadCommentFile *UploadCommentFile(const INSDataUploadComment &commentData) {
        FileVO fileBase;
        fileBase.name = commentData.name;
        return new INSUploadCommentFile(fileBase, commentData);
    }

    INSDRIVER_EXPORT INSUploadRequiredFile *
    UploadRequiredFile(const QString &filename, qint32 taskId, const QString &absolutePath) {
        FileVO fileBase;
        fileBase.name = filename;
        return new INSUploadRequiredFile(fileBase, taskId, absolutePath);
    }


    INSDRIVER_EXPORT INSUploadReferenceFile *
    UploadReferenceFile(const QString &filename, qint32 taskId, const QString &absolutePath) {
        FileVO fileBase;
        fileBase.name = filename;
        return new INSUploadReferenceFile(fileBase, taskId, absolutePath);
    }


    INSDRIVER_EXPORT INSUploadOutputFile *
    UploadOutputFile(const QString &filename, const QString &strDirectory, qint32 taskId, const QString &absolutePath) {
        FileVO fileBase;
        fileBase.name = filename;
        fileBase.directory = strDirectory;
        return new INSUploadOutputFile(fileBase, taskId, absolutePath);
    }


    INSDRIVER_EXPORT INSUploadLibraryFile *
    UploadLibraryFile(const QString &filename, const QString &strDirectory, const QString &absolutePath) {
        FileVO fileBase;
        fileBase.name = filename;
        fileBase.directory = strDirectory;
        return new INSUploadLibraryFile(fileBase, absolutePath);
    }

	INSDRIVER_EXPORT INSUploadSequenceTaskFile *
		UploadSequenceTaskFile(const QString &filename, qint32 taskId, const QString& absolutePath) {
		FileVO fileBase;
		fileBase.name = filename;
		return new INSUploadSequenceTaskFile(fileBase, taskId, absolutePath);
	}
};