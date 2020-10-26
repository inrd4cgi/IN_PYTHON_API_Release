#include "insdriver.h"
#include "insnetwork.h"
#include "inslogin.h"
#include "inspersonhandle.h"
#include "insdllteamhandle.h"
#include "insnotification.h"
#include "insdashboard.h"
#include "insdllgetsysversion.h"
#include "inssetting.h"

namespace INS_INTERFACE {

	INSDRIVER_EXPORT INQRespondInfo GetClientUpdateServerPath(QString& path) {
		INSCommonRequest<QString, qint32> commonRequest(352, 0);
		commonRequest.WaitForFinished();
		path = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT void SetNotificationCallback(std::function<void(const QByteArray&)> p_callback) {
		static INSNotificationListener notificationListener;
		notificationListener.SetCallbackFunc(p_callback);
	}


	//日志业务 通过查询参数查询日志
	INSDRIVER_EXPORT INQRespondInfo GetLogs(QList<INQLogInfo> &logs, INQGetLogBusParams &logParams) {
		INSCommonRequest<QList<INQLogInfo>, INQGetLogBusParams> commonRequest(99, logParams);
		commonRequest.WaitForFinished();
		logs = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	/*文件结构模板篇*/
	//创建文件结构模板,fileStrcTemplName和fileStructDetail非空,创建成功之后返回模板详情
	INSDRIVER_EXPORT INQRespondInfo CreateFileStructTempl(INFileStructTemplate &fileStructTempl) {
		INSCommonRequest<INFileStructTemplate, INFileStructTemplate> commonRequest(501, fileStructTempl);
		commonRequest.WaitForFinished();
		fileStructTempl = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//通过文件结构模板id获取文件结构模板,fileStrctTemplId非空
	INSDRIVER_EXPORT INQRespondInfo GetFileStructTempl(INFileStructTemplate &fileStructTempl) {
		INSCommonRequest<INFileStructTemplate, qint32> commonRequest(502, fileStructTempl.fileStrcTemplId);
		commonRequest.WaitForFinished();
		fileStructTempl = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//获取文件结构模板列表
	INSDRIVER_EXPORT INQRespondInfo GetFileStructTempls(QList<INFileStructTemplate> &fileStructTempls) {
		INSCommonRequest<QList<INFileStructTemplate>> commonRequest(503, 0);
		commonRequest.WaitForFinished();
		fileStructTempls = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//更新文件结构模板,成员变量均非空[名称按照需求不能修改]
	INSDRIVER_EXPORT INQRespondInfo UpdateFileStructTempl(INFileStructTemplate &fileStructTempl) {
		INSCommonRequest<INFileStructTemplate, INFileStructTemplate> commonRequest(504, fileStructTempl);
		commonRequest.WaitForFinished();
		fileStructTempl = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	INSDRIVER_EXPORT qint32 GetAvatarInfo(Avatar &avatar) {
		INSGetAvatarInfo avatarinfo(avatar);
		avatarinfo.WaitForFinished();
		avatar = avatarinfo.m_avatar;
		return avatarinfo.m_return_value;
	}

	INSDRIVER_EXPORT qint32 InsertAvatarInfo(const Avatar Iavatar) {
		INSInsertAvatarInfo iavatar(Iavatar);
		iavatar.WaitForFinished();
		return iavatar.m_return_value;
	}

	INSDRIVER_EXPORT qint32 UpdateAvatarInfo(const Avatar Uavatar) {
		INSUpdateAvatarInfo uavatar(Uavatar);
		uavatar.WaitForFinished();
		return uavatar.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTaskInfoFromProID(ProjectTaskInfo &pti) {
		INSGetTaskInfo taskinfo(pti);
		taskinfo.WaitForFinished();
		pti = taskinfo.m_pti;
		return taskinfo.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTaskStatusFromProID(ProjectTaskInfo &pti) {
		INSGetTaskStatus taskstatus(pti);
		taskstatus.WaitForFinished();
		pti = taskstatus.m_pti;
		return taskstatus.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTeamInfoFromProID(ProjectTaskInfo &pti) {
		INSGetTeamInfo teaminfo(pti);
		teaminfo.WaitForFinished();
		pti = teaminfo.m_pti;
		return teaminfo.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetMenFormProID(ProjectTaskInfo &pti) {
		INSGetMen meninfo(pti);
		meninfo.WaitForFinished();
		pti = meninfo.m_pti;
		return meninfo.m_return_value;
	}


	INSDRIVER_EXPORT bool ConnectToServer(const QString &hostaddress, const qint32 &port) {
		//连接到主服务器。用hostaddress作为连接id
		QString str_address(hostaddress);
		qint32 n_port(port);

		if (str_address.isNull())
			str_address = SETTING->value("server_address", "0.0.0.0").toString();

		if (n_port <= 0)
			n_port = SETTING->value("server_port", 6666).toInt();

		return INSNETWORK->ConnectToAppServer(str_address, n_port);
	}

	INSDRIVER_EXPORT void SetReconnectAndReLoginEnable(bool bEnable, int secNum) {
		std::function<void()> p_func{ nullptr };
		if (bEnable)
		{
			p_func = std::bind(&INS::INSLogin::ReConnectThenLogin);
			INS::INSLogin::m_reloginTimeout = secNum;
		}
		INSNETWORK->SetReConnectFuncPointer(p_func);
	}

	INSDRIVER_EXPORT void SetAppServerNetworkStatusSig(std::function<void(bool)> callbackSig)
	{
		if (callbackSig)
		{
            INSNETWORK->connect(INSNETWORK, &INSNetwork::SigAppServerSocketStatus, callbackSig);
			INSLogin::LoginStatusCallback = callbackSig;
		}
	}

	INSDRIVER_EXPORT qint32 Login(const QString &username, const QString &password, bool &normalRole, const QString &type) {
		INSLogin login(username, password, type);
		login.WaitForFinished();
		normalRole = login.m_normalRole;
		return login.m_return_value;
	}

    INSDRIVER_EXPORT qint32 Logout() {
        INSCommonRequest<qint32> commonRequest(110);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value.code;
	}

	INSDRIVER_EXPORT qint32 ActivateAccount(const QString &username, const QString &password) {
		INSActivateAccount resetpassword(username, password);
		resetpassword.WaitForFinished();
		return resetpassword.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetSysVersion(QString &version) {
		INSDLLGetSysVersion sysversion(version);
		sysversion.WaitForFinished();
		version = sysversion.m_ver;
		return sysversion.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetInboxList(QList<SelectInboxEntity> &reInlist) {
		INSInboxList getinboxlist;
		getinboxlist.WaitForFinished();
		reInlist = getinboxlist.m_inboxList;
		return getinboxlist.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetOutboxList(QMap<qint32, SelectSendboxEntity> &reoutlist) {
		INSOutboxList getoutboxlist;
		getoutboxlist.WaitForFinished();
		reoutlist = getoutboxlist.m_sentboxList;
		return getoutboxlist.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetInMsg(const qint32 msgID, MailobjEntity &remsg) {
		INSSelect1inMsg selmsg(msgID);
		selmsg.WaitForFinished();
		remsg = selmsg.m_inmailobj;
		return selmsg.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetSentMsg(const qint32 msgID, MailobjEntity &remsg) {
		INSSelect1outMsg selomsg(msgID);
		selomsg.WaitForFinished();
		remsg = selomsg.m_sentmailobj;
		return selomsg.m_return_value;
	}

	INSDRIVER_EXPORT qint32 SentMsg(const MailobjEntity &mail) {
		INSSendMsg sentmsg(mail);
		sentmsg.WaitForFinished();
		return sentmsg.m_return_value;
	}

	INSDRIVER_EXPORT qint32 DeleteMsg(const MailListEntity &maillist) {
		INSDeleteMsg delmsg(maillist);
		delmsg.WaitForFinished();
		return delmsg.m_return_value;
	}


	//Worklog模块
	INSDRIVER_EXPORT qint32 CreateWorklog(SimpleWorklog &worklog) {
		INVariadicRequest<0, SimpleWorklog, SimpleWorklog> commonRequest(702, worklog);
		commonRequest.WaitForFinished();
		worklog = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT qint32 UpdateWorklog(SimpleWorklog &worklog) {
		INVariadicRequest<0, SimpleWorklog, SimpleWorklog> commonRequest(703, worklog);
		commonRequest.WaitForFinished();
		worklog = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, QList<SimpleWorklog> &worklogs) {
		INVariadicRequest<0, QList<SimpleWorklog>, qint32> commonRequest(700, publisherId);
		commonRequest.WaitForFinished();
		worklogs = commonRequest.retData;
		return commonRequest.m_return_value;
	}


	INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, const QDateTime &startTime, const QDateTime &endTime,
		QList<SimpleWorklog> &worklogs) {
		INVariadicRequest<0, QList<SimpleWorklog>, qint32, QDateTime, QDateTime> request(701, publisherId, startTime,
			endTime);
		request.WaitForFinished();
		worklogs = request.retData;
		return request.m_return_value;
	}


	INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id, Notification &no) {
		INVariadicRequest<0, Notification, qint32, Notification> request(
			760, recv_id, no);
		request.WaitForFinished();
		no = request.retData;
		return request.m_return_value;
	}


	INSDRIVER_EXPORT qint32 GetInboxNofitication(qint32 recipient_id, qint32 beg, qint32 offset,
		QList<Notification> &nos) {
		INVariadicRequest<0, QList<Notification>, qint32, qint32, qint32> request(761,
			recipient_id,
			beg, offset);
		request.WaitForFinished();
		nos = request.retData;
		return request.m_return_value;
	}


	INSDRIVER_EXPORT qint32 SendUserNofitication(Notification &no) {
		INVariadicRequest<0, Notification, Notification> request(762,
			no);
		request.WaitForFinished();
		no = request.retData;
		return request.m_return_value;
	}

	//holiday
	INQRespondInfo CreateHolidayTemplate(INQHolidayTemplate &holidayTemplate)
    {
		INSCommonRequest<INQHolidayTemplate, INQHolidayTemplate> request(5302, holidayTemplate);
	    request.WaitForFinished();
		holidayTemplate = request.retData;
	    return request.m_return_value;
    }

	INQRespondInfo EditHolidayTemplate(INQHolidayTemplate &holidayTemplate)
    {
		INSCommonRequest<INQHolidayTemplate, INQHolidayTemplate> request(5303, holidayTemplate);
        request.WaitForFinished();
        holidayTemplate = request.retData;
        return request.m_return_value;
    }

	INQRespondInfo GetAllHolidays(QList<INQHolidayTemplate>& holidays)
    {
		INSCommonRequest<QList<INQHolidayTemplate>> request(5301);
        request.WaitForFinished();
	    holidays = request.retData;
        return request.m_return_value;
    }

	INQRespondInfo GetAllHolidaysInNewlyYear(QList<INQHolidayTemplate> &holidays)
    {
		INSCommonRequest<QList<INQHolidayTemplate>> request(5300);
	    request.WaitForFinished();
	    holidays = request.retData;
	    return request.m_return_value;
    }

	INQRespondInfo DeleteHolidayTemplate(qint32 templateId)
	{
		INSCommonRequest<qint32, qint32> request(5303, templateId);
		request.WaitForFinished();
		return request.m_return_value;
	}

};
