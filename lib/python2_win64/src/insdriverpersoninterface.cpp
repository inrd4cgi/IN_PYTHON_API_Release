#include "insdriverpersoninterface.h"

#include "inscommonhandle.h"

namespace INS_INTERFACE {

    INSDRIVER_EXPORT qint32 GetJobList(QList<IdName> &idNames) {
        INSCommonRequestRetInt<QList<IdName>, qint32> commonRequest(134, 0);
        commonRequest.WaitForFinished();
        idNames = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 CreateAdmin(Person &person) {

        INSCommonRequestRetInt<Person, QString> commonRequest(135, person.account);
        commonRequest.WaitForFinished();
        person = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 RemovePerson(qint32 personId) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(136, personId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 DeletePerson(qint32 personId) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(137, personId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 ResetPassword(qint32 personId) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(138, personId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 ModifyPerson(Person &person) {

        INSCommonRequestRetInt<Person, Person> commonRequest(117, person);
        commonRequest.WaitForFinished();
        person = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetPerson(Person &person) {

        INSCommonRequestRetInt<Person, Person> commonRequest(118, person);
        commonRequest.WaitForFinished();
        person = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 CreatePerson(Person &person) {

        INSCommonRequestRetInt<Person, Person> commonRequest(113, person);
        commonRequest.WaitForFinished();
        person = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTeams(QList<Team> &teams, const qint32 &department_id, qint32 projectId) {

        INSCommonRequestRetInt<QList<Team>, qint32, qint32> commonRequest(122, department_id, projectId);
        commonRequest.WaitForFinished();
        teams = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 CreateTeam(Team &teaminfo) {

        INSCommonRequestRetInt<Team, Team> commonRequest(124, teaminfo);
        commonRequest.WaitForFinished();
        teaminfo = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 DeleteTeam(const qint32 &teamid) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(127, teamid);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetTeam(Team &team) {

        INSCommonRequestRetInt<Team, Team> commonRequest(131, team);
        commonRequest.WaitForFinished();
        team = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 DeleteDepartment(const qint32 &departmentid) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(128, departmentid);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 CreateDepartment(Department &department) {

        INSCommonRequestRetInt<Department, Department> commonRequest(123, department);
        commonRequest.WaitForFinished();
        department = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetDepartments(QList<Department> &departments, qint32 filter) {

        INSCommonRequestRetInt<QList<Department>, qint32> commonRequest(121, filter);
        commonRequest.WaitForFinished();
        departments = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32
    GetPersonList(QList<Person> &personlist, const qint32 &department_id, const qint32 &team_id, qint32 fileter) {

        INSCommonRequestRetInt<QList<Person>, qint32, qint32, qint32> commonRequest(125, department_id, team_id,
                                                                                    fileter);
        commonRequest.WaitForFinished();
        personlist = commonRequest.retData;
        return commonRequest.m_return_value;
    }


    INSDRIVER_EXPORT qint32 ModifyTeam(Team &team) {

        INSCommonRequestRetInt<Team, Team> commonRequest(129, team);
        commonRequest.WaitForFinished();
        team = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 ModifyDepartment(Department &department) {

        INSCommonRequestRetInt<Department, Department> commonRequest(130, department);
        commonRequest.WaitForFinished();
        department = commonRequest.retData;
        return commonRequest.m_return_value;

    }

    INSDRIVER_EXPORT qint32 GetDepartment(Department &department) {

        INSCommonRequestRetInt<Department, Department> commonRequest(132, department);
        commonRequest.WaitForFinished();
        department = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetOneself(Person &person) {

        INSCommonRequestRetInt<Person, qint32> commonRequest(133, 0);
        commonRequest.WaitForFinished();
        person = commonRequest.retData;
        return commonRequest.m_return_value;
    }
};