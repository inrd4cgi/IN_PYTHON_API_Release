#pragma once
#include "insrequest.h"

namespace INS
{

	//通用请求模板
	template<typename Recv, typename Send = qint32>
	class INSCommonRequest :public INSRequest {
	private:
		const static qint32 noUsedData = 0;
	public:
		INSCommonRequest(qint32 serviceId, const Send& sendData = noUsedData) {
			*mp_out << serviceId << m_request_id << sendData;
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				m_return_value = -999;
				m_lock.unlock();
			}
			return;
		}
		~INSCommonRequest() {}

		INQRespondInfo m_return_value;
		Recv retData;
		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			*mp_in >> m_return_value;
			if (m_return_value.code == 1)
			{
				*mp_in >> retData;
			}
			m_finished = true;
			return;
		}
	};

	//通用请求模板,返回值为int
	template<typename Recv, typename Send = qint32>
	class INSCommonRequestRetInt :public INSRequest {
	private:
		const static qint32 noUsedData = 0;
		qint32 m_defaultSucceedValue;

	public:
		INSCommonRequestRetInt(qint32 serviceId, const Send& sendData = noUsedData, qint32 defaultSucceedValue = 1)
		:m_defaultSucceedValue(defaultSucceedValue)
		{
			*mp_out << serviceId << m_request_id << sendData;
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				m_return_value = -999;
				m_lock.unlock();
			}
			return;
		}
		~INSCommonRequestRetInt() {}

		qint32 m_return_value;
		Recv retData;

		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			*mp_in >> m_return_value;
			if (m_return_value == m_defaultSucceedValue)
			{
				*mp_in >> retData;
			}
			m_finished = true;
			return;
		}
	};


	template <qint32 successCode, typename Recv, typename... Args>
	class INVariadicRequest : public INSRequest
	{
	private:
		qint32 code = successCode;

		template <typename Arg>
		void push(Arg arg)
		{
			*mp_out << arg;
		}

		template <typename First, typename... Params>
		void push(First first, Params&&... params)
		{
			push(std::forward<First>(first));
			push(std::forward<Params>(params)...);
		}

	public:
		INVariadicRequest(qint32 serviceId, Args... args)
		{
			*mp_out << serviceId << m_request_id;
			push(args...);
			if (!INSNETWORK->SendDataToAppServer(m_senddata))
			{
				m_return_value = -999;
				m_lock.unlock();
			}
			return;
		}

		qint32 m_return_value{};
		Recv retData;

		void Process(const QByteArray& data) {
			m_data = data;
			mp_in->device()->seek(0);
			*mp_in >> m_return_value;
			if (m_return_value == code)
			{
				*mp_in >> retData;
			}
			m_finished = true;
			return;
		}

	};

	/*****************************************************************************************************/
	//获取职位列表
	class INSGetJobList :public INSRequest
	{
	public:
		INSGetJobList();
		~INSGetJobList() {}

		qint32 m_return_value = 0;
		QList<tag_CIdName> idNames;
		void Process(const QByteArray&);
	};

	//创建IN-admin
	class INSCreateAdmin :public INSRequest
	{
	public:
		Person person;

		qint32 m_return_value = 0;
		INSCreateAdmin(QString& account);
		~INSCreateAdmin() {}
		void Process(const QByteArray& data);
	};

	//移除人员进IN-Space
	class INSRemovePerson :public INSRequest {
	public:
		qint32 m_return_value = 0;
		INSRemovePerson(qint32 personId);
		~INSRemovePerson() {}
		void Process(const QByteArray& data);
	};
	//删除人员
	class INSDeletePerson :public INSRequest {
	public:
		qint32 m_return_value = 0;
		INSDeletePerson(qint32 personId);
		~INSDeletePerson() {}
		void Process(const QByteArray& data);
	};
	//重置密码
	class INSResetPassword :public INSRequest {
	public:
		qint32 m_return_value = 0;
		INSResetPassword(qint32 personId);
		~INSResetPassword() {}
		void Process(const QByteArray& data);
	};

	/*****************************************************************************************************/
	//创建人员
	class INSCreatePerson :public INSRequest
	{
	public:
		INSCreatePerson(Person& person);
		~INSCreatePerson();
		qint32 m_return_value;
		Person m_person;
		void Process(const QByteArray&);
	};

	//请求获取一个指定id的人员.
	class INSGetPerson : public INSRequest
	{
	public:
		INSGetPerson(Person& person);
		~INSGetPerson();

		Person m_person;
		qint32 m_return_value;
		void Process(const QByteArray&);
	};

	//请求修改一个指定id的人员信息。
	class INSModifyPerson : public INSRequest
	{
	public:
		INSModifyPerson(Person& person);
		~INSModifyPerson();

		Person m_person;
		qint32 m_return_value;
		void Process(const QByteArray&);
	};

	//获取人员列表
	class INSGetPersonList : public INSRequest
	{
	public:
		INSGetPersonList(const qint32& department_id, const qint32& team_id, qint32 fileter);
		~INSGetPersonList();

		QList<Person> m_personlist;
		qint32 m_return_value;
		void Process(const QByteArray&);
	};

	//获取自己个人信息
	class INSGetOneself : public INSRequest
	{
	public:
		INSGetOneself();
		~INSGetOneself() {};

		Person m_person;
		qint32 m_return_value;
		void Process(const QByteArray&);
	};
	
	class ReCreateJsonPH : public INSRequest 
	{
	public:
		ReCreateJsonPH(qint32 jsonid, qint32 proid, qint32 taskId);
		~ReCreateJsonPH() {};

		qint32 m_return_value;
		void Process(const QByteArray&);
	};
}