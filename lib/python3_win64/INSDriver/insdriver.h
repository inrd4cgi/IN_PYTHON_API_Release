#pragma once

#include "insdriver_global.h"
#include "insdriverworkflowinterface.h"
#include "insdriverassetshotinterface.h"
#include "insdriverprojectinterface.h"
#include "insdriverpermissioninterface.h"
#include "insdrivertaskinterface.h"
#include "insdrivertransinterface.h"
#include "insdriverpersoninterface.h"
#include "PyContainerWapper.h"
#include "insdatastructure.h"


namespace INS_INTERFACE
{
    INSDRIVER_EXPORT QString jsonRequest(int serviceId, QString &queryParam);

    //获取客户端更新文件的服务器路径
    INSDRIVER_EXPORT MessageInfo GetClientUpdateServerPath(QString& path);

	INSDRIVER_EXPORT void SetNotificationCallback(std::function<void(QString)> p_callback);

	INSDRIVER_EXPORT void SetLoginConfilctCallback(std::function<void(QString)> p_callback);


	//日志业务
	//参数说明：logParams.type = 1,表示查询类型为Log Status logParams.type = 2 表示查询类型为 Administrative actions
	//logParams.fromTime/logParams.toTime 为空表示该项不考虑,即该项条件没限制
	INSDRIVER_EXPORT MessageInfo GetLogs(QList<LogInfoVO>& logs, LogBusParams& logParams);

	//Dashboard篇
	//获取dashboard信息
	INSDRIVER_EXPORT qint32 GetAvatarInfo(Avatar& avatar);

	//新增dashboard信息
	INSDRIVER_EXPORT qint32 InsertAvatarInfo(const Avatar Iavatar);

	//更改dashboard信息
	INSDRIVER_EXPORT qint32 UpdateAvatarInfo(const Avatar Uavatar);

	//根据projectId获取信息
	INSDRIVER_EXPORT qint32 GetProjectTaskDateByProjectId(qint32 projectId, ProjectTaskInfo& pti);

	//使用IP地址[hostaddress]和端口[port]连接到服务器。IP和端口在配置文件中都有默认值。
	//返回说明：连接成功返回true,连接失败返回false。失败时会debug出失败原因。
	extern "C" INSDRIVER_EXPORT bool ConnectToServer(const QString&, const qint32& = 0);

	//设置是否使用断线重连的功能，默认情况下关闭。
	extern "C" INSDRIVER_EXPORT void SetReconnectAndReLoginEnable(bool bEnable, int secNum);

	//设置接收断开连接的槽函数.
	//参数callbackSig是一个Qt的信号。
	extern "C" INSDRIVER_EXPORT void SetAppServerNetworkStatusSig(std::function<void(bool)> callbackSig);

	//使用账号[username]，密码[password]登录系统。[type]为登录类型。登录类型有：JIMC;MAYAC;KATANAC;HOUDINIC;UE4C.默认为JIMC。
	//返回说明：1==成功登录;0==账号密码错误;-1==登录成功，但是账号未激活;-2==该账户在其他地方已经登录。
    extern "C" INSDRIVER_EXPORT qint32 Login(const QString& username, const QString& password, bool &normalRole, const QString& type = "JIMC");

	//为用户自己激活账号。[username],[password]为修改后的账号密码。
	//返回说明：1==激活成功;0==激活失败账号已被占用;-1==该账户无需激活。
	extern "C" INSDRIVER_EXPORT qint32 ActivateAccount(const QString& username, const QString& password);

	//获取客户端版本
	extern "C" INSDRIVER_EXPORT qint32 GetSysVersion(QString& version);

    INSDRIVER_EXPORT qint32 Logout();

	//消息系统功能
	INSDRIVER_EXPORT qint32 GetInboxList(QList<SelectInboxEntity>& reInlist);

	INSDRIVER_EXPORT qint32 GetOutboxList(QMap<qint32, SelectSendboxEntity>& reoutlist);

	INSDRIVER_EXPORT qint32 GetInMsg(const qint32 msgID, MailobjEntity& remsg);

	INSDRIVER_EXPORT qint32 GetSentMsg(const qint32 msgID, MailobjEntity& remsg);

	INSDRIVER_EXPORT qint32 SentMsg(const MailobjEntity& mail);

	INSDRIVER_EXPORT qint32 DeleteMsg(const MailListEntity& maillist);


	//Worklog模块
	INSDRIVER_EXPORT qint32 CreateWorklog(SimpleWorklog& worklog);

	INSDRIVER_EXPORT qint32 UpdateWorklog(SimpleWorklog& worklog);

	INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, QList<SimpleWorklog>& worklogs);
	
	INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, const QDateTime& startTime, const QDateTime& endTime, QList<SimpleWorklog>& worklogs);

	// Notification 部分 
	//INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id, Notification& no);
	INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id);

	//INSDRIVER_EXPORT qint32 SendUserNofitication(Notification& no);
		//INSDRIVER_EXPORT qint32 SendUserNofitication(Notification& no);

	INSDRIVER_EXPORT qint32 GetNofitications(
		qint32 recipient_id, 
		QList<NotificationMessage>& nos, 
		qint32 category,
		qint32 notificationID = 0);

	INSDRIVER_EXPORT qint32 GetNofiticationOverview(qint32 recipient_id, QMap<qint32, qint32>& data);

    INSDRIVER_EXPORT MessageInfo GetUnreadMsgAmount(qint32 &amount);

	//Holiday
	INSDRIVER_EXPORT MessageInfo CreateHolidayTemplate(INQHolidayTemplate& holidayTemplate);

	INSDRIVER_EXPORT MessageInfo EditHolidayTemplate(INQHolidayTemplate& holidayTemplate);

	INSDRIVER_EXPORT MessageInfo GetAllHolidays(QList<INQHolidayTemplate>& holidays);

	INSDRIVER_EXPORT MessageInfo GetAllHolidaysInNewlyYear(QList<INQHolidayTemplate> &holidays);

	INSDRIVER_EXPORT MessageInfo DeleteHolidayTemplate(qint32 templateId);
};