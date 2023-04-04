import os
import re
from pprint import pprint

from prototype import constants
from prototype.domain.errors import TankError


class Template(object):

    def __init__(self, name, keys, definition):
        """

        :param name: [str] Name of the Template
        :param keys: [dict] All keys from template.yml
                    {'Root': <tests.StringKey object at 0x0000021CF9556B50>,
                    'Shot': <tests.StringKey object at 0x0000021CF9556CD0>}
        :param definition: [str] Full path with tokens
                    "C\{dir}\nuke\{Shot}-{Task}-base-v{version}.nk"
        """
        self.name = name
        self.__keys = keys
        self.definition = definition
        self._clean_definition = self._clean_definition(self.definition)
        self._keys, self._ordered_keys = self._keys_from_definition(self.definition, self.name, self.__keys)

    ##PROPERTIES

    @property
    def keys(self):
        """
        List of all tokens in Order they appear in path
        :return: [list]
        """
        return self._ordered_keys

    @property
    def clean_definition(self):
        """
        Match definition for easily replace token with value

        C\%(dir)s\%(Shot)s\%(Task)s\nuke\%(Shot)s-%(Task)s-base-v%(version)s.nk"
        :return: [str]
        """
        return self._clean_definition

    @property
    def static_tokens(self):
        """
        Get non-token element from definition
        "C\{dir}\nuke\{Shot}-{Task}-base-v{version}.nk"
        :return: [list] ["\nuke\", "-base-v", ".nk"]
        """
        return self._get_static_tokens(self.definition)

    ## MAIN FUNCTIONS

    def validate(self, path):
        path_fields = self.get_fields(path)

        if not path_fields:
            return None

        # IS ALL FIELDS ARE MATCHING
        if len(path_fields) != len(self._keys):
            return None

        return path_fields is not None

    def apply_fields(self, fields):
        return self._clean_definition % fields

    def get_fields(self, path):

        fields = {}
        path_split = path.split(os.sep)
        definition_split = self._clean_definition.split(os.sep)
        len_path = len(path_split)
        len_defi = len(definition_split)
        if len_path != len_defi:
            return

        satic_token = self._get_static_tokens(self.definition)

        regex = r"%\({}\)s".format(constants.REGEX_STR_INT)
        for i in range(len_path):
            is_token = re.match(regex, definition_split[i])

            if is_token:
                tokens = re.findall(regex, definition_split[i])

                # if {token}-{token}-text-v{1}
                if len(tokens) > 1:

                    # place "-" at the end of the filter
                    if "-" in satic_token:
                        satic_token.append(satic_token.pop(satic_token.index("-")))

                    static_parse = "|".join(satic_token)
                    values = re.split(static_parse, path_split[i])
                    tokens_parse = re.split(static_parse, definition_split[i])

                    for token, value in zip(tokens_parse, values):
                        if not value or any([value in tokens_parse for i in tokens_parse]):
                            continue
                        token_name = re.findall(r"({})\)".format(constants.REGEX_STR_INT), token)[0]
                        fields[token_name] = self._get_key_value(token_name, value)

                else:
                    token_name = re.findall(constants.REGEX_STR_INT, tokens[0])[0]
                    value = path_split[i]
                    # if special character
                    if re.findall(r"[-.]", value): #TODO sad way to filter
                        return
                    fields[token_name] = self._get_key_value(token_name, value)

            else:
                if path_split[i] != definition_split[i]:
                    return

        return fields

    ## PRIVATE

    def _clean_definition(self, definition):
        """
        Convert path with keys for easily replace.
        Token: {..} replace %(..)%
        :param definition:
        :return: [str] "C\%(dir)s\nuke\%(Shot)s-%(Task)s-base-v%(version)s.nk"
        """
        # Create definition with key names as strings with no format, enum or default values
        regex = r"{(%s)}" % constants.REGEX_STR_INT
        cleaned_definition = re.sub(regex, r"%(\g<1>)s", definition)
        return cleaned_definition

    def _get_key_value(self, token, value):
        """
        Convert value of key from is type
        ie: Token type = int
        value convert into int
        :param token:
        :param value:
        :return:
        """
        for key in self.keys:
            if key.name != token:
                continue
            if type(value) != key.type:
                values = re.findall(r"[0-9\.]+", value)
                if values:
                    value = int(values[0])

        return value

    def _get_static_tokens(self, definition):
        """
        Finds the tokens from a definition which are not involved in defining keys.
        """
        # expand the definition to include the prefix unless the definition is empty in which
        # case we just want to parse the prefix.  For example, in the case of a path template,
        # having an empty definition would result in expanding to the project/storage root
        expanded_definition = (
            definition
        )
        regex = r"{%s}" % constants.REGEX_STR_INT
        tokens = re.split(regex, expanded_definition.lower())
        # Remove empty strings
        return [x for x in tokens if x]

    def _keys_from_definition(self, definition, template_name, keys):
        """Extracts Template Keys from a definition.

        :param definition: Template definition as string
        :param template_name: Name of template.
        :param keys: Mapping of key names to keys as dict

        :returns: Mapping of key names to keys and collection of keys ordered as they appear in the definition.
        :rtype: List of Dictionaries
        """
        names_keys = {}
        ordered_keys = []

        # regular expression to find key names
        regex = r"(?<={)%s(?=})" % constants.REGEX_STR_INT
        key_names = re.findall(regex, definition)
        for key_name in key_names:
            key = keys.get(key_name)
            if key is None:
                msg = "Template definition for template %s refers to key {%s}, which does not appear in supplied keys."
                raise ValueError(msg % (template_name, key_name))
            else:
                if names_keys.get(key.name, key) != key:
                    # Different keys using same name
                    msg = (
                            "Template definition for template %s uses two keys"
                            + " which use the name '%s'."
                    )
                    raise ValueError(msg % (template_name, key.name))
                names_keys[key.name] = key
                ordered_keys.append(key)
        return names_keys, ordered_keys


if __name__ == "__main__":
    from app.domain.config import read_templates
    from app.domain.templates import Templates

    templates = Templates(read_templates())
    template = templates.templates["nuke"]

    path = "C\\Desk\\010\\cmp\\nuke\\010-cmp-base-v1.nk"
    template_fields = template.get_fields(path)
    print()
    print(template_fields)
