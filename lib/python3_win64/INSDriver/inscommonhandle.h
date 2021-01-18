#pragma once
#include "insrequest.h"
#include "JsonMessageUtils.h"

#define WAITFORFINISHEDTHENRETURN commonRequest.WaitForFinished();\
return commonRequest.getRetValue();

#define WAITFORFINISHEDANDGETVALUETHENRETURN(dataContainer) commonRequest.WaitForFinished();\
dataContainer = commonRequest.getRecvData();\
return commonRequest.getRetValue();

namespace INS {

	//通用请求模板:内部用
	template<typename Recv, typename Ret>
	class __INSCommonRequestBase :public INSRequest {

		Recv _recvData;
		Ret _retValue;
		bool serialed = false;

	public:
		template<typename... Send>
		__INSCommonRequestBase(qint32 serviceId, bool jsonParsing, Send...sendData) {
			if(!jsonParsing) {
				return;
			}
			QByteArray jsonStr = JsonMessageUtils::dataToJsonArrayBinaryData(sendData...);
			*mp_out << serviceId << m_request_id << jsonStr;
		}

		__INSCommonRequestBase() {
			//TODO 该对象延迟析构
		}

		Recv getRecvData() {
			if(!serialed) {
				JsonMessageUtils::jsonArrayBinaryDataToData(m_data, _retValue, _recvData);
				serialed = true;
			}
			return _recvData;
		}

		Ret getRetValue() {
			if(!serialed) {
				JsonMessageUtils::jsonArrayBinaryDataToData(m_data, _retValue, _recvData);
				serialed = true;
			}
			return _retValue;
		}
	};

	template<typename Recv>
	class INSCommonRequest :public __INSCommonRequestBase<Recv, MessageInfo> {
	public:
		template<typename... Send>
		INSCommonRequest(qint32 serviceId, Send...sendData) :__INSCommonRequestBase(serviceId, true, sendData...) {}
	};

	template<typename Recv>
	class INSCommonRequestRetInt :public __INSCommonRequestBase<Recv, qint32> {
	public:
		template<typename... Send>
		INSCommonRequestRetInt(qint32 serviceId, Send...sendData) :__INSCommonRequestBase(serviceId, true, sendData...) {}
	};

	template<typename Recv>
	class JsonRequest :public __INSCommonRequestBase<QString, QString> {
	public:
		template<typename... Send>
		JsonRequest(qint32 serviceId, const QString& jsonStr) :__INSCommonRequestBase(serviceId, false) {
			QByteArray jsonArrayData = QJsonDocument::fromJson(jsonStr.toUtf8()).toBinaryData();
			*mp_out << serviceId << m_request_id << jsonArrayData;
		}
		QString getRecvData() {
			return QJsonDocument::fromBinaryData(m_data).toJson(QJsonDocument::Indented);
		}
	};
}