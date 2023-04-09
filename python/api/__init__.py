import os
import sys
from pprint import pprint

CURR_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(CURR_DIR,"cpp", "lib")
sys.path.append(MODULE_PATH)

import tank_module

keys = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str'}, 'version' : {'type': 'int', 'default': '1'}, 'test' : {'type': 'str', 'default': 'aa'}}"
paths = "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}'," \
       "'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', " \
       "'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"


# pprint(dir(tank_module))
print()
x = tank_module.Tank(paths, keys)

templates = x.get_templates()
nuke_template = templates["nuke"]

fields = {
    "dir": "test",
    "Shot": "sh_010",
    "version": "1",
    "Task": "cmp",
}
path = nuke_template.apply_fields(fields)

print(nuke_template)
print(path)
print(nuke_template.get_fields(path))

# for i, tempalte in templates.items():
#     print()
#     print(tempalte.name())
#     print(tempalte.definition())
#     print(tempalte.static_token())
#     print(tempalte.ordered_keys())
#     print(tempalte.apply_fields(fields))


