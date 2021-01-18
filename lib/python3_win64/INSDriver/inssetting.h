//定义配置文件类
//Note that the Windows registry and INS files use case-insensitive keys
#pragma once
#include <QSettings>

#define SETTING INSSetting::GetInstance()
namespace INS
{
	class INSSetting :public QSettings
	{
	public:
		static INSSetting* GetInstance();
	private:
		static INSSetting* gp_instance;

		//构造函数私有化
		INSSetting(const QString& path, QSettings::Format format);
		INSSetting() {};
		~INSSetting() {};

		//把复制构造函数和=操作符也设为私有,防止被复制
		INSSetting(const INSSetting&) {};
		INSSetting& operator=(const INSSetting&) {};
	};
};