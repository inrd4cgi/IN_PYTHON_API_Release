#include "insdriverpersoninterface.h"

#include "inspersonhandle.h"
#include "insdllteamhandle.h"
#include "insdepartmenthandle.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT qint32 GetJobList(QList<tag_CIdName> &idNames) {
		INSGetJobList jobList;
		jobList.WaitForFinished();
		idNames = jobList.idNames;
		return jobList.m_return_value;
	}

	INSDRIVER_EXPORT qint32 CreateAdmin(Person &person) {
		INSCreateAdmin createAdmin(person.account);
		createAdmin.WaitForFinished();
		person = createAdmin.person;
		return createAdmin.m_return_value;
	}

	INSDRIVER_EXPORT qint32 RemovePerson(qint32 personId) {
		INSRemovePerson removePerson(personId);
		removePerson.WaitForFinished();
		return removePerson.m_return_value;
	}

	INSDRIVER_EXPORT qint32 DeletePerson(qint32 personId) {
		INSDeletePerson deletePerson(personId);
		deletePerson.WaitForFinished();
		return deletePerson.m_return_value;
	}

	INSDRIVER_EXPORT qint32 ResetPassword(qint32 personId) {
		INSResetPassword resetPassword(personId);
		resetPassword.WaitForFinished();
		return resetPassword.m_return_value;
	}

	INSDRIVER_EXPORT qint32 ModifyPerson(Person &person) {
		INSModifyPerson moduserinfo(person);
		moduserinfo.WaitForFinished();
		person = moduserinfo.m_person;
		return moduserinfo.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetPerson(Person &person) {
		INSGetPerson getperson(person);
		getperson.WaitForFinished();
		person = getperson.m_person;
		return getperson.m_return_value;
	}

	INSDRIVER_EXPORT qint32 CreatePerson(Person &person) {
		INSCreatePerson createperson(person);
		createperson.WaitForFinished();
		person = createperson.m_person;
		return createperson.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTeams(QList<TeamInfomation> &teams, const qint32 &department_id, qint32 projectId) {
		INSGetTeams getteams(department_id, projectId);
		getteams.WaitForFinished();
		teams = getteams.m_teams;
		return getteams.m_return_value;
	}

	INSDRIVER_EXPORT qint32 CreateTeam(TeamInfomation &teaminfo) {
		INSCreateTeam createteam(teaminfo);
		createteam.WaitForFinished();
		teaminfo = createteam.m_teaminfo;
		return createteam.m_return_value;
	}

	INSDRIVER_EXPORT qint32 DeleteTeam(const qint32 &teamid) {
		INSDeleteTeam deleteteam(teamid);
		deleteteam.WaitForFinished();
		return deleteteam.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetTeam(TeamInfomation &team) {
		INSGetTeam getteam(team);
		getteam.WaitForFinished();
		team = getteam.m_team;
		return getteam.m_return_value;
	}

	INSDRIVER_EXPORT qint32 DeleteDepartment(const qint32 &departmentid) {
		INSDeleteDepartment deletedepartment(departmentid);
		deletedepartment.WaitForFinished();
		return deletedepartment.m_return_value;
	}

	INSDRIVER_EXPORT qint32 CreateDepartment(Department &department) {
		INSCreateDepartment createprojectgroup(department);
		createprojectgroup.WaitForFinished();
		department = createprojectgroup.m_department;
		return createprojectgroup.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetDepartments(QList<Department> &departments, qint32 filter) {
		INSGetDepartmentList getdepartments(filter);
		getdepartments.WaitForFinished();
		departments = getdepartments.m_departments;
		return getdepartments.m_return_value;
	}

	INSDRIVER_EXPORT qint32
		GetPersonList(QList<Person> &personlist, const qint32 &department_id, const qint32 &team_id, qint32 fileter) {
		INSGetPersonList getpersonlist(department_id, team_id, fileter);
		getpersonlist.WaitForFinished();
		personlist = getpersonlist.m_personlist;
		return getpersonlist.m_return_value;
	}


	INSDRIVER_EXPORT qint32 ModifyTeam(TeamInfomation &team) {
		INSModifyTeam modifyteam(team);
		modifyteam.WaitForFinished();
		team = modifyteam.m_team;
		return modifyteam.m_return_value;
	}

	INSDRIVER_EXPORT qint32 ModifyDepartment(Department &department) {
		INSModifyDepartment modifydepartment(department);
		modifydepartment.WaitForFinished();
		department = modifydepartment.m_department;
		return modifydepartment.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetDepartment(Department &department) {
		INSGetDepartment getdepartment(department);
		getdepartment.WaitForFinished();
		department = getdepartment.m_department;
		return getdepartment.m_return_value;
	}

	INSDRIVER_EXPORT qint32 GetOneself(Person &person) {
		INSGetOneself getoneself;
		getoneself.WaitForFinished();
		person = getoneself.m_person;
		return getoneself.m_return_value;
	}
};