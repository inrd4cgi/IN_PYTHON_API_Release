#include "insnotification.h"


namespace INS {
    //**************************************************************************************************
    INSNotificationListener::INSNotificationListener()
            : INSRequest(-1010) {
        m_lock.unlock();
    }

    void INSNotificationListener::SetCallbackFunc(std::function<void(QString)> p_func) {
        m_notificationCallback = p_func;
    }

    void INSNotificationListener::Process(const QByteArray &byteArray) {
        //在python api下，这个成员可能为空。

		if (m_notificationCallback) {
			m_data = byteArray;
			mp_in->device()->seek(0);
			QByteArray jsonStr;
			*mp_in >> jsonStr;

			QString msg;
			JsonMessageUtils::jsonArrayBinaryDataToData(jsonStr, msg);
			m_notificationCallback(msg);
		}
    }
}
