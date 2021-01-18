#include "insnetwork.h"
#include "inssetting.h"

#include <QMetaType>
#include <QDebug>
#include <QCoreApplication>
#include <QSharedPointer>
#include <QNetworkAccessManager>

namespace INS
{
	INSNetwork* INSNetwork::gp_instance = Q_NULLPTR;
	QNetworkAccessManager* INSHttpRequest::m_httpNetworkManager = nullptr;


	/**************************************************************************************************
	Description: 构造函数,已被私有化。
	**************************************************************************************************/
	INSNetwork::INSNetwork(QObject *parent)
		: QObject(parent)
	{
		qDebug() << "new INSNetwork";
		connect(this, SIGNAL(EventConnectToAppServer(QString, qint32)), this, SLOT(SlotConnectToAppServer(QString, qint32)), Qt::QueuedConnection);
	}

	/**************************************************************************************************
	Description:INSNetwork为单例，不允许有多个出现。单例模式下获取实例函数。
	**************************************************************************************************/
	INSNetwork * INSNetwork::GetInstance()
	{
		if (gp_instance == Q_NULLPTR)
		{
			gp_instance = new INSNetwork(nullptr);
		}
		return gp_instance;
	}

	/**************************************************************************************************
	Description:连接到服务器函数。IP地址为[hostaddress]，端口为[port]。IP地址为空，就使用前一次调用
	ConnectToServer的IP地址。如果是第一次调用，就会是使用配置文件中的IP地址和端口。
	**************************************************************************************************/
	bool INSNetwork::ConnectToAppServer(const QString &hostaddress, const qint32& port)
	{
		SETTING->setValue("server_address", hostaddress);

		qDebug() << "new server socket, ip: " << hostaddress << " . port: " << port;
		QSharedPointer<INSServer> p_insserver = QSharedPointer<INSServer>(new INSServer(nullptr));
		QSharedPointer<QThread> p_thread = QSharedPointer<QThread>(new QThread(nullptr));
		p_insserver->mp_write_thread = p_thread;
		p_insserver->m_ipAddress = hostaddress;
		p_insserver->m_port = QString::number(port);
		p_insserver->moveToThread(p_thread.data());
		m_appServer = p_insserver;
		p_thread->start();

		connect(p_insserver.data(), SIGNAL(disconnected()), this, SLOT(SlotDisconnected()), Qt::QueuedConnection);
		if (!p_insserver->ConnectToHost(hostaddress, port))
		{
			qDebug() << "connect to server fail.using server address=" << hostaddress << "port=" << port;
			p_insserver->mp_write_thread->terminate();
			return false;
		}

		return true;
	}

	/**************************************************************************************************
	Description:发送连接到服务器信号，通过queueconnection 实现异步调用。[hostaddress]为服务器的ip地址。[port]
	为服务器的端口。[folderId]为客户端的连接id。[download]标记为连接到文件服务器后，是否做的是下载任务，否则为上传任务。
	**************************************************************************************************/
	void INSNetwork::ConnectToAppServerFromOtherThread(const QString hostaddress, const qint32& port)
	{
		emit EventConnectToAppServer(hostaddress, port);
	}

	/**************************************************************************************************
	Description:发送数据到IP地址为[hostaddress]的机子,发送成功返回true,发送失败返回false。
	**************************************************************************************************/
	bool INSNetwork::SendDataToAppServer(const QByteArray & data)
	{
		return m_appServer->SendData(data);
	}

	bool INSNetwork::ReqReConnectToAppServerHost()
	{
		return m_appServer->ReConnectToHost();
	}


	void INSNetwork::SlotConnectToAppServer(QString hostaddress, qint32 port)
	{
		ConnectToAppServer(hostaddress, port);
	}

	void INSNetwork::SlotDisconnected()
	{
        emit SigAppServerSocketStatus(false);
		qDebug() << "disconnected!";
		if (m_reConnectFuncPointer)
			m_reConnectFuncPointer();
	}


	//INSHttpRequest
	//************************************************************************************************************************
	INSHttpRequest::INSHttpRequest(QObject* parent)
		: INSHttpRequestAbstract(parent)
	{}

	QNetworkAccessManager * INSHttpRequest::GetHttpNetworkManager()
	{
		if (m_httpNetworkManager == nullptr)
			m_httpNetworkManager = new QNetworkAccessManager;
		return m_httpNetworkManager;
	}

	QNetworkReply * INSHttpRequest::CreatePostRequestOnlyWithJson(QString strAddress, QString strPort, const QString & strPath, const QByteArray & jsonByteArray)
	{
		QString strUrl{ GenerateHttpUrl(strAddress, strPort, strPath) };
		QNetworkRequest netReq{ GenerateNetRequest(strUrl) };
		auto netReply = INSNETWORKHTTP->post(netReq, jsonByteArray);
		return netReply;
	}

	QNetworkReply * INSHttpRequest::CreatePostRequestWithJson(QString strAddress, QString strPort, const QString & strPath, const QByteArray & jsonByteArray, bool bAutoConnect)
	{
		m_netReply = CreatePostRequestOnlyWithJson(strAddress, strPort, strPath, jsonByteArray);

		if (bAutoConnect)
			ConnectReplySlot(m_netReply);
		return m_netReply;
	}
};