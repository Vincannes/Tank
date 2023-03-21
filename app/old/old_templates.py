import yaml
from pprint import pprint

from app.old.old_template import Template
from app.domain.conform_paths import ConformPath


class Templates(object):

    def __init__(self):
        self.__templates = self.read_templates()
        self._templates = self.load_templates()
        self._conform_path = ConformPath(self.__templates)

    def read_templates(self):
        _templates = {}
        with open(r"/config/template.yml", "r") as stream:
            _templates = yaml.safe_load(stream)
        return _templates

    def load_templates(self):
        template_paths = self.__templates.get('paths')
        all_templates = {}
        for name, definitions in template_paths.items():
            keys = self._conform_path.get_definition_keys(definitions)
            print(keys)
            print(definitions)
            print()
            all_templates[name] = Template(name, keys, definitions)

        return all_templates

    def get_all_templates(self):
        return self._templates

if __name__ == '__main__':

    pathj = Templates()
    templates = pathj.get_all_templates()

    pprint(templates)
    print()
    print(templates["nuke"])
    field = {"dir": "sequence", "Shot": "010", "Task": "cmp", "version": 1}
    # print(templates["nuke"].apply_fields(field))

