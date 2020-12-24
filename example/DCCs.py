import os
import sys

import threading
import IN_API_CLIENT
import IN_COMMON

file_id     = None
ip          = IN_COMMON.API_SERVER_IP_ADDRESS
port        = IN_COMMON.API_SERVER_PORT
username    = None
password    = None
ctype       = "DCC"
webserver   = "http://{}:{}".format(ip, port)
root_tmp    = os.path.join(IN_COMMON.ROOT_DIR, 'temp')


def start_in_server():
    """
    Using IN_API_CLIENT
    """
    IN_COMMON.logger.info("start_server: {}".format(IN_API_CLIENT.start_server(only=True)))
    IN_COMMON.logger.info("check_server: {}".format(IN_API_CLIENT.check_server()))


def start_in_server_with_new_thread():
    """
    Python threading
    """
    work_thread = threading.Thread(target=start_in_server, args=())
    work_thread.start()


def stop_server():
    IN_COMMON.logger.info(IN_API_CLIENT.restart_server())


def restart_server():
    IN_COMMON.logger.info(IN_API_CLIENT.stop_server())


def call_api_example():
    """
    Using IN_API_CLIENT
    """
    IN_COMMON.logger.info("login_server: {}".format(IN_API_CLIENT.api_call("login_server", [username, password], )))
    # IN_COMMON.logger.info("get_tasks: {}".format(IN_API_CLIENT.api_call("get_tasks")))
    # IN_COMMON.logger.info("get_projects: {}".format(IN_API_CLIENT.api_call("get_projects")))

    # IN_COMMON.logger.info("download_file: {}".format(IN_API_CLIENT.api_call("download_file", [file_id, root_tmp])))


def call_native_api():
    api_client = IN_API_CLIENT.InApiClient.connectAndLogin("Z:/", ip, port, username, password, ctype, webserver)
    IN_COMMON.logger.info("getProjects: {}".format(api_client.getProjects()))


start_in_server_with_new_thread()
call_api_example()
