#include "insdriverpermissioninterface.h"

#include "inspersonhandle.h"
#include "inspermission.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT INQRespondInfo GetOneselfPermissionInfo(PersonPermissionVO &ret) {
		INSCommonRequest<PersonPermissionVO> commonRequest(212, 0);
		commonRequest.WaitForFinished();
		ret = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetPermissionTemp(INQProjectPermissionVO &temp) {
		INSGetPermissionTemp prjTemp(temp);
		prjTemp.WaitForFinished();
		temp = prjTemp.m_temp;
		return prjTemp.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo GetPermissionTemps(const qint32 &prj_id, QList<INQProjectPermissionVO> &temps) {
		INSGetPermissionTempS prjTemps(prj_id);
		prjTemps.WaitForFinished();
		temps = prjTemps.m_temps;
		return prjTemps.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo CreatePermissionTemp(INQProjectPermissionVO &temp) {
		INSCreatePermissionTemp prjTemp(temp);
		prjTemp.WaitForFinished();
		temp = prjTemp.m_temp;
		return prjTemp.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo ModifyPermissionTemp(INQProjectPermissionVO &temp) {
		INSModifyPermissionTemp prjTemp(temp);
		prjTemp.WaitForFinished();
		temp = prjTemp.m_temp;
		return prjTemp.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId) {
		INSDeletePermissionTemp prjTemp(prjId, tempId);
		prjTemp.WaitForFinished();
		return prjTemp.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo
		GetPersonPermissionTemps(QList<INQPersonTemplateVO> &temps, const qint32 &prjId, const qint32 &teamId,
			const qint32 &tempId) {
		INSGetPersonPermissionTemps personTemps(prjId, teamId, tempId);
		personTemps.WaitForFinished();
		temps = personTemps.m_temps;
		return personTemps.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo
		ModifyPersonPermissionTemp(const INQPersonTemplateVO &temp, QList<INQPersonTemplateVO> &temps) {
		INSModifyPersonPermissionTemp personTemp(temp);
		personTemp.WaitForFinished();
		temps = personTemp.m_temps;
		return personTemp.m_response;
	}

	INSDRIVER_EXPORT INQRespondInfo GetOneSelfAdminTemp(INQAdministrationPermissionVO &temp) {
		INSGetOneSelfAdminTemp getTemp;
		getTemp.WaitForFinished();
		temp = getTemp.m_temp;
		return getTemp.m_response;
	}
};