import unittest
from pprint import pprint

from prototype.domain.config import read_templates
from prototype.domain.templates import Templates


class TestApplyField(unittest.TestCase):

    def setUp(self):
        templates = read_templates()
        self.tank_templates = Templates(templates)

    def test_some_case_1(self):
        fields = {"dir": "Desk", "Shot": "010", "Task": "cmp"}
        expected = "C\\Desk\\010\\cmp"
        template = self.tank_templates.templates["test"].apply_fields(fields)
        self.assertEqual(expected, template)

    def test_some_case_2(self):
        fields = {"dir": "Desk", "Shot": "010", "Task": "cmp", "version": 1}
        expected = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
        template = self.tank_templates.templates["nuke"].apply_fields(fields)
        self.assertEqual(expected, template)

    def test_some_case_3(self):
        fields = {"dir": "Desk", "Shot": "010", "Task": "cmp", "version": 1}
        expected = "C\\Desk\\nuke\\010-cmp-base-v1.nk"
        template = self.tank_templates.templates["test_diff"].apply_fields(fields)
        self.assertEqual(expected, template)

