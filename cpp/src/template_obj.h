#pragma once

#include <map>
#include <vector>
#include <string>

#include "template_keys.h"

#ifndef TEMPLATE_H
#define TEMPLATE_H


class TemplatePath
{
public:

	// prototypes
	TemplatePath() = default;
	TemplatePath(std::string, std::map<std::string, TemplateKey>, std::string);

	// accesseurs
	bool validate(std::string);
	std::string getName() const;
	std::string getDefinition() const;
	std::vector<std::string> getStaticTokens() const;
	std::vector<std::string> getOrderedKeys() const;
	std::map<std::string, std::string> getFields(std::string);
	std::vector<std::string> missingKeys(std::map<std::string, std::string>);

	// manipulateurs
	std::string apply_fields(std::map<std::string, std::string>);

private:
	std::string _name;
	std::string _definition;
	std::string _orig_definition;
	std::vector<std::string>_ordered_keys;
	std::vector<std::string> _static_tokens;

	std::map<std::string, TemplateKey> _keys;
	std::map<std::string, TemplateKey> _all_keys;
	std::string _get_clean_definition(std::string);
	std::vector<std::string> _get_static_token() const;
	std::vector<std::string> _get_ordered_keys() const;
	std::vector<std::string> getTokensFromPath(std::string);
	std::map<std::string, TemplateKey> _keys_from_definition();

	
};

#endif // TEMPLATE_H