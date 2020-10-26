#pragma once
#include "insrequest.h"

namespace INS
{
	//请求删除回收站中的条目。
	class INSDeleteRecycles :public INSRequest
	{
	public:
		INSDeleteRecycles(const qint32 & project_id, const QList<qint32>& recycles);
		~INSDeleteRecycles() {};

		qint32 m_code = 0;
		qint32 m_amount_files = 0;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//回复确认删除
	class INSComfirmDelete :public INSRequest
	{
	public:
		INSComfirmDelete(const qint32 & ok, const qint32& code);
		~INSComfirmDelete() {};

		qint32 m_return_value = 1;
		void Process(const QByteArray&);
	};

	//将文件放入回收站
	class INSSendFilesToRecycleBin :public INSRequest
	{
	public:
		INSSendFilesToRecycleBin(const QList<INFileBase>& files);
		~INSSendFilesToRecycleBin() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//将文件夹放入回收站
	class INSSendFoldersToRecycleBin :public INSRequest
	{
	public:
		INSSendFoldersToRecycleBin(const QList<INFolderBase>& folders);
		~INSSendFoldersToRecycleBin() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//恢复回收站中的条目
	class INSRestoreRecycleBin :public INSRequest
	{
	public:
		INSRestoreRecycleBin(const qint32& project_id, const QList<qint32>& items_id);
		~INSRestoreRecycleBin() {};

		qint32 m_return_value = 0;
		qint32 m_code;
		QList<INFileBase> m_files;
		void Process(const QByteArray&);
	};

	//回复服务器要替换掉的文件。
	class INSReplaceFiles :public INSRequest
	{
	public:
		INSReplaceFiles(const qint32 & code, const qint32 & exit, const QList<INFileBase>& files);
		~INSReplaceFiles() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};

	//获取回收站内容
	class INSGetRecycleBin :public INSRequest
	{
	public:
		INSGetRecycleBin(const qint32 & project_id);
		~INSGetRecycleBin() {};

		qint32 m_return_value = 0;
		QMap<qint32, INRecycleBinInfo> m_recycle_bins;
		void Process(const QByteArray&);
	};
}
