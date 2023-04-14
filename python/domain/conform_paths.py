import os
from pprint import pprint


class ConformPath(object):

    def __init__(self, templates):
        self._templates = templates

    def _get_definitions(self, element):
        ele_key = element.replace('@', '')
        ele_path = self._templates.get('paths')[ele_key]

        ele_path_ls = []
        if '@' in ele_path:
            ele_path_split = ele_path.split('\\')

            for _ele in ele_path_split:
                if '@' in _ele:
                    _defin = self._get_definitions(_ele)
                    if isinstance(_defin, str):
                        ele_path_ls.append(_defin)
                    else:
                        ele_path_ls.extend(_defin)
                else:
                    ele_path_ls.append(_ele)

        if ele_path_ls:
            ele_path = ele_path_ls

        return ele_path

    def get_definition_keys(self, _path):
        splited_path = _path.split("\\")
        _definition = []
        for s in splited_path:
            if '@' in s:
                ele_path = self._get_definitions(s)
                if isinstance(ele_path, str):
                    _definition.append(ele_path)
                else:
                    _definition.extend(ele_path)
            else:
                _definition.append(s)
        return _definition

    def get_definitions_path(self, _path):
        return os.path.join(*self.get_definition_keys(_path))


if __name__ == '__main__':
    fake_templates = {
        'keys': {'Root': {'type': 'str'},
                 'Shot': {'type': 'str'},
                 'Task': {'type': 'str'},
                 'dir': {'type': 'str'}},
        'paths': {'desk': '@rootDir\\{dir}\\@caca', 'rootDir': 'C', "caca": "zzz"},
        'primary': None
    }
    a = ConformPath(fake_templates)
    pprint(a.get_definition_keys("@desk"))
