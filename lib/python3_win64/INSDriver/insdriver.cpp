#include "insdriver.h"
#include "insnetwork.h"
#include "inslogin.h"
#include "inscommonhandle.h"
#include "insnotification.h"
#include "inssetting.h"

namespace INS_INTERFACE {

    INSDRIVER_EXPORT QString jsonRequest(int serviceId, QString &queryParam) {
		JsonRequest<QString> jsonRequest(serviceId, queryParam);
		jsonRequest.WaitForFinished();
        return jsonRequest.getRecvData();
    }

    INSDRIVER_EXPORT MessageInfo GetClientUpdateServerPath(QString &path) {
        INSCommonRequest<QString> commonRequest(352, 0);
        commonRequest.WaitForFinished();
        path = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT void SetNotificationCallback(std::function<void(QString)> p_callback) {
        static INSNotificationListener notificationListener;
        notificationListener.SetCallbackFunc(p_callback);
    }

    void SetLoginConfilctCallback(std::function<void(QString)> p_callback)
    {
        static INSLoginConflictListener loginConflictListener;
        loginConflictListener.SetCallbackFunc(p_callback);
    }

    //日志业务 通过查询参数查询日志
    INSDRIVER_EXPORT MessageInfo GetLogs(QList<LogInfoVO> &logs, LogBusParams &logParams) {
        INSCommonRequest<QList<LogInfoVO>> commonRequest(99, logParams);
        commonRequest.WaitForFinished();
        logs = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT qint32 GetAvatarInfo(Avatar &avatar) {return 0;}

    INSDRIVER_EXPORT qint32 InsertAvatarInfo(const Avatar Iavatar) {return 0;}

    INSDRIVER_EXPORT qint32 UpdateAvatarInfo(const Avatar Uavatar) {return 0;}

    INSDRIVER_EXPORT qint32 GetProjectTaskDateByProjectId(qint32 projectId,ProjectTaskInfo &pti) {
        INSCommonRequestRetInt<ProjectTaskInfo> commonRequest(654, projectId);
        commonRequest.WaitForFinished();
        pti = commonRequest.getRecvData();
        return commonRequest.getRetValue();
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
        std::function<void()> p_func{nullptr};
        if (bEnable) {
            p_func = std::bind(&INS::INSLogin::ReConnectThenLogin);
            INS::INSLogin::m_reloginTimeout = secNum;
        }
        INSNETWORK->SetReConnectFuncPointer(p_func);
    }

    INSDRIVER_EXPORT void SetAppServerNetworkStatusSig(std::function<void(bool)> callbackSig) {
        if (callbackSig) {
            INSNETWORK->connect(INSNETWORK, &INSNetwork::SigAppServerSocketStatus, callbackSig);
            INSLogin::LoginStatusCallback = callbackSig;
        }
    }

    INSDRIVER_EXPORT qint32
    Login(const QString &username, const QString &password, bool &normalRole, const QString &type) {
        INSLogin login(username, password, type);
		login.WaitForFinished();
        normalRole = login.m_normalRole;
        return login.m_return_value;
    }

    INSDRIVER_EXPORT qint32 Logout() {
        INSCommonRequest<qint32> commonRequest(110);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue().code;
    }

    INSDRIVER_EXPORT qint32 ActivateAccount(const QString &username, const QString &password) {
        INSActivateAccount resetpassword(username, password);
		resetpassword.WaitForFinished();
        return resetpassword.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetSysVersion(QString &version) {return 0;}

    INSDRIVER_EXPORT qint32 GetInboxList(QList<SelectInboxEntity> &reInlist) {return 0;}

    INSDRIVER_EXPORT qint32 GetOutboxList(QMap<qint32, SelectSendboxEntity> &reoutlist) {return 0;}

    INSDRIVER_EXPORT qint32 GetInMsg(const qint32 msgID, MailobjEntity &remsg) {return 0;}

    INSDRIVER_EXPORT qint32 GetSentMsg(const qint32 msgID, MailobjEntity &remsg) {return 0;}

    INSDRIVER_EXPORT qint32 SentMsg(const MailobjEntity &mail) {return 0;}

    INSDRIVER_EXPORT qint32 DeleteMsg(const MailListEntity &maillist) {return 0;}


    //Worklog模块
    INSDRIVER_EXPORT qint32 CreateWorklog(SimpleWorklog &worklog) {
        INSCommonRequestRetInt<SimpleWorklog> commonRequest(702, worklog);
        commonRequest.WaitForFinished();
        worklog = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT qint32 UpdateWorklog(SimpleWorklog &worklog) {
        INSCommonRequestRetInt<SimpleWorklog> commonRequest(703, worklog);
        commonRequest.WaitForFinished();
        worklog = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }


    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, QList<SimpleWorklog> &worklogs) {
        INSCommonRequestRetInt<QList<SimpleWorklog>> commonRequest(700, publisherId);
        commonRequest.WaitForFinished();
        worklogs = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }


    INSDRIVER_EXPORT qint32 GetWorklogById(qint32 publisherId, const QDateTime &startTime, const QDateTime &endTime,
                                           QList<SimpleWorklog> &worklogs) {
        INSCommonRequestRetInt<QList<SimpleWorklog>>
                request(701, publisherId, startTime, endTime);
        request.WaitForFinished();
        worklogs = request.getRecvData();
        return request.getRetValue();
    }


    //INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id, Notification &no) {
    //    INSCommonRequestRetInt<Notification>
    //            request(760, recv_id, no);
    //    request.WaitForFinished();
    //    no = request.getRecvData();
    //    return request.getRetValue();
    //}

	INSDRIVER_EXPORT qint32 UpdateNotificationStatus(qint32 recv_id) 
	{
		INSCommonRequestRetInt<NotificationMessage>
			request(760, recv_id);
		request.WaitForFinished();
		return request.getRetValue();
	}


    //INSDRIVER_EXPORT qint32 GetInboxNofitication(qint32 recipient_id, qint32 beg, qint32 offset,
    //                                             QList<Notification> &nos) {
    //    INSCommonRequestRetInt<QList<Notification>>
    //            request(761, recipient_id, beg, offset);
    //    request.WaitForFinished();
    //    nos = request.getRecvData();
    //    return request.getRetValue();
    //}

	INSDRIVER_EXPORT qint32 GetNofitications(
		qint32 recipient_id, 
		QList<NotificationMessage>& nos, 
		qint32 category,
		qint32 notificationID) 
	{
		INSCommonRequestRetInt<QList<NotificationMessage>>
			request(761, recipient_id, category, notificationID);
		request.WaitForFinished();
		nos = request.getRecvData();
		return request.getRetValue();
	}

	INSDRIVER_EXPORT qint32 GetNofiticationOverview(
		qint32 recipient_id, 
		QMap<qint32, qint32>& data)
	{
		INSCommonRequestRetInt<QMap<qint32, qint32>>
			request(762, recipient_id);
		request.WaitForFinished();
		//request.m_lock.lock();
		data = request.getRecvData();
		return request.getRetValue();
	}

    INSDRIVER_EXPORT MessageInfo GetUnreadMsgAmount(qint32 &amount) {
        INSCommonRequest<qint32> request(763, 0);
        request.WaitForFinished();
        amount = request.getRecvData();
        return request.getRetValue();
    }

    //INSDRIVER_EXPORT qint32 SendUserNofitication(Notification &no) {
    //    INSCommonRequestRetInt<Notification> request(762, no);
    //    request.WaitForFinished();
    //    no = request.getRecvData();
    //    return request.getRetValue();
    //}

    //holiday
    MessageInfo CreateHolidayTemplate(INQHolidayTemplate &holidayTemplate) {
        INSCommonRequest<INQHolidayTemplate> request(5302, holidayTemplate);
        request.WaitForFinished();
        holidayTemplate = request.getRecvData();
        return request.getRetValue();
    }

    MessageInfo EditHolidayTemplate(INQHolidayTemplate &holidayTemplate) {
        INSCommonRequest<INQHolidayTemplate> request(5303, holidayTemplate);
        request.WaitForFinished();
        holidayTemplate = request.getRecvData();
        return request.getRetValue();
    }

    MessageInfo GetAllHolidays(QList<INQHolidayTemplate> &holidays) {
        INSCommonRequest<QList<INQHolidayTemplate>> request(5301);
        request.WaitForFinished();
        holidays = request.getRecvData();
        return request.getRetValue();
    }

    MessageInfo GetAllHolidaysInNewlyYear(QList<INQHolidayTemplate> &holidays) {
        INSCommonRequest<QList<INQHolidayTemplate>> request(5300);
        request.WaitForFinished();
        holidays = request.getRecvData();
        return request.getRetValue();
    }

    MessageInfo DeleteHolidayTemplate(qint32 templateId) {
        INSCommonRequest<qint32> request(5304, templateId);
        request.WaitForFinished();
        return request.getRetValue();
    }
};
