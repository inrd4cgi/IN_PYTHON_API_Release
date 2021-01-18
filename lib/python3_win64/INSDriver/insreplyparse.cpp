#include "insreplyparse.h"
#include "insrequest.h"
#include "insdriver_global.h"
#include "insdriver.h"
#include <QtConcurrent>

namespace INS
{

	INSReplyParse* INSReplyParse::gp_instance = Q_NULLPTR;

	/**************************************************************************************************
	Description: 构造函数,已被私有化。
	**************************************************************************************************/
	INSReplyParse::INSReplyParse(QObject *parent)
		: QObject(parent)
	{

	}

	/**************************************************************************************************
	Description:INSNetwork为单例，不允许有多个出现。单例模式下获取实例函数。
	**************************************************************************************************/
	INSReplyParse * INSReplyParse::GetInstance()
	{
		if (gp_instance == Q_NULLPTR)
			gp_instance = new INSReplyParse(0);
		return gp_instance;
	}

	/**************************************************************************************************
	Description:添加一个服务器回复数据[data]，从线程池mp_threadpool中获取一个线程进行处理。
	**************************************************************************************************/
	void INSReplyParse::AppendAReply(QByteArray & data)
	{
		QDataStream in(&data, QIODevice::ReadOnly);
		in.setVersion(STREAM_VERSION);
		qint32 request_id;
		in >> request_id;
		//若是心跳包
		if (-2020 == request_id) {
			//回复服务端
			QByteArray senddata;
			QDataStream out(&senddata, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_5_8);
			//requestId为-2020为心跳包
			out << -2020;
			INSNETWORK->SendDataToAppServer(senddata);
			return;
		}

		data.remove(0, 4);
		INSRequest* p_request = INSRequest::GetRequest(request_id);
		if (p_request != Q_NULLPTR)
		{
			//p_request->Process(data);
			p_request->Process(data);
			if (p_request->m_finished)
			    p_request->m_lock.unlock();
			
			return;
		}
		return;
	}
};