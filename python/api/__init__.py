import os
import sys
import yaml

TANK_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
CONFIG_PATH = os.path.join(TANK_DIR, "config", "template.yml")
sys.path.append(MODULE_PATH)

import tank_module

def read_templates():
    templates = {}
    with open(CONFIG_PATH, "r") as config:
        templates = yaml.safe_load(config)

    return templates

paths = read_templates().get("paths")
keys = read_templates().get("keys")

class sgtk(tank_module.Tank):
    
    def __init__(self):
        super().__init__(str(paths), str(keys))


# tk = tank_module.Tank(str(paths), str(keys))


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


