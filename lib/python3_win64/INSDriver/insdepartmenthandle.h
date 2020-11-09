#pragma once
#include "insrequest.h"
#include <QMap>

namespace INS
{
	//获取系统中所有的项目列表。
	class INSGetDepartmentList :public INSRequest
	{
	public:
		INSGetDepartmentList(qint32 filter);
		~INSGetDepartmentList() {}

		qint32 m_return_value = 0;
		QList<Department> m_departments;
		void Process(const QByteArray&);
	};

	//创建一个部门
	class INSCreateDepartment : public INSRequest
	{
	public:
		INSCreateDepartment(ProjectGroup& department);
		~INSCreateDepartment();

		qint32 m_return_value = 0;
		ProjectGroup m_department;
		void Process(const QByteArray& data);
	};

	//删除一个部门
	class INSDeleteDepartment : public INSRequest
	{
	public:
		INSDeleteDepartment(const qint32& departmentid);
		~INSDeleteDepartment() {};

		qint32 m_return_value = 0;
		void Process(const QByteArray& data);
	};

	//修改一个部门
	class INSModifyDepartment :public INSRequest
	{
	public:
		INSModifyDepartment(const Department& department);
		~INSModifyDepartment() {};

		qint32 m_return_value = 0;
		Department m_department;
		void Process(const QByteArray& data);
	};

	//获取一个部门
	class INSGetDepartment :public INSRequest
	{
	public:
		INSGetDepartment(const Department& department);
		~INSGetDepartment() {};

		qint32 m_return_value = 0;
		Department m_department;
		void Process(const QByteArray& data);
	};
}