#pragma once

#include "insdatastructure.h"
#include "insdriver_global.h"


namespace INS_INTERFACE
{

	//获取职位列表,返回idNames
	extern "C" INSDRIVER_EXPORT qint32 GetJobList(QList<IdName>& idNames);

	//创建IN-admin账号
	//account必填
	extern "C" INSDRIVER_EXPORT qint32 CreateAdmin(Person& person);

	//移除人员至IN-Space
	//personId
	extern "C" INSDRIVER_EXPORT qint32 RemovePerson(qint32 personId);

	//删除人员
	//personId
	extern "C" INSDRIVER_EXPORT qint32 DeletePerson(qint32 personId);

	//重置密码
	extern "C" INSDRIVER_EXPORT qint32 ResetPassword(qint32 personId, QString newPassword);

	//创建一个团队,团队名不能为空。创建时可以指明队长和成员，可以不指明部门。
	//返回说明：1==创建成功;0==没有权限,-1==部门名已被占用,-2==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 CreateTeam(Team& teaminfo);

	//删除一个团队。参数[teamid]为要删除的团队id。
	//返回说明：1==删除成功;0==没有权限;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 DeleteTeam(const qint32& teamid);

	//获取指定团队[team]的信息,team中有id属性就可以了。
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetTeam(Team& team);

	//删除一个部门,参数[departmentid]为要删除的部门id
	//返回说明：1==删除成功;0==没有权限;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 DeleteDepartment(const qint32& departmentid);

	//创建一个部门,部门名不能为空。创建时可以指明团队。
	//返回说明：1==创建成功;0==没有权限,-1==部门名已被占用,-2==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 CreateDepartment(Department& department);

	//获取系统中所有部门的列表[departments]。
	//filter为过滤器，默认为0，不做额外操作。第一位0表示不获取in space，为1表示获取。第二位为0 表示不获取in Admin，为1表示获取。
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetDepartments(QList<Department>& departments, qint32 filter = 0);

	//获取指定部门[department_id]下,或指定团队[team_id]的人员列表[personlist]。[department_id]和[team_id]默认为0，表示不做限制。
	//filter为过滤器，默认为0，不做额外操作。第一位0表示不获取in space的人员，为1表示获取。第二位为0 表示不获取in Admin的人员，为1表示获取。
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetPersonList(QList<Person>& personlist, const qint32& department_id = 0, const qint32& team_id = 0, qint32 fileter = 0);

	//获取指定部门[department_id]下的团队列表。[department_id]默认值0，表示不做限制。
	//返回说明：1==获取成功;0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetTeams(QList<Team>& teams, const qint32& department_id = 0, qint32 projectId = 0);

	//通过person的id修改人员[person]的信息,[person]为引用。
	//返回说明：1==修改成功，person为修改后的状态;0==数据出错,person为修改前状态;-1==权限不足,person为修改前状态。
	extern "C" INSDRIVER_EXPORT qint32 ModifyPerson(Person& person);

	//通过person的id获取一个[person]的信息,[person]中id属性正确就可以了。
	//返回说明：1==获取成功,0==获取失败。
	extern "C" INSDRIVER_EXPORT qint32 GetPerson(Person& person);

	//创建一个人员[person]。其中姓名，性别(male,female)，工作状态(fired,resigned,on_leave,part_time,full_time)为必填内容。
	//返回说明：1==创建成功,0==权限不足,-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 CreatePerson(Person& person);

	//修改团队信息。可以修改成员，队长，所属部门。
	//返回说明：1==修改成功;0==权限不足;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 ModifyTeam(Team& team);

	//修改部门信息。可以修改部门所拥有的团队，部门名。
	//返回说明：1==修改成功;0==权限不足;-1==数据出错。
	extern "C" INSDRIVER_EXPORT qint32 ModifyDepartment(Department& department);

	//获取指定部门[department]信息,部门id正确就可以了。
	//返回说明：1==获取成功;0==获取失败;
	extern "C" INSDRIVER_EXPORT qint32 GetDepartment(Department& department);

	//获取自己个人信息。
	//返回说明：1==获取成功;0==获取失败;
	extern "C" INSDRIVER_EXPORT qint32 GetOneself(Person& person);
};