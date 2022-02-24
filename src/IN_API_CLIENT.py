#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
print(sys.version)

import six
import os
import re
import time
import json
import pickle
import threading
import inspect
import locale
import functools
import tempfile
import traceback

import socket
import signal
import threading
import subprocess
import multiprocessing
import shlex
import logging


import API_TEMPLATES

import IN_COMMON
from IN_COMMON import logger, APIMode
from IN_COMMON import ReceiveDataError, SocketError
from traceback import format_exc
import INSPECT_HELPER

try:
    from queue import Queue
except ImportError:
    try:
        from Queue import Queue
    except Exception as exce:
        logger.warning("IN_API_CLIENT [global] import queue error")

import requests

import IN_STREAMING
import IN_DATA_STRUCTURE

from IN_API_CLIENT_B import InApiClient as InApiClient
from IN_API_CLIENT_B import printer as printer

__version__ = IN_COMMON.VERSION




@IN_COMMON.exception_capture
def new_socket():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((IN_COMMON.API_SERVER_IP_ADDRESS, IN_COMMON.API_SERVER_PORT))

    if client_socket is None:
        msg = "New Socket Error, Please Check The API Server Whether running"
        raise SocketError(msg)

    return client_socket


@IN_COMMON.exception_capture
def api_receive(client_socket, *args, **kwargs):
    config_overtime_normal = IN_COMMON.CLIENT_WAIT_SERVER_OVERTIME_NORMAL
    config_ignore_overtime = IN_COMMON.CLIENT_WAIT_SERVER_OVERTIME_IGNORE
    head = IN_COMMON.API_COMMUNICATION_HEAD
    seg = IN_COMMON.HEAD_SEG_SIGN
    start_time = time.time()

    client_socket.setblocking(IN_COMMON.USING_RECEIVE_BLOCKING)

    rec = None

    ignore_overtime = False
    ignore_time = None
    if 'ignore_overtime' in kwargs and kwargs['ignore_overtime']:
        ignore_overtime = True
        ignore_time = config_ignore_overtime
        logger.warning("IN_API_CLIENT [api_receive] got `ignore_overtime` in kwargs parm, "
                       "using the ignore time: {} for get method result".format(ignore_time))

    # receive return
    while True:
        now_time = time.time()

        try:
            recv_msg = IN_COMMON.socket_receive_method(client_socket)
        except ReceiveDataError:
            client_socket.close()
            raise ReceiveDataError

        except Exception:
            pass
        else:
            if recv_msg:
                # check head
                decode_recv = recv_msg.decode('utf-8')  # PY3 bytes -> str  PY2 str -> unicode
                sp_recv = decode_recv.split(seg)

                # [u'WSRD', u"{'method_return': 1, 'method_finished': True, 'error_msg': None, 'api_status': True}"]
                r_head = sp_recv[0]
                r_return = sp_recv[-1]
                if r_head != head:
                    logger.debug("IN_API_CLIENT [api_receive] Invalid Received Head: {}, Expected: {}".format(sp_recv[0], head))
                    break
                # XXX #001
                rec = eval(r_return)  # 03
                assert isinstance(rec, dict)

                break
            else:
                logger.debug("IN_API_CLIENT [api_receive] socket close, None recv_msg")
        if ignore_overtime:
            if now_time - start_time >= ignore_time:
                logger.warning("IN_API_CLIENT [api_receive] ignore over time for get return")
                break
        else:
            if now_time - start_time >= config_overtime_normal:
                logger.warning("IN_API_CLIENT [api_receive] normal over time for get return")
                break

    # ### close
    client_socket.close()

    logger.debug("IN_API_CLIENT [api_receive] closing client socket, "
                 "segment return: False")

    return rec


def _api_call(session, through_queue, prepared):
    result = session.send(prepared)
    through_queue.put(result)


@IN_COMMON.exception_capture
def api_call(api_name, parameter_list=None, parameter_dict=None, *args, **kwargs):
    """
    Extract parameter:
        args:    1. | bool               |  2. |
        kwargs:     | ignore_overtime    |     |
    """
    # kwargs deal
    if 'timeout' in kwargs and kwargs['timeout']:
        timeout = kwargs['timeout']
    else:
        timeout = IN_COMMON.CLIENT_API_CALL_OVERTIME

    if 'error_none' in kwargs and kwargs['error_none']:
        error_none = kwargs['error_none']
    else:
        error_none = False

    if "customize_timeout" in kwargs:
        customize_timeout = kwargs['customize_timeout']
    else:
        customize_timeout = False

    # check argument
    if not parameter_list:
        parameter_list = []
    elif not isinstance(parameter_list, list):
        raise AttributeError("The type of parameter_list argument must be a list ")

    if not parameter_dict:
        parameter_dict = {}
    elif not isinstance(parameter_dict, dict):
        raise AttributeError("The type of parameter_dict argument must be a dict ")

    if IN_COMMON.API_USING_MODE == APIMode.SOCKET_SERVER:
        # new socket

        client_socket = new_socket()
        if client_socket:
            socket_host_ip_tuple = client_socket.getsockname()
        else:
            raise SocketError("create new socket error, possible connect to server failed")

        kwargs['client_host_info'] = socket_host_ip_tuple

        uid = "None"

        # org send data
        call_seg = None
        if IN_COMMON.PYTHON_VERSION_2:
            call_seg = IN_COMMON.API_COMMUNICATION_HEAD + IN_COMMON.HEAD_SEG_SIGN + \
                       api_name + IN_COMMON.HEAD_SEG_SIGN + uid + IN_COMMON.HEAD_SEG_SIGN + IN_COMMON.HEAD_SEP_SIGN + \
                       str(parameter_list) + IN_COMMON.HEAD_SEP_SIGN + str(parameter_dict) + \
                       IN_COMMON.HEAD_SEP_SIGN + str(socket_host_ip_tuple) + IN_COMMON.HEAD_SEP_SIGN

        elif IN_COMMON.PYTHON_VERSION_3:
            call_seg = IN_COMMON.API_COMMUNICATION_HEAD.encode('utf-8') + IN_COMMON.HEAD_SEG_SIGN.encode('utf-8') + \
                       api_name.encode('utf-8') + IN_COMMON.HEAD_SEG_SIGN.encode('utf-8') + uid.encode('utf-8') + \
                       IN_COMMON.HEAD_SEG_SIGN.encode('utf-8') + IN_COMMON.HEAD_SEP_SIGN.encode('utf-8') + \
                       str(parameter_list).encode('utf-8') + IN_COMMON.HEAD_SEP_SIGN.encode() + \
                       str(parameter_dict).encode('utf-8') + IN_COMMON.HEAD_SEP_SIGN.encode() + \
                       str(socket_host_ip_tuple) + IN_COMMON.HEAD_SEP_SIGN.encode()

        # send
        client_socket.sendall(IN_COMMON.combine_package_client(call_seg))
        logger.info("IN_API_CLIENT [api_call] client socket sendall data after, length: {}".format(len(call_seg)))

        return api_receive(client_socket, *args, **kwargs)

    elif IN_COMMON.API_USING_MODE == APIMode.FLASK_SERVER:

        logger.debug("IN_API_CLIENT [api_call] api_name: {}, api_args: {}, api_kwargs: {}, "
                     "args: {}, kwargs: {}, timeout: {}".format(api_name, parameter_list, parameter_dict, args, kwargs,
                                                                timeout))

        url = "http://" + IN_COMMON.API_SERVER_IP_ADDRESS + ":" + str(IN_COMMON.API_SERVER_PORT) + "/" + api_name

        # handle prams
        new_parameter_list = []
        new_parameter_dict = {}
        if IN_COMMON.PYTHON_VERSION_2:
            new_parameter_list = IN_COMMON.params_unicode2str(parameter_list)
            new_parameter_dict = IN_COMMON.params_unicode2str(parameter_dict)
        else:
            new_parameter_list = parameter_list
            new_parameter_dict = parameter_dict

        logger.debug("IN_API_CLIENT [api_call] processed parameters: %s, %s" % (new_parameter_list, new_parameter_dict))

        req = requests.Request(method='POST', url=url, json=json.dumps(
            {'args': new_parameter_list, 'kwargs': new_parameter_dict}
        ))

        prepared = req.prepare()

        session = requests.Session()

        result = None
        if IN_COMMON.CLIENT_API_CALL_USE_OVERTIME:
            if customize_timeout:
                logger.debug("IN_API_CLIENT [api_call] using customize timeout")
                through_queue = Queue()
                t = threading.Thread(target=_api_call, args=(session, through_queue, prepared))
                t.start()
                start_time = time.time()
                overtime = False
                while True:
                    try:
                        result = through_queue.get(block=False)
                    except Exception as _:
                        pass
                    if result:
                        break
                    if time.time() - start_time > timeout:
                        overtime = True
                        break
                    time.sleep(0.3)

                if overtime:
                    logger.error("IN_API_CLIENT [api_call] Request timed out {}".format(timeout))
                    return IN_COMMON.seg_return(False, "Overtime", None, True)
            else:
                result = session.send(prepared, timeout=timeout)
        else:
            result = session.send(prepared)

        logger.debug("IN_API_CLIENT [api_call] http info ok: {}, api_name: {}, body: {}, status code: {}, "
                     "content length: {}".format(result.ok, api_name, prepared.body, result.status_code, len(result.content)))

        api_data = None

        if IN_COMMON.USING_FLASK_JSONIFY:
            api_data = result.json()
        else:
            content = result.content  # python3 bytes python2 str

            if IN_COMMON.PYTHON_VERSION_3 and not IN_COMMON.SERVICE_PYTHON_VERSION_3:
                _tmp_file = tempfile.TemporaryFile()
                try:
                    tmpfd, tempfilename = tempfile.mkstemp()
                    logger.debug("IN_API_CLIENT [api_call] writing pickle context to: %s" % (_tmp_file.name, ))
                    _tmp_file.write(content)
                    _tmp_file.seek(0)

                    os.close(tmpfd)
                    api_data = pickle.load(_tmp_file, encoding="latin1")

                    os.unlink(tempfilename)  # remove tmp file
                except Exception as exce:
                    logger.error("IN_API_CLIENT [api_call] processing pickle error: %s" % (format_exc(), ))
                    _tmp_file.close()
            else:
                api_data = pickle.loads(content)

        if not api_data['api_status']:
            # logger.error("IN_API_CLIENT [api_call] Failed at {} with follow error message: \n{}".format(
            #     api_name, api_data['error_msg']
            # ))
            if error_none:
                return IN_COMMON.seg_return(False, "APICallError", None, True)
            else:
                return api_data
        else:
            return api_data

    elif IN_COMMON.API_USING_MODE == APIMode.IMPORT_DIRECT:
        logger.warning("IN_API_CLIENT [api_call] The current mode is direct import, using `import IN_PYTHON_API`")
        return IN_COMMON.seg_return(False, "APIModeDirectlyImport", None, True)

    else:
        raise AttributeError("IN_API_CLIENT [api_call] It's not a valid mode for API_USING_MODE")


@IN_COMMON.exception_capture
def _prepare_server(force=False):
    """
    Check and Prepare the file status of Server Script That needs to run
    """
    # TODO make script automatically
    script_root_dir = IN_COMMON.SCRIPT_DIR
    pre_status = True
    for k_script_name, v_script_data in API_TEMPLATES.SCRIPT_TEMPLATE_DICT.items():
        script_file_path_in = script_root_dir + os.sep + k_script_name
        script_file_path = script_file_path_in[:-3]

        replace_vbs = False
        if not os.path.exists(script_file_path):
            replace_vbs = True
        elif force:
            replace_vbs = True

        # replace
        if replace_vbs:
            IN_COMMON.replace_data_for_file(script_file_path_in, script_file_path,
                                            v_script_data[0], v_script_data[1])

        # post check
        if not os.path.exists(script_file_path):
            pre_status = False

    return pre_status


@IN_COMMON.exception_capture
def check_server(port=IN_COMMON.API_SERVER_PORT):
    """
    Check The Server Status
    """
    return find_python_program_with_special_port(port)

def start_server(only=True):
    """
    Start API server
    Returns:
        return True if run script successful or already exists
        otherwise return False
    """
    try:
        _prepare_server(force=True)

        if only:
            py_pid_list = check_server()
            len_pid = len(py_pid_list)
            if len_pid:
                logger.warning("IN_API_CLIENT [start_server] "
                               "The API server already running, length: %s, pids: %s" % (
                                len_pid, py_pid_list))
                return True

        server_script_path = os.path.join(IN_COMMON.SRC_DIR, "script", "run_api_server.bat")
        print("server_script_path11111: ", server_script_path)

        print('USING_PYTHON_SUBPROCESS_DW_FLAGS: ', IN_COMMON.USING_PYTHON_SUBPROCESS_DW_FLAGS)
        if IN_COMMON.USING_PYTHON_SUBPROCESS_DW_FLAGS:
            p = subprocess.Popen(server_script_path, creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)

            # ----- Modified By Bon -----
            # p = subprocess.Popen(server_script_path, shell=True,
            #     stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            #     creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)
            print(p)
            # p = subprocess.Popen(server_script_path, shell=True, creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)
        else:
            p = subprocess.Popen(server_script_path)

    except Exception as e:
        traceback.print_exc()
        raise e
    return
    return p.pid

# @IN_COMMON.exception_capture
# def start_server(only=True):
#     """
#     Start API server
#     Returns:
#         return True if run script successful or already exists
#         otherwise return False
#     """
#
#     _prepare_server(force=True)
#
#     if only:
#         py_pid_list = check_server()
#         len_pid = len(py_pid_list)
#         if len_pid:
#             logger.warning("IN_API_CLIENT [start_server] "
#                            "The API server already running, length: %s, pids: %s" % (
#                             len_pid, py_pid_list))
#             return True
#
#     server_script_path = os.path.join(IN_COMMON.SRC_DIR, "script", "run_api_server.bat")
#
#     if not os.path.exists(server_script_path):
#         logger.error("IN_API_CLIENT [start_server] The script path doesn't exists, "
#                      "possible needs run prepare_server() method to config script, %s" % (server_script_path, ))
#         return False
#
#     if IN_COMMON.USING_PYTHON_SUBPROCESS:
#         logger.debug("IN_API_CLIENT [start_server] start a new server with python subprocess")
#
#         si = subprocess.STARTUPINFO()
#         si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.SW_HIDE | subprocess.STARTF_USESHOWWINDOW
#
#         # Add by Bon
#         # si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.SW_HIDE | subprocess.STARTF_USESHOWWINDOW | subprocess.STARTF_USESTDHANDLES
#
#         p = None
#         if IN_COMMON.USING_PYTHON_SUBPROCESS_DW_FLAGS:
#             # ----- Modified By Bon -----
#             p = subprocess.Popen(server_script_path, shell=True, creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)
#
#             # ----- Original -----
#             # p = subprocess.Popen(server_script_path, startupinfo=si)
#         else:
#             p = subprocess.Popen(server_script_path)
#
#         start_time = time.time()
#         stop_time = IN_COMMON.SERVER_START_OVERTIME
#         while True:
#
#             f_pid = check_server()
#             if f_pid and len(f_pid):
#                 logger.info("IN_API_CLIENT [start_server] Start the service successfully follow %s" % (f_pid, ))
#                 return True
#
#             now_time = time.time()
#             if now_time - start_time > stop_time:
#                 stop_result = stop_server()
#                 logger.error("IN_API_CLIENT [start_server] start server failed with overtime, "
#                              "stop server: %s\nPlease consider follow conditions: "
#                              "\n\t1.Try to manually start the service in the script directory to see if it succeeds"
#                              "\n\t2.Try to use py or pyd respectively" % (stop_result, ))
#                 return False
#
#             time.sleep(0.35)
#
#     else:
#         logger.debug("IN_API_CLIENT [start_server] start a new server with python multiprocessing")
#         p = multiprocessing.Process(target=IN_COMMON.execute_common, args=(server_script_path, ))
#         p.daemon = True
#         p.start()
#         py_pid_list = check_server()
#         if len(py_pid_list) != 0:
#             return True
#         else:
#             return False


@IN_COMMON.exception_capture
def stop_server(pid_list=None, using_psutil=True):
    """
    Stop API server
    """
    if pid_list is not None:
        py_pid_list = pid_list
    else:
        py_pid_list = check_server()

    if using_psutil:
        if py_pid_list:
            call_script('psutil_kill_program.py', py_pid_list)
            logger.debug("IN_API_CLIENT [stop_server] killing server that in pid %s with using psutil" % (
                    py_pid_list))
        else:
            logger.warning("IN_API_CLIENT [stop_server] No serve that running")
            return True
    else:
        if py_pid_list:
            for pid in py_pid_list:
                # os.kill(pid, signal.SIGTERM)
                params = '/f /pid {pid}'.format(pid=pid)
                os.system("taskkill {}".format(params))

            logger.debug("IN_API_CLIENT [stop_server] killing server that in pid %s with using os.kill" % (
                    py_pid_list))
        else:
            logger.warning("IN_API_CLIENT [stop_server] no running service")
            return True

    # post check
    final_pid = check_server()
    if not final_pid:
        logger.info("IN_API_CLIENT [stop_server] Stop the service successfully follow %s" % (py_pid_list))
        return True
    else:
        logger.error("IN_API_CLIENT [stop_server] Stop Server Failed, pid: %s" % (final_pid))
        return False


@IN_COMMON.exception_capture
def restart_server(only=True):
    """
    Restart API server
    """
    if stop_server():
        if start_server(only=only):
            return True
        else:
            logger.error("IN_API_CLIENT [restart_server] failed start server")
            return False
    else:
        logger.error("IN_API_CLIENT [restart_server] failed stop server")
        return False


@IN_COMMON.exception_capture
def close_server():
    """
    Close Server with socket
    """
    py_pid_list = check_server()
    length_of_server = len(py_pid_list)
    if not length_of_server:
        logger.debug("IN_API_CLIENT [close_server] no server is running")
        return True

    if IN_COMMON.API_USING_MODE == APIMode.SOCKET_SERVER:
        for i in range(length_of_server + IN_COMMON.SERVER_CLOSE_MORE_STEP):
            try:
                client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                client_socket.connect((IN_COMMON.API_SERVER_IP_ADDRESS, IN_COMMON.API_SERVER_PORT))
                client_socket.send(IN_COMMON.combine_package_client("exit"))
            except Exception as exc:
                logger.warning("IN_API_CLIENT [close_server] found mistake: %s" % (exc))
    else:
        raise AttributeError("that only supported for SOCKET_SERVER API mode")

    py_pid_list = check_server()
    if not py_pid_list:
        return True
    else:
        return False


@IN_COMMON.exception_capture
def call_script(script_name, script_argv):
    """
    subprocess call
    Args:
        script_name: str
        script_argv: list
    """
    # splitting script to get suffix
    suffix = script_name.split('.')[-1]

    # assemble call list
    common_script_path = os.path.join(IN_COMMON.SRC_DIR, "script", script_name)
    script_list = [common_script_path, ]
    call_list = script_list + script_argv

    # run with python interpreter if suffix equal 'py'
    # XXX try call python script without black-window
    if suffix == 'py':
        f_python_interpreter = os.path.join(os.path.dirname(IN_COMMON.WS_EXTRA_PYTHON_INTERPRETER), 'pythonw.exe')
        call_list.insert(0, f_python_interpreter)

    logger.debug("IN_API_CLIENT [call_script] call with suffix: %s, script name: %s" % (suffix, script_name))

    if IN_COMMON.USING_PYTHON_SUBPROCESS:
        si = subprocess.STARTUPINFO()
        si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.SW_HIDE | subprocess.STARTF_USESHOWWINDOW
        p = subprocess.Popen(call_list, shell=True, stdout=subprocess.PIPE, startupinfo=si)
        out, err = p.communicate()

        return out, err
    else:
        logger.debug("IN_API_CLIENT call_script with multiprocessing")
        q = Queue()
        p = multiprocessing.Process(target=IN_COMMON.execute_common_args, args=(call_list, q, ))
        p.daemon = True
        p.start()
        return q.get(timeout=IN_COMMON.OVERTIME)


def find_port_by_pid(pid):
    """
    description: find port from pid
    parameter : pid
    return: Array(port)
    """
    if IN_COMMON.WIN_PLATFORM:
        # ret = os.popen("netstat -ano|findstr " + str(pid))

        # ------------------------------------
        si = subprocess.STARTUPINFO()
        si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.SW_HIDE | subprocess.STARTF_USESHOWWINDOW | subprocess.STARTF_USESTDHANDLES

        # Fix: Use subprocess instead of above, because get no result in Maya
        cmd = 'netstat -ano'
        args = shlex.split(cmd)
        ret = subprocess.Popen(args, stdout=subprocess.PIPE, startupinfo=si)

        intermediate_stdout = ret.stdout
        # intermediate_result = intermediate_stdout.read().decode('gbk')

        cmd = 'findstr %s' % str(pid)
        args = shlex.split(cmd)
        ret = subprocess.Popen(args, stdin=intermediate_stdout, stdout=subprocess.PIPE, startupinfo=si)
        # ------------------------------------

        str_list = ret.stdout.read().decode('gbk')
        ret_list = re.split('\n', str_list)

        # if str_list:
        #     logger.debug("IN_API_CLIENT [find_port_by_pid] the program (%s) listen in"
        #                  "\n\t - FOUN: --> %s\n\t - SPLI: --> %s" % (pid, repr(str_list), ret_list))

        true_arr = []
        if len(ret_list) != 0:
            for each_sg in ret_list:
                # print each_sg
                if re.findall("LISTENING", each_sg):
                    true_id = re.findall("\d+\s+\W", each_sg)
                    if true_id[0]:
                        lastid = re.findall("\d+", true_id[0])[0]
                        if lastid not in true_arr:
                            true_arr.append(lastid)

        return true_arr

    else:
        # TODO other platform supported
        raise AttributeError


def find_python_program_with_special_port(port):
    """
    description: find num of python.exe , pid, port
    parameter : port
    return: Array(pid_list, port_list)
    """
    if IN_COMMON.WIN_PLATFORM:
        f_pid = []
        info_collect = []
        info_str_collect = "\n"

        # ret = os.popen('tasklist /fi "imagename eq python.exe"').read().decode('gbk')

        # ------------------------------------
        # Fix: Use subprocess instead of above, because get no result in Maya
        si = subprocess.STARTUPINFO()
        si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.SW_HIDE | subprocess.STARTF_USESHOWWINDOW | subprocess.STARTF_USESTDHANDLES

        cmd = 'tasklist /fi "imagename eq python.exe"'
        args = shlex.split(cmd)
        ret = subprocess.Popen(args, stdout=subprocess.PIPE, startupinfo=si)
        ret_str = ret.stdout.read().decode('gbk')
        # ------------------------------------

        # logger.debug("IN_API_CLIENT [find_python_program_with_special_port] result: %s" % (ret_str))

        if re.findall("python.exe\s+\d+", ret_str):
            py_list = re.findall("python.exe\s+\d+", ret_str)

            # logger.debug("IN_API_CLIENT [find_python_program_with_special_port] "
            #              "found python number after regex: %s" % (len(py_list)))

            if len(py_list) >= 1:
                for each in py_list:
                    each_pid = re.findall("\d+", each)
                    duan = find_port_by_pid(each_pid[0])

                    info_collect.append([each, each_pid, duan])
                    # print u"Port List: ", duan
                    if str(port) in duan:
                        f_pid.append(each_pid[0])

        for info in info_collect:
            info_str_collect += "\t"+str(info)+"\n"

        # logger.debug("IN_API_CLIENT [find_python_program_with_special_port]"
        #              "%s" % (info_str_collect))

        f_pid_list = [(str(pid)) for pid in f_pid]

        # logger.debug("IN_API_CLIENT [find_python_program_with_special_port] "
        #              "find server pids: %s for port: %s" % (f_pid_list, port))

        return f_pid_list

    else:
        # TODO other platform supported
        raise AttributeError


def kill_pid(pid):
    if IN_COMMON.WIN_PLATFORM:
        os.popen('taskkill /pid ' + str(pid) + ' /t /f')

    else:
        # TODO other platform supported
        raise AttributeError


def long_test():

    import sys
    from PySide2 import QtWidgets, QtGui
    from functools import partial

    root_tmp = os.path.join(IN_COMMON.ROOT_DIR, 'temp')

    class CustomAPIClientWidget(QtWidgets.QWidget):
        def __init__(self, close_server_when_exit):
            QtWidgets.QWidget.__init__(self)
            self.auto_close_server = close_server_when_exit

        def closeEvent(self, event):
            if self.auto_close_server:
                stop_server()
            event.accept()

    def menu_sel(_ue, _pe, _le, _te, action):
        t = action.text()
        call_result = None
        if t == 'start_server':
            call_result = start_server(only=True)
        elif t == 'restart_server':
            call_result = restart_server()
        elif t == 'stop_server':
            call_result = stop_server()
        elif t == 'check_server':
            call_result = check_server()
        elif t == 'close_server':
            call_result = close_server()
        elif t == 'test_call':
            client_socket = new_socket()
            if IN_COMMON.PYTHON_VERSION_3:
                call_result = client_socket.sendall(_le.text().encode('utf-8'))
            else:
                call_result = client_socket.sendall(_le.text())
        elif t == 'test_call (combine)':
            client_socket = new_socket()
            call_result = client_socket.sendall(IN_COMMON.combine_package_client(_le.text()))
        # ======================================================
        elif t == 'login_server':
            call_result = api_call("login_server", [_ue.text(), _pe.text(), "DCC"], timeout=7)
        elif t == 'logout_server':
            call_result = api_call("logout_server")
        elif t == 'download_file':
            call_result = api_call("download_file", [3544, root_tmp])
        elif t == "download_files":
            call_result = api_call("download_files", [root_tmp, [[-1, 3678, 1], [-1, 3693, 1], [-1, 3730, 1]]])
        elif t == 'all of data_flow func':
            call_result = api_call('data_flow_task_list')
        elif t == 'get_tasks':
            call_result = api_call("get_tasks", [], {'filter_list': ['objectName']})
        elif t == 'get_task_files':
            call_result = api_call('get_task_files', (_le.text()))
        elif t == 'get_projects':
            call_result = api_call('get_projects')
        elif t == 'get_assets':
            call_result = api_call("get_assets", eval(_le.text()))
        elif t == 'get_shots':
            call_result = api_call("get_shots", eval(_le.text()))
        elif t == 'call_api_dict':
            call_result = api_call('call_api_dict', eval(_le.text()))
        elif t == 'auto_gen':
            call_result = api_call('auto_gen', eval(_le.text()))
        elif t == 'test_serialized_data':
            call_result = api_call('test_serialized_data', [1, 2])
            print("---> [test_serialized_data] result: {}, type: {}".format(call_result, type(call_result)))
            obj = call_result['method_return']
            print("---> [test_serialized_data] obj: {}, type: {}".format(repr(obj), type(obj)))
            l_obj = None
            if IN_COMMON.PYTHON_VERSION_2:
                l_obj = pickle.loads(obj)
                print("---> [test_serialized_data] reverse: {}".format(
                    l_obj))  # pickle.dumps(obj, protocol=2)     using 2
            elif IN_COMMON.PYTHON_VERSION_3:
                # the server possible py2 or py3
                try:
                    l_obj = pickle.loads(obj)
                    # pickle.loads(bytes(obj, 'utf-8'))
                except Exception:
                    l_obj = pickle.loads(bytes(obj, 'utf-8'), encoding='utf-8')
                # _pickle.UnpicklingError: invalid load key, '\xc2'.
                # l_obj = pickle.loads(obj)
                print("---> [test_serialized_data] reverse: {}".format(l_obj))
            print("---> [test_serialized_data] func-call: {}".format(l_obj.print_hello("Orem")))
        # ======================================================
        elif t == 'test_unspecified_api':
            call_result = api_call('test_unspecified_api')
        else:
            pass
        _te.setText(str(call_result))
        print("\t--> call result: {}".format(call_result))

    def menu_deal(sel_menu):
        sel_menu.move(QtGui.QCursor.pos())
        sel_menu.exec_()

    app = QtWidgets.QApplication(sys.argv)
    w = CustomAPIClientWidget(True)
    w.setWindowTitle("python {}".format(sys.version_info[0]))
    lay = QtWidgets.QGridLayout(w)
    w.setMinimumSize(620, 520)
    b = QtWidgets.QPushButton()
    b.setText("Click Me!")
    ue = QtWidgets.QLineEdit()
    ue.setText("")
    ul = QtWidgets.QLabel("Username")
    pe = QtWidgets.QLineEdit()
    pe.setText("")
    le = QtWidgets.QLineEdit()
    le.setText('WSRD')
    pe.setEchoMode(QtWidgets.QLineEdit.Password)
    pl = QtWidgets.QLabel("Password")
    te = QtWidgets.QTextEdit()
    tet = QtWidgets.QTextEdit()
    tet.setMaximumHeight(100)
    tem = """["UpdateTaskStatus", [3230, 12]]
["GetTaskListPersonal", "INSIDE"]
["GetTaskNextAvailableStatus", [["INS", "QListqint"], ["SAP", "int", "3230"], ["FIL", 0]],]
"""
    tet.setText(tem)

    lay.addWidget(b, 0, 0)
    lay.addWidget(ul, 1, 0)
    lay.addWidget(ue, 1, 1)
    lay.addWidget(pl, 2, 0)
    lay.addWidget(pe, 2, 1)
    lay.addWidget(le, 3, 1)
    lay.addWidget(tet, 4, 1)
    lay.addWidget(te, 5, 1)

    m = QtWidgets.QMenu(b)
    m.addAction("start_server")
    m.addAction("restart_server")
    m.addAction("stop_server")
    m.addAction("check_server")
    m.addSeparator()
    m.addSeparator()
    m.addAction('auto_gen')
    m.addAction('call_api_dict')
    m.addAction("test_serialized_data")
    m.addAction("test_unspecified_api")
    m.addSeparator()
    m.addAction("login_server")
    m.addAction("logout_server")
    m.addAction("download_file")
    m.addAction("download_files")
    m.addAction('all of data_flow func')
    m.addAction("get_tasks")
    m.addAction("get_task_files")
    m.addAction("get_projects")
    m.addAction("get_assets")
    m.addAction('get_shots')
    m.addSeparator()
    m.addSeparator()
    m.addAction('close_server')
    m.addSeparator()
    m.addSeparator()
    m.addAction('test_call')
    m.addAction('test_call (combine)')
    m.addAction('get_task_reference_files')

    m.triggered.connect(partial(menu_sel, ue, pe, le, te))
    w.show()
    
    # b.clicked.connect(lambda l: menu_deal(m))
    b.clicked.connect(functools.partial(menu_deal, m))

    app.exec_()




if __name__ == '__main__':

    long_test()
    pass




