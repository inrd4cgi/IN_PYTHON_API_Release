#include "inssetting.h"

#include <QCoreApplication>

namespace INS
{
	INSSetting* INSSetting::gp_instance = Q_NULLPTR;

	/**************************************************************************************************
	Description:构造函数
	**************************************************************************************************/
	INSSetting::INSSetting(const QString& path, QSettings::Format format)
		:QSettings(path, format) {

	}

	/**************************************************************************************************
	Description:获取单例实例指针
	**************************************************************************************************/
	INSSetting* INSSetting::GetInstance()
	{
		if (gp_instance == Q_NULLPTR)
		{
			QString path = qApp->applicationDirPath() + "/inssetting.ini";
			QSettings::Format format = QSettings::IniFormat;
			gp_instance = new INSSetting(path, format);
			gp_instance->setValue("insdriver:","insdriver");
		}
		return gp_instance;
	};
};