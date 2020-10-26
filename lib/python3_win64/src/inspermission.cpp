#include "inspermission.h"

/**************************************************************************************************
Description:获取权限模板
**************************************************************************************************/
INS::INSGetPermissionTemp::INSGetPermissionTemp(INQProjectPermissionVO & prj_temp)
{
	*mp_out << qint32(206) << m_request_id << prj_temp;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==获取成功;0==获取失败;
**************************************************************************************************/
void INS::INSGetPermissionTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	if (m_response.code == 1)
		*mp_in >> m_temp;
	m_finished = true;
	return;
}

/**************************************************************************************************
Description:获取权限模板列表
**************************************************************************************************/
INS::INSGetPermissionTempS::INSGetPermissionTempS(const qint32& prj_id)
{
	*mp_out << qint32(204) << m_request_id << prj_id;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==获取成功;0==获取失败;
**************************************************************************************************/
void INS::INSGetPermissionTempS::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	if (m_response.code == 1)
		*mp_in >> m_temps;
	m_finished = true;
	return;
}

/**************************************************************************************************
Description:创建权限模板INQProjectPermissionVO
**************************************************************************************************/
INS::INSCreatePermissionTemp::INSCreatePermissionTemp(const INQProjectPermissionVO & temp)
{
	*mp_out << qint32(207) << m_request_id << temp;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/
void INS::INSCreatePermissionTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	if (m_response.code == 1)
		*mp_in >> m_temp;
	m_finished = true;
	return;
}


/**************************************************************************************************
Description:修改权限模板INQProjectPermissionVO
**************************************************************************************************/
INS::INSModifyPermissionTemp::INSModifyPermissionTemp(const INQProjectPermissionVO & temp)
{
	*mp_out << qint32(208) << m_request_id << temp;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/
void INS::INSModifyPermissionTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	if (m_response.code == 1)
		*mp_in >> m_temp;
	m_finished = true;
	return;
}


/**************************************************************************************************
Description:删除权限模板INQProjectPermissionVO
**************************************************************************************************/
INS::INSDeletePermissionTemp::INSDeletePermissionTemp(const qint32& prjId, const qint32 tempId)
{
	*mp_out << qint32(209) << m_request_id << prjId << tempId;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

void INS::INSDeletePermissionTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	m_finished = true;
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/


/**************************************************************************************************
Description:获取人员模板列表INQPersonTemplateVO
**************************************************************************************************/
INS::INSGetPersonPermissionTemps::INSGetPersonPermissionTemps(const qint32 & prjId, const qint32 & teamId, const qint32 & tempId)
{
	*mp_out << qint32(203) << m_request_id << prjId << teamId << tempId;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/
void INS::INSGetPersonPermissionTemps::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response;
	if (m_response.code == 1)
		*mp_in >> m_temps;
	m_finished = true;
	return;
}

/**************************************************************************************************
Description:修改人员权限模板INQPersonTemplateVO
**************************************************************************************************/
INS::INSModifyPersonPermissionTemp::INSModifyPersonPermissionTemp(const INQPersonTemplateVO & temp)
{
	*mp_out << qint32(205) << m_request_id << temp;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}

/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/
void INS::INSModifyPersonPermissionTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response >> m_temps;
	m_finished = true;
	return;
}

/**************************************************************************************************
Description:修改人员权限模板INQPersonTemplateVO
**************************************************************************************************/
INS::INSGetOneSelfAdminTemp::INSGetOneSelfAdminTemp()
{
	*mp_out << qint32(210) << m_request_id;
	if (!INSNETWORK->SendDataToAppServer(m_senddata))
	{
		m_response.code = -999;
		m_lock.unlock();
	}
	return;
}


/**************************************************************************************************
Description:服务器返回数据[data]处理函数。1==创建成功;0==权限不足;-1==创建失败，数据出错。
**************************************************************************************************/
void INS::INSGetOneSelfAdminTemp::Process(const QByteArray & data)
{
	m_data = data;
	mp_in->device()->seek(0);
	*mp_in >> m_response >> m_temp;
	m_finished = true;
	return;
}