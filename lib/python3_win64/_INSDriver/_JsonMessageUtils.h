//
// Created by jiangsiyong on 2020/9/25.
//

#ifndef IN_JSONMESSAGEUTILS_H
#define IN_JSONMESSAGEUTILS_H

#include "JsonSerializationUtils.h"
#include <QDebug>

class JsonMessageUtils {
private:

    template<typename T>
    static void appendData2JsonList(QStringList &jsonListItem, T t) {
        jsonListItem.append(JsonHelper::toJsonItem("", t, false));
    }

    template<typename T>
    void static getRequestDataInner(const QJsonArray &jsonArray, int idx, T &t) {
        JsonHelper::setValueByJson(&t, jsonArray[idx]);
    }

public:

    template<typename... Dt>
    QString static dataToJson(const Dt &... dt) {
        QStringList jsonList;
        std::initializer_list<int32_t>{((appendData2JsonList(jsonList, dt)), 0)...};
        QString jsonString = "[" + jsonList.join(",") + "]";
        return jsonString;
    }

    template<typename... Dt>
    void static jsonToData(const QString &data, Dt &... dt) {
        QJsonArray jsonArray = QJsonDocument::fromJson(data.toUtf8()).array();
        int i = 0;
        std::initializer_list<int32_t>{((getRequestDataInner(jsonArray, i++, dt)), 0)...};
    }
};

#endif //IN_JSONMESSAGEUTILS_H
