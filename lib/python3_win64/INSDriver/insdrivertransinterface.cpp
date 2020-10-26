#include "insdrivertransinterface.h"

#include "inspersonhandle.h"
#include "insrecycle.h"
#include "insproject.h"
#include "insfile.h"
#include "insfolder.h"
#include "insfiletransfer.h"
#include "insdatastructure.h"
#include "insdriver_global.h"

#include "insfiletransfer.h"
#include "instasktransfer.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT qint32 GetFileFromId(INFileBase &fileBase, qint32 fileId) {
		INSCommonRequest<INFileBase, qint32> commonRequest(325, fileId);
		commonRequest.WaitForFinished();
		fileBase = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	INSDRIVER_EXPORT qint32 GetFilePathFromId(const qint32 fileId, QString &filePath) {
		INFileBase file;
		if (1 != GetFileFromId(file, fileId)) {
			return 0;
		}
        filePath = file.directory;
		return 1;
	}


	INSDRIVER_EXPORT qint32 GetServerRootDirs(QList<INFileServerRoot> &root_dirs) {
		INSGetRootDirs getrootdirs;
		getrootdirs.WaitForFinished();
		root_dirs = getrootdirs.m_root_dirs;
		return getrootdirs.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetProjectFiles(QList<INProjectFile> &projects) {
		INSCommonRequest<QList<INProjectFile>, int> commonRequest(312, 0);
		commonRequest.WaitForFinished();
		projects = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

    INSDRIVER_EXPORT INQRespondInfo	GetFolderByParams(INFolderBase &folderbase, FolderParam &param) {
        INSCommonRequest<INFolderBase, FolderParam> commonRequest(303, param);
        commonRequest.WaitForFinished();
        folderbase = commonRequest.retData;
        return commonRequest.m_return_value;
    }

	INSDRIVER_EXPORT qint32 GetFolder(INFolderBase &folderbase, QMap<qint32, INFileBase> &files) {
		FolderParam param;
		param.folderId = folderbase.id;
		auto ret = GetFolderByParams(folderbase, param);
		files = folderbase.files;
		return ret.code;
	}

	INSDRIVER_EXPORT qint32 GetFileHistory(INFileBase &filebase, QList<INFileHistory> &file_histories) {
		auto ret = GetFileFromId(filebase, filebase.id);
		file_histories = filebase.version_list;
		return ret;
	}

	INSDRIVER_EXPORT qint32 ModifyFileStatus(INFileBase &filebase) {
		INSModifyFileStatus modify_file_status(filebase);
		modify_file_status.WaitForFinished();
		filebase = modify_file_status.m_file;
		return modify_file_status.m_return_value;
	}

	INSDRIVER_EXPORT qint32
		DeleteRecycles(const qint32 &project_id, const QList<qint32> &recycles, qint32 &code, qint32 &amount_files) {
		INSDeleteRecycles delete_recycles(project_id, recycles);
		delete_recycles.WaitForFinished();
		code = delete_recycles.m_code;
		amount_files = delete_recycles.m_amount_files;
		return delete_recycles.m_return_value;
	}

	INSDRIVER_EXPORT qint32 ComfirmDelete(const qint32 &ok, const qint32 &code) {
		INSComfirmDelete comfirm_delete(ok, code);
		comfirm_delete.WaitForFinished();
		return comfirm_delete.m_return_value;
	}

    INSDRIVER_EXPORT INQRespondInfo CreateFolderOrEdit(INFolderBase & folder) {
        INSCommonRequest<INFolderBase, QPair<qint32, QString>> commonRequest(309, qMakePair(folder.parent, folder.name));
        commonRequest.WaitForFinished();
        folder = commonRequest.retData;
        return commonRequest.m_return_value;
    }

	INSDRIVER_EXPORT qint32 CreateFolder(INFolderBase &folder) {
		return CreateFolderOrEdit(folder).code;
	}

	INSDRIVER_EXPORT qint32 RenameFolder(INFolderBase &folder, QMap<qint32, INFileBase> &files) {
		INSRenameFolder rename_folder(folder);
		rename_folder.WaitForFinished();
		folder = rename_folder.m_folder;
		files = rename_folder.m_files;
		return rename_folder.m_return_value;
	}


	INSDRIVER_EXPORT qint32 SendFilesToRecycleBin(const QList<INFileBase> &files) {
		INSSendFilesToRecycleBin send_file_to_recyclebin(files);
		send_file_to_recyclebin.WaitForFinished();
		return send_file_to_recyclebin.m_return_value;
	}

	INSDRIVER_EXPORT qint32 SendFoldersToRecycleBin(const QList<INFolderBase> &folders) {
		INSSendFoldersToRecycleBin send_folders_to_recyclebin(folders);
		send_folders_to_recyclebin.WaitForFinished();
		return send_folders_to_recyclebin.m_return_value;
	}

	INSDRIVER_EXPORT qint32
		RestoreRecycleBin(const qint32 &project_id, const QList<qint32> &items_id, QList<INFileBase> &files, qint32 &code) {
		INSRestoreRecycleBin restore_recycle_bin(project_id, items_id);
		restore_recycle_bin.WaitForFinished();
		files = restore_recycle_bin.m_files;
		code = restore_recycle_bin.m_code;
		return restore_recycle_bin.m_return_value;
	}

	INSDRIVER_EXPORT qint32 ReplaceFiles(const qint32 &code, const qint32 &exit, const QList<INFileBase> &files) {
		INSReplaceFiles replace_file(code, exit, files);
		replace_file.WaitForFinished();
		return replace_file.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetRecycleBin(const qint32 &project_id, QMap<qint32, INRecycleBinInfo> &recycle_bins) {
		INSGetRecycleBin get_recycle_bins(project_id);
		get_recycle_bins.WaitForFinished();
		recycle_bins = get_recycle_bins.m_recycle_bins;
		return get_recycle_bins.m_return_value;
	}

	INSDRIVER_EXPORT INSDownLoad *DownLoad(const INFileBase &file, const QString &rootDir) {
		return new INSDownLoad(file, rootDir);
	}

	INSDRIVER_EXPORT INSUpLoad *UpLoad(const INFileBase &file, const QString &rootDir, const QString& AbsolutePath) {
		return new INSUpLoad(file, rootDir, AbsolutePath);
	}

	INSDRIVER_EXPORT INSUploadTinyFile * UpLoadTinyFile(const QString & filename, const QString & absolutePath)
	{
		INFileBase fileBase;
		fileBase.name = filename;
		return new INSUploadTinyFile(fileBase, QString(), absolutePath);
	}

	INSDRIVER_EXPORT INSCheckIn *CheckIn(const INFileBase &file, const QString &rootDir, const QString& AbsolutePath) {
	    qDebug() << "rootDir == " << rootDir;
	    qDebug() << "AbsolutePath == " << AbsolutePath;
		return new INSCheckIn(file, rootDir);
	}

	INSDRIVER_EXPORT INSCheckOut *CheckOut(const INFileBase &file, const QString &rootDir) {
		return new INSCheckOut(file, rootDir);
	}

	INSDRIVER_EXPORT INSUploadPlaceHolders *UploadPlaceHolders(const INFileBase &file, const QString &AbsolutePath) {
		return new INSUploadPlaceHolders(file, AbsolutePath);
	}

	INSDRIVER_EXPORT INSUpLoadUserAvatar *UploadUserAvatar(const INFileBase &file, const QString &AbsolutePath) {
		return new INSUpLoadUserAvatar(file, AbsolutePath);
	}

	INSDRIVER_EXPORT INSUploadCommentFile * UploadCommentFile(const INSDataUploadComment & commentData)
	{
		INFileBase fileBase;
		fileBase.name = commentData.name;
		return new INSUploadCommentFile(fileBase, commentData);
	}

	INSDRIVER_EXPORT INSUploadRequiredFile * UploadRequiredFile(const QString & filename, qint32 taskId, const QString& absolutePath)
	{
		INFileBase fileBase;
		fileBase.name = filename;
		return new INSUploadRequiredFile(fileBase, taskId, absolutePath);
	}


	INSDRIVER_EXPORT INSUploadReferenceFile * UploadReferenceFile(const QString & filename, qint32 taskId, const QString& absolutePath)
	{
		INFileBase fileBase;
		fileBase.name = filename;
		return new INSUploadReferenceFile(fileBase, taskId, absolutePath);
	}


	INSDRIVER_EXPORT INSUploadOutputFile * UploadOutputFile(const QString & filename, const QString & strDirectory, qint32 taskId, const QString & absolutePath)
	{
		INFileBase fileBase;
		fileBase.name = filename;
		fileBase.directory = strDirectory;
		return new INSUploadOutputFile(fileBase, taskId, absolutePath);
	}


	INSDRIVER_EXPORT INSUploadLibraryFile * UploadLibraryFile(const QString & filename, const QString & strDirectory, const QString & absolutePath)
	{
		INFileBase fileBase;
		fileBase.name = filename;
		fileBase.directory = strDirectory;
		return new INSUploadLibraryFile(fileBase, absolutePath);
	}

};
