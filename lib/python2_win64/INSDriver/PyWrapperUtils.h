//
// Created by jsy on 6/2/20.
//

#ifndef INPYTHONAPI_PYWRAPPERUTILS_H
#define INPYTHONAPI_PYWRAPPERUTILS_H

#include <QString>
#include <QList>
#include <QMap>

struct TypeConvert {
    template<typename T>
    static QList<T *> get(QList <T> *value) {
        QList < T * > ret;
        for (T &item:*value) {
            ret.append(&item);
        }
        return ret;
    }

    static QList <qint32> get(QList <qint32> *value) {
        return *value;
    }

    static QList <QString> get(QList <QString> *value) {
        return *value;
    }

    template<typename K, typename V>
    static QMap<K *, V *> get(QMap <K, V> *value) {
        QMap < K * , V * > ret;
        for (auto &item:value->keys()) {
            ret.insert(&item, &((*value)[item]));
        }
        return ret;
    }

    template<typename V>
    static QMap<qint32, V *> get(QMap <qint32, V> *value) {
        QMap < qint32, V * > ret;
        for (auto item:value->keys()) {
            ret.insert(item, &((*value)[item]));
        }
        return ret;
    }

    static QMap <qint32, qint32> get(QMap <qint32, qint32> *value) {
        return *value;
    }

    static QMap <qint32, QString> get(QMap <qint32, QString> *value) {
        return *value;
    }

    static QMap <QString, QString> get(QMap <QString, QString> *value) {
        return *value;
    }

    template<typename T>
    static T *get(T *value) {
        return value;
    }
};

#define Gen4Py(type, property)\
type get_##property(){\
  return  TypeConvert::get(&property);\
}

#define PyWrapper(ClassName, WrapperType, PyType)\
class ClassName {\
public:\
    WrapperType value;\
    WrapperType unWrap() {return value;}\
    ClassName(){}\
    ClassName(WrapperType& value):value(value){}\
    Gen4Py(PyType,value)\
};

#endif //INPYTHONAPI_PYWRAPPERUTILS_H
