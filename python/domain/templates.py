from pprint import pprint

from template import Template
from conform_paths import ConformPath
from template_keys import StringKey, IntegerKey, TimestampKey


class Templates(object):

    def __init__(self, templates):
        self.__template_dict = templates
        self._conform_path = ConformPath(self.__template_dict)
        self._templates = self.load_templates()

    @property
    def templates(self):
        return self._templates

    @property
    def templates_dict(self):
        return self.__template_dict

    def get_keys(self, data):
        """
        Return dict of all possible Keys with default value
        :param data:
        :return: [dict] {"Key": KeyObject}
        """
        keys = {}
        names_classes = {
            "str": StringKey,
            "int": IntegerKey,
            "timestamp": TimestampKey,
        }
        for initial_key_name, key_data in data.items():
            keyClass = names_classes[key_data.get("type")]
            keys[initial_key_name] = keyClass(initial_key_name)

        return keys

    def load_templates(self):
        _templates = {}
        template_paths = self.__template_dict.get('paths')
        template_keys = self.get_keys(self.__template_dict.get("keys"))

        for name, definitions in template_paths.items():
            path_definition = self._conform_path.get_definitions_path(definitions)
            _templates[name] = Template(name, template_keys, path_definition)

        return _templates


if __name__ == "__main__":
    from app.domain.config import read_templates
    tank_templates = Templates(read_templates())

    fields = {"dir": "Desk", "Shot": "010", "Task": "cmp", "version": 1}
    template = tank_templates.templates["nuke"]
    path = template.apply_fields(fields)
    print(path)
