#pragma once

#include "insrequest.h"
#include "sfc_msg.h"

namespace INS {

    class INSNotificationListener : public INSRequest {
    public:
        INSNotificationListener();

        /*!
         * \brief 设置通知的回调函数，如果之前已经设置过回调函数，那么新的函数会覆盖掉旧的函数。
         * \details
         * \param[in] p_func 回调函数的函数指针
         * \return
         */
        void SetCallbackFunc(std::function<void(QString)> p_func);

        void Process(const QByteArray &byteArray) override;

    protected:
        std::function<void(QString)> m_notificationCallback {nullptr};
    };
}