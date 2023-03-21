
from app.domain.errors import TankError
from app.domain.config import read_templates
from app.domain.templates import Templates


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
        print(matched_templates)
        if len(matched_templates) == 0:
            return None
        elif len(matched_templates) == 1:
            return matched_templates[0]
        else:
            return TankError("%d templates are matching the path '%s'.\n" % (
                len(matched_templates), path))


