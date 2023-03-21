import os
import re

TEMPLATE_KEY_NAME_REGEX = r"[a-zA-Z_ 0-9\.]+"

class Template(object):

    def __init__(self, name, definitions, path):
        self._name = name
        self._path = path
        self._def = definitions
        self._definitions = os.path.join(*definitions)

        self._keys = definitions
        self._ordered_keys = []

        self._cleaned_definitions = []
        for definition in self._definitions:
            self._cleaned_definitions.append(self._clean_definition(definition))

    def __str__(self):
        return "{}: {}".format(self._name, self._definitions)

    @property
    def name(self):
        return self._name

    @property
    def path(self):
        return self._path

    @property
    def definition(self):
        """
        The template as a string, e.g ``shots/{Shot}/{Step}/pub/{name}.v{version}.ma``
        """
        return self._definitions

    @property
    def keys(self):
        regex = r"(?<={)%s(?=})" % TEMPLATE_KEY_NAME_REGEX
        return re.findall(regex, os.path.join(*self._path))

    def get_fields(self):
        return

    def apply_fields(self, field):
        regex = r"(?<={)%s(?=})" % TEMPLATE_KEY_NAME_REGEX
        zregex = r"{(%s)}" % TEMPLATE_KEY_NAME_REGEX
        print()
        # tokens = re.split(r"(\[[^]]*\])", self.path)
        # print(tokens)

        print("path ", self.path)
        print("def ", self._def)
        print("def ", self._definitions)
        print()
        print(self._clean_definition(self._definitions))
        print(self._get_static_tokens(self._definitions))

        test = []
        for ele in self._def:
            if re.search(regex, ele):
                values = []
                for key in re.findall(regex, ele):
                    value = self._get_value_from_field(key, field)
                    values.append(str(value))
                result = "-".join(values)

            else:
                result = ele
            test.append(result)

        print()
        path = os.path.join(*test)
        return path

    def test(self, fields, ignore_types=None, skip_defaults=False):
        ignore_types = ignore_types or []

        # find the largest key mapping without missing values
        keys = None
        # index of matching keys will be used to find cleaned_definition
        index = -1
        print(self._keys)
        for index, cur_keys in enumerate(self._keys):
            # We are iterating through all possible key combinations from the longest to shortest
            # and using the first one that doesn't have any missing keys. skip_defaults=False on
            # _apply_fields means we don't want to use a key that is not specified in the fields
            # parameter. So we want the missing_keys function to flag even the default keys that are
            # missing. Therefore we need to negate the skip_defaults parameter for the _missing_keys argument
            missing_keys = self._missing_keys(
                fields, cur_keys, skip_defaults=not skip_defaults
            )
            if not missing_keys:
                keys = cur_keys
                break

        if keys is None:
            raise ValueError(
                "Tried to resolve a path from the template %s and a set "
                "of input fields '%s' but the following required fields were missing "
                "from the input: %s" % (self, fields, missing_keys)
            )

        # Process all field values through template keys
        processed_fields = {}
        for key_name, key in keys.items():
            value = fields.get(key_name)
            ignore_type = key_name in ignore_types
            processed_fields[key_name] = key.str_from_value(
                value, ignore_type=ignore_type
            )

        return self._cleaned_definitions[index] % processed_fields

    # PRIVATE
    def _missing_keys(self, fields, keys, skip_defaults):
        """
        Compares two dictionaries to determine keys in second missing in first.

        :param fields: fields to test
        :param keys: Dictionary of template keys to test
        :param skip_defaults: If true, do not treat keys with default values as missing.
        :returns: Fields needed by template which are not in inputs keys or which have
                  values of None.
        """
        if skip_defaults:
            required_keys = [key.name for key in keys.values() if key.default is None]
        else:
            required_keys = keys

        return [x for x in required_keys if (x not in fields) or (fields[x] is None)]

    def _clean_definition(self, definition):
        # Create definition with key names as strings with no format, enum or default values
        regex = r"{(%s)}" % TEMPLATE_KEY_NAME_REGEX
        cleaned_definition = re.sub(regex, r"%(\g<1>)s", definition)
        return cleaned_definition

    def _get_static_tokens(self, definition):
        """
        Finds the tokens from a definition which are not involved in defining keys.
        """
        # expand the definition to include the prefix unless the definition is empty in which
        # case we just want to parse the prefix.  For example, in the case of a path template,
        # having an empty definition would result in expanding to the project/storage root
        expanded_definition = (
            definition
        )
        regex = r"{%s}" % TEMPLATE_KEY_NAME_REGEX
        tokens = re.split(regex, expanded_definition.lower())
        # Remove empty strings
        return [x for x in tokens if x]

    def _get_value_from_field(self, key, fields):
        key_clenead = key.replace("{", "").replace("}", "")
        return fields.get(key_clenead)



if __name__ == '__main__':
    template = Template(
        "test",
        ['C', '{dir}', '{Shot}', '{Task}', 'nuke', '{Shot}-{Task}-base-v{version}.nk'],
        "@test\\nuke\{Shot}-{Task}-base-v{version}.nk"
    )
    field = {"dir": "test", "Shot": "010", "Task": "cmp"}
    # C\test\010\cmp\nuke\010-cmp-base-vNone.nk
    print(template.apply_fields(field))
