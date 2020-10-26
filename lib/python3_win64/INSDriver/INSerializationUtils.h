#pragma once
#include <QVariant>
#include <QDataStream>


//序列化
class SerializationUtils {

	template<typename Tuple, size_t N>
	struct DataStreamBinder {
		static void bindToDataStream(const Tuple& fieldTuple, QDataStream& out, QDataStream& in) {
			DataStreamBinder<Tuple, N - 1>::bindToDataStream(fieldTuple, out, in);
			auto data = std::get<N - 1>(fieldTuple);
			out << *data;
			in >> *data;
		}
	};
	template<typename Tuple>
	struct DataStreamBinder<Tuple, 1> {
		static void bindToDataStream(const Tuple& fieldTuple, QDataStream& out, QDataStream& in) {
			auto data = std::get<0>(fieldTuple);
			out << *data;
			in >> *data;
		}
	};

public:

	template<typename... Args>
	static void bindDataStream(const std::tuple<Args...>& fieldTuple, QDataStream& out, QDataStream& in) {
		DataStreamBinder<decltype(fieldTuple), sizeof...(Args)>::bindToDataStream(fieldTuple, out, in);
	}
};

#define ARG_EXPAND(...) __VA_ARGS__
#define ARG_1(arg) &arg
#define ARG_2(arg,...) &arg,ARG_EXPAND(ARG_1(__VA_ARGS__))
#define ARG_3(arg,...) &arg,ARG_EXPAND(ARG_2(__VA_ARGS__))
#define ARG_4(arg,...) &arg,ARG_EXPAND(ARG_3(__VA_ARGS__))
#define ARG_5(arg,...) &arg,ARG_EXPAND(ARG_4(__VA_ARGS__))
#define ARG_6(arg,...) &arg,ARG_EXPAND(ARG_5(__VA_ARGS__))
#define ARG_7(arg,...) &arg,ARG_EXPAND(ARG_6(__VA_ARGS__))
#define ARG_8(arg,...) &arg,ARG_EXPAND(ARG_7(__VA_ARGS__))
#define ARG_9(arg,...) &arg,ARG_EXPAND(ARG_8(__VA_ARGS__))
#define ARG_10(arg,...) &arg,ARG_EXPAND(ARG_9(__VA_ARGS__))
#define ARG_11(arg,...) &arg,ARG_EXPAND(ARG_10(__VA_ARGS__))
#define ARG_12(arg,...) &arg,ARG_EXPAND(ARG_11(__VA_ARGS__))
#define ARG_13(arg,...) &arg,ARG_EXPAND(ARG_12(__VA_ARGS__))
#define ARG_14(arg,...) &arg,ARG_EXPAND(ARG_13(__VA_ARGS__))
#define ARG_15(arg,...) &arg,ARG_EXPAND(ARG_14(__VA_ARGS__))
#define ARG_16(arg,...) &arg,ARG_EXPAND(ARG_15(__VA_ARGS__))
#define ARG_17(arg,...) &arg,ARG_EXPAND(ARG_16(__VA_ARGS__))
#define ARG_18(arg,...) &arg,ARG_EXPAND(ARG_17(__VA_ARGS__))
#define ARG_19(arg,...) &arg,ARG_EXPAND(ARG_18(__VA_ARGS__))
#define ARG_20(arg,...) &arg,ARG_EXPAND(ARG_19(__VA_ARGS__))
#define ARG_21(arg,...) &arg,ARG_EXPAND(ARG_20(__VA_ARGS__))
#define ARG_22(arg,...) &arg,ARG_EXPAND(ARG_21(__VA_ARGS__))
#define ARG_23(arg,...) &arg,ARG_EXPAND(ARG_22(__VA_ARGS__))
#define ARG_24(arg,...) &arg,ARG_EXPAND(ARG_23(__VA_ARGS__))
#define ARG_25(arg,...) &arg,ARG_EXPAND(ARG_24(__VA_ARGS__))
#define ARG_26(arg,...) &arg,ARG_EXPAND(ARG_25(__VA_ARGS__))
#define ARG_27(arg,...) &arg,ARG_EXPAND(ARG_26(__VA_ARGS__))
#define ARG_28(arg,...) &arg,ARG_EXPAND(ARG_27(__VA_ARGS__))
#define ARG_29(arg,...) &arg,ARG_EXPAND(ARG_28(__VA_ARGS__))
#define ARG_30(arg,...) &arg,ARG_EXPAND(ARG_29(__VA_ARGS__))
#define ARG_31(arg,...) &arg,ARG_EXPAND(ARG_30(__VA_ARGS__))
#define ARG_32(arg,...) &arg,ARG_EXPAND(ARG_31(__VA_ARGS__))
#define ARG_33(arg,...) &arg,ARG_EXPAND(ARG_32(__VA_ARGS__))
#define ARG_34(arg,...) &arg,ARG_EXPAND(ARG_33(__VA_ARGS__))
#define ARG_35(arg,...) &arg,ARG_EXPAND(ARG_34(__VA_ARGS__))
#define ARG_36(arg,...) &arg,ARG_EXPAND(ARG_35(__VA_ARGS__))

#define RSEQ_N() 36,35,34,33,32,31,30,\
                29,28,27,26,25,24,23,22,21,20,\
                19,18,17,16,15,14,13,12,11,10,\
                9,8,7,6,5,4,3,2,1,0

#define ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,\
                _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,\
                _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,\
                _31,_32,_33,_34,_35,_36,N,...) N

#define ARG_COUNT_INNER(...) ARG_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...) ARG_COUNT_INNER(__VA_ARGS__,RSEQ_N())
#define ARG_LIST(N,arg,...) ARG##_##N(arg,__VA_ARGS__)
#define GEN_FUNC(N,...) ARG_EXPAND(ARG_LIST(N, __VA_ARGS__))

#define SERIALIZATION_INNER(Class,Func)\
private:\
    auto getSerializedProperty() {\
        return std::make_tuple(Func);\
    }\
public:\
    friend QDataStream& operator<<(QDataStream& out, const Class& c) {\
		static QByteArray tempBy;\
		static QDataStream tempDt(&tempBy, QIODevice::ReadWrite);\
		tempDt.device()->seek(0);\
        SerializationUtils::bindDataStream(const_cast<Class&>(c).getSerializedProperty(), out, tempDt);\
        return out;\
    }\
    friend QDataStream& operator >> (QDataStream& in, Class& c) {\
		static QByteArray tempBy;\
		static QDataStream tempDt(&tempBy, QIODevice::ReadWrite);\
		tempDt.device()->seek(0);\
        SerializationUtils::bindDataStream(c.getSerializedProperty(), tempDt, in);\
        return in;\
    }

#define Serialization(Class,...) SERIALIZATION_INNER(Class,GEN_FUNC(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__))
