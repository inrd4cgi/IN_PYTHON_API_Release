# -*- coding: utf-8 -*-

import os
import sys
import inspect


# ROOT_DIR                = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOT_DIR                = os.path.dirname(os.path.dirname(os.path.abspath(inspect.getframeinfo(inspect.currentframe()).filename)))
SRC_DIR                 = os.path.join(ROOT_DIR, "src_py3")
CONFIG_FILE_LOCATION    = ""

