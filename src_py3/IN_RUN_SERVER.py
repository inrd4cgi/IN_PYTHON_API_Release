#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-10-28 08:59:32
# @Author  : Your Name (you@example.org)
# @Link    : http://example.org
# @Version : $Id$


import os
import sys
import pathlib


# current_path = 'D:/DEV/Github/IN_PYTHON_API_Release/src_py3/IN_API_SERVER_B.pyd'

# e.g. D:/DEV/Github/IN_PYTHON_API_Release/src/IN_RUN_SERVER.py
current_path = pathlib.Path(__file__)
# print("\ncurrent_path: ", current_path)

python_exe = current_path.parent.parent / "env/win64/python3.7/python.exe"
# print("python_exe: ", python_exe)

sys.path.append(current_path.parent.as_posix())



LANGUAGE = "python"

# e.g. ['D:/DEV/Github/IN_PYTHON_API/src/IN_RUN_SERVER.py', 'js']
# e.g. ['D:/DEV/Github/IN_PYTHON_API/src/IN_RUN_SERVER.py', 'python']
if len(sys.argv) == 2:
    LANGUAGE = sys.argv[1]

# print("LANGUAGE: ", LANGUAGE, "  type: ", type(LANGUAGE))

#
# def start_server():
#     # Start Server
#
#     # for Python
#     # if LANGUAGE == "python":
#         # import IN_API_CLIENT
#         # r = IN_API_CLIENT.start_server()
#         # return r
#
#
#     # for Javascript
#     import IN_API_CLIENT
#     py_pid_list = IN_API_CLIENT.check_server()
#     len_pid = len(py_pid_list)
#     # print("pid: ", py_pid_list)
#     if not len_pid:
#         import IN_API_SERVER_B
#         print(IN_API_SERVER_B)
#         server = IN_API_SERVER_B.run(host='127.0.0.1', port='20618')
#     # p = subprocess.Popen(server_script_path, shell=True, creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)


# if LANGUAGE != "python":
#     start_server()


import IN_API_CLIENT
r = IN_API_CLIENT.start_server()
print(r)

# import IN_API_SERVER
# r = IN_API_SERVER.run_server()


