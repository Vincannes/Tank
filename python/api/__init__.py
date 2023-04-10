import os
import sys
import yaml
from pprint import pprint

TANK_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
CONFIG_PATH = os.path.join(TANK_DIR, "config", "template.yml")
sys.path.append(MODULE_PATH)

import tank_module

keys = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str'}, 'version' : {'type': 'int', 'default': '1'}, 'test' : {'type': 'str', 'default': 'aa'}}"
paths = "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}'," \
       "'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', " \
       "'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"


def read_templates():
    templates = {}
    with open(CONFIG_PATH, "r") as config:
        templates = yaml.safe_load(config)

    return templates

paths = read_templates().get("paths")
keys = read_templates().get("keys")

sgtk = tank_module.Tank(str(paths), str(keys))

tk = sgtk.get_templates()
nuke_template = tk["nuke"]

fields = {
    "dir": "test",
    "Shot": "sh_010",
    "version": "1",
    "Task": "cmp",
}
path = nuke_template.apply_fields(fields)

print(sgtk.template_from_path(path).name())
# print(nuke_template)
# print(path)
# print(nuke_template.get_fields(path))



# for i, tempalte in templates.items():
#     print()
#     print(tempalte.name())
#     print(tempalte.definition())
#     print(tempalte.static_token())
#     print(tempalte.ordered_keys())
#     print(tempalte.apply_fields(fields))


