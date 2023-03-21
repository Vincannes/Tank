import unittest
from pprint import pprint
from app.domain.conform_paths import ConformPath


fake_templates = {
    'keys': {'Root': {'type': 'str'},
              'Shot': {'type': 'str'},
              'Task': {'type': 'str'},
              'dir': {'type': 'str'}},
 'paths': {'desk': '@rootDir\\{dir}', 'rootDir': 'C', "caca": "@desk"},
 'primary': None
}


class ConformPathTests(unittest.TestCase):

    def test_some_case_1(self):
        template = ConformPath(fake_templates)
        expected = ['C', '{dir}', 'C', '{dir}', '{Task}']
        result = template.get_definition_keys("@rootDir\\{dir}\\@desk\\{Task}")
        self.assertEqual(expected, result)

    def test_some_case_2(self):
        template = ConformPath(fake_templates)
        expected = ['C', '{dir}', 'C', '{dir}', '{Task}', 'C', '{dir}']
        result = template.get_definition_keys("@rootDir\\{dir}\\@desk\\{Task}\\@caca")
        self.assertEqual(expected, result)
