#include "instcpsocket.h"
#include "inssetting.h"
#include "insreplyparse.h"
#include "insdriver_global.h"
#include "sfc_msg.h"

#include <QList>
#include <QHostAddress>
#include <QThread>
#include <QDebug>
#include <QNetworkAccessManager>

namespace INS
{
	/*******************************************************************
	Description:构造函数
	********************************************************************/
	INSServer::INSServer(QObject *parent)
		: QTcpSocket(parent)
	{
		m_package.head = 31415926;
		m_package.tail = 31415927;
		mp_out = QSharedPointer<QDataStream>(new QDataStream(&m_datasend, QIODevice::WriteOnly));

		connect(this, SIGNAL(readyRead()), this, SLOT(SlotReadyRead()));
		connect(this, SIGNAL(EventSendData(QByteArray)), this, SLOT(SlotSendData(QByteArray)), Qt::QueuedConnection);
		connect(this, SIGNAL(EventConnectToHost(QString, qint32)), this, SLOT(SlotConnectToHost(QString, qint32)), Qt::QueuedConnection);
		connect(this, SIGNAL(ReqDisonnectFromHost()), this, SLOT(SlotDisconnectFromHost()), Qt::QueuedConnection);
		connect(this, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),this, &INSServer::SlotSocketError);
	}

	INSServer::~INSServer()
	{
		qDebug() << "INSServer deleted." << m_ipAddress;

		if (mp_write_thread->isRunning())
			mp_write_thread->terminate();
	}

	/**************************************************************************************************
	Description:连接到服务器函数。IP地址为[hostaddress]，端口为[port]。等待5秒，如果5秒内没有连接成功，那么
	就放弃连接，返回false.这里只是发送一个信号，通过异步连接，使得连接操作在本线程中进行。
	**************************************************************************************************/
	bool INSServer::ConnectToHost(const QString & hostaddress, const qint32 & port)
	{
		emit(EventConnectToHost(hostaddress, port));

		qDebug() << "connecting server. ip: " << hostaddress << " . port:  " << port;

		//wait for 50x100=5000 mSecond.
		qint32 second = 0;
		while (second < 50)
		{
			QThread::msleep(100);
			second++;
			if (this->state() == QAbstractSocket::ConnectedState)
				return true;
		}
		return false;
	}

	bool INSServer::ReConnectToHost()
	{
		return ConnectToHost(m_ipAddress, m_port.toInt());
	}

	/**************************************************************************************************
	Description:对外开放的发送数据函数，通过信号槽的队列连接，实现数据发送在Socket所在的线程中进行。
	**************************************************************************************************/
	bool INSServer::SendData(const QByteArray& data)
	{
		if (this->isValid())
		{
			if (QThread::currentThreadId() == m_thread_id)
			{
				SlotSendData(data);
				return true;
			}

			emit(EventSendData(data));
			return true;
		}
		return false;
	}

	/**************************************************************************************************
	Description:发送数据到客户端或者文件服务器。数据最大为qint64所能表示的数值。调试版本会打印回复的代号。
	**************************************************************************************************/
	void INSServer::SlotSendData(QByteArray data)
	{
		m_thread_id = QThread::currentThreadId();
		//包装发送的数据
		m_package.length = data.size() + 20;
		m_package.data = data;

		//通过流的方式将结构体序列化为二进制
		*mp_out << m_package;
		this->write(m_datasend);
		this->flush();

		//重置数组的大小为0
		mp_out->device()->seek(0);
		m_datasend.clear();
	}

	/**************************************************************************************************
	Description:连接到服务器槽函数。IP地址为[hostaddress]，端口为[port]。
	**************************************************************************************************/
	void INSServer::SlotConnectToHost(QString hostaddress, qint32 port)
	{
		this->connectToHost(hostaddress, port);
	}

	/**************************************************************************************************
	Description: 客户端分派自己的任务,同一时刻，只会有一个客户端分派任务对于readyread信号，每次有新数据来，
	都会触发一次。这要求客户端发送的请求都是原子性的。也就是不允许两或多个个请求的数据合起来发送。
	**************************************************************************************************/
	void INSServer::SlotReadyRead()
	{
		m_data_buffer.append(readAll());
		QDataStream in(m_data_buffer);
		in.setVersion(STREAM_VERSION);
		total = 0;	//记录已处理的总数据量
		while (m_data_buffer.size() - total >= 24)	//最小的一个命令包为24字节
		{
			in >> m_package.head;		//读取包头
			if (m_package.head != qint32(31415926))
			{
				m_data_buffer.clear();	//数据有误的情况下,全部清除。
				qDebug() << "network packages analyzes error!";
				return;
			}
			in >> m_package.length;		//读取包的大小
			if (m_package.length > m_data_buffer.size() - total)	//如果真是数据报大小比缓存-已读数据大小要大，退出
				break;
			in >> m_package.data >> m_package.tail;	//读取尾部。
			if (m_package.tail != qint32(31415927))			//判断包尾的正确性
			{
				m_data_buffer.clear();
				qDebug() << "network packages analyzes error";
				break;
			}
			total += m_package.length;
			INSREPLYPARES->AppendAReply(m_package.data);
			m_package.data.clear();	//清空数据包
		}
		m_data_buffer.remove(0, total);
	}

	void INSServer::SlotDisconnectFromHost()
	{
		qDebug() << "disconnect from host. IP: " << m_ipAddress;
		disconnectFromHost();
	}

	void INSServer::SlotSocketError(QAbstractSocket::SocketError socketError)
	{
		qDebug() << "TcpSocket connection error type=" << socketError << "\t check Qt QAbstractSocket::SocketError!";
	}


	//INSHttpRequestAbstract
	//************************************************************************************************************************
	INSHttpRequestAbstract::INSHttpRequestAbstract(QObject* parent)
		:QObject(parent)
	{}

	INSHttpRequestAbstract::~INSHttpRequestAbstract()
	{
		if (!m_netReply.isNull())
		{
			if(m_netReply->isOpen())
				m_netReply->close();
			m_netReply->deleteLater();
		}
	}


	void INSHttpRequestAbstract::ConnectReplySlot(QNetworkReply * netReply)
	{
		assert(netReply != nullptr);
		if (m_netReply != netReply)
			m_netReply = netReply;

        connect(netReply, &QNetworkReply::downloadProgress, this, &INSHttpRequestAbstract::SlotReadDataFromNetReply);
		connect(netReply, &QNetworkReply::finished, this, &INSHttpRequestAbstract::SlotRequestFinished);
		connect(netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &INSHttpRequestAbstract::SlotRequestError);
	}

	void INSHttpRequestAbstract::SlotReadDataFromNetReply(qint64 bytesReceived, qint64 bytesTotal)
	{
		if (!m_netReply.isNull())
        {
            m_bytesReceived = bytesReceived;
            m_bytesTotal = bytesTotal;

            QByteArray by(std::move(m_netReply->readAll()));
            SlotReadyread(by);
        }
	}

	QString INSHttpRequestAbstract::GenerateHttpUrl(QString strAddress, QString strPort, const QString & strPath, const QStringList & strParam)
	{
		strAddress.prepend(QString("http://"));
		strAddress.append(":" + strPort);
		if (!strPath.isNull())
			strAddress.append(strPath);
		if (!strParam.isEmpty())
			strAddress.append(QString("?%1").arg(strParam.join("&")));
		return strAddress;
	}

	QNetworkRequest INSHttpRequestAbstract::GenerateNetRequest(const QString & strUrl, const char * contentTypeHeader)
	{
		QNetworkRequest netReq(strUrl);
		netReq.setHeader(QNetworkRequest::ContentTypeHeader, contentTypeHeader);
		return netReq;
	}

	void INSHttpRequestAbstract::ConnectReplySlot(QNetworkReply * reqReply, std::function<void(QByteArray&)> readyreadSlot, std::function<void()> finishedSlot, std::function<void(QNetworkReply::NetworkError)> errorSlot)
	{
		if (readyreadSlot)
		{
			connect(reqReply, &QNetworkReply::readyRead, [reqReply, readyreadSlot]() {
			    QByteArray by(std::move(reqReply->readAll()));
				readyreadSlot(by);
			});
		}

		if (finishedSlot)
			connect(reqReply, &QNetworkReply::finished, finishedSlot);

		if (errorSlot)
			connect(reqReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), errorSlot);
	}

};

