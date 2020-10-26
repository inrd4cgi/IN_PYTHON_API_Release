#pragma once
#include "insrequest.h"

namespace INS
{
	//获取文件服务器根目录列表
	class INSGetRootDirs : public INSRequest
	{
	public:
		INSGetRootDirs();
		~INSGetRootDirs() {};

		QList<INFileServerRoot> m_root_dirs;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};


	//获取项目列表
	class INSGetProjectFiles : public INSRequest
	{
	public:
		INSGetProjectFiles();
		~INSGetProjectFiles() {};

		QList<INProjectFile> m_projects;
		qint32 m_return_value = 0;
		void Process(const QByteArray&);
	};
};




