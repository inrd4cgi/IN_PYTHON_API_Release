#pragma once
#include "inrole.h"
#include "sfc_msg.h"
#include "PyWrapperUtils.h"
#include <QMap>
#include <QDateTime>
#include <QDataStream>
#include <QFileInfo>
#include <QPoint>
#include <QVector>
#include "INSerializationUtils.h"
#include <QMapNode>
#include <QSet>

namespace INS
{

	//id与名字类
	struct tag_CIdName {
		qint32 n_data_id = 0;
		QString str_name;

		tag_CIdName(qint32 n_id = 0, QString str_text = QString())
			:n_data_id(n_id), str_name(str_text) {
			;
		}

		friend QDataStream & operator << (QDataStream &out, const tag_CIdName & idandname) {
			out << idandname.n_data_id << idandname.str_name;
			return out;
		}
		friend QDataStream & operator >> (QDataStream &in, tag_CIdName & idandname) {
			in >> idandname.n_data_id >> idandname.str_name;
			return in;
		}

		bool operator==(const tag_CIdName& idname) {
			return this->n_data_id == idname.n_data_id;
		}
		bool operator!=(const tag_CIdName& idname) {
			return !(*this == idname);
		}
	};
	//文件服务器类,记录每个文件服务器中的可存放项目文件的根目录。
	//**********************************************************************************************************************
	struct INFileServerRoot {
		qint32 root_id = 0;        //根目录的id
		QString server_name = "";  //文件服务器名
		QString root_dir = "";     //文件服务器的一条根目录
		QString ipaddress = "";    //文件服务器的IP地址
		qint32 project_number = 0; //该目录下的项目个数
		qint32 remain;             //磁盘的剩余空间大小
		friend QDataStream& operator >> (QDataStream& in, INFileServerRoot& fileserver_root) {
			in >> fileserver_root.root_id >> fileserver_root.server_name >> fileserver_root.root_dir
				>> fileserver_root.ipaddress >> fileserver_root.project_number >> fileserver_root.remain;
			return in;
		}
		friend QDataStream& operator <<(QDataStream& out, const INFileServerRoot& fileserver_root) {
			out << fileserver_root.root_id << fileserver_root.server_name << fileserver_root.root_dir
				<< fileserver_root.ipaddress << fileserver_root.project_number << fileserver_root.remain;
			return out;
		}
	};

	//项目文件类
	//*********************************************************************************************************
	struct INProjectFile {
		qint32 project_id = 0;		//项目文件id
		QString project_name = "";	//项目名
		qint32 root_folder_id = -1;	//根文件夹id

		friend QDataStream& operator >> (QDataStream& in, INProjectFile& project_file) {
			in >> project_file.project_id >> project_file.project_name >> project_file.root_folder_id;
			return in;
		}
		friend QDataStream& operator << (QDataStream& out, const INProjectFile& project_file) {
			out << project_file.project_id << project_file.project_name << project_file.root_folder_id;
			return out;
		}

		bool operator == (const INProjectFile& prj_file) const {
			bool b_state(true);
			if(project_id != prj_file.project_id)
				b_state = false;
			if(project_name != prj_file.project_name)
				b_state = false;
			if(root_folder_id != prj_file.root_folder_id)
				b_state = false;

			return b_state;
		}

		bool operator != (const INProjectFile& prj_file) const {
			bool b_state(true);
			if(*this == prj_file)
				b_state = false;

			return b_state;
		}
	};


	/*!
	 * \struct FolderParam
	 * \ingroup file
	 * \brief 获取文件夹的参数
	 */
	struct FolderParam {

		qint32 folderId = 0;//若folderId不为0,表示根据文件夹id来获取文件夹
		qint32 projectId = 0;//若项目id不为0,表示根据项目id来获取文件夹

		Serialization(FolderParam, folderId, projectId)

	};
	struct INFileBase;
	//文件夹类的基类
	//***********************************************************************************************************************************************
	struct INFolderBase {
		qint32 id = -1;           //文件夹id
		qint32 project_id = 0;    //项目id
		QString directory = "";   //文件夹相对路径
		QString name = "";        //文件夹名
		qint32 parent = 0;        //父文件夹id,若为根，parent为0

		QMap<qint32, QString> folders;    //子文件夹id
		QMap<qint32, INFileBase> files;//子文件信息

		Serialization(INFolderBase, id, project_id, directory, name, parent, folders, files)
	};
	struct INFileHistory;

	//文件类的基类
	//**********************************************************************************************************************************************
	struct INFileBase {
		qint32 id = -1;					//文件id0
		qint32 project_id = 0;			//文件所属的项目(上传需要)
		QString directory = "";			//文件路径
		QString name = "";				//文件名（包含后缀)(上传需要)
		qint32 author_id = 0;			//文件作者的id值
		QString author_name = "";		//作者名字
		QDateTime datetime_create = QDateTime();         //文件创建时间
		QDateTime datetime_modify = QDateTime();         //文件最后一次修改时间(上传需要)
		qint32 version = 0;				//文件版本0
		QList<INFileHistory> version_list;	//文件版本列表，已排好序
		qint64 size = 0;				//文件大小，字节(上传需要)
		qint32 folder_id = 0;			//所在文件夹id(上传需要)
		QString md5 = "";				//文件的md5值-1
		qint32 preview_file_id = 0;		//预览文件id-1
        qint32 type = 0;				//文件的类型 0=asset,1=shot,-1=empty folder, others=2
		qint32 status = 0;				//1=check in,2=check out.
        qint32 last_update_person = 0;	//最后check out这个文件的人0
		QString comment = "";			//对文件最新上传时的评论

		Serialization(INFileBase, id, name, project_id, folder_id, directory, md5, size, preview_file_id, datetime_create,
                      datetime_modify, author_id, author_name, version, version_list, comment, status, last_update_person,type)
	};
	//文件类
	struct INFile :public INFileBase {
	};
	/*******************************************************************
	Description:用户个人信息,大体上对应数据库里的person表格
	********************************************************************/
	struct UserInfoStruct {
		QString legal_name = "";		//名字 必填
		tag_CIdName gender;			//性别。---> tag_CIdName
		tag_CIdName job_title;			//职位 ---> tag_CIdName
		tag_CIdName status;			//工作状态 ---> tag_CIdName
		QString phone = "";				//电话号码
		QDate birthday;					//生日

		friend QDataStream & operator << (QDataStream &out, const UserInfoStruct &userinfo) {
			out << userinfo.legal_name << userinfo.gender << userinfo.job_title << userinfo.status << userinfo.phone << userinfo.birthday;
			return out;
		}

		friend QDataStream & operator >> (QDataStream &in, UserInfoStruct &userinfo) {
			in >> userinfo.legal_name >> userinfo.gender >> userinfo.job_title >> userinfo.status >> userinfo.phone >> userinfo.birthday;
			return in;
		}
	};

	/*******************************************************************
	Description:用户的人员架构关系信息
	********************************************************************/
	struct PersonRelationInfo {
		QList<tag_CIdName> subordinates;  //下属
		tag_CIdName superior;      //直属上司
		tag_CIdName team;          //所在团队
		tag_CIdName project_group; //所在项目组

		friend QDataStream& operator >> (QDataStream& in, PersonRelationInfo& personrelation) {
			in >> personrelation.subordinates >> personrelation.superior >> personrelation.team >> personrelation.project_group;
			return in;
		}
		friend QDataStream& operator<<(QDataStream& out, const PersonRelationInfo& personrelation) {
			out << personrelation.subordinates << personrelation.superior << personrelation.team << personrelation.project_group;
			return out;
		}
	};

	/*******************************************************************
	Description:用户信息
	********************************************************************/
	struct Person {
		qint32 id = 0;                //用户系统id
		QString account = "";          //用户名
		UserInfoStruct info;      //其他基本信息
		PersonRelationInfo personrelation;  //人于人员架构中的信息
		qint32 avatar = 0;           //头像文件id
		qint32 authority = (int)SystemRoleEnum::DEPARTMENT_GENERAL;         //用户权限
		QString version = "";          //版本号
		bool notifyPermiss = false;

		bool islogined;           //登录状态，注意，登录状态变化频率较大，独立出来，与版本号无关。

		friend QDataStream & operator << (QDataStream &out, const Person & person) {
			out << person.id << person.account << person.info << person.personrelation << person.avatar << person.authority << person.version << person.notifyPermiss;
			return out;
		}
		friend QDataStream & operator >> (QDataStream &in, Person & person) {
			in >> person.id >> person.account >> person.info >> person.personrelation >> person.avatar >> person.authority >> person.version >> person.notifyPermiss;
			return in;
		}
	};

	/*******************************************************************
	Description:团队类
	********************************************************************/
	struct TeamInfomation {
		qint32 id = 0;					//团队的id，唯一标志。
		tag_CIdName project_group;		//部门
		QString name = "";				//团队名
		tag_CIdName  leader;			//队长
		QList<tag_CIdName> crews;		//用户名列表
		bool isdefault;					//是否为项目组的默认团队标记。
		QString version = "";			//版本号

		friend QDataStream & operator << (QDataStream &out, const TeamInfomation & team) {
			out << team.id << team.project_group << team.name << team.leader << team.crews << team.isdefault << team.version;
			return out;
		}
		friend QDataStream & operator >> (QDataStream &in, TeamInfomation & team) {
			in >> team.id >> team.project_group >> team.name >> team.leader >> team.crews >> team.isdefault >> team.version;
			return in;
		}
	};

	/*******************************************************************
	Description:团队所在项目组信息
	********************************************************************/
	struct ProjectGroup {
		qint32 id = 0;              //项目组的系统id
		QString name = "";          //项目组名
		QList<qint32> producers;    //项目组监制
		QList<qint32> directors;    //项目组导演
		QList<tag_CIdName> teams;   //项目组中的团队
		bool isdefault;             //是否为系统默认项目组标志。
		QString version = "";       //数据版本号
		tag_CIdName departmentRoot;
		QList<tag_CIdName> departmentAdmins;

		friend QDataStream & operator << (QDataStream &out, const ProjectGroup & projectgroup) {
			out << projectgroup.id << projectgroup.name << projectgroup.producers << projectgroup.directors << projectgroup.teams
				<< projectgroup.isdefault << projectgroup.version << projectgroup.departmentRoot << projectgroup.departmentAdmins;
			return out;
		}
		friend QDataStream & operator >> (QDataStream &in, ProjectGroup & projectgroup) {
			in >> projectgroup.id >> projectgroup.name >> projectgroup.producers >> projectgroup.directors >> projectgroup.teams >>
				projectgroup.isdefault >> projectgroup.version >> projectgroup.departmentRoot >> projectgroup.departmentAdmins;
			return in;
		}
	};
	typedef ProjectGroup Department;

	//INFileStatusEnum
	//************************************************************************************************************************************************
	enum INFileStatusEnum {
		TO_DO = 1,				//即将要做的文件，一般为place holder。
		WIP = 2,				//work in process,正在制作中的文件。
		AWAITING_APPROVAL = 3,	//等待审核的文件。
		PASSED = 4,				//通过的文件。
		LOCKED = 5				//锁定的文件，不可编辑。
	};
	//*********************************************************************************************************************************************

	//文件历史信息
	//*********************************************************************************************************
	struct INFileHistory {
		qint32 id = -1;						//文件id
		qint32 project_id = 0;				//文件所属的项目
		qint32 version = 0;					//文件版本0
		qint32 author_id = 0;				//文件作者的id值
		QString author_name = "";			//作者名字
		QString comment = "";				//对文件最新上传时的评论
		QDateTime datetime_modify = QDateTime();         //文件最后一次修改时间
		qint32 action = 1;					//产生该版本的动作
		qint64 size = 0;					//文件大小，字节
		QString checkCode;//校验码

		Serialization(INFileHistory, id, project_id, version, author_id, author_name, comment, datetime_modify, action, size, checkCode)
	};
	//*********************************************************************************************************

	//INFileDownInfo
	//*********************************************************************************************************
	struct INFileDownInfo {
		qint32 n_code = 0;					//文件的id
		QString str_server_ip = "";			//文件服务器IP地址
		INFileBase target_file;				//要下载的文件。

		friend QDataStream& operator << (QDataStream& out, const INFileDownInfo& file_info) {
			out << file_info.n_code << file_info.str_server_ip << file_info.target_file;
			return out;
		}

		friend QDataStream& operator >> (QDataStream &in, INFileDownInfo &file_info) {
			in >> file_info.n_code >> file_info.str_server_ip >> file_info.target_file;
			return in;
		}
	};
	//*********************************************************************************************************

	//回收站数据
	//*********************************************************************************************************
	struct INRecycleBinInfo {
		qint32 id = 0;						//key唯一索引
		qint32 iteid = 0;					//文件或文件夹id
		bool b_file = true;					//是否为文件，true表示文件，false表示文件夹
		QString name = "";					//文件或者是文件夹的名字，
		QString original_location = "";		//原始路径
		QDateTime date_deleted = QDateTime();	//删除日期时间
		QDateTime date_modified = QDateTime();//最后修改日期
		qint64 size = 0;						//文件或者文件夹大小，文件夹无大小。
		QString deleted_by = "";				//删除该文件夹或文件的用户姓名

		friend QDataStream& operator >> (QDataStream& in, INRecycleBinInfo& recyclebininfo) {
			in >> recyclebininfo.id >> recyclebininfo.iteid >> recyclebininfo.b_file >> recyclebininfo.name
				>> recyclebininfo.original_location >> recyclebininfo.date_deleted >> recyclebininfo.date_modified
				>> recyclebininfo.size >> recyclebininfo.deleted_by;
			return	in;
		}
		friend QDataStream& operator <<(QDataStream& out, const INRecycleBinInfo& recyclebininfo) {
			out << recyclebininfo.id << recyclebininfo.iteid << recyclebininfo.b_file << recyclebininfo.name
				<< recyclebininfo.original_location << recyclebininfo.date_deleted << recyclebininfo.date_modified
				<< recyclebininfo.size << recyclebininfo.deleted_by;
			return out;
		}
	};
	//*********************************************************************************************************

	//基础权限结构体
	//INKeyAndValue
	//***********************************************************************************************************
	struct INKeyAndValue {
		qint32 n_key;
		QString str_value;

		INKeyAndValue(qint32 n_number = 0, const QString& str_text = QString())
			:n_key(n_number), str_value(str_text) {
			;
		}

		friend QDataStream& operator >> (QDataStream& in, INKeyAndValue& key_value) {
			in >> key_value.n_key >> key_value.str_value;
			return in;
		}

		friend QDataStream& operator <<(QDataStream& out, const INKeyAndValue& key_value) {
			out << key_value.n_key << key_value.str_value;
			return out;
		}

		bool operator == (const INKeyAndValue& key_value) const {
			bool b_state = true;
			if(n_key != key_value.n_key)
				b_state = false;
			if(str_value != key_value.str_value)
				b_state = false;

			return b_state;
		}

		bool operator != (const INKeyAndValue& key_value) const {
			bool b_state = true;
			if(*this == key_value)
				b_state = false;

			return b_state;
		}
	};
	//***********************************************************************************************************

	//服务端回复给客户端的回复信息
	//**************************************************************************************************
	class INQRespondInfo {
	public:
		qint32 code{ 0 };//成功或者失败
		QString message;//回复的字符串信息

		INQRespondInfo(qint32 n_code = 0, const QString& str_message = QString())
			:code(n_code), message(str_message) {
		}

		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQRespondInfo& respondInfo) {
			out << respondInfo.code << respondInfo.message;
			return out;
		}

		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQRespondInfo& respondInfo) {
			in >> respondInfo.code >> respondInfo.message;
			return in;
		}
	};
	//**************************************************************************************************

	//**************************************************************************************************

	//人员性别的枚举
	//**************************************************************************************************
	class INGenderEnum {
	private:
		INGenderEnum() = delete;
		INGenderEnum(const INGenderEnum&) = delete;
		INGenderEnum& operator=(const INGenderEnum&) = delete;
	public:
		const static int MAILE = 0;//男
		const static int FEMALE = 1;//女
		static QString getValue(int key) {
			if(key != MAILE && key != FEMALE)
				return{};

			const std::map<int, QString> enumMap = {
				{ MAILE,"male" },
				{ FEMALE,"female" }
			};
			return enumMap.find(key)->second;
		}
	};
	//**************************************************************************************************

	//用工状态的枚举
	//**************************************************************************************************
	class INStatusEnum {
	private:
		INStatusEnum() = delete;
		INStatusEnum(const INStatusEnum&) = delete;
		INStatusEnum& operator=(const INStatusEnum&) = delete;
		const static int minKey = 0;
		const static int maxKey = 4;
	public:
		const static int FULLTIME = 0;//全职
		const static int FIRED = 1;//解雇
		const static int RESIGNED = 2;//辞职
		const static int ONLEAVE = 3;//休假
		const static int PARTTIME = 4;//兼职

		static QString getValue(int key) {
			if(key < minKey || key > maxKey)
				return "";
			const std::map<int, QString> enumMap = {
				{ FULLTIME,"Full_time" },
				{ FIRED,"Fired" },
				{ RESIGNED,"Resigned" },
				{ ONLEAVE,"On_leave" },
				{ PARTTIME,"Part_time" }
			};
			return enumMap.find(key)->second;
		}
	};
	//**************************************************************************************************
	//项目文件结构详情
	struct INFileStruct {
		qint32 itemId = 0;//文件结构中每一项的id
		qint32 fileStructId = 0;//文件结构中每一项的名称
		QString itemName = "";//文件结构中每一项的名称
		qint32 parentId = 0;//父亲节点的id
		INFileStruct() {}
		INFileStruct(qint32 itemId, qint32 fileStructId, QString itemName, qint32 parentId) {
			this->fileStructId = fileStructId;
			this->itemId = itemId;
			this->itemName = itemName;
			this->parentId = parentId;
		}

		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INFileStruct& fs) {
			out << fs.itemId << fs.fileStructId << fs.itemName << fs.parentId;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INFileStruct& fs) {
			in >> fs.itemId >> fs.fileStructId >> fs.itemName >> fs.parentId;
			return in;
		}
	};
	//项目文件结构模板
	struct INFileStructTemplate {
		qint32 fileStrcTemplId = 0;//文件结构模板id
		QString fileStrcTemplName = "";//文件结构模板名称
		QList<INFileStruct> fileStructDetail;//文件结构详情
		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INFileStructTemplate& fst) {
			out << fst.fileStrcTemplId << fst.fileStrcTemplName << fst.fileStructDetail;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INFileStructTemplate& fst) {
			in >> fst.fileStrcTemplId >> fst.fileStrcTemplName >> fst.fileStructDetail;
			return in;
		}
	};

	struct INPipelineStep;

	//项目的数据
	struct ProjectData {
		qint32 assetCount = 0;//项目资产数量
		qint32 shotCount = 0;//项目镜头数量
		qint32 taskCount = 0;//任务的数量
		QMap<qint32, qint32> assetData;//资产数据
		QMap<qint32, qint32> shotData;//镜头数据

		friend QDataStream& operator<<(QDataStream& out, const ProjectData& d) {
			out << d.assetCount << d.shotCount << d.taskCount << d.assetData << d.shotData;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, ProjectData& d) {
			in >> d.assetCount >> d.shotCount >> d.taskCount >> d.assetData >> d.shotData;
			return in;
		}
	};


	struct INProjectBaseObj {
		qint32 projectId = 0;						//项目Id
		QString project = "";						//项目名称
		QDateTime issueDate = QDateTime();			//计划开始日期
		QDateTime dueDate = QDateTime();			//计划结束日期
		QDateTime actual_start_time = QDateTime();	//实	际开始日期
		QDateTime actual_end_time = QDateTime();	//实	际结束日期
		QString description = "";					//描	述
		QString color = "";							//颜	色
		qint32 status = 0;							//状	态
		bool workfloweditflag = false;

		friend QDataStream& operator >> (QDataStream& in, INProjectBaseObj& ipro) {
			in >> ipro.projectId >> ipro.project >> ipro.issueDate >> ipro.dueDate >> ipro.actual_start_time >> ipro.actual_end_time \
				>> ipro.description >> ipro.color >> ipro.status >> ipro.workfloweditflag;
			return in;
		}
		friend QDataStream& operator << (QDataStream& out, INProjectBaseObj& opro) {
			out << opro.projectId << opro.project << opro.issueDate << opro.dueDate << opro.actual_start_time << opro.actual_end_time \
				<< opro.description << opro.color << opro.status << opro.workfloweditflag;
			return out;
		}
	};

	//项目的前端页面数据
	struct INQProjectVO :public INProjectBaseObj {
		QSet<QString> fileServerRoot;//文件服务器的服务器根。

		tag_CIdName projectRoot;//项目存放的项目根管理者id和名称的键值对
		tag_CIdName department;//项目存放的项目根管理者id和名称的键值对

		QList<INPipelineStep> pipelineSteps;//pipeline step的名称

		ProjectData projectData;//项目统计数据

	public:
		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQProjectVO& qpj) {
			out << (INProjectBaseObj &)(qpj);
			out << qpj.fileServerRoot << qpj.projectRoot << qpj.department << qpj.pipelineSteps << qpj.projectData;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQProjectVO& qpj) {
			in >> (INProjectBaseObj &)(qpj);
			in >> qpj.fileServerRoot >> qpj.projectRoot >> qpj.department >> qpj.pipelineSteps >> qpj.projectData;
			return in;
		}
	};

	//获取项目业务的参数过滤类
	class INQGetPrjBusinessFilter {
	public:
		QDateTime startTime;
		QDateTime dueTime;
		bool isNeededDetails = false;
		qint32 teamId = 0;//团队id


		Serialization(INQGetPrjBusinessFilter, startTime, dueTime, isNeededDetails, teamId)
	};



	//服务器磁盘信息
	struct INQDiskInfo {

		qint32 serverInfoId = 0;//信息对应的id
		QString rootPath = "";//磁盘根位置/盘符
		qint64 totalSpace = 0;//磁盘总空间大小
		qint64 freeSpace = 0;//磁盘可用空间总大小
		INQDiskInfo() {}
		INQDiskInfo(qint32 serverInfoId, QString rootPath, qint64 totalSpace, qint64 freeSpace) {
			this->freeSpace = freeSpace;
			this->rootPath = rootPath;
			this->totalSpace = totalSpace;
			this->serverInfoId = serverInfoId;
		}

		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQDiskInfo& qdi) {
			//故意不用发serverInfoId的,不要以为我写漏了
			out << qdi.rootPath << qdi.totalSpace << qdi.freeSpace;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQDiskInfo& qdi) {
			in >> qdi.serverInfoId >> qdi.rootPath >> qdi.totalSpace >> qdi.freeSpace;
			return in;
		}
	};

	//文件服务器的相关信息
	struct INQServerInfo {

		qint32 serverId = 0;//文件服务器磁盘信息的id
		QString fileServerName = "";//文件服务器名称
		QList<INQDiskInfo> diskInfos;//磁盘信息

		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQServerInfo& qfs) {
			out << qfs.serverId << qfs.fileServerName << qfs.diskInfos;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQServerInfo& qfs) {
			in >> qfs.serverId >> qfs.fileServerName >> qfs.diskInfos;
			return in;
		}
	};

	struct INQWorkPath;
	struct INPipelineStep {

		qint32 pipelineId = 0;      //pipeline的id
		qint32 pipelineType = 0;    //pipeline的类型
		QString pipelineName = "";  //pipeline的名称
		qint32 projectId = 0;       //项目id
		QPair<qint32, QString> coordinator;//由谁分配任务
		QPair<qint32, QString> supervisor; //审核人id,姓名
		QString description = "";
		QList<INQWorkPath> outputFileList;

		Serialization(INPipelineStep, pipelineId, pipelineType, pipelineName, projectId, coordinator, supervisor, description, outputFileList);
	};

	struct INQWorkPath {
        qint32 pathId = 0;
        qint32 pipelineId = 0;
        QString filePath = "";
        qint32 fileType = 0;
        qint32 fileID = 0;
        QString fileName = "";

        Serialization(INQWorkPath, pathId, pipelineId, filePath, fileType, fileID, fileName);
    };

	struct INWorkPath {
		qint32 pathId = 0;
		qint32 pipelineId = 0;
		QString filePath = "";
		qint32 fileType = 0;
		qint32 placeHoderFileId = 0;
		QString placeHoderFileName = "";

        Serialization(INWorkPath, pathId, pipelineId, filePath, fileType, placeHoderFileId, placeHoderFileName)
	};

	//work-flow详情
	struct WorkFlowDetlFile;
	struct INQWorkFlowDetail {
		qint32 workFlowStepId = 0;      //工作流每一步的id
		QString workFlowStepName = "";  //工作流每一步的名称
		qint32 workFlowId = 0;          //工作流模板的id
		QList<qint32> parentStepIds;    //工作流父亲节点的id集合
		QString color = "#FFFFFF";      //描述颜色
		QPair<qint32, QString> pipelineStep;
		QPair<QPoint, QPoint> position;
		qint32 wftype = 0; 
		qint32 containerId = 0;
		QList<WorkFlowDetlFile> wfdFileList;

		Serialization(INQWorkFlowDetail, workFlowStepId, workFlowStepName, workFlowId,
					  parentStepIds, color, pipelineStep, position, wftype, containerId, wfdFileList)
	};

	//work-flow
	struct INQWorkFlowVO {

		qint32 workFlowId = 0;//工作流模板的id
		QString workFlowName = "";//工作流名称
		qint32 projectId = 0;//所属项目的id
		qint32 pipelineType = 1;//所属pipeline的类型,1为Asset,2为Shot'
		QList<INQWorkFlowDetail> workFlowDetails;

		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQWorkFlowVO& qdata) {
			out << qdata.workFlowId << qdata.workFlowName << qdata.projectId
				<< qdata.pipelineType << qdata.workFlowDetails;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQWorkFlowVO& qdata) {
			in >> qdata.workFlowId >> qdata.workFlowName >> qdata.projectId
				>> qdata.pipelineType >> qdata.workFlowDetails;
			return in;
		}
	};

	struct INQLogInfo {
		qint32 logId = 0;//日志的id
		qint32 logType = 0;//业务类型
		QString logDetail = "";//日志详情
		QDateTime createTime;//日志产生时间
		QString clientIp = "";//客户端IP地址
		bool success = false;//客户端请求是否成功
		QPair<qint32, QString> role;//用户角色
		QPair<qint32, QString> user;//用户
		QPair<qint32, QString> action;//用户操作
		//对象序列化

		friend QDataStream& operator<<(QDataStream& out, const INQLogInfo& ql) {
			out << ql.logId << ql.logType << ql.logDetail
				<< ql.createTime << ql.clientIp << ql.role
				<< ql.success << ql.user << ql.action;
			return out;
		}

		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQLogInfo& ql) {
			in >> ql.logId >> ql.logType >> ql.logDetail
				>> ql.createTime >> ql.clientIp >> ql.role
				>> ql.success >> ql.user >> ql.action;
			return in;
		}
	};

	struct INQGetLogBusParams {
		qint32 type = 0;
		QDateTime fromTime;
		QDateTime toTime;
		//对象序列化
		friend QDataStream& operator<<(QDataStream& out, const INQGetLogBusParams& ql) {
			out << ql.type << ql.fromTime << ql.toTime;
			return out;
		}
		//对象反序列化
		friend QDataStream& operator >> (QDataStream& in, INQGetLogBusParams& ql) {
			in >> ql.type >> ql.fromTime >> ql.toTime;
			return in;
		}
	};

	//**************************************************************************************************
	//**************************************************************************************************

	//任务过滤条件
	//**************************************************************************************************
	struct INTaskSeachCondition {
		int projectId = 0;
		int teamId = 0;
		QDateTime beginTime = QDateTime();
		QDateTime endTime = QDateTime();
		bool unassigned = false; //筛选未分配的task

		friend QDataStream& operator >> (QDataStream& in, INTaskSeachCondition& itaskcondition) {
			in >> itaskcondition.projectId >> itaskcondition.teamId >> itaskcondition.beginTime
				>> itaskcondition.endTime >> itaskcondition.unassigned;
			return in;
		}
		friend QDataStream& operator <<(QDataStream& out, const INTaskSeachCondition& otaskcondition) {
			out << otaskcondition.projectId << otaskcondition.teamId << otaskcondition.beginTime <<
				otaskcondition.endTime << otaskcondition.unassigned;
			return out;
		}
	};
	//**************************************************************************************************
	struct INQTaskStatusItem {
		qint32 taskStatusId = 0;
		qint32 status = 0;//状态值
		QString remark = "";//标记
		QDateTime updateTime;//更新时间
		QPair<qint32, QString> operatedBy;//操作者

		Serialization(INQTaskStatusItem, taskStatusId, status, remark, updateTime, operatedBy)
	};

	struct INQTaskStatus {
		qint32 taskId = 0;
		qint32 reOpenCount = 0;
		QDateTime actualStartTime;//实际开始时间
		QDateTime actualEndTime;//实际结束时间
		QDateTime issueDate;//预计开始时间
		QDateTime dueDate;//预计结束时间
		//QList<INQTaskStatusItem> taskStatusItemList;//任务状态的列表
		QMap<QDate, QList<INQTaskStatusItem>> taskStatusItemMap;

		Serialization(INQTaskStatus, taskId, reOpenCount, actualStartTime, actualEndTime, issueDate,
					  dueDate, taskStatusItemMap)
	};

	//任务的结构体
	struct INTaskBaseObj {
		qint32 projectId = 0;          //项目Id
		QString project;               //项目名称
		QDateTime issueDate;           //计划开始日期
		QDateTime dueDate;             //计划结束日期
		QDateTime actual_start_time;   //实际开始日期
		QDateTime actual_end_time;     //实际结束日期
		QDateTime createdTime;			//创建时间
		QString description;           //描述
		QString color;                 //颜色
		QString pos;					//位置
		qint32 status = 0;             //状态

		Serialization(INTaskBaseObj, projectId, project, issueDate, dueDate, actual_start_time,
					  actual_end_time, description, color, status)
	};

	//人员的任务的结构体
	//**************************************************************************************************
	struct INTask : public INTaskBaseObj {
		qint32 taskId{ 0 };					//任务id
		qint32 objectId{ 0 };				//Asset/shotid
		QString objectName;					//Asset/shot名称
		QString taskName;				    //任务名
		qint32 assigneeTeamId{ 0 };			//任务执行人所属组id
		QString assigneeTeam;			    //任务执行人所属组
		qint32 assigneePersonId{ 0 };		//任务执行人id
		QString assigneePerson;			    //任务执行人
		qint32 pipelineStepId{ 0 };			//pipelinestepid
		QString pipelineStep;			    //pipelinestep名称
		qint32 supervisorId{ 0 };		    //任务审批人id
		QString supervisor;				    //任务审批人名
		qint32 coordinatorId{ 0 };          //分派者id
		QString coordinator;                //分派者
		qint32 organizerId{ 0 };			//项目创建人id
		QString organizer;				    //项目创建人
		qint32 reminderId{ 0 };
		qint32 difficulty{ 0 };			    //难度
		qint32 type{ 0 };				    //0:Asset/1:Shot
        qint32 wftype{ 0 };						//0节点，1容器
        qint32 workFlowStepId{ 0 };				//wf_step_id
        qint32 containerId{ 0 };                 //对应wftype为1的taskId
        QString storageType;				//存储类型

		//taskId,projectId,containerName,taskName,pipelineStep,supervisor,organizer,color,status,type不能为空
		bool checkTaskParam() {
			if(projectId == 0 || objectId == 0 || taskName.isEmpty() || organizerId == 0
			   || color.isEmpty() || status != 0 || type > 1 || type < 0)
				return false;
			else
				return true;
		}

		Serialization(INTask, projectId, project, issueDate, dueDate, actual_start_time, actual_end_time, createdTime,
					  description, color, pos, status, taskId, objectId, objectName, taskName, assigneeTeamId, assigneeTeam,
					  assigneePersonId, assigneePerson, pipelineStepId, pipelineStep, supervisorId, supervisor,
					  coordinatorId, coordinator, organizerId, organizer, reminderId, difficulty, type, wftype, workFlowStepId,
					  containerId, storageType)
	};

	//**************************************************************************************************

	////////// 文件相关 /////////////////////////
	/*!
	 * \struct FileTransferInfo
	 * \ingroup
	 * \brief 文件的传输信息
	 */
	struct FileTransferInfo {
		//文件对应的存储服务器的信息
		QString storageId = "";//文件服务器的文件id，若是上传,该字段信息为空
		QString token = "";//文件传输的校验码
		QString path = "";//文件服务器的文件路径
		QString name = "";//文件在存储服务器的文件名称,一般跟应用服务器的文件名不相同
		QString ip = ""; //存储服务器IP地址
		qint32 port = 0; //存储服务器的端口
		qint64 size{ 0 };

		INFileBase infoInClient;

		Serialization(FileTransferInfo, storageId, token, path, name, ip, port, size, infoInClient)
	};

	//INTaskComment
	//**************************************************************************************************
#define DataStreamIn(classType) friend QDataStream& operator >> (QDataStream& in, classType& obj)
#define DataStreamOut(classType) friend QDataStream& operator <<(QDataStream& out, const classType& obj)
	typedef QPair<qint32, QString> KeyValue;
	typedef QList<qint32> IntList;

	struct INTaskComment {
		qint32 commentId = 0;
		KeyValue person = KeyValue(0, QString());
		qint32 taskId = 0;
		qint32 taskStateId = 0;
		QDateTime submitDate;
		QString text;
		IntList audioIds;
		IntList videoIds;
		IntList pixmapIds;

		DataStreamOut(INTaskComment) {
			out << obj.commentId << obj.person << obj.taskId << obj.taskStateId << obj.submitDate << obj.text << obj.audioIds << obj.videoIds << obj.pixmapIds;
			return out;
		}

		DataStreamIn(INTaskComment) {
			in >> obj.commentId >> obj.person >> obj.taskId >> obj.taskStateId >> obj.submitDate >> obj.text >> obj.audioIds >> obj.videoIds >> obj.pixmapIds;
			return in;
		}
	};
	//**************************************************************************************************





	//资产过滤条件
	//**************************************************************************************************
	struct INAssetSeachCondition {
		qint32 projectId = 0;
		qint32 assetstatus = 0;
		QDateTime beginTime = QDateTime();
		QDateTime endTime = QDateTime();

		friend QDataStream& operator >> (QDataStream& in, INAssetSeachCondition& iassetcondition) {
			in >> iassetcondition.projectId >> iassetcondition.assetstatus >> iassetcondition.beginTime >> iassetcondition.endTime;
			return in;
		}
		friend QDataStream& operator <<(QDataStream& out, const INAssetSeachCondition& oassetcondition) {
			out << oassetcondition.projectId << oassetcondition.assetstatus << oassetcondition.beginTime << oassetcondition.endTime;
			return out;
		}
	};
	//**************************************************************************************************

	//资产的结构体
	//**************************************************************************************************
	struct INAsset : public INProjectBaseObj {
		qint32 assetId = 0;					//资产id
		QString assetName = "";				//资产名
		qint32 workflowId = 0;
		QString workflow = "";
		qint32 uploadFootageId = 0;
		QList<INTask> createtasklist;	//任务列表

		friend QDataStream& operator >> (QDataStream& in, INAsset& iasset) {
			in >> (INProjectBaseObj&)(iasset);
			in >> iasset.assetId >> iasset.assetName >> iasset.workflowId >> iasset.workflow \
				>> iasset.uploadFootageId >> iasset.createtasklist;
			return in;
		}

		friend QDataStream& operator << (QDataStream& out, const INAsset& oasset) {
			out << (INProjectBaseObj&)(oasset);
			out << oasset.assetId << oasset.assetName << oasset.workflowId << oasset.workflow \
				<< oasset.uploadFootageId << oasset.createtasklist;
			return out;
		}
	};
	//**************************************************************************************************

	//镜头过滤条件
	//**************************************************************************************************
	struct INShotSeachCondition {
		qint32 projectId = 0;
		qint32 shotstatus = 0;
		qint32 sceneId = 0;
		QDateTime beginTime = QDateTime();
		QDateTime endTime = QDateTime();
		friend QDataStream& operator >> (QDataStream& in, INShotSeachCondition& ishotcondition) {
			in >> ishotcondition.projectId >> ishotcondition.shotstatus >> ishotcondition.sceneId >> ishotcondition.beginTime >> ishotcondition.endTime;
			return in;
		}
		friend QDataStream& operator <<(QDataStream& out, const INShotSeachCondition& oshotcondition) {
			out << oshotcondition.projectId << oshotcondition.shotstatus << oshotcondition.sceneId << oshotcondition.beginTime << oshotcondition.endTime;
			return out;
		}
	};
	//**************************************************************************************************


	//镜头的结构体
	//**************************************************************************************************
	struct INShot : public INProjectBaseObj {
		qint32 shotId = 0;					//镜头id
		qint32 sceneId = 0;					//场景id
		QString scene = "";					//场景名
		QString shotName = "";				//镜头名
		qint32 workflowId = 0;
		QString workflow = "";
		qint32 uploadFootageId = 0;
		QList<INTask> createtasklist;	//任务列表

		friend QDataStream& operator >> (QDataStream& in, INShot& ishot) {
			in >> (INProjectBaseObj&)(ishot);
			in >> ishot.shotId >> ishot.sceneId >> ishot.scene >> ishot.shotName >> ishot.workflowId >> ishot.workflow \
				>> ishot.uploadFootageId >> ishot.createtasklist;
			return in;
		}

		friend QDataStream& operator << (QDataStream& out, const INShot& oshot) {
			out << (INProjectBaseObj&)(oshot);
			out << oshot.shotId << oshot.sceneId << oshot.scene << oshot.shotName << oshot.workflowId << oshot.workflow \
				<< oshot.uploadFootageId << oshot.createtasklist;
			return out;
		}
	};
	//**************************************************************************************************

    /*!
     * \brief The RequiredFileStruct struct Required文件描述结构体
     */
	struct RequiredFileStruct {
        qint32 taskID = 0; /*!< 产出此文件的任务ID */
        QString taskName = ""; /*!< 产出此文件的任务名字 */
        qint32 taskStatus = 0; /*!< 产出此文件的任务的当前状态 */
        INFileBase requiredFile; /*!< 文件结构体 */

		friend QDataStream& operator >> (QDataStream& in, RequiredFileStruct& irefile) {
            in >> irefile.taskID >> irefile.taskName >> irefile.taskStatus >> irefile.requiredFile;
			return in;
		}
		friend QDataStream& operator <<(QDataStream& out, const RequiredFileStruct& orefile) {
            out << orefile.taskID << orefile.taskName << orefile.taskStatus << orefile.requiredFile;
			return out;
		}
	};

	/////////////////////////标签部分/////////////////////////////////////////////////
	//标签资源的视图对象
	struct TagInfoVO {
		//标签信息
		qint32 tagId = 0;//标签的id
		QString tagName;//标签的名称
		QString color;//标签颜色
		qint32 tagUsedCount = 0;//标签使用次数

		//序列化
		Serialization(TagInfoVO, tagId, tagName, color, tagUsedCount)
	};

	//标签资源的视图对象
	struct TagResourceVO {
		QList<TagInfoVO> tagInfos;//标签信息
		QPair<qint32, QString> tagGroup;//所属的标签组信息
		QPair<qint32, QString> tagObject;//标签对象信息
		QVariantMap tagResourceInfo;//具体的标签资源信息

		Serialization(TagResourceVO, tagInfos, tagGroup, tagObject, tagResourceInfo)
	};

	//标签参数
	struct TagParam {
		qint32 tagObjectId = 0;//标签对象id,标签类型[必须的]
		QString tagName = "";//标签的名称[必须的]
		qint32 resourceId = 0;//标签资源id[必须的]
		qint32 resourceEntryId = 0;//资源组root的id[非必须,默认为resourceId]
        qint32 tagGroupId = 0;  //Param searchParamTag

		Serialization(TagParam, tagObjectId, tagName, resourceId, resourceEntryId)
	};

	/////////////////////////Work log部分/////////////////////////////////////////////////
	class SimpleWorklog {
	public:
		qint32 worklogId;
		qint32 publisherid;
		QDateTime publicationDate;
		QString content;

		friend QDataStream& operator<<(QDataStream& out, const SimpleWorklog& simpleworklog) {
			out << simpleworklog.worklogId << simpleworklog.publisherid << simpleworklog.publicationDate << simpleworklog.content;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, SimpleWorklog& simpleworklog) {
			in >> simpleworklog.worklogId >> simpleworklog.publisherid >> simpleworklog.publicationDate >> simpleworklog.content;
			return in;
		}
	};


	/******************** Task 筛选部分 ***************************/
	class TaskSpec {
	protected:
		qint16 spec_type;

	public:
		TaskSpec() : spec_type(-1) {};
		TaskSpec(qint16 spec_no) : spec_type(spec_no) {}

		virtual qint16 type() { return spec_type; }

		friend QDataStream& operator<<(QDataStream& out, const TaskSpec& spec) {
			out << spec.spec_type;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskSpec& spec) {
			in >> spec.spec_type;
			return in;
		}

	};

	class TaskAssigneeSpec : public TaskSpec {
	private:
		qint64 assignee_id;

	public:
		TaskAssigneeSpec() : assignee_id(-1) {};
		TaskAssigneeSpec(qint64 assignee_id) : assignee_id(assignee_id),
			TaskSpec(0) {};
		qint64 operator()() { return assignee_id; }

		friend QDataStream& operator<<(QDataStream& out, const TaskAssigneeSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.assignee_id << spec.assignee_id;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskAssigneeSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.assignee_id;
			return in;
		}

	};

	class TaskPipelinStepSpec : public TaskSpec {
	private:
		QString pipeline_step_name;

	public:
		TaskPipelinStepSpec() : pipeline_step_name("") {};
		TaskPipelinStepSpec(QString pipeline_step_name) : pipeline_step_name(pipeline_step_name), TaskSpec(1) {};

		QString operator()() { return  pipeline_step_name; }
		friend QDataStream& operator<<(QDataStream& out, const TaskPipelinStepSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.pipeline_step_name;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskPipelinStepSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.pipeline_step_name;
			return in;
		}
	};



	class TaskTypeSpec : public TaskSpec {
	private:
		qint16 type;

	public:
		TaskTypeSpec() : type(-1) {};
		TaskTypeSpec(qint16 type) : type(type), TaskSpec(2) {};
		qint16 operator()() { return type; }

		friend QDataStream& operator<<(QDataStream& out, const TaskTypeSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.type;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskTypeSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.type;
			return in;
		}
	};


	class TaskRelatedPropertySpec : public TaskSpec {
	private:
		qint16 property_id;

	public:
		TaskRelatedPropertySpec() : property_id(-1) {};
		TaskRelatedPropertySpec(qint16 container_id) : property_id(container_id), TaskSpec(3) {};

		qint16 operator()() { return  property_id; }

		friend QDataStream& operator<<(QDataStream& out, const TaskRelatedPropertySpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.property_id;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskRelatedPropertySpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.property_id;
			return in;
		}
	};


	class TaskSupervisorSpec : public TaskSpec {
	private:
		qint64 supervisor_id;

	public:
		TaskSupervisorSpec() : supervisor_id(-1) {};
		TaskSupervisorSpec(qint64 supervisor_id) : supervisor_id(supervisor_id), TaskSpec(4) {};

		qint64 operator()() { return supervisor_id; }

		friend QDataStream& operator<<(QDataStream& out, const TaskSupervisorSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.supervisor_id;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskSupervisorSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.supervisor_id;
			return in;
		}
	};


	class TaskStartDateSpec : public TaskSpec {
	private:
		QDateTime issue_date;

	public:
		TaskStartDateSpec() : issue_date(QDateTime()) {};
		TaskStartDateSpec(QDateTime issue_date) : issue_date(std::move(issue_date)), TaskSpec(5) {};

		QDateTime operator()() { return issue_date; }

		friend QDataStream& operator<<(QDataStream& out, const TaskStartDateSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.issue_date;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskStartDateSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.issue_date;
			return in;
		}
	};


	class TaskEndDateSpec : public TaskSpec {
	private:
		QDateTime due_date;

	public:
		TaskEndDateSpec() : due_date(QDateTime()) {};
		TaskEndDateSpec(QDateTime due_date) : due_date(std::move(due_date)), TaskSpec(6) {};

		QDateTime operator()() { return due_date; }

		friend QDataStream& operator<<(QDataStream& out, const TaskEndDateSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.due_date;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskEndDateSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.due_date;
			return in;
		}
	};


	class TaskDateRangeSpec : public TaskSpec {
	private:
		QDateTime issue_date;
		QDateTime due_date;

	public:
		TaskDateRangeSpec() : issue_date(QDateTime()), due_date(QDateTime()) {};
		TaskDateRangeSpec(QDateTime issue_date, QDateTime due_date) :issue_date(std::move(issue_date)), due_date(std::move(due_date)), TaskSpec(7) {};

		QPair<QDateTime, QDateTime> operator()() {
			return  QPair<QDateTime, QDateTime>(issue_date, due_date);
		}

		friend QDataStream& operator<<(QDataStream& out, const TaskDateRangeSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.issue_date << spec.due_date;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskDateRangeSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.issue_date >> spec.due_date;
			return in;
		}
	};


	class TaskStatusSpec : public TaskSpec {
	private:
		qint16 status_id;

	public:
		TaskStatusSpec() : status_id(-1) {};
		TaskStatusSpec(qint16 status_id) : status_id(status_id), TaskSpec(8) {};

		qint16 operator()() { return  status_id; }

		friend QDataStream& operator<<(QDataStream& out, const TaskStatusSpec& spec) {
			out << static_cast<const INS::TaskSpec&>(spec) << spec.status_id;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, TaskStatusSpec& spec) {
			in >> static_cast<INS::TaskSpec&>(spec) >> spec.status_id;
			return in;
		}
	};

	//项目的里程碑
	struct ProjectMilestone {
		int milestoneId = 0;//里程碑id
		int projectId = 0;//项目id
		QDateTime timePoint;//时间点
		QString description = "";//描述
		QString color = "";//颜色
		QDateTime createTime;//创建时间
		QString name = "";
		Serialization(ProjectMilestone, milestoneId, projectId, timePoint, description, color, createTime, name)
	};

	// 分类的消息

    class Recipient {
    public:
        qint64 recv_id{ -1 };
        qint32 recipient_id{ -1 }; // recipient id
        QString recipient_name; // recipient name
        bool read{ false }; // status

        Recipient() = default;

        Recipient(qint32 rid, const QString &rname) {
            recipient_id = rid;
            recipient_name = rname;
        }

        friend QDataStream &operator<<(QDataStream &out, const Recipient &recipient) {
            out << recipient.recv_id << recipient.recipient_id << recipient.recipient_name << recipient.read;
            return out;
        }

        friend QDataStream &operator>>(QDataStream &in, Recipient &recipient) {
            in >> recipient.recv_id >> recipient.recipient_id >> recipient.recipient_name >> recipient.read;
            return in;
        }

    };

    class NotificationHeader {
    public:
        qint64 nid{ -1 }; // notification id
        qint32 sid{ -1 }; // sender id
        QString sname; // sender name
        QDateTime timestamp; // notification creation
        qint32 type{ -1 };

        NotificationHeader() = default;
        NotificationHeader(qint32 sid, const QString& sname) :sid(sid), sname(sname) {}

        friend QDataStream& operator<<(QDataStream& out, const NotificationHeader& header) {
            out << header.nid << header.sid << header.sname << header.timestamp << header.type;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, NotificationHeader& header) {
            in >> header.nid >> header.sid >> header.sname >> header.timestamp >> header.type;
            return in;
        }
    };

    class Notification {
    public:
        NotificationHeader header;
        QString msg;
        QVector<Recipient> recipients;

        friend QDataStream& operator<<(QDataStream& out, const Notification& notification) {
            out << notification.header << notification.msg << notification.recipients;
            return out;
        }
        friend QDataStream& operator>>(QDataStream& in, Notification& notification) {
            in >> notification.header >> notification.msg >> notification.recipients;
            return in;
        }
    };

	struct Avatar {
		qint32 personId;
		QByteArray picavatar;
		bool isdefault = false;

		friend QDataStream& operator >> (QDataStream& in, Avatar& iavatar) {
			in >> iavatar.personId >> iavatar.picavatar;
			return in;
		}

		friend QDataStream& operator << (QDataStream& out, const Avatar& oavatar) {
			out << oavatar.personId << oavatar.picavatar;
			return out;
		}
	};


	/*!
	 * \struct StorageInfo
	 * \ingroup file
	 * \brief 存储服务器的信息
	 */
	struct StorageInfo {
		QString storageType = ""; //存储服务器类型  HDD or SSD
		QString groupName = ""; //存储服务器组名 group1
		QString instanceId = ""; //存储实例ID
		QString ip = ""; //存储服务器IP
		qint32 port = 0; //端口
		qint64 totalSpace = 0; //总空间  单位:byte
		qint64 freeSpace = 0; //可用空间 单位:byte
		QString basePath = ""; //根目录

		Serialization(StorageInfo, storageType, groupName, instanceId, ip, port, totalSpace, freeSpace, basePath)
	};


	//任务过滤参数
	struct TaskFilterParam {
		qint32 projectId = 0;//根据项目id查询
		QVariantList objectIds;//根据项目的资产或者镜头的id查询
		qint32 type = -1;//筛选资产类型或者镜头类型 0:资产,1:镜头
		qint32 status = 0;//根据项目的状态查询
		
		qint32 assignTeamId = 0;//根据分配的团队查询
		qint32 assigneeId = 0;//根据分配的人查询
		qint32 supervisorId = 0;//根据supervisorId查询

		QDateTime issueTime;//根据任务的发布时间查询
		QDateTime dueTime;//根据任务的截至时间查询
		bool isUnassigned = false; //筛选未分配的task
		QVariantList taskIds;//根据taskId查询
		qint32 pipelineId = 0;//根据pipilinestepid查询

		Serialization(TaskFilterParam, projectId, objectIds, type, status, assignTeamId, assigneeId, supervisorId, issueTime,
			dueTime, isUnassigned, taskIds, pipelineId)
	};

	//资产过滤参数
	struct AssetFilterParam {
		qint32 projectId = 0;//根据项目id查询
		QVariantList assetIds;//根据项目的资产id查询
		qint32 status = 0;//根据资产的状态查询
		qint32 workFlowId = 0;//资产的workFlowId
		QDateTime issueTime;//根据资产的发布时间查询
		QDateTime dueTime;//根据资产的截至时间查询

		QString searchKey = "";//资产名关键词查找

		TaskFilterParam taskFilterParam;//资产过滤条件下有任务的过滤条件

		Serialization(AssetFilterParam, projectId, assetIds, status, workFlowId, issueTime, dueTime,
                      searchKey, taskFilterParam)
	};

	//镜头过滤参数
	struct ShotFilterParam {
		qint32 projectId = 0;//根据项目id查询
		QVariantList shotIds;//根据项目的资产id查询
		QVariantList sceneIds;//根据场景号来查找

		qint32 status = 0;//根据资产的状态查询
		qint32 workFlowId = 0;//资产的workFlowId
		QDateTime issueTime;//根据资产的发布时间查询
		QDateTime dueTime;//根据资产的截至时间查询

		QString searchKey = "";

		TaskFilterParam taskFilterParam;//镜头过滤条件下有任务的过滤条件

		Serialization(ShotFilterParam, projectId, shotIds, sceneIds, status, workFlowId, issueTime, dueTime,
		                searchKey, taskFilterParam)
	};

	/*!
	 * \struct TaskFileRelationEditParam
	 * \ingroup project
	 * \brief 任务文件关系编辑接口
	 */
	struct TaskFileRelationEditParam {

		qint32 operationType = 0;//0：删除，1：添加
		qint32 taskId = 0;//任务id

		//REFERENCE_FILE = 0, //引用文件
		//REQUIRED_FILE = 2, //所需文件
		//OUTPUT_FILE = 3 //输出文件
		qint32 fileType = 0;

		qint32 fileId = 0;//文件id

		qint32 folderId = 0;//文件夹id

		QPair<QString, QString> path;//路径,一般是output file需要,first: 路径"/aa/bb/cc",second: aa.txt

		Serialization(TaskFileRelationEditParam, operationType, taskId, fileType, fileId, path)
	};



	/*!
	 * \enum FileTypeEnum
	 * \ingroup project
	 * \brief 文件类型的枚举
	 */
	enum class FileTypeEnum {
		ALL = -1,//所有的类型
		REFERENCE_FILE = 0, //引用文件
		REQUIRED_FILE = 2, //所需文件
		OUTPUT_FILE = 3 //输出文件
	};

	/*!
	 * \struct SequenceFileSetVO
	 * \ingroup file
	 * \brief 序列文件集视图对象
	 */
	struct SequenceFileSetVO {

		QString sequenceFileSetName = ""; //序列文件的名称
		QString directory = "";//序列文件的路径
		QList<INFileBase> files;//所有的序列文件

		Serialization(SequenceFileSetVO, sequenceFileSetName, directory, files)
	};


	/*!
	 * \struct Task
	 * \ingroup project
	 * \brief 任务实体类
	 */
	struct Task {

		qint32 taskId = 0;//任务id
		qint32 projectId = 0;//项目id
		QString taskName = "";
		qint32 type = 0;//0资产,1镜头
		qint32 assetOrShotId = 0;//资产或者镜头id
		QDateTime actualStartTime;//真正开始时间
		QDateTime actualEndTime;//真正结束时间
		bool isDeleted = false;//是否被删除
		qint32 status = 0;//任务状态
		QDateTime issueTime;//发布时间
		QDateTime dueTime;//任务结束时间
		QString storageType = "";//任务文件的存储类型
		qint32 coordinatorId = 0;
		qint32 supervisorId = 0;

		Serialization(Task, taskId, projectId, taskName, type, assetOrShotId, actualStartTime, actualEndTime, isDeleted, status,
					  issueTime, dueTime, storageType, coordinatorId, supervisorId)
	};

	/*!
     * \struct AffectedTaskInfo
     * \ingroup project
     * \brief 受影响的任务的信息
     */
	struct AffectedTaskInfo {
		qint32 taskId = 0;//任务id
		QString taskName = "";//任务名

		qint32 projectId = 0;
		qint32 objectId = 0;
		qint32 assigneeId = 0;
		qint32 type = 0;

		QDateTime issueTime;//任务的计划开始时间
		QDateTime dueTime;//任务的计划结束时间

		QDateTime affectedIssueTime;//受影响之后的发布时间
		QDateTime affectedDueTime;//受影响之后的截至时间

		Serialization(AffectedTaskInfo, taskId, taskName, projectId, objectId, assigneeId, type, issueTime, dueTime,
					  affectedIssueTime, affectedDueTime)
	};


	/*!
	 * \struct AffectedTaskVO
	 * \ingroup project
	 * \brief 受影响的task的前端视图对象
	 */
	struct AffectedObjectInfoVO {

		QMap<qint32, QString> affectedAssignees;//受影响的人员id信息
		QMap<qint32, QString> affectedAssets;//受影响的资产
		QMap<qint32, QString> affectedShots;//受影响的镜头
		QMap<qint32, QString> affectedProjects;//受影响的项目

		QMap<qint32, AffectedTaskInfo> affectedTaskInfos;//受影响的taskd的列表，key为taskId

		Serialization(AffectedObjectInfoVO, affectedAssignees, affectedAssets, affectedShots,
			affectedProjects, affectedTaskInfos)

	};

	/*!
	 * \struct TaskFileVO
	 * \ingroup project
	 * \brief 项目文件的视图对象
	 */
	struct TaskFileVO {

		qint32 taskId = 0;

		QList<INFileBase> files; //任务包含的所有产出单文件

		QMap<qint32, QString> folders;//文件夹 key文件夹id,value文件id

		QList<SequenceFileSetVO> sequenceFiles; //任务包含的所有序列文件

		QMap<qint32, Task> fileTaskMap;//文件文件对应的输出任务列表 key:文件id,value:任务信息

		Serialization(TaskFileVO, taskId, files, folders, sequenceFiles, fileTaskMap)
	};


	/*!
	 * \struct FileTaskVO
	 * \ingroup
	 * \brief
	 */
	struct FileTaskVO {
		INTask task;
		QList<INFileBase> files;
		Serialization(FileTaskVO, task, files)
	};

	/*!
	 * \struct 存储信息的查询查询
	 * \ingroup
	 * \brief
	 */
	struct StorageInfoSearchParam {
		qint32 projectId = 0;
		qint32 taskId = 0;
		Serialization(StorageInfoSearchParam, projectId, taskId)
	};

	struct PanelReviewVO {
		qint32 panelReviewId = 0;
		qint32 projectId = 0;
		QString theme = "";
		QString place = "";
		QDateTime fromTime;
		QDateTime toTime;
		QList<QPair<qint32, QString>> participents;
		QPair<qint32, QString> holder;
		qint32 taskId = 0;
		qint32 status = 0;//会议状态[0：未进行/进行中，1：会议结束]
		//新添加
		QString projectName = "";//项目名
		QString taskName = "";
		qint32 type = 0;
		qint32 containerId = 0;//资产或者镜头的id
		QString containerName = "";//资产或者镜头的名称
		qint32 wrapperId = 0;//若是镜头,则表示场次的id
		QString wrapperName = "";//若是镜头,则表示镜头的名称

		Serialization(PanelReviewVO, panelReviewId, projectId, theme, place, fromTime, toTime, participents, holder, taskId, status,
					  taskName, type, projectName, containerId, containerName, wrapperId, wrapperName)
	};

	struct PersonRoleDTO {
		qint32 entryId = 0;
		int roleId = 0;//角色id
		QString roleName;
		bool isDefault = false;//是否默认
		int grade = 0;//角色等级
		QString roleCode;//角色代码

		int personId = 0;//人员id
		QString userName;//用户名
		QString legalName;//真实姓名

		int teamId = 0;//团队id
		QString teamName;//团队名称

		int departmentId = 0;//部门id
		QString departmentName;//部门名称

		Serialization(PersonRoleDTO, entryId, roleId, roleName, isDefault, grade, roleCode,
					  personId, userName, legalName, teamId, teamName, departmentId, departmentName)
	};

	struct DeleteInfo {
		QString name;
		int type = 0; //删除的业务所属类型（task/asset/shot）
		int id = 0;
		QDateTime deleteTime;//删除时间
		int objectId = 0; //type为0时,taskid;type为1时,assetid;type为2时,shotid;
		int deleteBy = 0; //删除者ID

		Serialization(DeleteInfo, id, name, type, objectId, deleteBy, deleteTime)
	};


	struct ProjectTaskInfo {
		INQProjectVO currproject;
		QMap<qint32, QList<INTask>> taskList;
		int newlytasks = 0;
		QMap<QString, QMap<qint32, QString>> teamtotasklist;
		QMap<QString, QMap<qint32, QString>> persontotasklist;

		friend QDataStream& operator<<(QDataStream& out, const ProjectTaskInfo& d) {
			out << d.currproject << d.taskList << d.newlytasks << d.teamtotasklist << d.persontotasklist;
			return out;
		}

		friend QDataStream& operator >> (QDataStream& in, ProjectTaskInfo& d) {
			in >> d.currproject >> d.taskList >> d.newlytasks >> d.teamtotasklist >> d.persontotasklist;
			return in;
		}
	};

	struct  PersonInActionParam {
		QSet<qint32> actions = {};  //权限点集合 如：1263， 1264
		qint32 AndOr = 0;           //权限点之间的逻辑关系，and == 1,or == 2
		qint32 projectId = 0;       //项目id

		Serialization(PersonInActionParam, actions, AndOr, projectId)
	};

	struct WorkFlowDetlFile
	{
		qint32      workflowFileId = 0;    //主键ID
		qint32      workflowStepId = 0;    //work_flow_detl id
		qint32      parentWorkflowStepId = 0;    //父节点work_flow_detl id
		qint32      pathId = 0;
		QString     path = "";   //文件/文件夹路径
		qint32      type = 0;    //1表示文件，2表示文件夹
		QString     fileName = "";   //文件名
		qint32      fileId = 0;    //文件模板id
		qint32      fileType = 0;    //0=referenceFileId,1= repositoryFileId,2=requiredFileId,3=outFileId
		QDateTime   createTime;                     //创建时间

		Serialization(WorkFlowDetlFile, workflowFileId, workflowStepId, parentWorkflowStepId, pathId, path,
			type, fileName, fileId, fileType, createTime)
	};

	class INQHolidayDetail
	{
	public:
		qint32      detailId            = 0;        //节假日ID
		qint32      templateId          = 0;        //公众假期模板id
		QString     holidayName;                    //节假日名称
		qint32      annual              = 0;        //年度
		QDate       startDate;                      //开始日期,格式：YYYY-MM-DD
		QDate       endDate;                        //结束日期,格式：YYYY-MM-DD
		QDateTime   createTime;
		Serialization(INQHolidayDetail, detailId, templateId, holidayName, annual,startDate,endDate,createTime)
	};

	class INQHolidayTemplate
	{
	public:
		qint32      templateId          = 0;            //公众假期模板id
		QString     templateName;                       //公众假期模板名
		QString     color;                              //颜色
		QList<INQHolidayDetail>   detailList;             //节假日列表

		Serialization(INQHolidayTemplate, templateId, templateName, color, detailList)
	};
};
