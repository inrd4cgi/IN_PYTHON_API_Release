import os
import sys
import argparse

sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "s_utils"))
import utils.s_utils as s_utils
sys.path.append(s_utils.get_site_packages_home())

import psutil


def main(match_dict, iter_type='cmdline'):
    """
    Using psutil to check programs
    Returns:
        key_result dict
    """

    key_result = {}

    # fill list
    for key_name, value_key in match_dict.items():
        key_result[key_name] = []

    self_id = os.getpid()

    for p in psutil.process_iter():
        pid = p.pid
        p = psutil.Process(pid)

        # cmdline seem's
        # ['C:\\Windows\\System32\\cmd.exe', '/c', 'C:\\IN_PYTHON_API\\src\\script\\run_api_server.bat']
        # or
        # ['python', 'C:\\IN_PYTHON_API\\src\\IN_API_SERVER.py']
        for key_name, value_key in match_dict.items():
            if key_name == p.name():
                if hasattr(p, iter_type):
                    iter_ = getattr(p, iter_type)()
                else:
                    continue

                for ite in iter_:
                    if value_key in ite and pid != self_id:
                        f = [pid, iter_]
                        key_result[key_name].append(f)

    return key_result


if __name__ == '__main__':
    eg = """
    e.g.
    python psutil_check_program.py --p_names cmd.exe python.exe --p_keys run_api_server IN_API_SERVER --iter cmdline
    """

    parser = argparse.ArgumentParser(prog=sys.argv[0],
                                     description="Using Python psutil module to get the status of processing program"
                                                 " Notices: 1.the length of p_names must match with p_keys"
                                                 " {}".format(eg))

    parser.add_argument('--p_names', dest='names', nargs='*', type=str)
    parser.add_argument('--p_keys', dest='keys', nargs='*', type=str)
    parser.add_argument('--iter', action='store', type=str, dest='iter',
                        help='the attribute of psutil.Process object, e.g. cmdline')
    parse_data = parser.parse_args()

    names = parse_data.names
    keys = parse_data.keys
    p_iter = parse_data.iter
    dict_ = {}
    if not names:
        raise AttributeError("Without names, possible that not a valid argument")
    if len(names) != len(keys):
        raise AttributeError("Please input same numbers of p_names and p_keys")

    # merge two list to a dict
    for i, name_ in enumerate(names):
        dict_[name_] = keys[i]
    print(str(main(dict_, p_iter)))
