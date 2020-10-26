#!C:\cygwin\home\Aaron\DEV_PROJECT\LIBRARY\Digital_Asset_Library\IN_PYTHON_API\env\win64\python2.7\python.exe
# EASY-INSTALL-ENTRY-SCRIPT: 'Cython==0.29.21','console_scripts','cythonize'
__requires__ = 'Cython==0.29.21'
import re
import sys
from pkg_resources import load_entry_point

if __name__ == '__main__':
    sys.argv[0] = re.sub(r'(-script\.pyw?|\.exe)?$', '', sys.argv[0])
    sys.exit(
        load_entry_point('Cython==0.29.21', 'console_scripts', 'cythonize')()
    )
