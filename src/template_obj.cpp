#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "utils.h"
#include "template_obj.h"
#include "template_keys.h"

Template::Template(std::string name, std::vector<TemplateKey> keys, std::string definition)
{
	this->_name = name;
	this->_keys = keys;
	this->_orig_definition = definition;
	this->_definition = _get_clean_definition(definition);

}

std::string Template::getName() const
{
	return this -> _name;
}

std::string Template::getDefinition()
{
	return this->_definition;
}

std::vector<std::string> Template::getStaticTokens()
{
	return _get_static_token(this->_orig_definition);
}

std::vector<std::string> Template::getOrderedKeys() {

	return _get_ordered_keys(this->_orig_definition);
}


// MAIN FUNCTIONS

std::string Template::apply_fields(std::map<std::string, std::string> fields)
{
	std::string result = this->_definition;
	std::string::size_type pos = 0;

	while ((pos = result.find("%(", pos)) != std::string::npos) {
		std::string::size_type end_pos = result.find(')', pos);
		if (end_pos != std::string::npos) {
			std::string key = result.substr(pos + 2, end_pos - pos - 2);
			auto it = fields.find(key);
			if (it != fields.end()) {
				result.replace(pos, end_pos - pos + 1, it->second);
				pos += it->second.length();
			}
			else {
				// La clé n'a pas été trouvée dans le dictionnaire
				pos = end_pos + 1;
			}
		}
		else {
			// Parenthèse fermante manquante
			pos = pos + 2;
		}
	}

	return result;
}


std::map<std::string, std::string> Template::getFields(std::string path)
{
	std::map<std::string, std::string> fields = {};

	// verifier si la longueur du path est le meme que _definition 
	std::vector<std::string> path_splited = splitPath(path);
	std::vector<std::string> definition_splited = splitPath(this->_definition);

	// return dictionnaire vide si longueurs differents
	if (path_splited.size() != definition_splited.size()) {
		std::cout << "No fields find for this template " << std::endl;
		return fields;
	}

	std::vector<std::string> satic_token = getStaticTokens();

	// from satic_token list {"item", "-", "item"}, place "-" at the end of the list
	if (std::find(satic_token.begin(), satic_token.end(), "-") != satic_token.end()) {
		auto itr = std::find(satic_token.begin(), satic_token.end(), "-");
		satic_token.erase(itr);
		satic_token.push_back("-");
	}

	// Create REGEX pour separer les tokens a partir de chaque non Token dans le path
	std::string static_parse = joinListWithSeparator(satic_token, '|'); // move - to the end

	for (int i = 0; i < path_splited.size(); i++) {

		int is_token = std::regex_search(definition_splited[i], std::regex("\\%\\(.*\\)"));
		if (is_token) {

			std::vector<std::string> tokens = getTokensFromPath(definition_splited[i]);

			// Si un plusieurs patterns match
			if (tokens.size() > 1) {

				for (const auto& token_name : tokens)
				{
					std::regex rgx(static_parse);
					std::sregex_token_iterator iterDefin(definition_splited[i].begin(), definition_splited[i].end(), rgx, -1);
					std::sregex_token_iterator iterPath(path_splited[i].begin(), path_splited[i].end(), rgx, -1);

					std::vector<std::string> token_def(iterDefin, {});
					std::vector<std::string> tokens_val(iterPath, {});

					size_t sizeDefinition = token_def.size();
					size_t sizePath = tokens_val.size();

					if (sizePath != sizeDefinition) continue;

					for (int token_index = 0; token_index < sizePath; token_index++) {
						std::string token = token_def[token_index];
						std::string value = tokens_val[token_index];
						std::cout << "value " << value << std::endl;
						// si value est dans list de static Tokens on passe
						if (std::find(token_def.begin(), token_def.end(), value) != token_def.end()) {
							continue;
						}

						std::vector<std::string> valueFromPath = getTokensFromPath(token);
						for (const auto& token_name : valueFromPath) { // Verifier si plusieurs token trouve
							fields[token_name] = value;
						}

					}
				}
			}

			// Si un seul pattern match
			else if (tokens.size() == 1) {
				std::string token_name = tokens[0];
				std::string value = path_splited[i];
				//std::cout << "token_name  " << token_name << " value : " << value << std::endl;
				fields[token_name] = value;
			}
		}
	}

	return fields;
}


// MAIN REGEX FUNCTIONS

std::string Template::_get_clean_definition(const std::string definition) {

	std::regex pattern("[{]");
	std::regex pattern2("[}]");

	std::string tmp;
	std::string result;

	std::regex_replace(std::back_inserter(tmp), definition.begin(), definition.end(), pattern, "%(");
	std::regex_replace(std::back_inserter(result), tmp.begin(), tmp.end(), pattern2, ")");
	
	return result;
}


std::vector<std::string> Template::_get_static_token(const std::string definition) {

	std::regex rgx("\\\\?\\{[^\\}]*\\}");
	std::vector<std::string> result;

	std::sregex_token_iterator current_match(definition.begin(), definition.end(), rgx, -1);
	std::sregex_token_iterator last_match;

	// Itérer sur tous les matches et ajouter les résultats à la liste
	for (; current_match != last_match; ++current_match) {
		std::string s = *current_match;
		// Supprime les caractères vides
		s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
		if (!s.empty()) {
			result.push_back(s);
		}
	}

	return result;
}


std::vector<std::string> Template::_get_ordered_keys(const std::string definition) {

	std::regex re("\\{(.*?)\\}");
	std::vector<std::string> matches;

	std::sregex_iterator next(definition.begin(), definition.end(), re);
	std::sregex_iterator end;

	while (next != end) {
		std::smatch match = *next;
		matches.push_back(match.str(1));
		next++;
	}

	return matches;
}


std::vector<std::string> Template::getTokensFromPath(std::string path) {

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
