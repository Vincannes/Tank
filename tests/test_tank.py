import unittest
from pprint import pprint

from app.domain.errors import TankError
from app.domain.tank import Tank


class TestGetTemplateFromPath(unittest.TestCase):

    def setUp(self):
        self.tank = Tank()

    def test_some_case_1(self):
        path = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
        expected = "nuke"
        template = self.tank.template_from_path(path)
        self.assertEqual(expected, template.name)

    def test_some_case_2(self):
        path = "C\\Desk\\010\\cmp"
        expected = "test"
        template = self.tank.template_from_path(path)
        self.assertEqual(expected, template.name)

    def test_some_case_3(self):
        path = "C\\Desk\\nuke\\010-cmp-base-v1.nk"
        expected = "test_diff"
        template = self.tank.template_from_path(path)
        self.assertEqual(expected, template.name)
