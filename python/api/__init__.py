import os
import sys
import ctypes
import pybind11
from pprint import pprint

MODULE_PATH = 'D:\\Desk\\python\\Tank\\cpp\\build\\Release'
sys.path.append(os.path.join(MODULE_PATH))

import tank_module

keys = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str'}, 'version' : {'type': 'int', 'default': '1'}, 'test' : {'type': 'str', 'default': 'aa'}}"
paths = "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}'," \
       "'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', " \
       "'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"


# pprint(dir(tank_module))
print()
x = tank_module.Tank(paths, keys)
print(x)
print(x.getTemplates())

