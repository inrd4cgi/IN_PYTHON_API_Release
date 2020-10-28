#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-10-28 08:59:32
# @Author  : Your Name (you@example.org)
# @Link    : http://example.org
# @Version : $Id$


import os
import subprocess
import shlex
import sys

# e.g. D:/DEV/Github/IN_PYTHON_API_Release/src/IN_RUN.py
print __file__

sys.path.append(os.path.dirname(__file__))


import IN_API_SERVER
print(IN_API_SERVER)
server = IN_API_SERVER.run_server()


raw_input('end')


