#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import unicode_literals

import sys
print(sys.version)

import os

# os.environ['PATH'] = "D:/DEV/Github/IN_PYTHON_API_Release/env/win64/python3.7;D:/DEV/Github/IN_PYTHON_API_Release/env/win64/python3.7/Lib/site-packages/PySide2;D:/DEV/Github/IN_PYTHON_API_Release/env/win64/python3.7/../../../lib/python3_win64;"
# os.environ['PYTHONPATH'] = "D:/DEV/Github/IN_PYTHON_API_Release/env/win64/python3.7/Lib/site-packages;D:/DEV/Github/IN_PYTHON_API_Release/src_py3;D:/DEV/Github/IN_PYTHON_API_Release/env/win64/python3.7/Lib;"
# for k, v in os.environ.items():
#     print(k, v)


import sys
import ast
import time
import json
import pickle
import threading
import logging
import traceback
import inspect
from pprint import pprint, pformat
from http import HTTPStatus


# ----- PySide2 -----
from PySide2 import QtCore
from PySide2.QtWidgets import QApplication


# ----- Flask -----
from flask import Flask, request, jsonify, Response
from flask_cors import CORS


# ----- IN_PYTHON_API -----
import IN_COMMON
import IN_PYTHON_API
from IN_PYTHON_API import INS, INI
from IN_COMMON import logger, APIMode, ReceiveDataError
import IN_PYTHON_API_FUNC



# ---------- Instantiation ----------
qt_app = QApplication.instance() if QApplication.instance() else QApplication(sys.argv)
flask_app = Flask(__name__)
CORS(flask_app)



# ---------- Set Flask Logger to ERROR ----------
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)


# def receive():
#     # request.path:   u'/connectToServer'
#     # func:           IN_PYTHON_API_FUNC.connectToServer({u'ip': u'192.168.17.212', 'port': 1111})
#
#     if request.json:
#         func = 'IN_PYTHON_API_FUNC.%s(**%s)' % (request.path[1: ], json.loads(request.json))
#     else:
#         func = 'IN_PYTHON_API_FUNC.%s(**%s)' % (request.path[1: ], {})
#
#     return pickle.dumps(eval(func), protocol=2)
#
#     # Test
#     # return pickle.dumps(eval(func(**json.loads(request.get_json(force=True)))), protocol=2)
#     # return jsonify(1)


def receive():
    # request.path:   u'/connectToServer'
    # func:           IN_PYTHON_API_FUNC.connectToServer({u'ip': u'192.168.17.212', 'port': 1111})

    # print('request.path: %s' % request.path)
    # print('request.json: %s' % request.json)
    # print(type(request.json))
    # print(request.json)
    # a = request
    try:
        if isinstance(request.json, str):
            json_data = json.loads(request.json) if request.json else {}
            api_language = json_data.get('api_language', 'python')
            func = 'IN_PYTHON_API_FUNC.%s(**%s)' % (request.path[1: ], json_data)

        elif isinstance(request.json, dict):
            api_language = request.json.get('api_language', 'python')
            func = 'IN_PYTHON_API_FUNC.%s(**%s)' % (request.path[1: ], request.json)
        else:
            raise ValueError('Cannot parser json data')

    except Exception as e:
        raise Exception(f"Incorrect Params\n    {traceback.format_exc()}")

    if api_language == 'python':
        return pickle.dumps(eval(func), protocol=2)
    else:
        r = eval(func)
        # return jsonify({"hello_world": True})
        return jsonify(r)


    # Test
    # return pickle.dumps(eval(func(**json.loads(request.get_json(force=True)))), protocol=2)
    # return jsonify(1)


def addURL_IN_PYTHON_API_FUNC(app):

    # inspected_module = sys.modules[IN_PYTHON_API_FUNC]

    members = IN_PYTHON_API_FUNC._getSelfMembers()

    for k, func in members:

        if (type(func).__name__ != 'cython_function_or_method')\
                and (not inspect.isfunction(func)):
            continue

        # if not inspect.isfunction(func): continue

        # e.g. '/GetProjects'
        rule = '/' + func.__name__

        # e.g. 'IN_PYTHON_API_FUNC.GetProjects'
        endpoint = '.'.join([func.__module__, func.__name__])

        # e.g. IN_PYTHON_API_FUNC.GetProjects
        view_func = func

        # rule:
        #     'http://127.0.0.1:5000/connectToServer'
        #     'http://127.0.0.1:5000/login'
        #     'http://127.0.0.1:5000/getProjects'
        app.add_url_rule(rule, None, receive, methods=['POST'])

def flask_run(flask_app):
    flask_app.run(host=IN_COMMON.API_SERVER_IP_ADDRESS, port=IN_COMMON.API_SERVER_PORT)

def run_server():

    IN_COMMON.API_USING_MODE = APIMode.FLASK_SERVER
    IN_COMMON.check_config()

    # >>> --------------------- Long
    wrapperd_funcs = []
    for func_wrap in IN_PYTHON_API.wrapper_func_names:
        rule        = func_wrap[0]
        endpoint    = func_wrap[1]
        func        = func_wrap[2]
        wrapperd_funcs.append(func.__name__)

        flask_app.add_url_rule(rule, endpoint, func, methods=['POST'])

    # logger.debug("IN_API_SERVER [__main__] flask route wrapper length: {}".format(len(wrapperd_funcs)))
    # --------------------------<<<

    # >>> --------------------- Bon
    addURL_IN_PYTHON_API_FUNC(flask_app)
    # --------------------------<<<

    flaskThread=threading.Thread(target=flask_run,args=[flask_app,])
    flaskThread.start()
    # flask_app.run(host=IN_COMMON.API_SERVER_IP_ADDRESS, port=IN_COMMON.API_SERVER_PORT)

    notifier = INS.INSPythonNotifier.GetInstance()
    notifier.EventLogOff.connect(IN_PYTHON_API.logoff)
    qt_app.exec_()


@flask_app.errorhandler(Exception)
def SERVER_ERROR(err):
    # TODO: Save error log
    # ----- Save error log into file -----
    # print(traceback.print_exc())
    # logging.error()

    # logging.warning(err)

    # ----- Respond Client -----
    # <class 'flask.wrappers.Response'>
    response = jsonify(str(err))
    response.status_code = HTTPStatus.INTERNAL_SERVER_ERROR
    return response


@flask_app.errorhandler(HTTPStatus.EXPECTATION_FAILED)
def EXPECTATION_FAILED(err):
    # <class 'flask.wrappers.Response'>
    response = jsonify(err.description.get('result', None))
    response.status_code = err.code
    return response


if __name__ == '__main__':
    run_server()
