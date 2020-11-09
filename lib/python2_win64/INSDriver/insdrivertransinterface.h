#pragma once

#include "insdatastructure.h"
#include "insdriver_global.h"

#include "insfiletransfer.h"
#include "instasktransfer.h"


namespace INS_INTERFACE
{

	INSDRIVER_EXPORT qint32 GetFileFromId(FileVO& fileBase, qint32 fileId);

	//根据文件的ID获取其对应的文件路径
	INSDRIVER_EXPORT qint32 GetFilePathFromId(const qint32 fileId, QString& filePath);

	//获取项目文件列表[projects]。
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetProjectFiles(QList<ProjectRootFolderVO>& projects);

    //qint32 folderId = 0;//若folderId不为0,表示根据文件夹id来获取文件夹
    //qint32 projectId = 0;//若项目id不为0,表示根据项目id来获取文件夹
    INSDRIVER_EXPORT MessageInfo	GetFolderByParams(FolderVO &folderbase, FolderSearchParam &param);

	//获取一个指定id的文件夹。要求[folderbase]中有项目id和文件夹id。[files]为文件夹下的文件列表。
	//返回说明：1==创建成功;0==权限不足;
	extern "C" INSDRIVER_EXPORT qint32 GetFolder(FolderVO &folderbase, QMap<qint32, FileVO> &files);

	//获取指定文件的历史版本列表。要求[filebase]中有文件id
	//返回说明：1==获取成功;0==获取失败;
	extern "C" INSDRIVER_EXPORT qint32 GetFileHistory(FileVO &filebase, QList<FileVersionVO> &file_histories);

	//修改文件[filebase]的状态。要求[filebase]中有文件的id，项目id以及文件的新状态。
	//返回说明：1==修改成功;0==没有权限;修改失败。
	extern "C" INSDRIVER_EXPORT qint32 ModifyFileStatus(FileVO &filebase);

	//删除回收站中的条目。要指明项目id[projectId]和回收站条目id列表[recycles]。参数[code]为业务id,执行成功时，会返回一个值。
	//返回说明：1==请求删除成功,这里还需要进一步确认,调用函数ComfirmDelete(),参数为对应的[code];0==没有权限;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 DeleteRecycles(const qint32& project_id, const QList<qint32>& recycles, qint32& code, qint32& amount_files);

	//回复服务器删除是否确认。ok==0表示取消删除，其余全为确定删除。[code]为调用DeleteRecycles时得到的关联码。
	//返回说明：1==删除完成;0==删除过程中出现错误;-1==删除已取消。
	extern "C" INSDRIVER_EXPORT qint32 ComfirmDelete(const qint32& ok, const qint32& code);

	//创建一个文件夹[folder]。要求[folder]有文件夹名，父级文件夹id。
	//返回说明：1==创建成功;0==没有权限;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 CreateFolder(FolderVO & folder);

	//暂时不提供编辑文件夹的功能，先占个坑
	//1:创建成功 folderName和parentId必填
	INSDRIVER_EXPORT MessageInfo CreateFolderOrEdit(FolderVO & folder);

	//修改文件夹[folder]名。要求[folder]有项目id，文件夹id，新的文件夹名。[files]为文件列表，用以接收文件夹返回的文件。
	//返回说明：1==修改成功;0==没有权限;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 RenameFolder(FolderVO & folder, QMap<qint32, FileVO> &files);


	//将文件[files]放入回收站。可以是多个，但要求是在同一个文件夹下。[files]中条目要求有文件id，文件夹id，项目id。
	//返回说明：1==成功放入回收站;0==权限不足;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 SendFilesToRecycleBin(const QList<FileVO>& files);

	//将文件夹[folders]放入回收站。可以是多个，但要求是在同一个父级文件夹下。[folders]中条目要求有文件夹id，项目id。
	//返回说明：1==成功放入回收站;0==权限不足;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 SendFoldersToRecycleBin(const QList<FolderVO>& folders);

	//从项目[projectId]的回收站中恢复回收站条目[items_id]。[files]用来接收冲突文件。当恢复后文件有冲突时，[code]会有一个值
	//此时[files]列出所有冲突的文件。此时客户端需要调用ReplaceFiles函数来决定跳过的文件。
	//返回说明：1==恢复成功;0==权限不足;-1==恢复的文件有冲突，需要客户端做replace/skip的选择;-2==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 RestoreRecycleBin(const qint32& project_id, const QList<qint32>& items_id, QList<FileVO>& files, qint32& code);

	//回复服务器要替换的文件列表.[code]为调用RestoreRecycleBin时产生的业务关联码。[exit]为是否放弃恢复。
	//[files]为要replace掉的文件,即删除掉当前文件，选用回收站中的文件。
	//返回说明：1==恢复成功;0==恢复失败。
	extern "C" INSDRIVER_EXPORT qint32 ReplaceFiles(const qint32& code, const qint32& exit, const QList<FileVO>& files);

	//获取项目[projectId]的回收站中的内容[recycle_bins]
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetRecycleBin(const qint32& project_id, QMap<qint32, INRecycleBinInfo>& recycle_bins);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 从文件服务器下载文件到本地
	 * \details
	 * \param[in] file 文件的id必填。其余可不填。
	 * \param[in] rootDir 下载的文件的文件夹路径
	 * \return INSDownload指针对象，通过该对象调用start函数启动下载业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSDownLoad* DownLoad(const FileVO& file, const QString& rootDir);
	//EventError信号参数说明：-1==数据出错，暂时无法下载;-2==读写文件时发生错误;-3==无法与文件服务器传输数据


	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传文件到文件服务器
	 * \details
	 * \param[in] file 存放文件信息的类。\n
	 *            - 文件并非初次上传时，需要填写文件id。
	 *            - file中的 name 是必填项。
	 *            - 其他参数看rootDir和AbsolutePath的填写情况。
	 * \param[in] rootDir 存放文件目录的根路径。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 - 为空 参数rootDir必填，参数file的filename和directory字段必填。
	 - 不为空 file对象只需要folderID和directory选一个填写就好
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUpLoad* UpLoad(const FileVO& file, const QString& rootDir, const QString& AbsolutePath = QString());
	//EventError信号参数说明：0==权限不足;-1==数据出错，暂时无法上传;-2==读写文件时发生错误;-3==无法与文件服务器传输数据

		/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传小文件到文件服务器，小文件的定义是文件大小不超过32MB的文件。
	 * \details
	 * \param[in] filename 需要记录在应用服务器的文件名。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUploadTinyFile指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadTinyFile* UpLoadTinyFile(const QString &filename, const QString& absolutePath);

	/*!
	 * \brief 上传文件到文件服务器
	 * \details
	 * \param[in] file 存放文件信息的类。文件并非初次上传时，需要填写文件id。其他参数看rootDir和AbsolutePath的填写情况。
	 * \param[in] rootDir 存放文件目录的根路径。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 - 为空 参数rootDir必填，参数file的filename和directory字段必填。
	 - 不为空 file对象只需要folderID和directory选一个填写就好
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSCheckIn* CheckIn(const FileVO& file, const QString& rootDir, const QString& AbsolutePath = QString());
	//EventError信号参数说明：0==权限不足;-1==数据出错，暂时无法上传;-2==读写文件时发生错误;-3==无法与文件服务器传输数据

	//从服务器check out文件[file]。[root_dir]为文件所在的映射根路径。
	//发起check out任务成功，返回一个check out句柄指针,调用者可以通过这个句柄控制访问check out信息。
	extern "C" INSDRIVER_EXPORT INSCheckOut* CheckOut(const FileVO& file, const QString& rootDir);
	//EventError信号参数说明：0==权限不足;-1==数据出错，暂时无法下载;-2==读写文件时发生错误;-3==无法与文件服务器传输数据

    /*!
     * \ingroup businessAPI_fileModule
     * \brief 上传资源文件的参考文件
     * \details
     * \param[in] sourceId 资产ID或者镜头ID
     * \param[in] AbsolutePath 被上传的文件的绝对路径。
     * \param[in] isAssetFlag 资产标志位，传入的sourceId是资产则置位true,镜头置位false。
     * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
     */

    extern "C" INSDRIVER_EXPORT INSUpLoadSourceReferenceFile *UploadSourceReferenceFile(qint32 sourceId,const QString &absolutePath,bool isAssetFlag);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 上传PlaceHolders文件
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadPlaceHolders *UploadPlaceHolders(const FileVO &file, const QString &AbsolutePath);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief 更新用户头像,需要用户头像文件信息和路径信息。
	 * \details
	 * \param[in] file 存放文件信息的类。
	 * \param[in] AbsolutePath 被上传的文件的绝对路径。
	 * \return INSUpLoad指针对象，通过这个对象调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUpLoadUserAvatar *UploadUserAvatar(const FileVO &file, const QString &AbsolutePath);

	/*!
	 * \brief 上传评论文件的函数。所有参数都要正确填写
	 * \details
	 * \param[in] commentData 评论文件的数据
	 * \return 返回INSUploadCommentFile对象,调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadCommentFile *UploadCommentFile(const INSDataUploadComment &commentData);

	/*!
	 * \brief 上传required file的函数
	 * \details
	 * \param[in] filename 为该文件被记录的名字
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadRequiredFile对象，调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadRequiredFile *UploadRequiredFile(const QString &filename, qint32 taskId, const QString& absolutePath);

	/*!
	 * \brief 上传reference file的函数
	 * \details
	 * \param[in] filename 为该文件被记录的名字
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadReferenceFile对象，调用start启动上传业务。业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadReferenceFile *UploadReferenceFile(const QString &filename, qint32 taskId, const QString& absolutePath);

	/*!
	 * \brief 上传output file的函数
	 * \details
	 * \param[in] fileName 为需要记录的文件名
	 * \param[in] strDirectory 为相对项目的相对路径，需要确保路径在服务器存在，否则会报错
	 * \param[in] taskId 为该文件所属的task
	 * \param[in] absolutePath 为该文件在本地存放的绝对路径
	 * \return 返回INSUploadOutputFile对象，调用start启动上传业务，业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadOutputFile *UploadOutputFile(const QString &filename, const QString& strDirectory, qint32 taskId, const QString& absolutePath);

	/*! 
	 * \brief 上传library文件的函数
	 * \details 
	 * \param[in] filename 需要记录在应用服务器的文件名 
	 * \param[in] strDirectory 相对项目的相对路径，文件的存放路径，如果路径不存在，则会自动在应用服务器创建改路径。
	 * \return 返回INSUploadOutputFile对象，调用start启动上传业务，业务结束后，需要手动删除。
	 */
	extern "C" INSDRIVER_EXPORT INSUploadLibraryFile *UploadLibraryFile(const QString &filename, const QString& strDirectory, const QString& absolutePath);



};