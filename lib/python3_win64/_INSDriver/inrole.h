#pragma once
#include "JsonMessageUtils.h"
#include <QMap>
#include <QDateTime>

namespace INS
{
    //角色的类型[-1：系统管理者角色，0：通用角色，1：人员行政角色[部门角色]，2：项目角色，3：文件角色，4：task角色，5：团队角色]
    enum class RoleTypeEnum {
        SYSTEM_ADMIN = -1,//系统管理者类型
        COMMON = 0,//通用类型
        DEPARTMENT = 1,//人员行政类型[部门类型]
        PROJECT = 2,//项目类型
        FILE = 3,//文件类型
        TASK = 4,//[task]pipeline-step类型
        TEAM = 5//团队角色
    };

	enum class SystemRoleEnum {
		ROOT = 1,
		ADMIN = 2,
		DEPARTMENT_ROOT = 3,
		DEPARTMENT_ADMIN = 4,
		PROJECT_ROOT = 5,
		PROJECT_ADMIN = 6,
		//TASK_LEADER = 7,
		NOTIFICATION = 8,
		DEPARTMENT_GENERAL = 9,
		PROJECT_GENERAL = 10,
		PROJECT_DIRECTOR = 11,
		PIPELINE_TD = 12,
		TEAM_LEADER = 13,

		MAX_ROLE_ID = 99
	};

	//系统所有的权限点枚举
	enum class SystemActionEnum {
		FILE_ARCHIVE = 132,//文件归档
		SYS_ADMIN_ADD = 2,//添加系统的admin账号
		WF_EDIT = 1272,//编辑workFlow
		WF_DEL = 1273,//删除workFlow
		PILN_ADD = 1281,//添加pipeline step
		PILN_DEL = 1282,//删除pipeline step
		FILE_ACCESS = 131,//文件访问
		TEAM_EDIT = 1122,//编辑团队
		FILE_DEL = 133,//文件删除
		NOTIF_ADD = 141,//添加通知
		DEPT_ADD = 1111,//创建部门
		DEPT_EDIT = 1112,//编辑部门
		DEPT_DEL = 1113,//删除部门
		TEAM_ADD = 1121,//添加团队
		PILN_ASSIG = 1283,//分配pipeline
		TEAM_DEL = 1123,//删除团队
		PERS_ADD = 1131,//添加人员
		PERS_EDIT = 1132,//修改人员
		PERS_DEL = 1133,//删除人员
		PERS_RM = 1134,//移除人员出部门
		PERS_RESET = 1135,//重置人员密码
		PROJ_ADD = 1211,//添加项目
		PROJ_EDIT_TIME = 1212,//编辑项目时间
		PROJ_ADD_ROOT = 1213,//添加项目的projectRoot
		PROJ_ADD_MEMBER = 1214,//添加项目成员
		PROJ_RM_MEMBER = 1215,//移除项目成员
		PROJ_DEL = 1216,//删除项目
        PROJ_EDIT_ROOT_DIR = 1217,//修改项目根路径
		PILN_REASSIG = 1284,//pipeline step的重新分配
		RECYCLE_DEL = 1286, //删除回收站记录权限
        RECYCLE_RECOVER = 1287, //恢复回收站记录权限
		PERM_TEMPL_ADD = 1221,//添加项目权限模板
		PERM_TEMPL_EDIT = 1222,//编辑项目的权限模板
		PERM_TEMPL_DEL = 1223,//删除项目的权限模板
		PERM_TEMPL_ASSIG = 1224,//分配项目的权限模板
		ASSO_ADD = 1231,//添加镜头
		ASSO_EDIT = 1232,//编辑asset和shot的时间
		ASSO_EDIT_WF = 1233,//编辑asset和shot的workflow
		ASSO_DEL = 1234,//删除asset和shot
        ASSO_ASSET_ACCESS = 1235,//可以看到项目中所有的资产
        ASSO_SHOT_ACCESS = 1236,//可以看到项目中所有的镜头
		ASSO_SEQUENCE_ACCESS = 1237,//可以看到项目中所有的SEQ
		EDIT_SEQUENCE_SHOT = 1238, //编辑sequenceShot权限
		TASK_ALTER_ASSIGNEE = 1251,//修改任务的assignee
		TASK_CHECK_IN_OUT_FILE = 1252,//checkin/out task的output file
		TASK_ADD_REQUIRED_FILE = 1253,//添加task的requiredFile
		TASK_RM_REQUIRED_FILE = 1254,//移除requiredFile
		TASK_REOPEN_NOAPPROVED = 1255,//重开还没通过的任务
		TASK_REOPEN_APPROVED = 1256,//重开已经通过的任务
		TASK_APPROVE = 1257,//通过任务
		TASK_DEPRECATE_NOAPPROVED = 1258,//废弃未通过的任务
		TASK_DEPRECATE_APPROVED = 1259,//废弃通过的任务
		TASK_DEL = 1260,//删除任务
		TASK_ADD = 1261,//创建任务
		TASK_EDIT_TIME = 1262,//编辑任务的时间
		TASK_ALTER_SUPERVISOR = 1263,//编译任务的supervisor
		TASK_SUPERVISOR = 1264,//可被指定为任务的supervisor
        TASK_URGENT = 1265,//可设置任务加急权限
        TASK_APPROVAL_LIST_EDIT = 1266,//编辑任务审批流程权限
        TASK_EDIT_PRIV_TIME  = 1268,//编辑任务特权时间
        TASK_VIEW_PRIV_TIME  = 1269,//可以看到任务特权时间
		WF_ADD = 1271,//创建workFlow
		HOLIDAY_ADD = 1011,//C创建节假日
		HOLIDAY_EDIT = 1012,//编辑节假日
		HOLIDAY_DEL = 1013, //删除节假日
		TASK_ON_HOLD = 1267, //手动暂停
        TASK_ADD_OUTPUT_FILE = 1288,    //上传任务output file，包括新文件，已有文件新版本。
        TASK_REMOVE_OUTPUT_FILE = 1289  //删除任务output file
	};

	/************************************************************************
	角色实体类：
	包括人员行政角色和项目角色，以及其他拓展角色
	************************************************************************/
	struct Role {
		qint32 roleId = 0;//角色id
		QString roleName = "";//角色名称
		qint32 roleType = 0;//角色的类型[-1：系统管理者角色，0：通用角色，1：人员行政角色/部门角色，2：项目角色，3：文件角色，4：task角色，5：团队角色]
		qint32 parentId = 0;//父亲角色的id[暂时只是记录关系]
		qint32 entryId = 0;//模块入口id，比如项目类型的角色便是项目的id，人员类型的角色便是部门id
		qint32 subEntryId = 0;//子入口[默认为0，若不为0，表示也可以从该入口查询，非0表示该角色是有子入口的]
		QString roleCode = "";//角色代码，可以根据该代码找出该角色
		qint32 status = 0;//角色的状态[0：在用，1：无效]
		qint32 level = 0;//角色层级
		qint32 grade = 0;//权限等级
		bool isDefault = false;//是否是自定义的类型[1：系统自动产生的类型，0：用户自定义的类型]系统产生的类型用户查询时并不会显示在界面上
		bool isSingleUsed = false;//是否只能是一个人用[默认是否0：能被多人用，1：只能被一个人用]
		QDateTime createTime;//创建时间

		Serialization(roleId, roleName, roleType, parentId, entryId, subEntryId,
			roleCode, status, level, grade, isDefault, isSingleUsed, createTime)
	};

	//项目角色,对应于服务端的ProjectRole
	struct INQProjectPermissionVO {

		qint32 projectId = 0;//所属的项目id

		qint32 roleId = 0;//模板id
		QString roleName;//模板名称
		qint32 grade = 0;//权限等级
		bool isDefault = false;//角色是否是默认角色[1：系统自动产生的类型，0：用户自定义的类型]
        QSet<qint32> permissionSet;

		Serialization(projectId, roleId, roleName, grade, isDefault, permissionSet)
	};

	struct PersonPermissionVO {
		//人员id
		int personId = 0;

		//角色列表:key:roleCode
		QMap<QString, Role> roles;

		//权限列表
		//QSet含有元素0，且key不为空，表示拥有系统级别的的权限
		//key SystemActionEnum
		QMap<qint32, QSet<QString>> detailPermissions;

        bool hasRoles(SystemRoleEnum sysRole, qint32 entryId)
        {
            return roles.end() != std::find_if(roles.begin(), roles.end(), [&](const auto &r) {
                return (r.entryId == entryId && r.parentId == (int) sysRole) || r.roleId == (int) sysRole;
            });
        }

        //获取人员的行政角色[包括Root和admin]
        Role getPersonnelRoleFromPersonRoleInfoDTO() {
            for (auto &rs : this->roles) {
                if (RoleTypeEnum::DEPARTMENT == (RoleTypeEnum) rs.roleType ||
                    RoleTypeEnum::SYSTEM_ADMIN == (RoleTypeEnum) rs.roleType) {
                    return rs;
                }
            }
            return Role();
        }

		//是否包含某个权限
		const bool hasPermission(SystemActionEnum actionEnum) const {
			//判断是否是超级账号，如果是超级账号，直接返回
			if (roles.contains("root")) {
				return true;
			}
			if (roles.contains("admin")) {
				if (actionEnum != SystemActionEnum::SYS_ADMIN_ADD) {
					return true;
				}
			}
			return detailPermissions.contains((qint32) actionEnum);
		}

		//判断是否含有某个部门的权限
		const bool hasDepartmentPermission(SystemActionEnum actionEnum, qint32 departmentId) const {
			if (roles.contains("root")) {
				return true;
			}
			if (roles.contains("admin")) {
				if (actionEnum != SystemActionEnum::SYS_ADMIN_ADD) {
					return true;
				}
			}

			if (roles.contains("deptRoot:" + QString::number(departmentId))) {
				return true;
			}
			//项目根直接判断
			if(!detailPermissions.contains((qint32) actionEnum)){
                return false;
			}
			return detailPermissions[(qint32) actionEnum].contains(QString::number(departmentId));
		}

		//判断是否含有某个项目的权限
		const bool hasProjectPermission(SystemActionEnum actionEnum, qint32 projectId) const {
			if (roles.contains("root")) {
				return true;
			}
			if (roles.contains("admin")) {
				if (actionEnum != SystemActionEnum::SYS_ADMIN_ADD) {
					return true;
				}
			}
			//判断是不是项目的根，是的话直接放行
			if (roles.contains("projRoot:" + QString::number(projectId))) {
				return true;
			}
            if(!detailPermissions.contains((qint32) actionEnum)){
                return false;
            }
			//项目根直接判断
			return detailPermissions[(qint32) actionEnum].contains(QString::number(projectId));
		}
		Serialization(personId, roles, detailPermissions)
	};

	//VIEW OBJECT:人员的模板[项目模板]
	//**************************************************************************************************
	struct INQPersonTemplateVO {
		qint32 projectId = 0;//项目id
		qint32 teamId = 0;//团队id
		QString teamName = "";
		qint32 templateId = 0;//模板id

		qint32 personId = 0;//人员id
		QString personName = "";//人员名称
		QString templateName = "";//模板名称
		bool isdefault = false;//是否默认
		qint32 systemRole = 0;

		Serialization(projectId, teamId, templateId, personId,
			personName, templateName, isdefault, teamName, systemRole)
	};

};