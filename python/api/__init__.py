import os
import sys
import yaml
from pprint import pprint

TANK_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
CONFIG_PATH = os.path.join(TANK_DIR, "config", "templates.yml")
sys.path.append(MODULE_PATH)

import tank_module
from tank_module import TankMatchingTemplatesError

def read_templates():
    templates = {}
    with open(CONFIG_PATH, "r") as config:
        templates = yaml.safe_load(config)

    return templates

paths = read_templates().get("paths")
keys = read_templates().get("keys")
strings = read_templates().get("strings")
keys.update(strings)

class sgtk(tank_module.Tank):
    
    def __init__(self):
        super().__init__(str(paths), str(keys))


if __name__ == "__main__":
    # pprint(keys)

    tk = sgtk()

    templates = tk.templates()
    nuke_template = templates["Shot_NukeRender_Work_Sequence"]
    print()
    print(nuke_template)
    print(nuke_template.name())
    print(nuke_template.definition())
    print(nuke_template.static_token())
    print(nuke_template.ordered_keys())
    print()
    fields = {
        "Sequence": "sh",
        "Shot": "sh_010",
        "version": "1",
        "Task": "cmp",
    }
    path = nuke_template.apply_fields(fields)
    print()
    print("path")
    print(path)
    # pathTest = "D:/Desk/python/Tank/tests/project//test//sh_010//cmp//nuke//sh_010-cmp-base-v001.nk"

    # template = tk.template_from_path(path)
    # print()
    # print("definition")
    # print(template.definition())
    # print()
    # print("Order Key")
    # print(template.ordered_keys())
    # print()
    # print("Fields")
    # pprint(template.get_fields(pathTest))

