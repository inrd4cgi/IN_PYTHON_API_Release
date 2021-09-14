#pragma once

#include <QObject>
#include <QtConcurrent>
#include <QThreadPool>
#include <QThread>
#include <QMutex>
#include <QSharedPointer>

#define INSREPLYPARES INSReplyParse::GetInstance()
namespace INS
{
	class INSReplyParse : public QObject
	{
		Q_OBJECT

	public:
		void AppendAReply(QByteArray&);
		static INSReplyParse* GetInstance();

	private:
		INSReplyParse(QObject *parent);
		~INSReplyParse() {};
		static INSReplyParse* gp_instance;
	};
};