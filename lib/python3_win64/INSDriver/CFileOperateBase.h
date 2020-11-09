#ifndef CFILEOPERATEBASE_H
#define CFILEOPERATEBASE_H

#include <QString>

class QDateTime;

namespace NSCBasicClass
{
	class CFileOperateBase
	{
	public:
		CFileOperateBase() {};
		~CFileOperateBase() {};
		static void SetFileModifyTime(const QDateTime& modify_time, const QString& file_path);
	};

	
};
#endif // !CFILEOPERATEBASE_H
