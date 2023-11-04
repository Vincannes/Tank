#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "utils.h"
#include "exception.h"
#include "template_obj.h"
#include "conform_path.h"
#include "template_keys.h"

TemplatePath::TemplatePath(std::string name, std::map<std::string, TemplateKey*> keys, std::string definition, std::string root_path)
{
	this->_root_path             = root_path;
	this->_name                  = name;
	this->_all_keys              = keys;
	this->_orig_definition       = definition;
	this->_definition            = _get_clean_definition(definition);
	this->_pattern_definition    = _get_pattern_definition(definition);
	this->_definition_variations = _get_definition_variations(definition);
	this->_keys                  = _keys_from_origin_definition();
	this->_ordered_keys          = _get_ordered_keys();
	this->_static_tokens         = _get_static_token();

}

std::string TemplatePath::getName() const
{
	return this -> _name;
}

std::string TemplatePath::getDefinition() const
{
	return this->_definition;
}

std::map<std::string, TemplateKey*> TemplatePath::getKeys() const
{
	return this->_keys;
}

bool TemplatePath::validate(std::string path)
{
	std::map<std::string, std::string> path_fields = getFields(path);
	if(path_fields.empty()) return false;
	if(path_fields.size() != this->_keys.size()) return false; // IS ALL FIELDS ARE MATCHING
	return true;
}

std::vector<std::string> TemplatePath::getStaticTokens() const
{
	return this->_static_tokens;
}

std::vector<std::string> TemplatePath::getOrderedKeys() const
{

	return this->_ordered_keys;
}

std::vector<std::string> TemplatePath::getDefinitionVariants() const
{
	return this->_definition_variations;
}

// MAIN FUNCTIONS

std::string TemplatePath::apply_fields(std::map<std::string, std::string> fields, std::vector<std::string> missing_keys)
{
	int variant_index = _getDefinitionFromFields(fields);
	if(variant_index == -1){ 
		std::vector<std::string> fieldsMissing = _missing_key_from_field(this->_keys, fields);
		throw TankApplyFieldsTemplateError(getName(), getDefinition(), fieldsMissing);
	}
	return _apply_fields_to_definition(this->_definition_variations[variant_index], fields, missing_keys);
}


std::map<std::string, std::string> TemplatePath::getFields(std::string path) 
{
	if(path.find(this->_root_path) == 0){
		path = removePatternInString(path, this->_root_path, "");
		path = matchSeparator(path);
	}
	std::map<std::string, std::string> fields = {};

	// verifier si la longueur du path est le meme que _definition 
	std::vector<std::string> path_splited = splitPath(path);
	std::vector<std::string> definition_splited = splitPath(this->_definition);

	// return dictionnaire vide si longueurs differents
	if (path_splited.size() != definition_splited.size()) {
		// std::cout << "No fields find for this template " << std::endl; // TODO Raise error gere
		return fields;
	}

	std::string clean_def = removePatternInString(this->_pattern_definition, "/", "\\/");
	std::regex pattern(clean_def);
    if(!std::regex_match(path, pattern)){
		return fields;
	}
	std::vector<std::string> satic_token = getStaticTokens();
	std::vector<std::string> modified_tokens;

	// if "." in static_token, add "\\." for regex 
	for (const std::string& token : satic_token) {
        if (token == ".") {
            modified_tokens.push_back("\\.");
        } else {
            modified_tokens.push_back(token);
        }
    }

	// from satic_token list {"item", "-", "item"}, place "-" at the end of the list
	if (std::find(modified_tokens.begin(), modified_tokens.end(), "-") != modified_tokens.end()) {
		auto itr = std::find(modified_tokens.begin(), modified_tokens.end(), "-");
		modified_tokens.erase(itr);
		modified_tokens.push_back("-");
	}

	// Create REGEX pour separer les tokens a partir de chaque non Token dans le path
	std::string static_parse = joinListWithSeparator(modified_tokens, '|'); // move - to the end

	for (size_t i = 0; i < path_splited.size(); i++) {

		int is_token = std::regex_search(definition_splited[i], std::regex("\\%\\(.*\\)"));
		if (is_token) {

			std::vector<std::string> tokens = getTokensFromPath(definition_splited[i]);

			// Si un plusieurs patterns match
			if (tokens.size() > 1) 
			{

				for (const std::string token_name : tokens)
				{
					std::regex rgx(static_parse);
					std::sregex_token_iterator iterDefin(definition_splited[i].begin(), definition_splited[i].end(), rgx, -1);
					std::sregex_token_iterator iterPath(path_splited[i].begin(), path_splited[i].end(), rgx, -1);

					std::vector<std::string> token_def(iterDefin, {});
					std::vector<std::string> tokens_val(iterPath, {});

					size_t sizeDefinition = token_def.size();
					size_t sizePath = tokens_val.size();

					if (sizePath != sizeDefinition) continue;

					for (size_t token_index = 0; token_index < sizePath; token_index++) {
						if (token_index < token_def.size() && token_index < tokens_val.size()) {
							std::string token = token_def[token_index];
							std::string value = tokens_val[token_index];

							// si value est dans list de static Tokens on passe
							if (std::find(token_def.begin(), token_def.end(), value) != token_def.end()) {
								continue;
							}

							std::vector<std::string> valueFromPath = getTokensFromPath(token);
							for (const auto& _token_name : valueFromPath) { // Verifier si plusieurs token trouve
								try{
									std::string value_reformat = _getValueFromKeyObject(_token_name, value);
									if(_token_name == "version"){
										int num1 = std::stoi(value_reformat);
										value_reformat = std::to_string(num1);
									}
									fields[_token_name] = value_reformat;
									// std::cout << "_token_name  "<<_token_name << "   "<< value_reformat << std::endl;
								}catch(const TankTemplateWrongValue& e){
									continue;
								}
							}
						}

					}
				}
			}

			// Si un seul pattern match
			else if (tokens.size() == 1) {
				std::string token_name = tokens[0];
				std::string token_value = path_splited[i];
				fields[token_name] = token_value;
			}
		}
	}

	return fields;
}


std::vector<std::string> TemplatePath::missingKeys(std::map<std::string, std::string> fields)
{
	// >>> tk.templates["max_asset_work"].missing_keys({})
    //         ['Step', 'sg_asset_type', 'Asset', 'version', 'name']

    // >>> tk.templates["max_asset_work"].missing_keys({"name": "foo"})
    //         ['Step', 'sg_asset_type', 'Asset', 'version']

	return _missing_key_from_field(this->_keys, fields);
}


void TemplatePath::createFile(std::map<std::string, std::string> fields, std::vector<std::string> missing_keys)
{
	std::string pathToCreate = apply_fields(fields, missing_keys);
	
}

// MAIN REGEX FUNCTIONS

std::string TemplatePath::_get_clean_definition(const std::string definition) {

	std::regex pattern("[{]");
	std::regex pattern2("[}]");

	std::string tmp2 = removePatternInString(definition, "[", "");
	tmp2 = removePatternInString(tmp2, "]", "");

	std::string tmp;
	std::string result;

	std::regex_replace(std::back_inserter(tmp), tmp2.begin(), tmp2.end(), pattern, "%(");
	std::regex_replace(std::back_inserter(result), tmp.begin(), tmp.end(), pattern2, ")");

	return result;
}


std::vector<std::string> TemplatePath::_get_definition_variations(const std::string definition) {
	
	std::vector<std::string> variants;

	for (const std::string& variant : _generateVariants(definition)) {
		variants.push_back(_get_clean_definition(variant));
	}
	return variants;
}


std::string TemplatePath::_get_pattern_definition(const std::string definition) {

	std::regex patternPadd("\\{SEQ\\}");
	std::regex pattern("\\{([^\\}]*)\\}");
    std::string remplacement = "(\\w+)";
    std::string remplPadding = "(\\W+)";

	std::string clean_def = std::regex_replace(definition, patternPadd, remplPadding);
    std::string result = std::regex_replace(clean_def, pattern, remplacement);

	return result;
}


std::vector<std::string> TemplatePath::_get_static_token() const
{
	// Get non-token element from definition
	// "C\{dir}\nuke\{Shot}-{Task}-base-v{version}.nk"
	// :return: [list] ["\nuke\", "-base-v", ".nk"]

	std::regex rgx("\\\\?\\{[^\\}]*\\}");
	std::vector<std::string> result;

	std::sregex_token_iterator current_match(this->_orig_definition.begin(), this->_orig_definition.end(), rgx, -1);
	std::sregex_token_iterator last_match;

	// Iterer sur tous les matches et ajouter les resultats a la liste
	for (; current_match != last_match; ++current_match) {
		std::string s = *current_match;
		// Supprime les caracteres vides
		s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
		if (!s.empty()) {
			result.push_back(s);
		}
	}

	return result;
}


std::vector<std::string> TemplatePath::_get_ordered_keys() const
{
	std::regex re("\\{(.*?)\\}");
	std::vector<std::string> matches;

	std::sregex_iterator next(this->_orig_definition.begin(), this->_orig_definition.end(), re);
	std::sregex_iterator end;

	while (next != end) {
		std::smatch match = *next;
		matches.push_back(match.str(1));
		next++;
	}

	return matches;
}


std::map<std::string, TemplateKey*> TemplatePath::_keys_from_origin_definition()
{
	std::regex re("\\{(.*?)\\}");
	return _sub_keys_from_definition(this->_orig_definition, re);
}


std::map<std::string, TemplateKey*> TemplatePath::_keys_from_definition(std::string definition)
{
    std::regex re("%\\(([^)]+)\\)");
	return _sub_keys_from_definition(definition, re);
}


std::vector<std::string> TemplatePath::getTokensFromPath(std::string path) {

	std::vector<std::string> words;
	std::smatch match;

	std::string::const_iterator searchStart(path.cbegin());
	while (std::regex_search(searchStart, path.cend(), match, std::regex(R"(\%\((\w+)\))")))
	{
		if (match.size() > 1)
		{
			words.push_back(match[1].str());
		}
		searchStart = match.suffix().first;
	}

	return words;
}


std::vector<std::string> TemplatePath::_generateVariants(const std::string& definition) {
    std::vector<std::string> variants;
    std::regex pattern("\\[([^\\[\\]]+)\\]");

    std::smatch match;
    if (std::regex_search(definition, match, pattern)) {
        std::string before = match.prefix();
        std::string inside = match[1].str();
        std::string after = match.suffix();

        std::vector<std::string> recursiveVariants = _generateVariants(after);
        for (const std::string& recursiveVariant : recursiveVariants) {
            variants.push_back(before + inside + recursiveVariant);
            variants.push_back(before + recursiveVariant);
        }
    } else {
        variants.push_back(definition);
    }

    return variants;
}


// PRIVATE FUNCTIONS

int TemplatePath::_getDefinitionFromFields(std::map<std::string, std::string> fields)
{
	int variant_index = -1;
	for (const std::string& definaaition : this->_definition_variations) {
		variant_index ++;
		std::map<std::string, TemplateKey*> def_keys = _keys_from_definition(definaaition);
		int size = _missing_key_from_field(def_keys, fields).size();
		if (size == 0){ // no missing key find == good template
			return variant_index;
		}
    }
	return -1;
}


std::vector<std::string> TemplatePath::_missing_key_from_field(std::map<std::string, TemplateKey*> keys, std::map<std::string, std::string> fields)
{
	std::vector<std::string> _missing_keys;

	for (const auto& field : keys) {
        if (fields.count(field.first) == 0) {
			_missing_keys.push_back(field.first);
        }
    }
	return _missing_keys;
}


std::string TemplatePath::_getValueFromKeyObject(std::string tokenKey, std::string fieldValue)
{
	// TODO si cle existe pas dans field Input mais default value

	std::string value;

	// Recuperer le pointeur de la valeur
	auto _key_from_token = this->_all_keys.find(tokenKey);
	TemplateKey* tkPtr = _key_from_token->second; 

	// Is missing tkPtr ? 
	if (tkPtr == nullptr) {}
	else{}

	if (StringTemplateKey* d1 = dynamic_cast<StringTemplateKey*>(tkPtr)) {
		d1->setValue(fieldValue);
		value = d1->getValue();
	} else if (IntegerTemplateKey* d2 = dynamic_cast<IntegerTemplateKey*>(tkPtr)) {
		d2->setValue(fieldValue);
		value = d2->getValue();
	} else if (SequenceTemplateKey* d2 = dynamic_cast<SequenceTemplateKey*>(tkPtr)) {
		d2->setValue(fieldValue);
		value = d2->getValue();
	} else {
		value = "Unknow";
	}

	return value;
}


std::string TemplatePath::_apply_fields_to_definition(std::string definition, std::map<std::string, std::string> fields, std::vector<std::string> missing_keys)
{
	std::string result = definition;
	std::string::size_type pos = 0;
	std::vector<std::string> fieldsMissing;

	while ((pos = result.find("%(", pos)) != std::string::npos) {
		std::string::size_type end_pos = result.find(")", pos);

		if (end_pos != std::string::npos) {
			std::string value;
			std::string key = result.substr(pos + 2, end_pos - pos - 2);
			std::string oldSubstring = "%(" + key +")";
			auto it = fields.find(key);
			bool isMissingKey = false;

			// If find key from definition inside fields parameter
			if (it != fields.end()) { 

				// Check if key is part of missing_keys parameter
				for (const auto& str : missing_keys) {
					if (str == key) {
						isMissingKey = true;
						break;
					}
				}
				// If not key in missing_fields parameter 
				if(!isMissingKey){
					value = _getValueFromKeyObject(it->first, it->second);
				}else{
					value = it->second;
				}
				result = removePatternInString(result, oldSubstring, value);
				pos += it->second.length();
			}

			// Key not find in fields
			else {
				pos = end_pos + 1;
				value = _getValueFromKeyObject(key, "");
				// If default value inside Key Template
				if(!value.empty()){
					size_t _pos = result.find(oldSubstring);
					if (_pos != std::string::npos) { 
						result = removePatternInString(result, oldSubstring, value);
					}
				}
				// If anything find
				else{
					fieldsMissing.push_back(key);
				}
			}
		}
		else {
			// Parenthese fermante manquante
			pos = pos + 2;
		}
	}
	// missings multiple fields ?
	std::cout << "fieldsMissing   "<< fieldsMissing.size() << std::endl;
	std::cout << "result   "<< result << std::endl;
	if(fieldsMissing.size() > 0){ 
		throw TankApplyFieldsTemplateError(getName(), getDefinition(), fieldsMissing);
	}
	return stringPathJoin(this->_root_path, result, "", "");
}


std::string TemplatePath::_get_longest_variant(std::vector<std::string> definition_variants)
{
	std::string def_variant = definition_variants[0];

	for (const std::string &chaine : definition_variants) {
        if (chaine.length() > def_variant.length()) {
            def_variant = chaine;
        }
    }
	return def_variant;
}


std::map<std::string, TemplateKey*> TemplatePath::_sub_keys_from_definition(std::string definition, std::regex re)
{
	std::map<std::string, TemplateKey*> keys;
	std::sregex_iterator next(definition.begin(), definition.end(), re);
	std::sregex_iterator end;

	while (next != end) {

		std::smatch match = *next;
		std::string key_name = match.str(1);

		for (auto const& pair : this->_all_keys) {
        	if(key_name == pair.first){
				keys.insert(std::make_pair(key_name, pair.second));
			}
    	}
		next++;
	}

	return keys;
}

