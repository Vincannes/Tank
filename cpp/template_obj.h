#pragma once

#include "template_keys.h"
#include <iostream>
#include <string>
#include <vector>

class Template
{
public:

	// prototypes
	Template(std::string name, std::vector<StringKey> keys, std::string definition);

	// accesseurs
	std::string getName() const;
	std::string getDefinition();
	std::vector<std::string> getStaticTokens();
	std::vector<std::string> getOrderedKeys();
	std::string apply_fields(std::map<std::string, std::string> fields);
	std::map<std::string, std::string> getFields(std::string path);

	// manipulateurs
	//...

private:
	std::string _name;
	std::string _definition;
	std::string static_tokens;
	std::string _orig_definition;
	std::vector<StringKey> _keys;
	std::string _get_clean_definition(std::string _definition);
	std::vector<std::string> _get_static_token(std::string _definition);
	std::vector<std::string> _get_ordered_keys(std::string _definition);
	std::vector<std::string> _apply_fields(std::string _definition);
	std::vector<std::string> splitPath(const std::string& path);
	std::vector<std::string> getTokensFromPath(std::string path);
	std::string joinListWithSeparator(std::vector<std::string> list, char separator);

};

