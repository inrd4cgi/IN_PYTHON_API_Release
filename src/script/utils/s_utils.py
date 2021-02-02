import os
import sys
import site
import platform
import sysconfig
import setuptools


def get_site_packages_home():
    """
    Get site-packages dir
    """
    site_packages_path = sysconfig.get_paths()["purelib"]
    site_packages_path = site.getsitepackages()
    site_packages_path = setuptools.__path__[0]

    py3 = True if sys.version_info[0] == 3 else False
    py2 = True if sys.version_info[0] == 2 else False
    win_ = True if platform.system() == "Windows" else False
    linux_ = True if platform.system() == "Linux" else False
    os_ = True if platform.system() == "Darwin" else False
    python_home = os.path.dirname(os.path.abspath(sys.executable))
    site_packages_path = None
    if win_:
        site_packages_path = os.path.join(python_home, 'Lib', "site-packages")
    elif linux_:
        site_packages_path = os.path.join(python_home, '..', "lib", "python2.7", "site-packages")
    elif os_:
        # TODO set site-packages on other platform
        site_packages_path = ""
    else:
        raise AttributeError("Unknown platform")

    return site_packages_path
