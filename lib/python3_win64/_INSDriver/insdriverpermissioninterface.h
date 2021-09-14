#pragma once

#include "insdriver_global.h"
#include "insdatastructure.h"

namespace INS_INTERFACE
{

	INSDRIVER_EXPORT MessageInfo GetOneselfPermissionInfo(PersonPermissionVO& ret);

	//获取指定的项目权限。项目id和权限id要保证正确。
	INSDRIVER_EXPORT MessageInfo GetPermissionTemp(INQProjectPermissionVO& temp);

	//获取项目权限列表，项目id要保证正确。
	INSDRIVER_EXPORT MessageInfo GetPermissionTemps(const qint32& prj_id, QList<INQProjectPermissionVO>& temps);

	INSDRIVER_EXPORT MessageInfo CreatePermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT MessageInfo ModifyPermissionTemp(INQProjectPermissionVO& temp);

	INSDRIVER_EXPORT MessageInfo DeletePermissionTemp(const qint32 prjId, const qint32 tempId);

	//获取人员权限列表，项目id，团队id，模板id为筛选条件。
	INSDRIVER_EXPORT MessageInfo GetPersonPermissionTemps(QList<INQPersonTemplateVO>& temps, const qint32& prjId = 0, const qint32& teamId = 0, const qint32& tempId = 0);

	INSDRIVER_EXPORT MessageInfo ModifyPersonPermissionTemp(const INQPersonTemplateVO& temp, QList<INQPersonTemplateVO>& temps);

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleAsset(QList<IdName> &assets, qint32 projectId, qint32 roleId);

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleShot(QList<IdName> &shots, qint32 projectId, qint32 roleId);

    INSDRIVER_EXPORT MessageInfo GetRoleAccessibleSequence(QList<IdName> &sequences, qint32 projectId, qint32 roleId);

    /*!
     * \brief 更新可看的资产和镜头
     * \details
     * \param[in]roleId 模板id。
     * \param[in]assets 模板资产列表。
     * \param[in]DataAuthVO.roleId 模板id,必填。
     * \param[in]DataAuthVO.actionId 权限id,必填。
     * \param[in]DataAuthVO.resourceId 资产或镜头id,必填。
     * \return
     */
    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleAsset(qint32 roleId, QList<DataAuthVO> &assets);

    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleShot(qint32 roleId, QList<DataAuthVO> &shots);

    INSDRIVER_EXPORT MessageInfo UpdateRoleAccessibleSequence(qint32 roleId, QList<DataAuthVO> &sequence);


    /*!
     * \brief 查询当前人员是否审批类型，如果是，并获取审批类型
     * \details
     * \param[out]approvalType 审批人员的类型，0为普通人员，1为普通批员，2为默认审批员
     * \param[in]personId 被查询的人员id
     * \param[in]prjId 查询的项目id。0表示所有项目
     * \return
     */

	INSDRIVER_EXPORT MessageInfo GetPersonApprovalInfo(qint32& approvalType, qint32 personId, qint32 prjId = 0);

};