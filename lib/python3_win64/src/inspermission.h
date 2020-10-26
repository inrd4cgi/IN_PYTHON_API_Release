#pragma once

#include "insrequest.h"

namespace INS
{
	//获取文件模板
	class INSGetPermissionTemp : public INSRequest
	{
	public:
		INSGetPermissionTemp(INQProjectPermissionVO& prj_temp);
		~INSGetPermissionTemp() { ; }
		INQRespondInfo m_response;
		INQProjectPermissionVO m_temp;
		void Process(const QByteArray& data);
	};



	//获取文件模板列表
	class INSGetPermissionTempS : public INSRequest
	{
	public:
		INSGetPermissionTempS(const qint32& prj_id);
		~INSGetPermissionTempS() { ; }

		INQRespondInfo m_response;
		QList<INQProjectPermissionVO> m_temps;
		void Process(const QByteArray& data);
	};


	//创建权限模板
	class INSCreatePermissionTemp : public INSRequest
	{
	public:
		INSCreatePermissionTemp(const INQProjectPermissionVO& temp);

		INQRespondInfo m_response;
		INQProjectPermissionVO m_temp;
		void Process(const QByteArray& data);
	};

	
	//修改权限模板
	class INSModifyPermissionTemp : public INSRequest
	{
	public:
		INSModifyPermissionTemp(const INQProjectPermissionVO& temp);

		INQRespondInfo m_response;
		INQProjectPermissionVO m_temp;
		void Process(const QByteArray& data);
	};

	//INSDeletePermissionTemp
	class INSDeletePermissionTemp : public INSRequest
	{
	public:
		INSDeletePermissionTemp(const qint32& prjId, const qint32 tempId);

		INQRespondInfo m_response;
		void Process(const QByteArray& data);
	};

	//获取人员权限模板
	class INSGetPersonPermissionTemps : public INSRequest
	{
	public:
		INSGetPersonPermissionTemps(const qint32& prjId, const qint32& teamId, const qint32& tempId);

		INQRespondInfo m_response;
		QList<INQPersonTemplateVO> m_temps;
		void Process(const QByteArray& data);
	};


	//修改人员权限模板
	class INSModifyPersonPermissionTemp : public INSRequest
	{
	public:

		INSModifyPersonPermissionTemp(const INQPersonTemplateVO& temp);

		INQRespondInfo m_response;
		QList<INQPersonTemplateVO> m_temps;
		void Process(const QByteArray& data);
	};


	class INSGetOneSelfAdminTemp : public INSRequest
	{
	public:
		INSGetOneSelfAdminTemp();
		INQRespondInfo m_response;
		INQAdministrationPermissionVO m_temp;
		void Process(const QByteArray& data);
	};

};