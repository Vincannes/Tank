import os
import re
from pprint import pprint
from errors import TankError
from config import read_templates
from templates import Templates


class Tank(object):

    def __init__(self):
        self._template_dict = read_templates()
        self.__templates = Templates(self._template_dict)

    @property
    def templates(self):
        return self.__templates.templates

    def templates_from_path(self, path):
        matched_templates = []
        for key, template in self.__templates.templates.items():
            if template.validate(path):
                matched_templates.append(template)
        return matched_templates

    def template_from_path(self, path):

        matched_templates = self.templates_from_path(path)

        if len(matched_templates) == 0:
            return None
        elif len(matched_templates) == 1:
            return matched_templates[0]
        else:
            return TankError("%d templates are matching the path '%s'.\n" % (
                len(matched_templates), path))

    def abstract_paths_from_template(self, template, fields, skip_keys=None):
        abstract_paths = []

        skip_keys = skip_keys or []

        # construct local fields dictionary that doesn't include any skip keys:
        local_fields = dict(
            (field, fields[field]) for field in fields if field not in skip_keys
        )

        # we always want to automatically skip 'required' keys that weren't
        # specified so add wildcards for them to the local fields
        for key in template.missing_keys(local_fields):
            if key not in skip_keys:
                skip_keys.append(key)
            local_fields[key] = ".*"

        # print("skip_keys ", skip_keys)
        # print("local_fields ", local_fields)
        # print()
        
        found_files = set()
        globs_searched = set()
        # pprint(template._keys_dict)
        for keys in template._keys_dict:
            # create fields and skip keys with those that
            # are relevant for this key set:
            current_local_fields = local_fields.copy()
            current_skip_keys = []
            for key in skip_keys:
                if key in keys:
                    current_skip_keys.append(key)
                    current_local_fields[key] = ".*"

            glob_str = template.apply_fields(current_local_fields)
            pattern = "\\\\".join(glob_str.split("\\"))

            for root, dirs, files in os.walk('D:\\Desk\\python\\Tank\\tests'):
                for dir in files:
                    file_path = os.path.join(root, dir)
                    if re.match(pattern, file_path):
                        abstract_paths.append(os.path.join(root, file_path))

        return list(set(abstract_paths))
    
if __name__ == "__main__":
    tank = Tank()
    fields = {
        # "Shot": "sh_020",
        "Task": "cmp",
        "version": "1",
        "Root": "test",
        # "variant": "base",
        "dir": "test",
    }
    template = tank.templates["nuke"]
    pprint(template.clean_definition)
    pprint(tank.abstract_paths_from_template(template, fields))

    # pprint(list(glob.iglob("D:\\Desk\\python\\Tank\\tests\\project\\test\\*\\cmp\\nuke\\*-cmp-base-v*.nk")))
    # pprint(list(glob.iglob("D\\Desk\\python\\Tank\\tests\\project\\test\\*")))
    # pprint(list(glob.iglob("D\\Desk\\python\\Tank\\tests\\project\\test\\.*\\cmp\\nuke\\.*-cmp-base-v01.nk")))
    # import re
    matching_folders = []
    # pattern = "D:\\\\Desk\\\\python\\\\Tank\\\\tests\\\\project\\\\test\\\\sh_020\\\\cmp\\\\nuke\\\\sh_020-cmp-base-v.*.nk"
    # pattern = "D:\\\\Desk\\\\python\\\\Tank\\\\tests\\\\project\\\\test\\\\sh_020\\\\cmp\\\\nuke\\\\sh_020-cmp-base-v.*.nk"
    # for root, dirs, files in os.walk('D:\\Desk\\python\\Tank\\tests'):
    #     for dir in files:
    #         file_path = os.path.join(root, dir)
    #         if re.match(pattern, file_path):
    #             print(file_path)
    #             matching_folders.append(file_path)
