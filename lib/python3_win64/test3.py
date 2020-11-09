# coding:utf-8

import time
import sys, os
import INSDriver
from INSDriver import *
from multiprocessing import Process

def works(func, arg, worknum):
    proc_record = []
    for i in range(worknum):
        time.sleep(1)
        p = Process(target=func,args = (i,))
        p.start()
        proc_record.append(p)
    for p in proc_record:
        p.join()

def test_tag_info():
    result = INS.QListTagInfoVO()
    searchmap = {"tagGroupId": 1, "resourceId": 18}
    ret = INI.GetTagInfo(result, searchmap)
    print(ret)

def test_get_team_info_proID():
    pt = INS.ProjectTaskInfo()
    for i in [148,149,150,151,153,154,155]:
        pt.currproject.projectId = i
        ret = INI.GetTeamInfoFromProID(pt)
        print(ret)

def test_GetTaskListPersonal():
    personid = 20200170
    obj = INS.QListINTask()
    ret = INI.GetTaskListPersonal(personid, obj);

def get_tasks():
    param1 = INS.QListINTask()
    param2 = INS.TaskFilterParam()
    ret = INI.GetTasksByConditions(param1, param2)
    print(ret)


#注意要启用事件循环 app.exec()
def test_upload_library():
    target_file_name = "lib_CFileOperateBase.cpp"
    remote_dir = "/aaa/bbb"
    local_file_dir = r"C:\Users\22973\Desktop\python_api_0820_3\src\CFileOperateBase.cpp"
    up = INI.UploadLibrayFile(target_file_name, remote_dir, local_file_dir)
    up.Start()

def conn_test(j):
    app = INI.initApp()
    ipAddr = "192.168.17.25"
    port = 6060
    INI.ConnectToServer(ipAddr, port)
    ret = INI.Login("tiantian", "1", True, str(j))
    if ret != 1:
        print("log in error")
        return
    
    #通过调节接口调用次数来给服务器压力
    checkin_test()
    app.exec_()

def checkin_test():
    file_base = INS.INFileBase()
    file_base.id = 2406
    
    #文件名
    file_base.name = "note.txt"
    #相对目录
    file_base.directory = "/assets/apple"
    #根目录
    path = "C:/Users/22973/Desktop/pythonAPI-win-0821/data"
    #以上三个组成：path+file_base.directory+file_base.name = 
    #C:/Users/22973/Desktop/pythonAPI-win-0821/data/assets/apple/note.txt
    #注意事项：
    #1、确保路径中文件确实存在
    #2、确保checkout的人是测试使用的登录名，可用jim客户端checkout 这里checkin
    #3、请修改文件，一面md5相同。没有修改的文件，不允许check in。
    
    r = INI.CheckIn(file_base, path, '')
    r.Start()

if __name__ == '__main__':
    arg = 0
    #进程个数，模拟用户数量
    procs = 1
    works(conn_test, arg, procs)
