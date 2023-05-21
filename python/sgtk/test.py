import os
import glob
from pprint import pprint


def _paths_from_template(template, fields, skip_keys=None, skip_missing_optional_keys=False):
   
    skip_keys = skip_keys or []
    if isinstance(skip_keys, str):
        skip_keys = [skip_keys]

    # construct local fields dictionary that doesn't include any skip keys:
    local_fields = dict(
        (field, fields[field]) for field in fields if field not in skip_keys
    )
    # we always want to automatically skip 'required' keys that weren't
    # specified so add wildcards for them to the local fields
    for key in template.missing_keys(local_fields):
        if key not in skip_keys:
            skip_keys.append(key)
        local_fields[key] = "*"

    # iterate for each set of keys in the template:
    found_files = set()
    globs_searched = set()
    for keys in template._keys_dict:

        # create fields and skip keys with those that
        # are relevant for this key set:
        current_local_fields = local_fields.copy()
        current_skip_keys = []
        # print("keys ", keys)

        for key in skip_keys:
            if key in keys:
                current_skip_keys.append(key)
                current_local_fields[key] = "*"

        # find remaining missing keys - these will all be optional keys:
        missing_optional_keys = template._missing_keys(
            current_local_fields, keys, False
        )
        # if missing_optional_keys:
        #     if skip_missing_optional_keys:
        #         # Add wildcard for each optional key missing from the input fields
        #         for missing_key in missing_optional_keys:
        #             current_local_fields[missing_key] = "*"
        #             current_skip_keys.append(missing_key)
        #     else:
        #         # if there are missing fields then we won't be able to
        #         # form a valid path from them so skip this key set
        #         continue

        # Apply the fields to build the glob string to search with. We are iterating
        # through all the possible key combinations that do and do not include the
        # optional keys so we need _apply_fields to skip defaults otherwise if an
        # optional key has a default value, we will never find files that don't include
        # the optional key in their file name
        glob_str = template._apply_fields(
            current_local_fields
        )
        print(glob_str)
        globs_searched.add(glob_str)

    return list(glob.iglob(glob_str))


# def paths_from_template(template, fields, skip_keys=None, skip_missing_optional_keys=False):

    # for keys in template._keys_dict:


class Template(object):

    def __init__(self):
        self._keys_dict = [{"Shot": str}, {"Task": str}, {"version": int}, {"Root": str}, {"variant": str}]
        self._keys = ["Shot", "Task", "version", "Root", "variant"]
        self._cleaned_definitions = "D:\\Desk\\python\\Tank\\tests\\project\\test\\%(Shot)s\\%(Task)s\\nuke\\%(Shot)s-%(Task)s-%(variant)s-v%(version)s.nk"

    def _missing_keys(self,  fields, keys, skip_defaults):
        required_keys = self._keys
        return [x for x in required_keys if (x not in fields) or (fields[x] is None)]
    
    def missing_keys(self, field):
        return ["variant", "version"]
    
    def _apply_fields(self, fields, ignore_types=None, platform=None, skip_defaults=False):
        return self._cleaned_definitions % fields


if __name__ == "__main__":

    template = Template()
    
    fields = {
        "Shot": "sh_010",
        "Task": "cmp",
        # "version": "1",
        "Root": "C",
        "variant": "base",
    }

    # print(template._missing_keys(fields, template._keys, False))
    # print(template.missing_keys(fields))
    # print(template._apply_fields(fields))
    # a = paths_from_template(template, fields, skip_keys={})
    # pprint(a)
    glob_str = "D:\\Desk\\python\\Tank\\tests\\project\\test\\sh_010\\cmp\\nuke\\sh_010-cmp-caca-v*.nk"
    pprint(list(glob.iglob(glob_str)))
