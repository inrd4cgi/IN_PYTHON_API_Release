#pragma once
#ifndef SFC_MSG_H
#define SFC_MSG_H
#include <qglobal.h>
#include <QDataStream>
#include <QTcpSocket>
#include <QDateTime>

struct SelectInboxEntity
{
	qint32 m_mailID;
	QString m_subject;
	QString m_senderName;
	qint8 m_isRead;
	QDateTime m_receivedate;

	friend QDataStream & operator >> (QDataStream & in, SelectInboxEntity & obj)
	{
		in >> obj.m_mailID >> obj.m_subject >> obj.m_senderName >> obj.m_isRead >> obj.m_receivedate;
		return in;
	}

	friend QDataStream & operator << (QDataStream & out, const SelectInboxEntity & obj)
	{
		out << obj.m_mailID << obj.m_subject << obj.m_senderName << obj.m_isRead << obj.m_receivedate;
		return out;
	}
};

struct SelectSendboxEntity
{
	QString m_subject;
	QList<QString> m_receivers;
	QDateTime m_senddate;

	friend QDataStream & operator >> (QDataStream & in, SelectSendboxEntity & obj)
	{
		in >> obj.m_subject >> obj.m_receivers >> obj.m_senddate;
		return in;
	}

	friend QDataStream & operator << (QDataStream & out, const SelectSendboxEntity & obj)
	{
		out << obj.m_subject << obj.m_receivers << obj.m_senddate;
		return out;
	}
};

struct MailobjEntity
{
	qint32 m_mailID;
	QDateTime m_senddate;
	QString m_subject;
	QString m_senderName;
	qint8 m_isread;
	QList<qint32> m_receiverIdList;
	QMap<QString, qint8> m_receiverList;
	QString m_msg;

	friend QDataStream & operator >> (QDataStream & in, MailobjEntity & obj)
	{
		in >> obj.m_mailID >> obj.m_senddate >> obj.m_subject >> obj.m_senderName >> obj.m_isread >> obj.m_receiverIdList >> obj.m_receiverList >> obj.m_msg;
		return in;
	}

	friend QDataStream & operator << (QDataStream & out, const MailobjEntity & obj)
	{
		out << obj.m_mailID << obj.m_senddate << obj.m_subject << obj.m_senderName << obj.m_isread << obj.m_receiverIdList << obj.m_receiverList << obj.m_msg;
		return out;
	}
};

struct MailListEntity
{
	QList<qint32> m_mailIDList;

	friend QDataStream & operator >> (QDataStream & in, MailListEntity & objlist)
	{
		in >> objlist.m_mailIDList;
		return in;
	}

	friend QDataStream & operator << (QDataStream & out, const MailListEntity & objlist)
	{
		out << objlist.m_mailIDList;
		return out;
	}
};

typedef struct node_msg {
	quint16 mark;
	quint32 uuid;//the same as uuid
	quint8  msgtype;//预留 0x03为头包，0x01为内容，0x2为验证。0x04下载code，0x05上传code。
	quint64 data_length;//实际每个包发送的大小
	quint32 packsize;//分包后的总包数
	quint32 realpacksize;//实际发送过后的实分包总数
	quint32 packno;//发送包的编号
	quint32 fileno;//文件名的解算结果(根据ASCII码+时间值换算)
	quint8	privilege;//权限
}SFC_TRANS_MSG;

typedef struct node_heartBeating {
	quint16 mark;
	quint32 uuid;
}SFC_HEARTBEATING;

typedef struct net_data_pack
{
	//包头31415926
	qint32 head = 31415926;
	qint64 length;
	QByteArray data;
	//包尾31415927
	qint32 tail = 31415927;
	//输入流运算符重载
	friend QDataStream& operator >> (QDataStream& in, net_data_pack& package)
	{
		in >> package.head >> package.length >> package.data >> package.tail;
		return in;
	}
	//输出流运算符重载
	friend QDataStream& operator << (QDataStream& out, net_data_pack& package)
	{
		out << package.head << package.length << package.data << package.tail;
		return out;
	}
}SFC_NETPACK;

SFC_NETPACK g_GenerateNetPack(QByteArray &par_byte_array);
QByteArray g_GeneratePackBytearray(SFC_NETPACK &par_net_pack);
SFC_HEARTBEATING g_GenerateHeartBeat(quint16 n_mark, quint32 n_id);
QByteArray g_GenerateHeartBytearray(SFC_HEARTBEATING &par_hear_beat);
QByteArray g_GenerateTransByte(SFC_TRANS_MSG& par_trans_msg);

//发送数据命令函数。只发送命令。没有数据内容
void g_TcpSendCmd(QTcpSocket *t_socket, qint32 par_cmd);


//发送命令及数据函数。数据中有内容
void g_TcpSendPacket(QTcpSocket *t_socket, QByteArray &par_byte_array);


//接收数据包函数, t_socket为tcp套接字, get_byte是经过处理后还剩下的未处理的数据，Parse_Func是解析函数的函数指针。
void g_RecvPacket(QTcpSocket* t_socket, QByteArray &remain_byte, bool(*Parse_Func)(QByteArray&));
//解析数据包函数，若解析成功或因未数据不足导致的失败返回ture。若因为解包数据出错返回false。
bool gb_ParsePacket(QByteArray &par_byte, void(*Parse_Func)(QByteArray&));

//tcp连接错误返回的socketerror生成字符串
QString g_TcpConnectError(QAbstractSocket::SocketError socketError);


#endif // !SFC_MSG_H

