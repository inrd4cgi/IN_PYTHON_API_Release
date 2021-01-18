//
// Created by Jiangsiyong on 2021-01-14.
//

#ifndef INTELLIGENT_NODE_JSONSERIALIZATIONUTILS_H
#define INTELLIGENT_NODE_JSONSERIALIZATIONUTILS_H

#include <QVariant>
#include <QDataStream>
#include <QSet>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <sstream>
#include <QDebug>
#include <QPoint>
#include <limits>

namespace INS {
	//id与名字类
	struct IdName {
		qint32 id = 0;
		QString name = 0;

		IdName() {}

		IdName(qint32 id, const QString &name) {
			this->id = id;
			this->name = name;
		}

		bool operator==(const IdName &idname) const {
			return idname.id == this->id;
		}

		bool operator!=(const IdName &idname) const {
			return idname.id != this->id;
		}

		bool operator<(const IdName &idName) const {
			return this->id < idName.id;
		}
	};
};
Q_DECLARE_METATYPE(INS::IdName)
using INS::IdName;

#define ARG_EXPAND(...) __VA_ARGS__
#define ARG_1(arg) qMakePair(QString(#arg),&arg)
#define ARG_2(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_1(__VA_ARGS__))
#define ARG_3(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_2(__VA_ARGS__))
#define ARG_4(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_3(__VA_ARGS__))
#define ARG_5(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_4(__VA_ARGS__))
#define ARG_6(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_5(__VA_ARGS__))
#define ARG_7(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_6(__VA_ARGS__))
#define ARG_8(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_7(__VA_ARGS__))
#define ARG_9(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_8(__VA_ARGS__))
#define ARG_10(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_9(__VA_ARGS__))
#define ARG_11(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_10(__VA_ARGS__))
#define ARG_12(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_11(__VA_ARGS__))
#define ARG_13(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_12(__VA_ARGS__))
#define ARG_14(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_13(__VA_ARGS__))
#define ARG_15(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_14(__VA_ARGS__))
#define ARG_16(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_15(__VA_ARGS__))
#define ARG_17(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_16(__VA_ARGS__))
#define ARG_18(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_17(__VA_ARGS__))
#define ARG_19(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_18(__VA_ARGS__))
#define ARG_20(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_19(__VA_ARGS__))
#define ARG_21(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_20(__VA_ARGS__))
#define ARG_22(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_21(__VA_ARGS__))
#define ARG_23(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_22(__VA_ARGS__))
#define ARG_24(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_23(__VA_ARGS__))
#define ARG_25(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_24(__VA_ARGS__))
#define ARG_26(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_25(__VA_ARGS__))
#define ARG_27(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_26(__VA_ARGS__))
#define ARG_28(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_27(__VA_ARGS__))
#define ARG_29(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_28(__VA_ARGS__))
#define ARG_30(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_29(__VA_ARGS__))
#define ARG_31(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_30(__VA_ARGS__))
#define ARG_32(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_31(__VA_ARGS__))
#define ARG_33(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_32(__VA_ARGS__))
#define ARG_34(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_33(__VA_ARGS__))
#define ARG_35(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_34(__VA_ARGS__))
#define ARG_36(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_35(__VA_ARGS__))
#define ARG_37(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_36(__VA_ARGS__))
#define ARG_38(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_37(__VA_ARGS__))
#define ARG_39(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_38(__VA_ARGS__))
#define ARG_40(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_39(__VA_ARGS__))
#define ARG_41(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_40(__VA_ARGS__))
#define ARG_42(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_41(__VA_ARGS__))
#define ARG_43(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_42(__VA_ARGS__))
#define ARG_44(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_43(__VA_ARGS__))
#define ARG_45(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_44(__VA_ARGS__))
#define ARG_46(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_45(__VA_ARGS__))
#define ARG_47(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_46(__VA_ARGS__))
#define ARG_48(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_47(__VA_ARGS__))
#define ARG_49(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_48(__VA_ARGS__))
#define ARG_50(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_49(__VA_ARGS__))
#define ARG_51(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_50(__VA_ARGS__))
#define ARG_52(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_51(__VA_ARGS__))
#define ARG_53(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_52(__VA_ARGS__))
#define ARG_54(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_53(__VA_ARGS__))
#define ARG_55(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_54(__VA_ARGS__))
#define ARG_56(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_55(__VA_ARGS__))
#define ARG_57(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_56(__VA_ARGS__))
#define ARG_58(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_57(__VA_ARGS__))
#define ARG_59(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_58(__VA_ARGS__))
#define ARG_60(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_59(__VA_ARGS__))
#define ARG_61(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_60(__VA_ARGS__))
#define ARG_62(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_61(__VA_ARGS__))
#define ARG_63(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_62(__VA_ARGS__))
#define ARG_64(arg, ...) qMakePair(QString(#arg),&arg),ARG_EXPAND(ARG_63(__VA_ARGS__))

#define RSEQ_N() 64,63,62,61,60,\
                59,58,57,56,55,54,53,52,51,50,\
                49,48,47,46,45,44,43,42,41,40,\
                39,38,37,36,35,34,33,32,31,30,\
                29,28,27,26,25,24,23,22,21,20,\
                19,18,17,16,15,14,13,12,11,10,\
                9,8,7,6,5,4,3,2,1,0

#define ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
                _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
                _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
                _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
                _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
                _61, _62, _63, _64, N, ...) N


#define ARG_COUNT_INNER(...) ARG_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...) ARG_COUNT_INNER(__VA_ARGS__,RSEQ_N())
#define ARG_LIST(N, arg, ...) ARG##_##N(arg,__VA_ARGS__)
#define GEN_FUNC(N, ...) ARG_EXPAND(ARG_LIST(N, __VA_ARGS__))

#define SERIALIZATION_INNER(Func)\
private:\
    auto getSerializedProperty() const {\
        return std::make_tuple(Func);\
    }\
public:\
    QJsonObject toJsonObject() const {\
        return JsonHelper::getJsonFromTuple(std::make_tuple(Func));\
    }\
    void fromJsonObject(const QJsonObject& jsonObj) {\
        JsonHelper::convertJson2Entity(std::make_tuple(Func), jsonObj);\
    }\
    void fromJsonString(const QString& jsonStr) {\
        QJsonObject jsonObj = QJsonDocument::fromJson(jsonStr.toUtf8()).object();\
        fromJsonObject(jsonObj);\
    }\
    QString toJsonString() const {\
        QJsonObject jsonObj = toJsonObject();\
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Indented);\
    }

#define Serialization(...) SERIALIZATION_INNER(GEN_FUNC(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__))


class JsonHelper {
private:
	template<typename Tuple, size_t N>
	struct DataGetter {
		static void genJsonObject(const Tuple &fieldTuple, QJsonObject &jsonObj) {
			QString resultTmp;

			DataGetter<Tuple, N - 1>::genJsonObject(fieldTuple, jsonObj);
			auto data = std::get<N - 1>(fieldTuple);
			QString key = data.first;
			auto value = *data.second;

			jsonObj.insert(key, toJsonValue(value));
		}
	};

	template<typename Tuple>
	struct DataGetter<Tuple, 1> {
		static void genJsonObject(const Tuple &fieldTuple, QJsonObject &jsonObj) {
			auto data = std::get<0>(fieldTuple);
			QString key = data.first;
			auto value = *data.second;
			jsonObj.insert(key, toJsonValue(value));

		}
	};

	/////////////////////
	template<typename Tuple, size_t N>
	struct DataSetter {
		static void getValueFromJsonObject(const Tuple &fieldTuple, const QJsonObject &jsonObj) {
			DataSetter<Tuple, N - 1>::getValueFromJsonObject(fieldTuple, jsonObj);
			auto data = std::get<N - 1>(fieldTuple);
			QString key = data.first;
			if(jsonObj.contains(key)) {
				//设置值
				setValueByJson(data.second, jsonObj[key]);
			}

		}
	};

	template<typename Tuple>
	struct DataSetter<Tuple, 1> {
		static void getValueFromJsonObject(const Tuple &fieldTuple, const QJsonObject &jsonObj) {
			auto data = std::get<0>(fieldTuple);

			QString key = data.first;
			if(jsonObj.contains(key)) {
				//设置值
				setValueByJson(data.second, jsonObj[key]);
			}

		}
	};

public:
	static void setValue(int *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toInt();
	}

	static void setValue(QString *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toString();
	}

	static void setValue(bool *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toInt();
	}

	static void setValue(QDateTime *field, const QJsonValue &jsonValue) {
		qint64 time = 0;
		setValue(&time, jsonValue);
		if(UINT_MAX == time || 0 == time) {
			*field = QDateTime();
		} else {
			*field = QDateTime::fromTime_t(time);
		}
	}

	static void setValue(QDate *field, const QJsonValue &jsonValue) {
		qint64 time = 0;
		setValue(&time, jsonValue);
		if(UINT_MAX == time || 0 == time) {
			*field = QDate();
		} else {
			*field = QDateTime::fromTime_t(time).date();
		}
	}

	static void setValue(qint64 *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toDouble();
	}

	static void setValue(double *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toDouble();
	}

	static void setValue(QVariant *field, const QJsonValue &jsonValue) {
		*field = jsonValue.toVariant();
	}

	template<typename T>
	static void setValue(T *field, const QJsonValue &jsonValue) {
		field->fromJsonObject(jsonValue.toObject());
	}

public:

	template<typename T>
	static void convertValueFromString(const QString &str, T &v) {
		std::stringstream ss;
		ss << str.toStdString();
		ss >> v;
	}

	static void convertValueFromString(const QString &str, QString &v) { v = str; }

	template<typename T>
	static void setValueByJson(T *field, const QJsonValue &jsonVal) {
		setValue(field, jsonVal);
	}

	template<typename T>
	static void setValueByJson(QList<T> *field, const QJsonValue &jsonValue) {
		auto JsonArray = jsonValue.toArray();
		int size = JsonArray.size();
		field->reserve(size);//重写大小
		for(int i = 0; i < size; ++i) {
			T t;
			setValueByJson(&t, JsonArray[i]);
			field->append(t);
		}
	}

	template<typename T>
	static void setValueByJson(QVector<T> *field, const QJsonValue &jsonValue) {
		auto JsonArray = jsonValue.toArray();
		int size = JsonArray.size();
		field->reserve(size);//重写大小
		for(int i = 0; i < size; ++i) {
			T t;
			setValueByJson(&t, JsonArray[i]);
			field->append(t);
		}
	}

	template<typename K, typename V>
	static void setValueByJson(QMap<K, V> *field, const QJsonValue &jsonVal) {
		auto jsonObjTmp = jsonVal.toObject();
		for(const QString &keyItem : jsonObjTmp.keys()) {
			K k;
			convertValueFromString(keyItem, k);
			//不使用局部变量，不知道为啥有时候会67掉，真是奇了个怪了。。。
			//直接使用field的空间
			V v;
			setValueByJson(&v, jsonObjTmp[keyItem]);
			field->insert(k, v);
		}
	}

	template<typename K, typename V>
	static void setValueByJson(QPair<K, V> *field, const QJsonValue &jsonVal) {
		auto jsonArrayTmp = jsonVal.toArray();
		setValueByJson(&(field->first), jsonArrayTmp[0]);
		setValueByJson(&(field->second), jsonArrayTmp[1]);
	}

	//IdName特殊处理，哎，好难啊......
	static void setValueByJson(IdName *field, const QJsonValue &jsonVal) {
		QPair<qint32, QString> pair;
		setValueByJson(&pair, jsonVal);
		field->id = pair.first;
		field->name = pair.second;
	}

	template<typename T>
	static void setValueByJson(QSet<T> *field, const QJsonValue &jsonVal) {
		auto jsonArray = jsonVal.toArray();
		field->reserve(jsonArray.size());//先预先扩大一定的大小
		for(QJsonValue v : jsonArray) {
			T t;
			setValueByJson(&t, v);
			field->insert(t);
		}
	}

	static void setValueByJson(QVariantMap *field, const QJsonValue &jsonVal) {
		auto jsonObjTmp = jsonVal.toObject();
		for(const QString &keyItem : jsonObjTmp.keys()) {
			QString k;
			convertValueFromString(keyItem, k);

			QVariant v;
			setValueByJson(&v, jsonObjTmp[keyItem]);
			field->insert(k, v);
		}
	}

	static void setValueByJson(QVariantList *field, const QJsonValue &jsonValue) {
		auto JsonArray = jsonValue.toArray();
		int size = JsonArray.size();
		field->reserve(size);//重写大小
		for(int i = 0; i < size; ++i) {
			QVariant t;
			setValueByJson(&t, JsonArray[i]);
			field->append(t);
		}
	}

	static void setValueByJson(QPoint *field, const QJsonValue &jsonVal) {
		QPair<int, int> pair;
		setValueByJson(&pair, jsonVal);
		field->setX(pair.first);
		field->setY(pair.second);
	}

public:

	static QJsonValue genJsonValue(bool value) {
		return QJsonValue((int)value);
	}

	static QJsonValue genJsonValue(qint32 value) {
		return QJsonValue(value);
	}

	static QJsonValue genJsonValue(const QString &value) {
		return QJsonValue(value);
	}

	static QJsonValue genJsonValue(const char *value) {
		return QJsonValue(value);
	}

	static QJsonValue genJsonValue(qint64 value) {
		return QJsonValue(value);
	}

	static QJsonValue genJsonValue(double value) {
		return QJsonValue(value);
	}

	static QJsonValue genJsonValue(const QDateTime &value) {
		qint64 time = value.toTime_t();
		return QJsonValue(time);
	}

	static QJsonValue genJsonValue(const QDate &value) {
		qint64 time = QDateTime(value).toTime_t();
		return genJsonValue(time);
	}

	static QJsonValue genJsonValue(const QVariant &value) {
		return QJsonValue::fromVariant(value);//转为string类型
	}

	template<typename T>
	static QJsonValue genJsonValue(const T &value) {
		return value.toJsonObject();
	}

public:

	template<typename T>
	static QJsonValue toJsonValue(const T &value) {
		return genJsonValue(value);
	}

	template<typename T>
	static QJsonValue toJsonValue(const QSet<T> &values) {
		QJsonArray jsonArray;
		for(const auto &v : values) {
			jsonArray.append(toJsonValue(v));
		}
		return jsonArray;
	}

	template<typename T>
	static QJsonValue toJsonValue(const QList<T> &values) {
		QJsonArray jsonArray;
		for(const auto &v : values) {
			jsonArray.append(toJsonValue(v));
		}
		return jsonArray;
	}

	template<typename T>
	static QJsonValue toJsonValue(const QVector<T> &values) {
		QJsonArray jsonArray;
		for(const auto &v : values) {
			jsonArray.append(toJsonValue(v));
		}
		return jsonArray;
	}

	template<typename K, typename V>
	static QJsonValue toJsonValue(const QMap<K, V> &values) {
		QJsonObject jsonObj;
		for(const auto &k : values.keys()) {
			//key 需要转为字符串
			QString keyStr = "%1";
			keyStr = keyStr.arg(k);
			jsonObj.insert(keyStr, toJsonValue(values[k]));
		}
		return jsonObj;
	}

	template<typename K, typename V>
	static QJsonValue toJsonValue(const QPair<K, V> &value) {
		QJsonArray jsonArray;
		jsonArray.append(toJsonValue(value.first));
		jsonArray.append(toJsonValue(value.second));
		return jsonArray;
	}

	static QJsonValue toJsonValue(const QVariantMap &values) {
		QJsonObject jsonObj;
		for(const auto &k : values.keys()) {
			//key 需要转为字符串
			QString keyStr = "%1";
			keyStr = keyStr.arg(k);
			jsonObj.insert(keyStr, toJsonValue(values[k]));
		}
		return jsonObj;
	}

	static QJsonValue toJsonValue(const QVariantList &values) {
		QJsonArray jsonArray;
		for(const auto &v : values) {
			jsonArray.append(toJsonValue(v));
		}
		return jsonArray;
	}


	static QJsonValue toJsonValue(const QPoint &value) {
		QPair<int, int> pair = { value.x(), value.y() };
		return toJsonValue(pair);
	}

	static QJsonValue toJsonValue(const IdName &value) {
		QPair<int, QString> pair = { value.id, value.name };
		return toJsonValue(pair);
	}

public:
	template<typename... Args>
	static QJsonObject getJsonFromTuple(const std::tuple<Args...> &fieldTuple) {
		QJsonObject jsonObj;
		DataGetter<decltype(fieldTuple), sizeof...(Args)>::genJsonObject(fieldTuple, jsonObj);
		return jsonObj;
	}

	template<typename... Args>
	static void convertJson2Entity(const std::tuple<Args...> &fieldTuple, const QJsonObject &jsonObj) {

		DataSetter<decltype(fieldTuple), sizeof...(Args)>::getValueFromJsonObject(fieldTuple, jsonObj);
	}

};

#endif //INTELLIGENT_NODE_JSONSERIALIZATIONUTILS_H
