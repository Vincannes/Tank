import os
import sys
from pprint import pprint

# & "C:\Users\User\AppData\Local\Programs\Python\Python37\python.exe" d:/Desk/python/Tank/python/sgtk/__init__.py

TANK_DIR = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
MODULE_PATH = os.path.join(TANK_DIR, "cpp", "bin")
sys.path.append(MODULE_PATH)

ROOT_PATH = "D:/Desk/python/Projects"

import tank_module
from tank_module import TankMatchingTemplatesError


class Tank(tank_module.Tank):

    def __init__(self, path=None):
        CONFIG_PATH = os.environ.get("CONFIG_PATH")

        if not CONFIG_PATH:
            CONFIG_PATH = os.path.join(TANK_DIR, "config", "templates.yml")

        path = path if path else ROOT_PATH
        super().__init__(CONFIG_PATH, path)


def test_all_fields():
    fields = {"Shot": "sh_010", "Sequence": "sh", "Task": "src", "colorspace": "aces",
              "extension": "exr", "ext_render_nuke": "jpg", "variant": "master01",
              "version": "1", "SEQ": "%04d", "name": "sh_010", "Asset": "test",
              "render_aov": "path_test", "image_ext": "png", "ext_render_flame": "tiff",
              "ext_cache_houdini": "abc", "ext_proxy": "jpg", "ext_scene_photoshop": "psd",
              "cache_type_houdini": "adc", "ext_render_clarisse": "jpg", "ext_render_afterfx": "exr",
              "ext_render_blender": "png", "ext_render_c4d": "tiff", "ext_cache_maya": "abc",
              "flame_render_source": "fl", "photoshop_render_source": "ps", "afterfx_render_source": "ae",
              "blender_render_source": "bl", "harmony_render_source": "ha", "houdini_render_source": "htoa",
              "footage_source": "aucune_idee", "write_node_parent": "aucune_idee", "node": "aucune_idee",
              "export_ass_set_suffix": "aucune_idee", "cache_variant": "aucune_idee", "image_variant": "aucune_idee",
              "export_ass_top_namespace": "aucune_idee", "vendor": "bangalor", "extra_variant": "aucune_idee",
              "segment_name": "aucune_idee", "export_fur_top_namespace": "aucune_idee", "camera": "test",
              "project_resolution": "1920x1080", "render_source": "nk", "render_layer": "beauty",
              "write_node": "out", "slate_frame": "1001", "delivery_image_type": "exr",
              "client_step": "prep", "delivery_quicktime_suffix": "test", "cut_name": "caca",
              "cut_revision": "cut_revision", "tool": "nuke", "output": "output", "HSEQ": "HSEQ",
              }
    # print(tk.templates()["Hiero_Footage_Sequence"].apply_fields(s))

    # template = tk.template_from_path(aa)

    print("")
    index = 0
    for i in tk.templates():
        try:
            index += 1
            template = tk.templates()[i]
            path = template.apply_fields(fields)
            print(index, len(tk.templates()), i, path)
            template_path = tk.template_from_path(path)
            if template_path:
                print("       ", template_path.name())
        except:
            pass


if __name__ == "__main__":
    # pprint(keys)

    tk = Tank("D:/Desk/python/Tank/tests/project")

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
    pathTestWork = "D:/Desk/python/Projects/sequence/sh/sh_010/cmp/image/wip/sh_010-cmp-caca-nk-out-v0001-linear-exr/sh_010-cmp-caca-nk-out-v0001-linear.####.exr"
    pathTest = "D:/Desk/python/Tank/tests/project/sequence/test_020/010/cmp/nuke/wip/010-cmp-base-v0001.nk"
    aa = 'D:/Desk/python/Tank/tests/project/sequence/sh/sh_010/cmp/image/wip/sh_010-cmp-caca-nk-out-v001-linear-exr/sh_010-cmp-caca-nk-out-v001-linear.####.exr'
    zz = "D:/Desk/python/Tank/tests/project/sequence/sh/sh_010/common/footage/sh_010-src-master01-v001-aces-exr/sh_010-src-master01-v001-aces.####.exr"
    sequence_path = "D:/Desk/python/Tank/tests/project/sequence/sh/sh_010/common/footage/sh_010-src-master01-v001-aces-exr"

    # pprint(templates)
    # pprint(templates.get('Sequence', None))
    template = tk.template_from_path(sequence_path)
    print()
    print("definition")
    print(template.name())
    print(template.definition())
    print()
    # # print("Order Key")
    # # print(template.ordered_keys())
    # # print()
    # # print("Fields")
    # pprint(template.get_fields(aa))
