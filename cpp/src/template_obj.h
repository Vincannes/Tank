#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "template_keys.h"

#ifndef TEMPLATE_H
#define TEMPLATE_H


class TemplatePath
{
public:

	// prototypes
	TemplatePath(std::string name, std::vector<TemplateKey> keys, std::string definition);

	// accesseurs
	std::string getName() const;
	std::string getDefinition() const;
	std::vector<std::string> getStaticTokens() const;
	std::vector<std::string> getOrderedKeys() const;
	std::string apply_fields(std::map<std::string, std::string> fields);
	std::map<std::string, std::string> getFields(std::string path);

	// manipulateurs
	//...

private:
	std::string _name;
	std::string _definition;
	std::string static_tokens;
	std::string _orig_definition;
	std::vector<TemplateKey> _keys;
	std::string _get_clean_definition(std::string _definition);
	std::vector<std::string> _get_static_token(std::string _definition) const;
	std::vector<std::string> _get_ordered_keys(std::string _definition) const;
	std::vector<std::string> getTokensFromPath(std::string path);

};

#endif // TEMPLATE_H