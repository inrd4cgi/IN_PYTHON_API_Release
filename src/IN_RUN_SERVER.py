#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-10-28 08:59:32
# @Author  : Your Name (you@example.org)
# @Link    : http://example.org
# @Version : $Id$


import os
import sys


# e.g. D:/DEV/Github/IN_PYTHON_API_Release/src/IN_RUN.py
current_path = __file__
print(current_path)
# current_path = 'D:/DEV/Github/IN_PYTHON_API_Release/src_py3/IN_API_SERVER_B.pyd'

sys.path.append(os.path.dirname(current_path))


import IN_API_SERVER
print(IN_API_SERVER)
server = IN_API_SERVER.run_server()



