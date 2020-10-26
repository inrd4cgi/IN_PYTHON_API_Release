#pragma once

#include "insdriver_global.h"
#include "insdatastructure.h"

namespace INS_INTERFACE
{

	INSDRIVER_EXPORT INQRespondInfo GetOneselfPermissionInfo(PersonPermissionVO& ret);

	//获取指定的项目权限。项目id和权限id要保证正确。
	INSDRIVER_EXPORT INQRespondInfo GetPermissionTemp(INQProjectPermissionVO& temp);

	//获取项目权限列表，项目id要保证正确。
	INSDRIVER_EXPORT INQRespondInfo GetPermissionTemps(const qint32& prj_id, QList<INQProjectPermissionVO>& temps);

	INSDRIVER_EXPORT INQRespondInfo CreatePermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT INQRespondInfo ModifyPermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT INQRespondInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId);

	//获取人员权限列表，项目id，团队id，模板id为筛选条件。
	INSDRIVER_EXPORT INQRespondInfo GetPersonPermissionTemps(QList<INQPersonTemplateVO>& temps, const qint32& prjId = 0, const qint32& teamId = 0, const qint32& tempId = 0);

	INSDRIVER_EXPORT INQRespondInfo ModifyPersonPermissionTemp(const INQPersonTemplateVO& temp, QList<INQPersonTemplateVO>& temps);

	INSDRIVER_EXPORT INQRespondInfo GetOneSelfAdminTemp(INQAdministrationPermissionVO& temp);
};