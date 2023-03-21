import unittest
from app.old.old_template import Template


fake_templates = {
    'keys': {'Root': {'type': 'str'},
              'Shot': {'type': 'str'},
              'Task': {'type': 'str'},
              'dir': {'type': 'str'},
              'aa': {'type': 'str'}},
 'paths': {'desk': '@rootDir\\{dir}', 'rootDir': 'C', "caca": "@desk\\{aa}"},
 'primary': None
}



class TemplateTest(unittest.TestCase):

    def test_case_apply_fields(self):
        templt = Template(
            "test",
            ['C', '{dir}', '{aa}'],
            "@desk\{dir}\{aa}"
        )
        field = {"dir": "test", "aa": "test2"}
        expected = "C\\test\\test2"
        self.assertEqual(expected, templt.apply_fields(field))

    def test_case_apply_fields_2(self):
        templt = Template(
            "desk",
            ['C', '{dir}', '{aa}'],
            "@desk\{dir}\{aa}"
        )
        field = {"dir": "test", "aa": "test2"}
        expected = "C\\test\\test2"
        self.assertEqual(expected, templt.apply_fields(field))

    def test_case_apply_fields_2(self):
        templt = Template(
            "desk",
            ['C', '{dir}', '{Shot}', '{Task}', 'nuke', '{Shot}-{Task}-base-v{version}.nk'],
            "@test\nuke\{Shot}-{Task}-base-v{version}.nk"
        )
        field = {"dir": "test", "aa": "test2", "Shot":"010", "version":1}
        print(templt.apply_fields(field))
        expected = "C\\test\\test2\\010-v1.nk"
        self.assertEqual(expected, templt.apply_fields(field))
