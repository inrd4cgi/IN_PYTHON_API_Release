#pragma once
#include "insrequest.h"

namespace INS
{
	//获取指定id的文件夹。
	class INSGetFolder : public INSRequest
	{
	public:
		INSGetFolder(INFolderBase &folderbase);
		~INSGetFolder() {};

		INFolderBase m_folder;
		QMap<qint32, INFileBase> m_files;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//创建一个文件夹
	class INSCreateFolder : public INSRequest
	{
	public:
		INSCreateFolder(const INFolderBase &);
		~INSCreateFolder() {};

		INFolderBase m_folder;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//重命名文件夹INSRenameFolder
	class INSRenameFolder : public INSRequest
	{
	public:
		INSRenameFolder(const INFolderBase & folder);
		~INSRenameFolder() {};

		INFolderBase m_folder;
		QMap<qint32, INFileBase> m_files;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};
};

