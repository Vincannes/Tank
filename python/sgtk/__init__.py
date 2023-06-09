import os
import sys
import yaml
from pprint import pprint

TANK_DIR =  os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
CONFIG_PATH = os.path.join(TANK_DIR, "config", "templates.yml")

sys.path.append(MODULE_PATH)

ROOT_PATH = "D:/Desk/python/Projects"

import tank_module
from tank_module import TankMatchingTemplatesError

def read_templates():
    templates = {}
    with open(CONFIG_PATH, "r") as config:
        templates = yaml.safe_load(config)

    return templates

keys = read_templates().get("keys")
paths = read_templates().get("paths")
strings = read_templates().get("strings")
# print(paths)
# print(keys)
# print(strings)

class tank(tank_module.Tank):
    
    def __init__(self, path=None):
        path = path if path else ROOT_PATH
        super().__init__(str(paths), str(keys), str(strings), path)


if __name__ == "__main__":
    # pprint(keys)

    tk = tank("D:/Desk/python/Tank/tests/project")

    templates = tk.templates()
    nuke_template = templates["Shot_NukeRender_Work_Sequence"]
    # pprint(tk.keys())
    # print(nuke_template)
    # print(nuke_template.name())
    # print(nuke_template.definition())
    # print(nuke_template.static_token())
    # print(nuke_template.ordered_keys())
    fields = {
        "Sequence": "sh",
        "Shot": "sh_010",
        "version": "1",
        "Task": "cmp",
        "name": "sh_010",
        "write_node": "out",
        "colorspace": "linear",
        "variant": "caca",
        "render_source": "nk",
        "ext_render_nuke": "exr"
    }
    path = nuke_template.apply_fields(fields)
    # print()
    # print("path")
    # print(path)
    pathTest = "D:/Desk/python/Tank/tests/project/sequence/test_020/010/cmp/nuke/wip/010-cmp-base-v0001.nk"

    template = tk.template_from_path(pathTest)
    print()
    print("definition")
    print(template.definition())
    print()
    # print("Order Key")
    # print(template.ordered_keys())
    # print()
    # print("Fields")
    pprint(template.get_fields(pathTest))

