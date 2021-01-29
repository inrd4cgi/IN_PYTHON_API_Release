import os
import sys
import time
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "s_utils"))
import utils.s_utils as s_utils
sys.path.append(s_utils.get_site_packages_home())

import psutil


def main(pid_list):
    """
    Using psutil to kill a process
    """
    for pid in pid_list:
        p = psutil.Process(pid)
        p.terminate()
        time.sleep(0.001)


if __name__ == '__main__':
    loa = len(sys.argv)
    if loa > 1:
        # convert argv to list
        pid_list_ = []
        for index in range(1, loa):
            pid_list_.append(int(sys.argv[index]))
        main(pid_list_)
    else:
        print("please input PIDs")
