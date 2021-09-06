# coding:utf-8

import time
import sys, os
import INSDriver
from INSDriver import *
from multiprocessing import Process


def works(func, arg, worknum):
    proc_record = []
    for i in range(worknum):
        time.sleep(0.1)
        p = Process(target=func,args = (i,))
        p.start()
        proc_record.append(p)
    for p in proc_record:
        p.join()
    
def test_GetContentByCommentId():
    jstr = "[612]"
    pp = INI.jsonRequest(287, jstr)
    print(pp.encode("utf-8"))
    
    
def test_GetReviewTaskList():
    jstr = "[{\"projectId\":97,\"objectType\":1}]"
    pp = INI.jsonRequest(282, jstr)
    print(pp.encode("utf-8"))
    
def test_test():
    jstr = "[]"
    pp = INI.jsonRequest(288, jstr)
    print(pp.encode("utf-8"))
    
handler = 1
def test_DownLoad():
    f = INS.FileVO()
    f.fileId = 104583
    handler = INI.DownLoad(f, "")
    handler.Start()
    
    
def test_getTaskByCondition():
    jstr = "[{\"objectIds\":[1642], \"types\":[0]}]"
    pp = INI.jsonRequest(5202, jstr)
    print(pp.encode("utf-8"))
    
def test_getTasksExtraInfo():
    jstr = "[[15014,15015,15016]]"
    pp = INI.jsonRequest(5213, jstr)
    print(pp.encode("utf-8"))
    
def test_PostReview():
    jstr = "[{\"taskId\":75009, \"pixmapIds\":[31492, 31492, 31506]}]"
    pp = INI.jsonRequest(284, jstr)
    print(pp.encode("utf-8"))
    


def test_saveTaskRelationFile():
    jstr = '[{"taskId":1884, "fileType":0, "fileList":[{"fileId":1,"variantId":0,"isIntermediate":0,"isReview":0,"path":"/ab","name":"ba.txt"}]}]'
    pp = INI.jsonRequest(5215, jstr)
    print(pp.encode("utf-8"))
def test_GetTaskOutputFileComment():
    jstr = '["taskId":1884]'
    pp = INI.jsonRequest(5216, jstr)
    print(pp.encode("utf-8"))
def test_GetTaskDefaultOutputPath():
    jstr = '["taskId":1884]'
    pp = INI.jsonRequest(5217, jstr)
    print(pp.encode("utf-8"))
def test_getOutputFiles():
    jstr = '["projectId": 0,"objectType": 0,"pipelineStepId": 0,"assetName": "","seasonId": 0,"episodeId": 0,"sceneId": 0,"shotNumber": 0,"fileName": ""]'
    pp = INI.jsonRequest(5218, jstr)
    print(pp.encode("utf-8"))
def test_getRequiredFiles():
    jstr = '["taskId":1884]'
    pp = INI.jsonRequest(5219, jstr)
    print(pp.encode("utf-8"))
    
def test_uploadFilesBatch():
    jstr = '["projectId": 0,"taskId": 0,"assetId": 0,"shotId": 0,"uploadType": 0,"files":[{"fileId":0,"fileType":0,"path":"","fileName":"","checkCode":""}]]'
    pp = INI.jsonRequest(340, jstr)
    print(pp.encode("utf-8"))
def test_downloadFilesBatch():
    jstr = '["taskId":1884,"fileList":[{"fileId":0,"version":0}]]'
    pp = INI.jsonRequest(341, jstr)
    print(pp.encode("utf-8"))
def test_postFileComment():
    jstr = '["taskId":1884,"comment":"123"]'
    pp = INI.jsonRequest(342, jstr)
    print(pp.encode("utf-8"))

def conn_test(j):
    app = INI.initApp()
    # ipAddr = "192.168.17.25"
    ipAddr = "192.168.17.212"
    port = 7000
    INI.ConnectToServer(ipAddr, port)
    ret = INI.Login("root", "wsrnd", True, str(j))
    if ret != 1:
        print("log in error")
        return
    #调用次数
    #time.sleep(1);
    times = 1
    for i in range(times):
        test_saveTaskRelationFile()
        test_GetTaskOutputFileComment()
        test_GetTaskDefaultOutputPath()
        test_getOutputFiles()
        test_getRequiredFiles()
        test_uploadFilesBatch()
        test_downloadFilesBatch()
        test_postFileComment()
    
    #通过调节接口调用次数来给服务器压力
    #checkin_test()
    app.exec_()

if __name__ == '__main__':
    arg = 0
    #进程个数，模拟用户数量
    procs = 1
    works(conn_test, arg, procs)
