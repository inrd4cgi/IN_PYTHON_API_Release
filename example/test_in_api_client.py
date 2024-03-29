#usr/bin/env python
# -*- coding: utf-8 -*-


import os
import sys
import time
import inspect
from pprint import pprint
import collections
import unittest


# IN Python Module
from IN_API_CLIENT_B import InApiClient
from IN_API_CLIENT_B import printer
import IN_DATA_STRUCTURE
import IN_STREAMING
import IN_PYTHON_API_LIB

# 你可能用到的一些 Enum 的结构体
from IN_DATA_STRUCTURE import TagObjectID, BusFileType, TaskFileType, FileStatus, CommentType, TaskStatus, PipelineType



# ---------------------- 需要添加本项目路径 ----------------------------
# 如果 3rd_party_plugins 和 Launch Tool 里已添加路径可不加
# 在外部运行时, 需要添加本项目的路径,
# 如果你没有 requests 的一些包, 也需要添加 3rd 里的路径

# sys.path.append(r"C:\test_3rd_party_plugins\site-packages\IN_PYTHON_API_Release\src")
# sys.path.append(r"C:\test_3rd_party_plugins\site-packages\python27")



# ---------------------- 需要先启动 Server ----------------------------
# 你可以在任何地方启动/停止 Server, 整个本地只会使用一个 Server
# 运行 Server 需要用到我们提供的 env 里的 python.exe, Client 则不需要

# Server 和 Client 能在外部分开单独运行


# ------ 在 DCC 外, 添加了 sys 路径后, 可直接开启 Server ------
# import IN_API_SERVER
# server = IN_API_SERVER.run_server()



# ------ 在 DCC 里可运行以下命令 启动/停止 Server ------
# import IN_API_CLIENT
#
# # result: [pid]
# if IN_API_CLIENT.check_server():
#     IN_API_CLIENT.stop_server()
#
# assert IN_API_CLIENT.start_server() is True


# -------------------- 注意 --------------------
# 在结束的时候使用 stop_server
# 或者在更新 API 之后注意后台有没 server 存在, 即 python.exe

# print("stop: {}".format(IN_API_CLIENT.stop_server()))



# 打印信息太多, 请调用
import logging
logging.getLogger().setLevel(logging.ERROR)


# -------------------- 连接到刚打开的 Local Server --------------------

in_map_dir = 'I:/'

ip, port, username, password, ctype, webserver = '192.168.17.212', 7000, 'sbon', 'qwer', 'DCC', "http://127.0.0.1:20618"
ip, port, username, password, ctype, webserver = '192.168.17.110', 7000, 'sbon', 'qwer', 'DCC', "http://127.0.0.1:20618"
# ip, port, username, password, ctype, webserver = '192.168.3.32', 7000, 'root', 'wsrnd', 'DCC', "http://127.0.0.1:20618"


# 在本工程里, src 外有一份 config.json, 里面填写了一些默认值
# 你可调用 `IN_COMMON` 获得这些值
# ip = IN_COMMON.IN_SERVER_IP_ADDRESS
# port = IN_COMMON.IN_SERVER_PORT
# webserver = 'http://%s:%s' % (IN_COMMON.API_SERVER_IP_ADDRESS, IN_COMMON.API_SERVER_PORT)



# 第一次登陆
in_api = InApiClient.connectAndLogin(in_map_dir, ip, port, username, password, ctype, webserver)


# ---------------------------------------------------

# import INSPECT_HELPER
#
# for k, v in inspect.getmembers(InApiClient):
#     if k.startswith('_'): continue
#     if inspect.isroutine(v):
#         args = INSPECT_HELPER.getargspec(v).args[1: ]
#         print(k, args)

# 如果之前已启动过 Server, 并登录过, 那么在其它 DCC,0 可以不用再登录
# in_api = InApiClient(in_map_dir, webserver=webserver)


# 在不同的 py 文件, 可直接调用 instance
# in_api = InApiClient.instance()


# -------------------- Examples --------------------
# projs = in_api.getProjectFiles()
# printer(projs)

# proj = in_api.getProject()
# printer(proj)

# files = in_api.listdir(folder_id=12161)
# printer(files)



# -------------------- 如何获取 doc --------------------
# 在其它地方可直接 help(InApiClient)

# 在 Maya 里需要
# import codecs
# for func in dir(InApiClient):
#     doc = eval('InApiClient.%s' % func).__doc__
#     print('-'*60)
#     print func, '\n'
#     if doc:
#         s = codecs.decode(doc, 'utf-8')
#         print s

# -----------------------------------------------------------------


# ------------------------------ Get ------------------------------
_test_Get = False
if _test_Get:
    project_id = 120

    # ----- Staff -----
    myself = in_api.getOneself()
    departments = in_api.getDepartments()
    department = in_api.getDepartment(department_id=141)
    teams_info = in_api.getTeams(department_id=141)    # department_id=0
    team_info = in_api.getTeam(team_id=388)
    people = in_api.getPersonList(department_id=141, team_id=0, filter=0)
    person = in_api.getPerson(person_id=20200502)
    jobs = in_api.getJobList()


    # ----- Miscellaneous -----
    storage = in_api.getStorageInfos(project_id=project_id)
    placeholder_list = in_api.getPlaceHolderList()


    # ----- Project -----
    proj_files = in_api.getProjectFiles()
    projs = in_api.getProjects()
    proj = in_api.getProject(project_id=project_id)    # project_id=72


    # ----- File, Folder -----
    files = in_api.listdir(folder_id=12345)
    file = in_api.getFileFromId(file_id=4985)
    file_histories = in_api.getFileHistory(file_id=3650)


    # ----- Pipeline, Workflow -----
    p_steps = in_api.getPipelineSteps(project_id=project_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)
    workflow_list = in_api.getWorkFlowTempls(project_id=project_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)
    workflow = in_api.getWorkFlowTempl(workflow_id=2083)


    # ----- Asset -----
    assets = in_api.getAssetsByCondition(project_id=project_id)    # project_id=72, asset_ids=[435]
    asset_id = 4840
    asset = in_api.getAssetInfo(asset_id=asset_id)
    task_workflow = in_api.getWorkFlowInstance(resource_id=asset_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)


    # ----- Scene Shot -----
    shots = in_api.getShotsByCondition(project_id=project_id)    # project_id=72, scene_ids=[65, 61], shot_ids=[533, 534]
    scenes = in_api.getSceneList(project_id=project_id)    # 80, 137, 167, 174, 177, 199
    shot = in_api.getShotInfo(shot_id=122)


    # ----- Task -----
    tasks = in_api.getTasksByConditions(project_id=project_id)
    # tasks = in_api.getTasksByConditions(object_ids=[968], type=IN_DATA_STRUCTURE.TaskPipelineType.Asset)
    # tasks = in_api.getTasksByConditions(task_ids=[6603])
    task_id = 75607
    file_task_vos = in_api.getTaskFileUsageRecord(task_id=task_id, project_id=project_id, file_type=TaskFileType.All)
    tasks = in_api.getTaskListPersonal(person_id=20200502)
    files_dict = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.All)    # return dict: {TaskFileType: `TaskFileVO`}
    task = in_api.getTaskFromID(task_id=task_id)
    comments = in_api.getTaskComment(task_id=task_id)        # TODO: GetTaskComment 的 jsonRequest 返回结果无法解释, 由于IN前端填了错误信息进数据库


    # ----- Tag -----
    tags = in_api.getTagInfo()    # tag_name="TestTag", tag_object_id=6, resource_id=90
    resources = in_api.getTagResource(tag_name="BonAssetTag_1")



# ------------------------------ Tag ------------------------------
_test_Tag = False
if _test_Tag:

    tag_name, resource_id, tag_object_id = 'BonProjectTag_10', 120, TagObjectID.Project
    # tag_name, resource_id, tag_object_id = 'BonWorkflowTag_1', 5748, TagObjectID.Workflow
    # tag_name, resource_id, tag_object_id = 'BonAssetTag_1', 1029, TagObjectID.Asset
    # tag_name, resource_id, tag_object_id = 'BonShotTag_1', 690, TagObjectID.Shot
    # tag_name, resource_id, tag_object_id = 'BonTaskTag_1', 6808, TagObjectID.Task
    # tag_name, resource_id, tag_object_id = 'BonFolderTag_1', 13200, TagObjectID.Folder
    # tag_name, resource_id, tag_object_id = 'BonFileTag_1', 5439, TagObjectID.File



    # ---------- Make Tag ----------
    # result = in_api.makeTag(tag_name="cgfilm", resource_id=90, tag_object_id=TagObjectID.Folder)           # folder
    result = in_api.makeTag(tag_name=tag_name, resource_id=resource_id, tag_object_id=tag_object_id)     # asset
    # result = in_api.makeTag(tag_name="TestTag", resource_id=2031, tag_object_id=TagObjectID.Workflow)      # task
    assert result.code == 1


    # ---------- Get Tag ----------
    resources = in_api.getTagResource(tag_name=tag_name)
    print('Get Tag `%s`: %s' % (tag_name, len(resources)))
    printer(resources)


    # ---------- Remove Tag ----------
    result = in_api.removeTag(tag_name=tag_name, resource_id=resource_id, tag_object_id=tag_object_id)
    assert result is True

    resources = in_api.getTagResource(tag_name=tag_name)
    print('Get Tag `%s`: %s' % (tag_name, len(resources)))


# ------------------------ Upload & Download ------------------------
_test_Streaming = False
if _test_Streaming:

    def testUpload():
        # 只限第一次上传文件, 上传后使用 CheckOut

        path = r'I:\BonProject\assets\GG\surfacing\textures\plant\tree\1.jpg'
        folder_id = 5344
        r = in_api.upload(src_path=path, folder_id=folder_id)
        print('upload: ', r)


    def testDownload():
        path = r'I:/BonProject/assets/BonAsset_9/none/b.jpg'
        file_id = 5735
        # 不填 dst_path, 则下载到映射路径下
        r = in_api.download(file_id=file_id, dst_path=None, version=None)
        print('download: ', r)


    def testCheckIn():
        path = r'C:\Users\admin\Downloads\x.txt'
        file_id = 5748
        file = in_api.getFileFromId(file_id=file_id)

        if file.status != IN_DATA_STRUCTURE.FileStatus.CheckOuted:
            raise ValueError('Please Checkout first')

        r = in_api.checkin(file_id=file_id, src_path=path)
        print('checkin: ', r)


    def testCheckOut():
        file_id = 5439
        file = in_api.getFileFromId(file_id=file_id)

        if file.status != IN_DATA_STRUCTURE.FileStatus.CheckIn:
            raise ValueError('Please Checkin first')

        # download=True, checkout 时 可选择是否下载文件
        r = in_api.checkout(file_id=file_id, download=True, version=None)
        print('checkout: ', r)


    def testUploadReference():
        path = u'D:/bon/other/face/小坏坏/3.jpg'
        task_id = 6478

        r = in_api.uploadReferenceFile(task_id=task_id, src_path=path)
        assert r is True

        files = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.Reference)    # return dict: {FileType: `TaskFileVO`}
        for _file_type, task_file_vo in files.items():
            # Here are All References Files
            for file in task_file_vo.files:
                print(file.fileId, file.name)

            for seq_file in task_file_vo.sequenceFiles:
                for file in seq_file.files:
                    print(file.fileId, file.name)


    def testUploadRequired():
        path = u'D:/bon/other/face/小坏坏/3.jpg'
        task_id = 6478

        r = in_api.uploadRequiredFile(task_id=task_id, src_path=path)
        assert r is True


        # result:
        #     {
        #         0: <IN_DATA_STRUCTURE.TaskFileVO object at 0x000000000494EE80>,
        #         1: <IN_DATA_STRUCTURE.TaskFileVO object at 0x000000000494EE80>,
        #         2: <IN_DATA_STRUCTURE.TaskFileVO object at 0x000000000494EE80>,
        #     }

        files = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.Required)    # return dict: {FileType: `TaskFileVO`}
        for _file_type, task_file_vo in files.items():
            # Here are All References Files
            for file in task_file_vo.files:
                print(file.fileId, file.name)

            for seq_file in task_file_vo.sequenceFiles:
                for file in seq_file.files:
                    print(file.fileId, file.name)


    def testUploadOutputFile():
        path = 'I:/BonProject/assets/BonAsset_9/none/c.jpg'
        task_id = 6622

        r = in_api.uploadOutputFile(task_id=task_id, src_path=path)
        assert r is True

        files = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.Output)    # return dict: {FileType: `TaskFileVO`}
        for _file_type, task_file_vo in files.items():
            for file in task_file_vo.files:
                print(file.fileId, file.name)

            for seq_file in task_file_vo.sequenceFiles:
                for file in seq_file.files:
                    print(file.fileId, file.name)


    def testUploadLibraryFile():
        src_path = u'D:/bon/other/face/小坏坏/11.jpg'
        directory = '/com_1/TEXTURE'

        r = in_api.uploadLibraryFile(src_path, directory=directory, file_name=None)
        assert r is True

        files = in_api.listdir(folder_id=12961)    # library: 12161
        printer(files)


    def testUploadCommentFile():
        path = r'D:\Introduction.mp4'
        task_id = 6478

        r = in_api.uploadCommentFile(
              task_id=task_id, src_path=path,
              comment_type=IN_DATA_STRUCTURE.CommentType.Video)
        assert r is True
        comments = in_api.getTaskComment(task_id)
        for comment in comments:
            print(comment)


    def testUploadPlaceHolders():
        path = r'C:\Users\admin\Desktop\temp.mb'

        r = in_api.uploadPlaceHolders(src_path=path)
        assert r is True

        placeholder_list = in_api.getPlaceHolderList()
        printer(placeholder_list)


    # testUpload()
    # testDownload()
    # testCheckIn()
    testCheckOut()
    # testUploadReference()
    # testUploadRequired()
    # testUploadOutputFile()
    # testUploadLibraryFile()
    # testUploadCommentFile()
    # testUploadPlaceHolders()


# ------------------------------ Project ------------------------------
_test_Project = False
if _test_Project:
    # ---------- Create Project ----------

    """
    ----------StorageInfo----------
    basePath       /mnt/wd_hdd_4t/data
    freeSpace      2905481093465
    groupName      hdd_group_00
    instanceId     hdd_group_00_01
    ip           192.168.17.212
    port           6000
    storageType    hdd
    totalSpace     3998831599616
    """

    # 从 StorageInfo 里拿到 storageType
    storage_list = in_api.getStorageInfos()
    # file_server_root = storage_list[0].storageType
    printer(storage_list)

    file_server_root = 'wsrd'

    index = 14
    project_name = 'PythonAPIProject_%s' % index

    # result: `INQProjectVO`
    proj = in_api.createProject(
        project_name=project_name,
        type=IN_DATA_STRUCTURE.ProjectType.FILM,
        file_server_root=file_server_root,
        department_id=141,
        project_root_id=20200502,
        issue_date='2021-01-12 00:00:00',
        due_date='2021-12-31 00:00:00',
        root_dir='I:',
        description='Created by Python API',
        color='#0000ff',
    )
    print('Create Project: %s' % proj.projectId)



# ------------------------------ PipelineStep ------------------------------
_test_PipelineStep = False
if _test_PipelineStep:

    def createPipelineStep():
        project_id = 120
        pipeline_name = 'PythonPipelineStep'
        coordinator_id = 20200502

        # ---------- Delete PipelineStep ----------
        p_steps = in_api.getPipelineSteps(project_id=project_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)
        for p_step in p_steps:
            if p_step.pipelineName == pipeline_name:
                is_successful = in_api.deletePipelineStep(pipeline_id=p_step.pipelineId)
                print('Delete Pipeline %s: %s' % (p_step.pipelineId, is_successful))
                break


        # ---------- Create PipelineStep ----------
        # Method 1: [ [file_path, file_name, placeholder_id], ... ]
        # output_files = [['/geo', 'source.mb', 12767], ]
        # output_files = [['/geo/rig', '', -1], ]

        # Method 2: [ file_path, ... ]
        output_files = ['/geo/source.mb', '/geo/fx', '/geo/rig', '<asset_name>/geo']

        pipeline_type = IN_DATA_STRUCTURE.PipelineType.Asset
        coordinator_id = coordinator_id
        approval_list = [coordinator_id]    # personId
        description = 'Created by Python API'
        to_validate = False
        loader_script = ''
        validation_script = ''

        # result: `INPipelineStep`
        pipeline = in_api.createPipelineStep(
            project_id=project_id,
            pipeline_name=pipeline_name,
            pipeline_type=pipeline_type ,
            coordinator_id=coordinator_id,
            approval_list=approval_list,
            output_files=output_files,
            description=description,
            to_validate=to_validate,
            loader_script=loader_script,
            validation_script=validation_script,
        )
        print('Create Pipeline: %s' % pipeline.pipelineId)
        return


    def updatePipelineStep_1():
        # ---------- Update PipelineStep ----------

        project_id = 120
        coordinator_id = 20200502
        pipeline_name = 'PythonPipelineStep'

        # name: 'PythonPipelineStep', id: 1266
        p_steps = in_api.getPipelineSteps(project_id=project_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)
        # printer(p_steps)

        # 用名字获得 Pipeline ID
        pipeline = list(filter(lambda p_step: p_step.pipelineName == pipeline_name, p_steps))
        if not pipeline: raise ValueError('There are not Pipeline')
        pipeline_id = pipeline[0].pipelineId

        output_files = ['<asset_name>/geo']

        new_pipeline_name = pipeline_name

        pipeline_type = IN_DATA_STRUCTURE.PipelineType.Asset
        coordinator_id = coordinator_id
        approval_list = [coordinator_id]    # personId
        description = 'Created by Python API Modified'
        to_validate = False
        loader_script = ''
        validation_script = ''


        pipeline = in_api.updatePipelineStep(
            project_id=project_id,
            pipeline_id=pipeline_id,
            pipeline_name=new_pipeline_name,
            pipeline_type=pipeline_type,
            approval_list=approval_list,
            output_files=output_files,
            coordinator_id=coordinator_id,
            description=description,
            to_validate=to_validate,
            loader_script=loader_script,
            validation_script=validation_script,
        )
        print('Update Pipeline: %s' % pipeline.pipelineId)
        return


    def updatePipelineStep_2():
        # ---------- Update PipelineStep ----------

        # 由于 update pipeline 之后,
        # 如果以前有路径  '/old_path/xxx/', 但现在没有, 则原有的 WorkflowTempalte 连接就会断开
        # 此时, 你可以先 `getWorkFlowTempl`, 记录原有的关系
        # 之后调用 `updateWorkFlowTempl`, 将会自动连上所有 OutputFile

        workflow_id = 1393
        pipeline_id = 1856
        output_files = ['<project_name>/<asset_name>/source.mb']

        # Get old Workflow
        workflow_vo = in_api.getWorkFlowTempl(workflow_id=workflow_id)

        # build PipelineNodes
        pipeline_nodes = IN_PYTHON_API_LIB._rebuildWorkflowPipelineNodes(workflow_vo)

        # Update Pipeline
        pipeline = in_api.updatePipelineStep(pipeline_id=pipeline_id, output_files=output_files)
        print('Update Pipeline: %s' % pipeline.pipelineId)

        # Reset Workflow relationship
        workflow = in_api.updateWorkFlowTempl(workflow_id=workflow_id, pipeline_nodes=pipeline_nodes)

        print('Update Workflow: %s' % workflow.workFlowId)
        return


    # createPipelineStep()
    # updatePipelineStep_1()
    # updatePipelineStep_2()


# ------------------------------ Workflow Template ------------------------------
_test_WorkflowTemplate = False
if _test_WorkflowTemplate:

    project_id = 120
    index = 1
    workflow_name = 'PythonWorkflow_%s' % index

    def createWorkflow():

        # ---------- Delete WorkflowTemplate ----------
        workflow_list = in_api.getWorkFlowTempls(project_id=project_id, pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset)
        for workflow in workflow_list:
            if workflow.workFlowName == workflow_name:
                is_successful = in_api.deleteWorkFlowTempl(workflow_id=workflow.workFlowId)
                print('Delete Workflow %s: %s' % (workflow.workFlowId, is_successful))
                break


        # ---------- Create WorkflowTemplate ----------
        ids = [2700, 2701, 2702, 2703]

        # ---------- Test 1 ----------
        # 注意 parents 是一个 list
        p1_1 = IN_DATA_STRUCTURE.PipelineNode(id=ids[0], alias='s1_alias_name')
        p1_2 = IN_DATA_STRUCTURE.PipelineNode(id=ids[0])
        p1_3 = IN_DATA_STRUCTURE.PipelineNode(id=ids[0])
        p1_4 = IN_DATA_STRUCTURE.PipelineNode(id=ids[0])
        p1_5 = IN_DATA_STRUCTURE.PipelineNode(id=ids[0])
        p2_1 = IN_DATA_STRUCTURE.PipelineNode(id=ids[1], parents=[p1_1])
        p2_2 = IN_DATA_STRUCTURE.PipelineNode(id=ids[1], parents=[p1_1])
        p2_3 = IN_DATA_STRUCTURE.PipelineNode(id=ids[1], parents=[p1_1])
        p2_4 = IN_DATA_STRUCTURE.PipelineNode(id=ids[1], parents=[p1_2])
        p2_5 = IN_DATA_STRUCTURE.PipelineNode(id=ids[1], parents=[p1_2])
        p3_1 = IN_DATA_STRUCTURE.PipelineNode(id=ids[2], parents=[p2_1, p2_2])
        p3_2 = IN_DATA_STRUCTURE.PipelineNode(id=ids[2], parents=[p1_4, p2_2])
        p4_1 = IN_DATA_STRUCTURE.PipelineNode(id=ids[3], parents=[p3_1])
        p5_1 = IN_DATA_STRUCTURE.PipelineNode(id=ids[3], parents=[p4_1])
        pipeline_nodes = [p1_1, p1_2, p1_3, p1_4, p1_5, p2_1, p2_2, p2_3, p2_4, p2_5, p3_1, p3_2, p4_1, p5_1]


        # ---------- Test 2 ----------
        column_count = 4
        pipelines_id = [2700, 2701, 2702, 2703]
        pipeline_nodes = []

        for row, pipeline_id in enumerate(pipelines_id):
            for _ in range(column_count):
                # 注意 parents 是一个 list
                parents = []
                parent_index = len(pipeline_nodes) - column_count
                if parent_index >= 0:
                    parents = [pipeline_nodes[parent_index]]

                pipeline_nodes.append(IN_DATA_STRUCTURE.PipelineNode(pipeline_id, parents=parents))


        # ---------- Create WorkflowTemplate ----------
        # result: `INQWorkFlowVO`
        workflow = in_api.createWorkFlowTempl(
            project_id=project_id,
            workflow_name=workflow_name,
            pipeline_type=IN_DATA_STRUCTURE.PipelineType.Asset,
            pipeline_nodes=pipeline_nodes)
        print('Create Workflow: %s' % workflow.workFlowId)
        return

    def updateWorkflow():
        # ---------- Update WorkflowTemplate ----------

        # 参照 updatePipelineStep_2()

        return


    createWorkflow()


# ------------------------------ Asset ------------------------------
_test_Asset = False
if _test_Asset:

    # ---------- Create Asset ----------
    # 创建 Asset 之后, 会按 workflow 自动创建对应数量的任务
    # 如果你想 Assign Task to Person, 你需要自己获取任务 id, 详见下面 `testEditTask`

    i = 3
    asset_name = 'BonAsset_%s' % i
    alias = asset_name
    project_id, workflow_id, asset_color = 120, 1393, ''
    tags = [ ['bon_tag_name', '#0000ff'], ['bon_tag_name_2', '#ff0000'] ] # [ [tag_name, tag_color] ]


    # ---------- Delete Asset ----------
    assets = in_api.getAssetsByCondition(project_id=project_id)
    for asset in assets:
        if asset.assetName == asset_name:
            is_successful = in_api.deleteAsset(asset.assetId, force=True)
            print('Delete Asset %s: %s' % (asset.assetId, is_successful))

    # ----- Clear in RecycleBin -----
    records_id = [record.id
     for record in in_api.getBusRecycleBinList(project_id=project_id)
     if asset_name in record.objectName]

    if records_id:
        in_api.deleteObjectInRecordBin(project_id=project_id, records_id=records_id)

    # ---------- createAsset ----------
    # result: `INAsset`
    asset_obj = in_api.createAsset(
        project_id, workflow_id, asset_name, alias, asset_color=asset_color,
        description='Created By Python API', tags=tags)
    asset_id = asset_obj.assetId
    print('Create Asset: %s' % asset_id)


    # ---------- Get Asset Info ----------
    # assets = in_api.getAssetsByCondition(project_id=217)    # project_id=72, asset_ids=[435]
    # asset_id = 963
    asset = in_api.getAssetInfo(asset_id=asset_id)
    printer(asset)

    # And
    # assets = in_api.getAssetsByCondition(project_id=217)    # project_id=72, asset_ids=[435]

    # ---------- Edit Asset ----------
    r = in_api.editAsset(asset_id=asset_id, color='#000000', description='Edit Asset by Python API')
    print('Edit Asset: %s' % r)


# ------------------------------ Shot ------------------------------
_test_Shot = False
if _test_Shot:

    # ---------------------------------------------
    # CreateScene 接口已废弃, 全部统一采用 CreateShot
    # 包括, Film/TV 类型
    # ---------------------------------------------

    def test_delete_shot(project_id, shot_name):
        # ---------- Delete Shot ----------
        shots = in_api.getShotsByCondition(project_id=project_id)
        for shot in shots:
            if shot.shotName == shot_name:
                is_successful = in_api.deleteShot(shot.shotId, force=True)
                print('Delete Shot %s: %s' % (shot.shotId, is_successful))

        # ----- Clear in RecycleBin -----
        for record in in_api.getBusRecycleBinList(project_id=project_id):
            if shot_name in record.objectName:
                try:
                    in_api.deleteObjectInRecordBin(record_id=record.id)
                except Exception as e:
                    logging.warning(e)


    def test_film_shot():
        project_id, workflow_id, scene_number, shot_number, shot_color = 120, 1398, '001', '0400', '#ffffff'
        shot_name = 'shot%s' % shot_number
        tags = [ ['bon_shot_tag_name', '#ffffff'], ['bon_shot_tag_name_2', ''] ]    # [ [tag_name, tag_color] ]

        test_delete_shot(project_id, shot_name)

        # ---------- Create Shot (Film) ----------
        # 创建 Film Shot,  不需要传入 type, 因为你创建 project 的时候已经设定了 Film / TV 类型了
        shot_obj = in_api.createShot(
            project_id, workflow_id,
            scene=scene_number,
            shot=shot_number,
            shot_color=shot_color,
            description='Created by Python API',
            tags=tags)
        shot_id = shot_obj.shotId
        print('Create Shot: %s' % shot_id)


        # ---------- Edit Shot ----------
        r = in_api.editShot(shot_id=shot_id, color='#000000', description='Edit Asset by Python API')
        print('Edit Shot: %s' % r)
        return


    def test_tv_shot():
        project_id = 240
        workflow_id = 2128
        season_number = '001'
        episode_number = '001'
        scene_number = '001'
        shot_number = '0800'
        shot_color = '#0000ff'
        shot_name = 'shot%s' % shot_number
        tags = [ ['bon_shot_tag_name', '#ffffff'], ['bon_shot_tag_name_2', ''] ]    # [ [tag_name, tag_color] ]

        test_delete_shot(project_id, shot_name)

        # ---------- Create Shot (TV) ----------

        # 创建 TV Shot
        # result: `INShot`
        shot_obj = in_api.createShot(
            project_id, workflow_id,
            season=season_number,
            episode=episode_number,
            scene=scene_number,
            shot=shot_number)
        shot_id = shot_obj.shotId
        print('Create Shot: %s' % shot_id)


        # ---------- Get Shot Info ----------
        # e.g. [<INShot>, ...]
        shots = in_api.getShotsByCondition(project_id=project_id, workflow_id=workflow_id)
        # pprint(shots)
        for shot in shots:
            # print(shot.shotId, shot.shotName)
            if shot_id == shot.shotId:
                break
        else:
            raise Exception('Invalid shot_id')

        # And
        # shots = in_api.getShotsByCondition(project_id=72)    # project_id=72, scene_ids=[65, 61], shot_ids=[533, 534]

        # ---------- Edit Shot ----------
        r = in_api.editShot(shot_id=shot_id, color='#000000', description='Edit Asset by Python API')
        print('Edit Shot: %s' % r)
        return

    test_film_shot()
    # test_tv_shot()


# ------------------------------ Task ------------------------------
_test_Task = False
if _test_Task:

    # -------------------- Get Task Info --------------------
    def testGetTaskInfo():
        tasks = in_api.getTasksByConditions(project_id=120)    # object_ids=[644, 659], task_ids=[5217, 5319, 5320], project_id=72
        # printer(tasks)

        for task in tasks:
            # result: `INTask`
            task = in_api.getTaskFromID(task.taskId)
            print('Task:', task.taskId, task.taskName)
        return

    def testCreateTask():

        pipeline_type = IN_DATA_STRUCTURE.PipelineType.Asset,
        project_id = 120
        object_id = 4592    # object_id 为 Asset / Shot / Sequence ID, 取决于 pipeline_type
        pipeline_step_id = 1856    # Pipeline Step ID, 可通过 `getPipelineSteps` 获取
        alias = 'Python API Task Alias'
        assignee_team_id = 388    # Assignee 给某Team
        assignee_person_id = 20200502    # Assignee 给某人
        issue_date = '2020-01-19 00:00:00'
        due_date = '2020-01-19 00:00:00'
        privilege_start_time = '2020-12-28 00:00:00'
        privilege_end_time = '2020-12-28 00:00:00'
        storage_type = 'film'    # storage_type 需要调用 `getStorageInfos` 获取, 若传入None则默认存在第一个 Server
        color = '#ff0000'
        description = 'Created by Python API `createTask`'

        task = in_api.createTask(
            pipeline_type=pipeline_type,
            project_id=project_id,
            object_id=object_id,
            pipeline_step_id=pipeline_step_id,
            alias=alias,
            assignee_team_id=assignee_team_id,
            assignee_person_id=assignee_person_id,
            storage_type=storage_type,
            issue_date=issue_date,
            due_date=due_date,
            privilege_start_time=privilege_start_time,
            privilege_end_time=privilege_end_time,
            color=color,
            description=description,
        )
        print('Create Task: %s' % task.taskId)
        return

    # -------------------- Edit Task Info --------------------

    def testEditTask():

        task_id = 39971

        # Test
        to_validate=False
        loader_script='loader_script.py'
        validation_script='validation_script.py'

        # ----- Edit Task -----
        # 能传入任意参数编辑 Task, 包括 Assign 给某人
        r = in_api.editTask(task_id, color='#ff00ff', description='Edited by Python API',
            to_validate=to_validate,
            loader_script=loader_script,
            validation_script=validation_script,)
        print('Edit Task: %s' % r)


        # ----- Assign Task to Person -----
        project_id = 120
        storage_list = in_api.getStorageInfos(project_id=project_id)
        if len(storage_list) == 0: raise ValueError('Invalid Storage Info')
        # 从 storage 里拿到 type, storage_list[0].storageType    # str: hdd

        team_id = 388
        person_id = 20200502
        issue_date = '2020-01-09 00:00:00'    # 开始时间
        due_date = '2020-01-30 00:00:00'    # 结束时间
        privilege_start_time = '2020-01-09 00:00:00'
        privilege_end_time = '2020-01-30 00:00:00'


        # -----------------------------------------------------
        # 第一次 Assign Task to Person, `需要至少传入下面这几个参数`
        # -----------------------------------------------------
        r = in_api.editTask(
            task_id,
            assignee_team_id=team_id,
            assignee_person_id=person_id,
            storage_type=storage_list[0].storageType, # e.g. 'hdd', 创建项目时会要求选一个 storage_type, 默认为 None, 会存储在第一个 storage
            issue_date=issue_date, # 开始时间, 需按照具体格式填写
            due_date=due_date, # 结束时间, 需按照具体格式填写
            privilege_start_time=privilege_start_time,
            privilege_end_time=privilege_end_time,
        )
        print('Assign task to person: %s' % r)
        return

    def testEditTask_Others():
        task_ids = [40052]
        assignee = 20200502
        issue_date = '2020-01-20 00:00:00'    # 开始时间
        due_date = '2020-01-31 00:00:00'    # 结束时间

        print(in_api.editTaskAssignee(task_ids, assignee))
        print(in_api.editTaskTime(task_ids, issue_date, due_date))
        return

    # -------------------- Update Task Status --------------------
    # 想要获得任务的流向, 判断任务先后顺序, 需要调用 `getWorkFlowInstance` 接口
    # 判断 TaskWorkflow.taskList.parentTaskIdList,
    # 没有 parent 的, 就证明是单个节点, 或是最 top 的节点
    # 这里只列出了 parent attribute, 没有 child

    def testToWorkInProgress(task_id):
        # ----- to WorkInProgress -----
        # e.g. 'I:'
        in_map_dir = in_api.getINMapDir()

        # int: 2
        new_status = IN_DATA_STRUCTURE.TaskStatus.WorkInProgress

        # e.g. [2, 9, 10]
        next_statuses = in_api.getTaskNextAvailableStatus(task_id)
        print(next_statuses)

        if new_status not in next_statuses:
            raise ValueError('\n    new_status %s not in NextAvailableStatus %s' % (new_status, next_statuses))

        # 要改为 WorkInProgress, 要先 Checkout 所有 OutputFile
        if new_status == IN_DATA_STRUCTURE.TaskStatus.WorkInProgress:
            # Get output files id & checkout all files
            # getTaskOutputFiles 只返回一些数据, 想获得详细参数, 请用 getTaskRelatedFiles
            for file in in_api.getTaskOutputFiles(task_id):
                print(file.fileId, file.directory, file.name, file.status)
                if file.status == IN_DATA_STRUCTURE.FileStatus.CheckOuted:
                    continue

                r = in_api.checkout(file.fileId, download=True)
                print('checkouted file_id %s: %s' % (file.fileId, r))

        # Update Status
        r = in_api.updateTaskStatus(task_id, new_status, is_required_first_approved=False)
        print('update task status:', r)
        return


    def testToPendingApproval(task_id):
        # ----- to PendingApproval -----

        # 现在 IN 需要在每个 Project 上面设置映射路径,
        # 所以这个 in_map_dir 不是太必要,
        # 如果你需要获得映射路径, 可以 getProject()
        # e.g. 'I:'
        in_map_dir = in_api.getINMapDir()

        # int: 3
        new_status = IN_DATA_STRUCTURE.TaskStatus.PendingApproval

        # e.g. [3, 9, 10]
        next_statuses = in_api.getTaskNextAvailableStatus(task_id)
        print(next_statuses)

        if new_status not in next_statuses:
            raise ValueError('\n    new_status %s not in NextAvailableStatus %s' % (new_status, next_statuses))

        # 要改为 PendingApproval, 要先 Checkin 所有 OutputFile
        if new_status == IN_DATA_STRUCTURE.TaskStatus.PendingApproval:
            # Get output files id & checkout all files

            # getTaskOutputFiles 只返回一些数据, 想获得详细参数, 请用 getTaskRelatedFiles
            for file in in_api.getTaskOutputFiles(task_id):

                print(file.fileId, file.directory, file.name, file.status)

                if file.status == IN_DATA_STRUCTURE.FileStatus.CheckIn: continue

                # 文件夹的话需要自己递归, 找出哪些文件需要 upload
                # 上传新 OutputFile 文件需要调用 uploadOutputFile 接口
                # 之前上传过的, 已经在 OutputFile 列表里了
                if file.type == IN_DATA_STRUCTURE.BusFileType.BusEmptyFolderFile: continue

                src_path = in_map_dir + '/'.join([file.directory, file.name])
                print(src_path)
                r = in_api.checkin(file.fileId, src_path=src_path)
                print('checkin:', file.fileId)
                continue


        # Update Status
        r = in_api.updateTaskStatus(task_id, new_status, is_required_first_approved=False)
        print('update task status:', r)
        return


    # -------------------- Edit Task Files --------------------

    def testTaskReferenceFile(task_id, file_id):
        # ----- Task Reference File -----

        # Add
        r = in_api.addTaskReferenceFile(task_id, file_id, variant_id=0)
        print('Add reference file %s: %s' % (file_id, r))

        # Get
        files = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.Reference)
        pprint(list(files.values())[0].files + list(files.values())[0].sequenceFiles)

        # Remove
        r = in_api.removeTaskReferenceFile(task_id, file_id)
        print('Remove reference file %s: %s\n' % (file_id, r))
        return True


    def testTaskRequiredFile(task_id, file_id):
        # ----- Task Required File -----
        # Add
        r = in_api.addTaskRequiredFile(task_id, file_id, variant_id=0)
        print('Add required file %s: %s' % (file_id, r))

        # Get
        files = in_api.getTaskRelatedFiles(task_id=task_id, file_type=TaskFileType.Required)
        pprint(list(files.values())[0].files + list(files.values())[0].sequenceFiles)

        # Remove
        r = in_api.removeTaskRequiredFile(task_id, file_id)
        print('Remove required file %s: %s\n' % (file_id, r))
        return True


    def testTaskOutputFile(task_id):
        # ----- Task Output & Intermediate File -----

        # 你要添加的 OutputFile 路径
        relpath_n_name = ('/BonProject/assets/BonAsset_100/none', 'a.b.c.mb')    # e.g. file
        suffix = 'mb'

        # relpath_n_name = ('/BonProject/assets/BonAsset_100/none/a.b.c.d', '')    # e.g. folder
        # suffix = '.folder'

        # relpath_n_name = ('/BonProject/assets/GG/geo', 'source.mb')    # e.g. file
        # relpath_n_name = (r'\BonProject\assets\GG\geo', '')    # e.g. folder

        placeholder_file_id = None

        # Add
        # 检查你要设置的 OutputFile 路径, 它的后缀, 是否存在于 placeholder list
        # 若不存在, 需要先调用 `uploadPlaceHolders`
        placeholder_files = in_api.getPlaceHolderList()
        for file in placeholder_files:
            if file.name == suffix:
                placeholder_file_id = file.fileId
                break
        else:
            raise ValueError('Please upload placeholder file first')

        # PendingApproval 状态下, 不能添加 OutputFile
        # 这里 Add OutputFile, 仅仅是添加路径, 实际并不上传文件,
        # 注意 relpath_n_name, 是 list/tuple, 是 2 个 elements,
        r = in_api.addTaskOutputFile(task_id, placeholder_file_id, relpath_n_name, is_intermediate_file=False)
        print('Add output file, placeholder_file %s: %s' % (placeholder_file_id, r))


        # 检查是否添加成功, 添加之后服务器可能有延迟, 所以下面可能有报错, 可以 time.sleep 一下
        time.sleep(2)
        file_id = None
        # Get
        for file in in_api.getTaskOutputFiles(task_id=task_id):
            print(file.fileId, file.directory, file.name, file.status)
            if (file.directory == relpath_n_name[0]) and (file.name == relpath_n_name[1]):
                file_id = file.fileId
                print('\nYour new OutputFile ID: %s' % file_id)
                break
        else:
            raise ValueError('Not found your new OutputFile')

        # Edit
        # Exception: INTERNAL_SERVER_ERROR: Insufficient permissions or other errors
        # r = in_api.editTaskOutputFile(file_id, is_intermediate_file=True)
        # print('edit output file %s: %s' % (file_id, r))

        # Remove
        r = in_api.removeTaskOutputFile(task_id, file_id)
        print('Remove output file %s: %s' % (file_id, r))

        return True


    # -------------------- Delete Task --------------------
    def testDeleteTask(task_id):
        # ----- Delete Task -----
        r = in_api.deleteTask(task_id, force=True)
        print('Delete task: %s' % r)
        return True


    # testGetTaskInfo()
    # testCreateTask()
    # testEditTask()
    # testEditTask_Others()
    # testToWorkInProgress(task_id=40052)
    # testToPendingApproval(task_id=40052)
    # testTaskReferenceFile(task_id=39972, file_id=89973)
    # testTaskRequiredFile(task_id=39972, file_id=89973)
    # testTaskOutputFile(task_id=39972)
    # testDeleteTask(task_id=39972)


# ------------------------------ Variant ------------------------------
_test_Variant = False
if _test_Variant:

    asset_id = 4592
    variant_name = 'Variant Created by Python API'

    # ----- Delete Variant -----
    [in_api.deleteVariantById(variant.variantId)
    for variant in in_api.getVariantByAssetId(asset_id=asset_id)
    if variant.variantName == variant_name]

    # ----- Create Variant -----
    variant_id = in_api.createVariant(asset_id, variant_name, files_id=None)
    print('Created Variant: %s' % variant_id)


    # ----- Get Asset Variant Record/Usage -----
    variants_record = in_api.getVariantRecordByAssetId(asset_id=asset_id)
    printer(variants_record)


    # ----- Get Asset Variant -----
    variants = in_api.getVariantByAssetId(asset_id=asset_id)
    for variant in variants:
        print(variant.variantId, variant.variantName)
        if variant.variantId != variant_id: continue

        # variant.taskFiles:    `FileTaskVO`
        for file_task_vo in variant.taskFiles:
            # 假设名字是这个,
            # <Task>: <file_name>
            # Grooming: bianfu_patch.abc

            # 能看到文件属于哪个 Task
            # file_task_vo.task:    `INTask`
            print(file_task_vo.task)

            # 最终的 Files
            # file_task_vo.files:    list of `FileVO`
            for file in file_task_vo.files:
                print(file.fileId, file.name)


    # ----- Edit Variant -----
    variant_name = 'Variant Edited by Python API'
    r = in_api.editVariant(asset_id, variant_id, variant_name, files_id=None)
    print('Edit Variant: %s' % r)



    # ----- Delete Variant -----
    r = in_api.deleteVariantById(variant_id)
    print('Delete Variant: %s' % r)


# ------------------------------ Super Search ------------------------------
_test_superSearch = False
if _test_superSearch:

    regex = 'shot=shot0100'
    regex = 'shot=shot0100&&pro=BonProject'
    regex = 'pro=bon*&asset=*20*'
    regex = 'asset=*&&pro=BonProject'
    regex = 'asset=BonAsset*'
    regex = 'pro=BonProject&&file=*'
    regex = 'file=D.jpg'
    regex = 'file=source.mb'
    regex = 'folder=library'
    regex = 'folder=*BonAsset_*'
    regex = 'folder=/BonProject/assets'
    regex = 'folder=/BonProject/assets/BonAsset_31/*||file=/BonProject/assets/BonAsset_31/*'
    regex = 'file=/BonProject/assets/BonAsset_31/geo/source.mb'
    regex = 'file=/BonProject/assets/BonAsset_31/geo/*'
    regex = 'file=/BonProject/assets/BonAsset_31/*'
    regex = 'file=D.jpg||folder=*components*'


    # 列出所有 tag==char 的 object
    regex = 'tag=char'
    # 列出所有 tag==char 的 object, 如果 shot / task / file... 也带有 char, 都会列出
    regex = 'tag=char&&pro=BonProject'
    # 如果只要 asset, 不要其它
    regex = 'tag=char&&pro=BonProject&&asset=Bon*'
    # 这里和上面有些区别, 这里只是单纯找 project
    # 先找到所有 Bon* Project, 然后检查它们的 Attribute, tag == char
    regex = 'pro=Bon*&&pro.tag=char'

    # 先获取所有 tag == char 的 Asset. 然后, && 检查它们的 Attribute, project == tvtest2
    regex = 'asset.tag=char&&pro=tvtest2'

    """
    result: {'assets': [INAsset, ...],
             'files': [FileVO, ...],
             'folders': [FolderVO, ...],
             'projects': [INQProjectVO, ...],
             'shots': [INShot, ...],
             'tasks': [INTask, ...]}
    """
    # 更多 Example / Introduction, 请 help(in_api.superSearch)
    _dict = in_api.superSearch(regex)
    pprint(_dict)





