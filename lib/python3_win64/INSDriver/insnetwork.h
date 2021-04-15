//网络模块，管理着所有的连接和请求的产生，数据的收发控制。

#pragma once
#include "instcpsocket.h"

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QMap>
#include <QMutex>
#include <QSharedPointer>

#define INSNETWORK INSNetwork::GetInstance()
#define INSNETWORKHTTP INSHttpRequest::GetHttpNetworkManager()
namespace INS
{
	class INSNetwork : public QObject
	{
		Q_OBJECT

	public:
		//获取单例
		static INSNetwork* GetInstance();

		bool ConnectToAppServer(const QString& hostaddress, const qint32& port);
		//这个函数用于在其他线程调用。
		void ConnectToAppServerFromOtherThread(const QString hostaddress, const qint32& port);
		bool SendDataToAppServer(const QByteArray& data);

		/*! 
		 * \brief 设置断线重连的函数指针。
		 * \details 
		 * \param[in] p_func 为断线重连具体实现的函数的指针。 
		 * \return
		 */
		void SetReConnectFuncPointer(std::function<void()> p_func) { m_reConnectFuncPointer = p_func; }

		/*! 
		 * \brief 请求重新连接到应用服务器，连接的ip和地址为上一次连接的ip和地址。
		 * \details 
		 * \param 
		 * \return
		 - true 表示连接应用服务器成功。
		 - false 表示连接应用服务器失败。
		 */
		bool ReqReConnectToAppServerHost();

	signals:
		void EventConnectToAppServer(QString hostaddress, qint32 port);
		void SigAppServerSocketStatus(bool);

	protected:
		//保存了断线重连功能的函数指针。
		std::function<void()> m_reConnectFuncPointer{ nullptr };

	private:
		INSNetwork(QObject *parent = 0);
		~INSNetwork() {};

		static INSNetwork* gp_instance;
		QSharedPointer<INSServer> m_appServer;

	private slots:
		void SlotConnectToAppServer(QString hostaddress, qint32 port);
		void SlotDisconnected();

	};


	/*!
	 * \class INSHttpRequest
	 * \ingroup businessAPI_fileModule
	 * \brief 文件服务器HTTP请求的业务对象。里面封装了QNetworkAccressManager对象。如果需要改变QNetworkAccressManager对象。需要继承INSHttpRequestAbstract类重写一个类似INSHttpRequest的类。
	 */
	class INSHttpRequest : public INSHttpRequestAbstract
	{
		Q_OBJECT;

	public:
		explicit INSHttpRequest(QObject* parent = nullptr);

		/*! 
		 * \brief 获取QNetworkAccessManager对象的指针函数。
		 * \details 
		 * \param 
		 * \return 返回QNetworkAccessManager的指针。
		 */
		static QNetworkAccessManager* GetHttpNetworkManager();

		/*! 
		 * \brief 通过参数创建一个QNetworkRequest对象。并通过QNetworkAccessManager发出请求。
		 * \details 
		 * \param[in] strAddress HTTP请求的ip或域名
		 * \param[in] strPort HTTP请求的端口，如果strAddress为域名，则可以不填端口信息。
		 * \param[in] strPath HTTP请求的路径
		 * \param[in] strJsonByteArray 请求的报文体。数据是QJsonObject转成的QByteArray类型。
		 * \return	返回QNetworkReply的指针。
		 */
		static QNetworkReply* CreatePostRequestOnlyWithJson(QString strAddress, QString strPort, const QString & strPath, const QByteArray& jsonByteArray);

		/*! 
		 * \brief 通过参数创建QNetworkRequest对象，并通过QNetworkAccessManager发出请求。
		 * \details 
		 * \param[in] strAddress HTTP请求的ip或域名
		 * \param[in] strPort HTTP请求的端口，如果strAddress为域名，则可以不填端口信息。
		 * \param[in] strPath HTTP请求的路径
		 * \param[in] jsonByteArray 请求的报文体。数据是QJsonObject转成的QByteArray类型。
		 * \param[in] bAutoDelete 如果为true则收到finished信号后，自动删除当前对象
		 * \param[in] bAutoConnect 如果为true则调用ConnectReplySlot函数。
		 * \return
		 */
		QNetworkReply* CreatePostRequestWithJson(QString strAddress, QString strPort, const QString & strPath, const QByteArray& jsonByteArray, bool bAutoConnect);

	private:
		static QNetworkAccessManager* m_httpNetworkManager;	//HTTP请求的管理类。封装了请求的封装和网络的各种设置。
	};
};