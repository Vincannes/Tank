import unittest
from pprint import pprint

from Tank import sgtk


class TestGetTemplateFromPath(unittest.TestCase):

    def setUp(self):

        self.tank = sgtk()
        self.templates = self.tank.get_templates()
        nuke_template = self.templates["nuke"]

        fields = {
            "dir": "test",
            "Shot": "sh_010",
            "version": "1",
            "Task": "cmp",
        }
        path = nuke_template.apply_fields(fields)


    def test_some_case_1(self):
        path = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
        expected = "nuke"
        template = self.tank.template_from_path(path)
        print(template)
        print(template.name())
        print(template.definition())
        self.assertEqual(expected, template.name())

    # def test_some_case_2(self):
    #     path = "C\\Desk\\010\\cmp"
    #     expected = "test"
    #     template = self.tank.template_from_path(path)
    #     self.assertEqual(expected, template.name)

    # def test_some_case_3(self):
    #     path = "C\\Desk\\nuke\\010-cmp-base-v1.nk"
    #     expected = "test_diff"
    #     template = self.tank.template_from_path(path)
    #     self.assertEqual(expected, template.name)
