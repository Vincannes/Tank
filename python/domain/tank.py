from pprint import pprint

from prototype.domain.errors import TankError
from prototype.domain.config import read_templates
from prototype.domain.templates import Templates


class Tank(object):

    def __init__(self):
        self._template_dict = read_templates()
        self.__templates = Templates(self._template_dict)

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


