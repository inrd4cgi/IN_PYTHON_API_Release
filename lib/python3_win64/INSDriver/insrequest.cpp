#include "insrequest.h"
#include "insdriver_global.h"
#include <QDataStream>

namespace INS
{
	QMutex INSRequest::g_lock;
	qint32 INSRequest::g_max_id = 1 << 30;
	qint32 INSRequest::g_current_id = 1;
	QMap<qint32, INSRequest*> INSRequest::g_requests;
	INSRequest::INSRequest()
	{
		InitRequestId();
	}

	INSRequest::INSRequest(int customRequestId)
	{
		InitRequestId(true, customRequestId);
	}

	/**************************************************************************************************
	Description:对象析构时，从g_requests列表中移除掉。
	**************************************************************************************************/
	INSRequest::~INSRequest()
	{
		g_lock.lock();
		g_requests.remove(m_request_id);
		g_lock.unlock();
	}

	/**************************************************************************************************
	Description: 通过业务id[business_id]在全局列表g_business_list获取一个业务指针。如果列表中没有这个id，
	那么返回一个空指针。如果有，同时将需要的数据[p_datastream]。
	**************************************************************************************************/
	INSRequest* INSRequest::GetRequest(const qint32& business_id)
	{
		QMutexLocker locker(&g_lock);
		return g_requests.value(business_id, Q_NULLPTR);
	}

	void INSRequest::WaitForFinished(int timeout)
	{
		if(!INSNETWORK->SendDataToAppServer(m_senddata)) {
			m_lock.unlock();
			this->m_finished = true;
			return;
		}

		this->m_finished = true;
		if(m_lock.tryLock(timeout)) {
			//若等到了锁，说明请求已经到了，则后面再开始处理数据
			m_lock.unlock();
		} else {
			//如果在这时候，恰巧被解析线程拿到锁，怎么办？？？？？？
			//只能先用一招了，该对象延迟析构，后面可以再加一把锁去解决这个问题
			//如果等不到锁，那么直接移除掉那个指针,防止请求在此时又到来了
			g_lock.lock();
			g_requests.remove(m_request_id);
			g_lock.unlock();

			m_lock.unlock();
		}
	}

	void INSRequest::Process(const QByteArray& data) {
		m_data = data;
		QByteArray tmp;
		mp_in->device()->seek(0);
		*mp_in >> tmp;

		m_data = tmp;
	}

	void INSRequest::InitRequestId(bool bCustom, int n_requestId)
	{
		mp_out = QSharedPointer<QDataStream>(new QDataStream(&m_senddata, QIODevice::WriteOnly));
		mp_in = QSharedPointer<QDataStream>(new QDataStream(&m_data, QIODevice::ReadOnly));
		mp_out->setVersion(STREAM_VERSION);
		m_lock.lock();
		g_lock.lock();

		//自动生成requestI folderId
		if (!bCustom)
		{
			//当id达到最大值的时候，再从头开始
			do {
				if (g_current_id >= g_max_id)
					g_current_id = 1;
				g_current_id++;
			} while (g_requests.contains(g_current_id));
			m_request_id = g_current_id;
		}
		else
		{
			//手动指定request folderId。
			assert(!g_requests.contains(n_requestId));
			m_request_id = n_requestId;
		}

		g_requests.insert(m_request_id, this);
		g_lock.unlock();
	}
};