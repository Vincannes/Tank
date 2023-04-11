import os
from Tank import sgtk
from Tank import TankMatchingTemplatesError

import unittest

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

    def test_some_case_MATCH(self):
        path = os.path.join("C", "test", "sh_010", "cmp", "nuke", "sh_010-cmp-base-v1.nk")
        path = path.replace('\\', '\\\\')
        expected = "nuke"
        template_name = self.tank.template_from_path(path).name()
        self.assertEqual(expected, template_name)

    def test_some_case_NO_MATCH(self):
        path = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
        with self.assertRaises(TankMatchingTemplatesError):
            self.tank.template_from_path(path)

    def test_some_case_2(self):
        path = os.path.join("C", "test")
        path = path.replace('\\', '\\\\')
        expected = "desk"
        template_name = self.tank.template_from_path(path).name()
        self.assertEqual(expected, template_name)

    # def test_some_case_3(self):
    #     path = "C\\Desk\\nuke\\010-cmp-base-v1.nk"
    #     expected = "test_diff"
    #     template = self.tank.template_from_path(path)
    #     self.assertEqual(expected, template.name)
