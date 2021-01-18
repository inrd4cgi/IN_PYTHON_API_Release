#include "insdriverpermissioninterface.h"

#include "inscommonhandle.h"

namespace INS_INTERFACE {
    INSDRIVER_EXPORT MessageInfo GetOneselfPermissionInfo(PersonPermissionVO &ret) {
        INSCommonRequest<PersonPermissionVO> commonRequest(212, 0);
        commonRequest.WaitForFinished();
        ret = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetPermissionTemp(INQProjectPermissionVO &temp) {
        INSCommonRequest<INQProjectPermissionVO> commonRequest(206, temp);
        commonRequest.WaitForFinished();
        temp = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetPermissionTemps(const qint32 &prj_id, QList<INQProjectPermissionVO> &temps) {
        INSCommonRequest<QList<INQProjectPermissionVO>> commonRequest(204, prj_id);
        commonRequest.WaitForFinished();
        temps = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo CreatePermissionTemp(INQProjectPermissionVO &temp) {
        INSCommonRequest<INQProjectPermissionVO> commonRequest(207, temp);
        commonRequest.WaitForFinished();
        temp = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo ModifyPermissionTemp(INQProjectPermissionVO &temp) {
        INSCommonRequest<INQProjectPermissionVO> commonRequest(208, temp);
        commonRequest.WaitForFinished();
        temp = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId) {
        INSCommonRequest<qint32> commonRequest(209, prjId, tempId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo
    GetPersonPermissionTemps(QList<INQPersonTemplateVO> &temps, const qint32 &prjId, const qint32 &teamId,
                             const qint32 &tempId) {

        INSCommonRequest<QList<INQPersonTemplateVO>> commonRequest(203, prjId, teamId, tempId);
        commonRequest.WaitForFinished();
        temps = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo
    ModifyPersonPermissionTemp(const INQPersonTemplateVO &temp, QList<INQPersonTemplateVO> &temps) {

        INSCommonRequest<QList<INQPersonTemplateVO>> commonRequest(205, temp);
        commonRequest.WaitForFinished();
        temps = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleAsset(QList<IdName> &assets, qint32 projectId, qint32 roleId) {
        INSCommonRequest<QList<IdName>> commonRequest(251, projectId, roleId);
        commonRequest.WaitForFinished();
        assets = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleShot(QList<IdName> &shots, qint32 projectId, qint32 roleId) {
        INSCommonRequest<QList<IdName>> commonRequest(252, projectId, roleId);
        commonRequest.WaitForFinished();
        shots = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleSequence(QList<IdName> &sequences, qint32 projectId, qint32 roleId) {
        INSCommonRequest<QList<IdName>> commonRequest(255, projectId, roleId);
        commonRequest.WaitForFinished();
        sequences = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleAsset(qint32 roleId, QList<DataAuthVO> &assets) {
        INSCommonRequest<qint32> commonRequest(253, roleId, assets);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleShot(qint32 roleId, QList<DataAuthVO> &shots) {
        INSCommonRequest<qint32> commonRequest(254, roleId, shots);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleSequence(qint32 roleId, QList<DataAuthVO> &sequence) {
        INSCommonRequest<qint32> commonRequest(256, roleId, sequence);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetPersonApprovalInfo(qint32 &approvalType, qint32 personId, qint32 prjId) {

        INSCommonRequest<qint32> commonRequest(535, prjId, personId);
        commonRequest.WaitForFinished();
        approvalType = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }
};