#pragma once
#include "insnetwork.h"
#include "insdatastructure.h"

#include <QMutex>
#include <QByteArray>
#include <QSharedPointer>
#include <QMap>

constexpr int TIMEOUT_UNIT = 1000;
constexpr int BUSINESS_TIMEOUT = TIMEOUT_UNIT * 10;

namespace INS {
	class INSRequest {
	public:
		INSRequest();
		INSRequest(int);

		virtual ~INSRequest();

		bool m_finished = false;
		QMutex m_lock;
		qint32 m_request_id = 0;

		//收发数据
		QSharedPointer<QDataStream> mp_out;
		QSharedPointer<QDataStream> mp_in;
		QByteArray m_data;
		QByteArray m_senddata;

		//服务器回复的代码
		qint32 m_reply_code = 0;

		static INSRequest* GetRequest(const qint32&);

		virtual void Process(const QByteArray& data);

		void WaitForFinished(int timeout = BUSINESS_TIMEOUT);

	protected:
		/*!
		 * \brief 初始化当前业务的request folderId。
		 * \details
		 * \param[in] bCustom 决定是否自动生成request id的标志。
		 * \param[in] n_requestId 自定义的request folderId。如果bCustom为true时使用，否则不使用。
		 * \return
		 */
		void InitRequestId(bool bCustom = false, int n_requestId = 0);

	private:
		static QMutex g_lock;

		//定义最大的请求id
		static qint32 g_max_id;
		static qint32 g_current_id;
		static QMap<qint32, INSRequest*> g_requests;
	};

};