//
// Created by Jsiyong on 2021-01-14.
//

#ifndef INTELLIGENT_NODE_JSONMESSAGEUTILS_H
#define INTELLIGENT_NODE_JSONMESSAGEUTILS_H

#include "JsonSerializationUtils.h"

class JsonMessageUtils {
private:

	template<typename T>
	static void appendData2JsonArray(QJsonArray &jsonArray, const T &t) {
		jsonArray.append(JsonHelper::toJsonValue(t));
	}

	template<typename T>
	void static getRequestDataInner(const QJsonArray &jsonArray, int idx, T &t) {
		JsonHelper::setValueByJson(&t, jsonArray[idx]);
	}

public:

	template<typename... Dt>
	QJsonArray static dataToJsonArray(const Dt &... dt) {
		QJsonArray jsonArray;
		std::initializer_list<int32_t>{((appendData2JsonArray(jsonArray, dt)), 0)...};

		return jsonArray;
	}

	template<typename... Dt>
	void static jsonArrayToData(const QJsonArray &jsonArray, Dt &... dt) {

		int i = 0;
		std::initializer_list<int32_t>{((getRequestDataInner(jsonArray, i++, dt)), 0)...};
	}

	template<typename... Dt>
	QByteArray static dataToJsonArrayBinaryData(const Dt &... dt) {
		QJsonArray jsonArray = dataToJsonArray(dt...);
		return QJsonDocument(jsonArray).toBinaryData();
	}

	template<typename... Dt>
	void static jsonArrayBinaryDataToData(const QByteArray &jsonByteArray, Dt &... dt) {
		QJsonArray jsonArray = QJsonDocument::fromBinaryData(jsonByteArray).array();
		jsonArrayToData(jsonArray, dt...);
	}

};

#endif //INTELLIGENT_NODE_JSONMESSAGEUTILS_H
