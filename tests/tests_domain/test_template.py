
import unittest

from prototype.domain.template import Template
from prototype.domain.template_keys import StringKey, IntegerKey


class TestApplyField(unittest.TestCase):

    def setUp(self):
        name = "nuke"
        definition = "C\\{dir}\\{Shot}\\{Task}\\nuke\\{Shot}-{Task}-base-v{version}.nk"
        self.keys = {
            "Root": StringKey("Root"), "Shot": StringKey("Shot"), "dir": StringKey("dir"),
            "Task": StringKey("Task"), "version": IntegerKey("version")
        }
        self.template = Template(name, self.keys, definition)

    def test_some_case_1(self):
        path = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
        expected = {"dir": "Desk", "Shot": "010", "Task": "cmp", "version": 1}
        template_fields = self.template.get_fields(path)
        self.assertEqual(expected, template_fields)

    def test_some_case_NOT(self):
        expected = None
        path = "C\\Desk\\010\\cmp\\010-cmp-base-v1.nk"
        template = self.template.get_fields(path)
        self.assertEqual(expected, template)

    def test_some_case_3(self):
        name = "test"
        definition = "C\\{dir}\\{Shot}\\{Task}"

        template = Template(name, self.keys, definition)

        path = "C\\Desk\\010\\cmp"
        expected = {"dir": "Desk", "Shot": "010", "Task": "cmp"}
        template_fields = template.get_fields(path)
        self.assertEqual(expected, template_fields)
