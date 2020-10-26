#include "CFileOperateBase.h"
#include <QDateTime>
#include <time.h>
#include <QDebug>
#include <string>


#ifdef Q_OS_WIN
#include <windows.h>
#include <sys/utime.h>
#else
#include <utime.h>
#endif // Q_OS_WIN

//这个类用于修改文件的基本信息，大多与平台挂钩。
namespace NSCBasicClass
{
	//设置文件的最后修改时间。[file_path]为文件的绝对路径。[modify_time]为文件的最后修改日期和时间。
	void CFileOperateBase::SetFileModifyTime(const QDateTime & modify_time, const QString & file_path)
	{
		if (file_path.isEmpty() || !modify_time.isValid() || modify_time.isNull())
		{
			qCritical() << "Please check you input Time or file_path is correct!";
			return;
		}
		int fYear = modify_time.date().year() - 1900;
		int fMonth = modify_time.date().month() - 1;
		int fDay = modify_time.date().day();
		int fHour = modify_time.time().hour();
		int fMinute = modify_time.time().minute();
		int fSec = modify_time.time().second();

		struct tm tmf = { 0 };
		tmf.tm_year = fYear;
		tmf.tm_mon = fMonth;
		tmf.tm_mday = fDay;
		tmf.tm_hour = fHour;
		tmf.tm_min = fMinute;
		tmf.tm_sec = fSec;
		tmf.tm_isdst = 0;
#ifdef Q_OS_WIN
		struct _utimbuf ut;
#else
		struct utimbuf ut;
#endif
		ut.modtime = mktime(&tmf);
		ut.actime = mktime(&tmf);

		//使用标准库的string，以及toLocal8Bit()解决中文乱码问题
		auto fileNameByteArray = file_path.toLocal8Bit();
        std::string file_name(fileNameByteArray.constData(), fileNameByteArray.length());

#ifdef Q_OS_WIN
		if (_utime(file_name.c_str(), &ut) == -1)
#else
		if (utime(file_name.c_str(), &ut) == -1)
#endif
			qDebug() << "file modified_datetime modify failed!";
		else
			qDebug() << "file modified_datetime modified!";
	}
}