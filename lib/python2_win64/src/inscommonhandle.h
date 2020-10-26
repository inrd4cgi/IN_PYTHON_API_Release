#pragma once
#include "insrequest.h"
#include "JsonMessageUtils.h"

namespace INS
{

	//通用请求模板
	template<typename Recv, typename... Send>
	class INSCommonRequest :public INSRequest {
	private:
		const static qint32 noUsedData = 0;
	public:
		INSCommonRequest(qint32 serviceId, Send...sendData) {
		    QString jsonStr = JsonMessageUtils::dataToJson(sendData...);
			*mp_out << serviceId << m_request_id << jsonStr;
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				m_return_value = -999;
				m_lock.unlock();
			}
			return;
		}
		~INSCommonRequest() {}

		MessageInfo m_return_value;
		Recv retData;
		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			QString jsonStr;
            *mp_in >> jsonStr;
            JsonMessageUtils::jsonToData(jsonStr, m_return_value, retData);
			m_finished = true;
			return;
		}
	};

	//通用请求模板,返回值为int
	template<typename Recv, typename... Send>
	class INSCommonRequestRetInt :public INSRequest {
	private:
		const static qint32 noUsedData = 0;

	public:
		INSCommonRequestRetInt(qint32 serviceId, Send... sendData)
		{
		    QString jsonStr = JsonMessageUtils::dataToJson(sendData...);
			*mp_out << serviceId << m_request_id << jsonStr;
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				m_return_value = -999;
				m_lock.unlock();
			}
			return;
		}
		~INSCommonRequestRetInt() {}

		qint32 m_return_value;
		Recv retData;

		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			QString jsonStr;
            *mp_in >> jsonStr;
            JsonMessageUtils::jsonToData(jsonStr, m_return_value, retData);
			m_finished = true;
			return;
		}
	};

	//json字符串请求
	class JsonRequest : public INSRequest {
	private:
		MessageInfo m_return_value = MessageInfo::fail();

	public:
		JsonRequest(qint32 serviceId, const QString &jsonStr) {
			*mp_out << serviceId << m_request_id << jsonStr;
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				retData = JsonMessageUtils::dataToJson(m_return_value);
				m_lock.unlock();
			}
			return;
		}
		~JsonRequest() {}

		QString retData;

		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			*mp_in >> retData;

			m_finished = true;
			return;
		}
	};
}