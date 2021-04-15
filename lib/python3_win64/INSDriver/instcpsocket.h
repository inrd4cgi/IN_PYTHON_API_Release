//客户端连接类非线程安全。
#pragma once

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QSharedPointer>
#include <QNetworkReply>
#include <functional>
#include <assert.h>
#include <QPointer>

class QNetworkAccessManager;

namespace INS
{

	//网络传输数据包
	struct NetworkDataPackage
	{
		qint32 head = 31415926;	//包头标志31415926
		qint64 length = 0;		//描述data的长度,整个包的长度
		QByteArray data;		//内容
		qint32 tail = 31415927;	//包尾31415927
		friend QDataStream& operator >> (QDataStream& in, NetworkDataPackage& package)
		{
			in >> package.head >> package.length >> package.data >> package.tail;
			return in;
		}
		friend QDataStream& operator << (QDataStream& out, NetworkDataPackage& package)
		{
			out << package.head << package.length << package.data << package.tail;
			return out;
		}
	};

	class INSServer : public QTcpSocket
	{
		Q_OBJECT

	public:
		//构造函数
        explicit INSServer(QObject *parent = nullptr);
		~INSServer() override;

		QSharedPointer<QThread> mp_write_thread;
		Qt::HANDLE m_thread_id;

		//连接类型1=client
		qint32 m_connection_type = 1;
		QString m_ipAddress;
		QString m_port;

		/*! 
		 * \brief 供外部调用的连接应用服务器的函数。
		 * \details 
		 * \param[in] QString 为服务器的ip地址 
		 * \param[in] qint32 为服务器的端口 
		 * \return
		 */
		bool ConnectToHost(const QString&, const qint32&);
		
		/*! 
		 * \brief 再次连接App Server。内部实现调用ConnectToHost函数。
		 * \details 
		 * \param 
		 * \return
		 - true 再次连接服务器成功
		 - false 连接服务器失败
		 */
		bool ReConnectToHost();


		/*! 
		 * \brief 外部调用的发送数据的函数
		 * \details 
		 * \param[in] data 为要发送的数据 
		 * \return
		 - false 表示要发送的数据无效，不能发送。
		 - true 表示发送的数据有效，可以正常发送。
		 */
		bool SendData(const QByteArray& data);

	private:
		QByteArray m_data_buffer;
		NetworkDataPackage m_package;
		qint64 total = 0;

		//要发送和接收的数据包
		QSharedPointer<QDataStream> mp_out;
		QByteArray m_datasend;

	private slots:
		//发送数据函数
		void SlotSendData(QByteArray data);
		void SlotConnectToHost(QString, qint32);
		void SlotReadyRead();
		void SlotDisconnectFromHost();
		void SlotSocketError(QAbstractSocket::SocketError);

	signals:
		//发送数据信号
		void EventSendData(QByteArray data);
		void EventConnectToHost(QString, qint32);
		void ReqDisonnectFromHost();
	};


	/*!
	 * \class INSHttpRequestAbstract
	 * \ingroup businessAPI_fileModule
	 * \brief HTTP的请求接口，定义请求的槽函数，但是还没有connect。
	 */
	class INSHttpRequestAbstract : public QObject
	{
		Q_OBJECT;

	public:
        explicit INSHttpRequestAbstract(QObject* parent = nullptr);
		~INSHttpRequestAbstract() override;

		QPointer<QNetworkReply> m_netReply;	//HTTP请求的返回对象。
		qint64 m_bytesReceived {0};
		qint64 m_bytesTotal {0};

		/*! 
		 * \brief 该函数主要用途时执行发出HTTP请求。具体的请求内容需要在该函数中重载。
		 * \details 
		 * \param 
		 * \return
		 */
		virtual void RunRequest() = 0;

		/*! 
		 * \brief connect回复的信号。默认connect的信号为readyread信号，finished信号和error信号。槽函数分别为SlotReadyRead，SlotRequestFinished和SlotRequestError。
		 * \details 
		 * \param 
		 * \return
		 */
		virtual void ConnectReplySlot(QNetworkReply* netReply);

		/*! 
		 * \brief 连接readyread信号，从m_netreply中读取数据，并把数据传入函数SlotReadyread。
		 * \details 
		 * \param 
		 * \return
		 */
		virtual void SlotReadDataFromNetReply(qint64 bytesReceived, qint64 bytesTotal);

		/*! 
		 * \brief 关联readyRead信号的槽函数，
		 * \details 
		 * \param[in] byteArray 文件服务器发过来的数据。 
		 * \return
		 */
		virtual void SlotReadyread(QByteArray& byteArray) {}

		/*! 
		 * \brief 关联finished信号的槽函数。
		 * \details 
		 * \param 
		 * \return
		 */
		virtual void SlotRequestFinished() {}

		/*! 
		 * \brief 关联error信号的槽函数
		 * \details 
		 * \param[in] netError HTTP请求的错误信息。
		 * \return
		 */
		virtual void SlotRequestError(QNetworkReply::NetworkError netError) {}

		/*! 
		 * \brief 通过参数的拼接，生成URL字符串。
		 * \details 
		 * \param[in] strAddress 服务器的ip或域名
		 * \param[in] strPort 服务器的端口，如果strAddress为域名，这里可以不填。
		 * \param[in] strPath Url的路径
		 * \param[in] strParam 需要拼接在url路径后面的参数。列表中的每个QString的格式需要为QString("key=value")格式。
		 * \return 字符串的URL。
		 */
		static QString GenerateHttpUrl(QString strAddress, QString strPort, const QString & strPath, const QStringList & strParam = QStringList());

		/*! 
		 * \brief 通过参数，构建一个HTTP请求对象QNetworkRequest。
		 * \details 
		 * \param[in] strUrl HTTP请求的url路径。
		 * \param[in] contentTypeHeader HTTP请求头的类型。默认是application/json。
		 * \return 返回QNetworkReply指针对象。
		 */
		static QNetworkRequest GenerateNetRequest(const QString& strUrl, const char* contentTypeHeader = "application/json");

		/*! 
		 * \brief 关联QNetworkReply对象的信号。信号分别是readyread信号，finished信号和error信号。
		 * \details 
		 * \param[in] reqReply HTTP请求的回复对象。
		 * \param[in] readyreadSlot readyread信号的槽函数的函数指针。
		 * \param[in] finishedSlot finished信号的槽函数的函数指针。
		 * \param[in] errorSlot error信号的槽函数的函数指针。
		 * \return
		 */
		static void ConnectReplySlot(QNetworkReply * reqReply, std::function<void(QByteArray&)> readyreadSlot, std::function<void()> finishedSlot, std::function<void(QNetworkReply::NetworkError)> errorSlot);

	};

};