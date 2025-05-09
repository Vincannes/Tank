#pragma once

#include <map>
#include <regex>
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
	// TemplatePath(std::string);
	TemplatePath(std::string, std::map<std::string, TemplateKey*>, std::string, std::string);

	// accesseurs
	bool validate(std::string);
	std::string getName() const;
	std::string getDefinition() const;
	std::vector<std::string> getStaticTokens() const;
	std::vector<std::string> getOrderedKeys() const;
	std::vector<std::string> getDefinitionVariants() const;
	std::map<std::string, TemplateKey*> getKeys() const;
	std::map<std::string, std::string> getFields(std::string);
	std::vector<std::string> missingKeys(std::map<std::string, std::string>);

	// manipulateurs
	std::string apply_fields(std::map<std::string, std::string>, std::vector<std::string> = {});
	void createFile(std::map<std::string, std::string>, std::vector<std::string> = {});

private:
	std::string _name;
	std::string _root_path;
	std::string _definition;
	std::string _orig_definition;
	std::string _pattern_definition;
	std::vector<std::string>_ordered_keys;
	std::vector<std::string> _static_tokens;
	std::vector<std::string> _definition_variations;

	std::map<std::string, TemplateKey*> _keys;
	std::map<std::string, TemplateKey*> _all_keys;
	std::string _get_clean_definition(std::string);
	std::string _get_pattern_definition(std::string);
	std::vector<std::string> _get_static_token() const;
	std::vector<std::string> _get_ordered_keys() const;
	std::vector<std::string> getTokensFromPath(std::string);
	std::string _getValueFromKeyObject(std::string, std::string);
	int _getDefinitionFromFields(std::map<std::string, std::string> fields);
	std::map<std::string, TemplateKey*> _keys_from_origin_definition();
	std::map<std::string, TemplateKey*> _keys_from_definition(std::string definition);
	std::map<std::string, TemplateKey*> _sub_keys_from_definition(std::string definition, std::regex re);
	std::vector<std::string> _get_definition_variations(const std::string definition);
	std::vector<std::string> _generateVariants(const std::string& definition);
	std::string _apply_fields_to_definition(std::string definition, std::map<std::string, std::string> fields, std::vector<std::string> missing_keys);
	std::string _get_longest_variant(std::vector<std::string> definition_variants);
	std::vector<std::string> _missing_key_from_field(std::map<std::string, TemplateKey*> keys, std::map<std::string, std::string> fields);

};

#endif // TEMPLATE_H