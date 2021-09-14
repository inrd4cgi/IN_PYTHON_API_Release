#include "sfc_msg.h"
#include <qmutex.h>
#include <qobject.h>
#include <QDebug>

static const qint32 NET_HEAD_BEGIN = 31415926;
static const qint32 NET_HEAD_END = 31415927;

//生成SFC_NETPACK结构体对象
SFC_NETPACK g_GenerateNetPack(QByteArray &par_byte_array)
{
	SFC_NETPACK net_packet;
	net_packet.data = par_byte_array;
	net_packet.length = qint64(par_byte_array.size() + (sizeof(qint32) * 3) + sizeof(qint64));

	return net_packet;
}

//根据SFC_NETPACK结构体生成字节数数组
QByteArray g_GeneratePackBytearray(SFC_NETPACK &par_net_pack)
{
	QByteArray byte_array;
	QDataStream data_stream(&byte_array, QIODevice::WriteOnly);
	data_stream << par_net_pack;

	return byte_array;
}

//根据n_mark和n_id生成心跳包的结构体SFC_HEARTBEATING。n_mark是上传或下载标志，n_id是用户的id。
//上传下载0xADAD, 心跳0xBEBE
SFC_HEARTBEATING g_GenerateHeartBeat(quint16 n_mark, quint32 n_id)
{
	SFC_HEARTBEATING hear_beat;
	hear_beat.mark = n_mark;
	hear_beat.uuid = n_id;

	return hear_beat;
}

//把par_hear_beat结构体的数据传入qbytearray，并返回一个qbytearray。
QByteArray g_GenerateHeartBytearray(SFC_HEARTBEATING &par_hear_beat)
{
	QByteArray byte_array(sizeof(par_hear_beat), 0);
	SFC_HEARTBEATING *heat_beat = (SFC_HEARTBEATING*)byte_array.data();
	heat_beat->mark = par_hear_beat.mark;
	heat_beat->uuid = par_hear_beat.uuid;

	return byte_array;
}

//将SFC_TRANS_MSG结构体放入字节数组qbytearray中
QByteArray g_GenerateTransByte(SFC_TRANS_MSG& par_trans_msg)
{
	QByteArray byte_array(sizeof(par_trans_msg), 0);
	SFC_TRANS_MSG* trans_msg = (SFC_TRANS_MSG*)byte_array.data();
	trans_msg->mark = par_trans_msg.mark;
	trans_msg->uuid = par_trans_msg.uuid;
	trans_msg->msgtype = par_trans_msg.msgtype;
	trans_msg->data_length = par_trans_msg.data_length;

	return byte_array;
}

QString g_TcpConnectError(QAbstractSocket::SocketError socketError)
{
	QString str_error;
	switch (socketError)
	{
	case QAbstractSocket::HostNotFoundError:
		str_error = QObject::tr("The host address was not found!");
		break;
	case QAbstractSocket::SocketTimeoutError:
		str_error = QObject::tr("The socket operation timed out!");
		break;
	case QAbstractSocket::NetworkError:
		str_error = QObject::tr("An error occurred with the network!");
		break;
	default:
		str_error = QObject::tr("Tcp error!");
		break;
	}
	return str_error;
}

//接收数据包。若数据包满足最小数据包大小。则尝试解析数据包，并把函数指针传入解析函数中。
void g_RecvPacket(QTcpSocket* t_socket, QByteArray &remain_byte, void(*Parse_Func)(QByteArray&))
{
	bool ret_bool;
	do
	{
		QByteArray byte_current = t_socket->readAll();
		ret_bool = byte_current.isEmpty();
		if (!ret_bool)
			remain_byte += byte_current;
	} while (!ret_bool);
	
	if (remain_byte.size() >= ((sizeof(qint32) * 2) + sizeof(qint64)))
	{
		ret_bool = gb_ParsePacket(remain_byte, Parse_Func);
		if (ret_bool == false)
			remain_byte.clear();
	}
}

//解析数据包中的数据, 提取出数据。如果解析出错，返回false.则移除清空字节数组（byte_array）。
//解析数据包成功或因数据不完整导致失败，返回true
bool gb_ParsePacket(QByteArray &par_byte, void(*Parse_Func)(QByteArray&))
{
	qint64 used_length = 0;
	qint64 remain_size = par_byte.size();
	SFC_NETPACK net_pack;
	QDataStream data_stream(par_byte);
	data_stream >> net_pack.head >> net_pack.length;

	while (remain_size >= net_pack.length)
	{
		data_stream >> net_pack.data >> net_pack.tail;
		if ((net_pack.head == NET_HEAD_BEGIN) && (net_pack.tail == NET_HEAD_END))
		{
			Parse_Func(net_pack.data);		//通过信号发送读取出来的数据
			used_length += net_pack.length;
			remain_size -= net_pack.length;

			//判断剩余的字节数组是否大于等于数据包大小，是则输出头和长度，清空数据和尾，继续解包。
			if (remain_size >= ((sizeof(qint32) * 2) + sizeof(qint64)))
			{
				data_stream >> net_pack.head >> net_pack.length;
				net_pack.data = 0;
				net_pack.tail = 0;
			}
		}
		else
		{
			qDebug() << "package analyze error!";
			return false;
		}
			
	}

	if (used_length > 0)
		par_byte.remove(0, used_length);//移除已经解析成功的数据

	return true;
}

//发送数据包。并且打印发送的id信息和tcp状态
void g_TcpSendPacket(QTcpSocket *t_socket, QByteArray &par_byte_array)
{
	SFC_NETPACK net_packet = g_GenerateNetPack(par_byte_array);
	QByteArray byte_array = g_GeneratePackBytearray(net_packet);
	t_socket->write(byte_array);

	QDataStream ds(par_byte_array);
	qint32 cmd_id;
	ds >> cmd_id;
	qInfo() << cmd_id << t_socket->state();
}

//tcp发送数据包。但是数据包内只有命令，没有其他内容
void g_TcpSendCmd(QTcpSocket *t_socket, qint32 par_cmd)
{
	QByteArray array_cmd;
	QDataStream data_stream(&array_cmd, QIODevice::WriteOnly);
	data_stream << par_cmd;

	SFC_NETPACK net_packet = g_GenerateNetPack(array_cmd);
	QByteArray byte_array = g_GeneratePackBytearray(net_packet);
	t_socket->write(byte_array);

	qInfo() << par_cmd << t_socket->state();
}
