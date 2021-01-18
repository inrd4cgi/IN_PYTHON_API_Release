//
// Created by jiangsiyong on 2020/9/25.
//

#ifndef IN_JSONSERIALIZATIONUTILS_H
#define IN_JSONSERIALIZATIONUTILS_H

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
#include <climits>

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
    QString toJsonString() const {\
        return JsonHelper::getJsonStringFromTuple(std::make_tuple(Func));\
    }\
    void fromJsonString(const QString& jsonStr) {\
        QJsonObject jsonObj = QJsonDocument::fromJson(jsonStr.toUtf8()).object();\
        JsonHelper::convertJsonString2Entity(std::make_tuple(Func), jsonObj);\
    }


#define Serialization(...) SERIALIZATION_INNER(GEN_FUNC(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__))


class JsonHelper {
private:
	template<typename Tuple, size_t N>
	struct DataGetter {
		static void genJsonString(const Tuple &fieldTuple, QString &jsonStr) {
			QString resultTmp;

			DataGetter<Tuple, N - 1>::genJsonString(fieldTuple, jsonStr);
			auto data = std::get<N - 1>(fieldTuple);
			QString key = data.first;
			auto value = *data.second;

			QString strJoinTmp = "%1,%2";
			jsonStr = strJoinTmp.arg(jsonStr).arg(toJsonItem(key, value));
		}
	};

	template<typename Tuple>
	struct DataGetter<Tuple, 1> {
		static void genJsonString(const Tuple &fieldTuple, QString &jsonStr) {
			auto data = std::get<0>(fieldTuple);

			QString key = data.first;
			auto value = *data.second;

			jsonStr = toJsonItem(key, value);

		}
	};

	/////////////////////
	template<typename Tuple, size_t N>
	struct DataSetter {
		static void getValueFromJsonString(const Tuple &fieldTuple, const QJsonObject &jsonObj) {
			DataSetter<Tuple, N - 1>::getValueFromJsonString(fieldTuple, jsonObj);
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
		static void getValueFromJsonString(const Tuple &fieldTuple, const QJsonObject &jsonObj) {
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

	static void setValue(QVariant *field, const QJsonValue &jsonValue) {
		QString str;
		setValue(&str, jsonValue);
		*field = str;
	}

	template<typename T>
	static void setValue(T *field, const QJsonValue &jsonValue) {
		field->fromJsonString(QJsonDocument(jsonValue.toObject()).toJson(QJsonDocument::Compact));
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
		field->reserve(size);
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
		field->reserve(size);
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
			V v;
			setValueByJson(&v, jsonObjTmp[keyItem]);
			field->insert(k,v);
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
		*field = QJsonDocument(jsonVal.toObject()).object().toVariantMap();
	}

	static void setValueByJson(QVariantList *field, const QJsonValue &jsonVal) {
		*field = QJsonDocument(jsonVal.toArray()).array().toVariantList();
	}

	static void setValueByJson(QPoint *field, const QJsonValue &jsonVal) {
		QPair<int, int> pair;
		setValueByJson(&pair, jsonVal);
		field->setX(pair.first);
		field->setY(pair.second);
	}

public:

	static QString getJsonItemValue(bool value) {
		QString jsonItemTemplate = "%1";
		return jsonItemTemplate.arg(value);
	}


	static QString getJsonItemValue(qint32 value) {
		QString jsonItemTemplate = "%1";
		return jsonItemTemplate.arg(value);
	}

	static QString getJsonItemValue(qint64 value) {
		QString jsonItemTemplate = "%1";
		return jsonItemTemplate.arg(value);
	}

	static QString getJsonItemValue(const QString &value) {
		QString jsonItemTemplate = "\"%1\"";
		QString valueTmp = value;
		valueTmp = valueTmp.replace("\\", "\\\\");
		valueTmp = valueTmp.replace("\"", "\\\"");
		//传入的value需要对所有的""进行转义
		return jsonItemTemplate.arg(valueTmp);
	}

	static QString getJsonItemValue(const char *value) {
		QString jsonItemTemplate = "\"%1\"";
		return jsonItemTemplate.arg(value);
	}

	static QString getJsonItemValue(const QDateTime &value) {
		qint64 time = value.toTime_t();
		return getJsonItemValue(time);
	}

	static QString getJsonItemValue(const QDate &value) {
		qint64 time = QDateTime(value).toTime_t();
		return getJsonItemValue(time);
	}

	static QString getJsonItemValue(const QVariant &value) {
		return getJsonItemValue(value.toString());//转为string类型
	}

	template<typename T>
	static QString getJsonItemValue(const T &value) {
		return value.toJsonString();
	}

public:

	template<typename K0, typename T>
	static QString toJsonItem(K0 key, const T &value, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) : "";
		return jsonItemTemplate.append(getJsonItemValue(value));
	}

	template<typename K0, typename T>
	static QString toJsonItem(K0 key, const QSet<T> &values, bool hasKey = true) {
		//json没有集合，直接转为QList
		return toJsonItem(key, values.toList(), hasKey);
	}

	template<typename K0, typename T>
	static QString toJsonItem(K0 key, const QList<T> &values, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) + "[" : "[";
		int index = 0;
		for(auto &v : values) {
			//注意，列表里的项不需要有key值
			jsonItemTemplate.append(toJsonItem("", v, false));

			if(index != values.size() - 1) {
				jsonItemTemplate.append(",");
			}
			index++;
		}
		return jsonItemTemplate.append("]");
	}

	template<typename K0, typename T>
	static QString toJsonItem(K0 key, const QVector<T> &values, bool hasKey = true) {
		//转为跟List一样的格式，列表中元素顺序不变，不必担心
		return toJsonItem(key, values.toList(), hasKey);
	}

	template<typename K0, typename K, typename V>
	static QString toJsonItem(K0 key, const QMap<K, V> &value, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) + "{" : "{";
		int idx = 0;
		for(auto &k : value.uniqueKeys()) {
			//注意，没错，map结构需要有那个key值的
			QString itemStr = toJsonItem(k, value[k]);
			jsonItemTemplate.append(itemStr);
			if(idx != value.size() - 1) {
				jsonItemTemplate.append(",");
			}
			idx++;
		}
		return jsonItemTemplate.append("}");
	}

	template<typename K0, typename K, typename V>
	static QString toJsonItem(K0 key, const QPair<K, V> &value, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) + "[%1,%2]" : "[%1,%2]";
		QString str1 = toJsonItem("", value.first, false);
		QString str2 = toJsonItem("", value.second, false);
		return jsonItemTemplate.arg(str1).arg(str2);
	}

	template<typename K0>
	static QString toJsonItem(K0 key, const QVariantMap &value, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) + "" : "";
		QString str = QJsonDocument::fromVariant(value).toJson(QJsonDocument::Compact);
		return jsonItemTemplate.append(str);
	}

	template<typename K0>
	static QString toJsonItem(K0 key, const QVariantList &value, bool hasKey = true) {
		QString KEY = "\"%1\":";
		QString jsonItemTemplate = hasKey ? KEY.arg(key) + "" : "";
		QString str = QJsonDocument::fromVariant(value).toJson(QJsonDocument::Compact);
		return jsonItemTemplate.append(str);
	}

	template<typename K0>
	static QString toJsonItem(K0 key, const QPoint &value, bool hasKey = true) {
		QPair<int, int> pair = { value.x(), value.y() };
		return toJsonItem(key, pair, hasKey);
	}

	template<typename K0>
	static QString toJsonItem(K0 key, const IdName &value, bool hasKey = true) {
		QPair<int, QString> pair = { value.id, value.name };
		return toJsonItem(key, pair, hasKey);
	}

public:
	template<typename... Args>
	static QString getJsonStringFromTuple(const std::tuple<Args...> &fieldTuple) {
		QString jsonStr;
		DataGetter<decltype(fieldTuple), sizeof...(Args)>::genJsonString(fieldTuple, jsonStr);
		return QString("{%1}").arg(jsonStr);
	}

	template<typename... Args>
	static void convertJsonString2Entity(const std::tuple<Args...> &fieldTuple, const QJsonObject &jsonObj) {

		DataSetter<decltype(fieldTuple), sizeof...(Args)>::getValueFromJsonString(fieldTuple, jsonObj);
	}

};


/**
 *
 * 以下是示例
 *
 *
 */

#if false

struct DEF {
	int b = 13;
	QString v = "nmasd";
	QDateTime time = QDateTime::currentDateTime();

	Serialization(b, v, time)
};

struct ABC {

	qint64 as = 9999;
	QVariantList vl = { 1,"213",90 };

	QMap<qint32, QVariantList> vl2;

	QMap<QString, QVariant> vm = { {"12",1},{"213","{\"a\":23}"} };

	int a = 1;
	QString b = "ab";
	bool c = true;
	QList<QString> d = { "avc","1ra" };
	QList<qint32> e = { 1,5 };
	QSet <bool> f = QSet<bool>({ 1 });
	QPair<qint32, QString> pa = { 1,"12" };


	DEF def;

	QList<DEF> defs = { DEF(),DEF() };

	QMap<qint32, DEF> pp1 = { {12,DEF()},{14,DEF()} };

	QMap<QString, DEF> pp2 = { {"mmm",DEF()},{"aiq",DEF()} };

	Serialization(vl2, vl, vm, a, b, c, d, e, def, defs, pp2, pp1, pa, as)
};



struct BBB {
	qint64 as = 0;

	QMap<QString, DEF> pp2;
	QVariantMap vm;
	QVariantList vl;
	int a;
	QMap<qint32, QVariantList> vl2;

	QString b;
	DEF def;
	QList<qint32> e;
	QMap<qint32, DEF> pp1;

	QList<QString> d;

	QPair<qint32, QString> pa;
	Serialization(vl2, vl, vm, a, b, e, pp2, def, d, pp1, pa, as)
};
int main() {


	ABC ad;
	ad.a = 213213;
	ad.b = "asdsa";
	ad.def.b = 8858;
	ad.vl2[12].append({ 1,3,"abv" });;
	QString str = ad.toJsonString();

	BBB dddd;
	dddd.fromJsonString(str);

	return 0;
}

#endif

#endif //IN_JSONSERIALIZATIONUTILS_H
