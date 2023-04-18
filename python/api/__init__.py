import os
import sys
import yaml
from pprint import pprint

TANK_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
CONFIG_PATH = os.path.join(TANK_DIR, "config", "template.yml")
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

class sgtk(tank_module.Tank):
    
    def __init__(self):
        super().__init__(str(paths), str(keys))


if __name__ == "__main__":
    tk = sgtk()

    templates = tk.get_templates()
    nuke_template = templates["nuke"]

    fields = {
        "dir": "test",
        "Shot": "sh_010",
        "version": "1",
        "Task": "cmp",
    }
    path = nuke_template.apply_fields(fields)
    pathTest = "C\\\\\\\\\\\\test\\\\\\\\\\\\sh_010\\\\\\\\\\\\cmp\\\\\\\\\\\\nuke\\\\\\\\\\\\sh_010-cmp-base-v01.nk"

    template = tk.template_from_path(path)
    print(template)
    # print(template.name())
    # print(template.definition())
    # print(template.static_token())
    pprint(template.get_fields(pathTest))

