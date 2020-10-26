#!C:\cygwin\home\Aaron\DEV_PROJECT\LIBRARY\Digital_Asset_Library\IN_PYTHON_API\env\win64\python3.7\python.exe
# EASY-INSTALL-ENTRY-SCRIPT: 'Cython==3.0a6','console_scripts','cython'
__requires__ = 'Cython==3.0a6'
import re
import sys
from pkg_resources import load_entry_point

if __name__ == '__main__':
    sys.argv[0] = re.sub(r'(-script\.pyw?|\.exe)?$', '', sys.argv[0])
    sys.exit(
        load_entry_point('Cython==3.0a6', 'console_scripts', 'cython')()
    )
