#include <map>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
#include "template_keys.h"
#include "template_obj.h"
#include "templates_obj.h"
#include <unordered_map>

//utilise <unordered_map> si pas besoin d ordre


void testKeys() {

	StringKey key1{ "Shot", "vae" };
	IntegerKey key2{ "Task", "azz" };
	IntegerKey key3{ "Taskasasas", "" };

	std::cout << key1.getName() << std::endl;
	std::cout << key1.getDefault() << std::endl;
	std::cout << key1.getType() << std::endl;

	std::cout << key2.getName() << std::endl;
	std::cout << key2.getDefault() << std::endl;
	std::cout << key2.getType() << std::endl;

	std::cout << key3.getName() << std::endl;
	std::cout << key3.getDefault() << std::endl;
}

void testTemplate() {
	
	std::string path = "C\\Test\\sh010\\cmp\\nuke\\sh010-cmp-base-v2.nk";

	std::string definition = "C\\{dir}\\{Shot}\\{Task}\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	std::vector<StringKey> keys = { StringKey("Root", ""),StringKey("Shot", ""), StringKey("dir", ""), StringKey("Task", "") };
	Template template1 = Template("test", keys, definition);

	std::cout << "Template Name : " << template1.getName() << std::endl;
	std::cout << "Full path with token : " << template1.getDefinition() << std::endl;

	for (const auto& s : template1.getStaticTokens()) {
		//std::cout << s << std::endl;
	}
	for (const auto& s : template1.getOrderedKeys()) {
		//std::cout << s << std::endl;
	}
	std::map<std::string, std::string> fields = template1.getFields(path);
	std::cout << "template1.apply_fields : " << template1.apply_fields(fields) << std::endl;

	std::cout << "" << std::endl;
	for (const auto& elem : fields)
	{
		std::cout << elem.first << " " << elem.second << std::endl;
	}

}

void listOfALlKeys() {


	std::string path = "C\\Test\\sh010\\cmp\\nuke\\sh010-cmp-base-v2.nk";

	std::vector <TemplateKey > keysList{};
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	std::map<std::string, std::map<std::string, std::string>> pathsdict;

	keydict["keys"]["Root"]["type"] = "str";
	keydict["keys"]["Shot"]["type"] = "str";
	keydict["keys"]["Task"]["type"] = "str";
	keydict["keys"]["dir"]["type"] = "str";
	keydict["keys"]["version"]["type"] = "str";
	keydict["keys"]["version"]["default"] = "1";

	for (auto outerIt = keydict["keys"].begin(); outerIt != keydict["keys"].end(); ++outerIt) {

		bool isType;
		bool isDefault;
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string name = outerIt->first;

		for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt) {
			std::string key = innerIt->first;
			std::string value = innerIt->second;
			if (key == "type") {
				isType = true;
				isTypeValue = value;
			}
			else if (key == "default") {
				isDefault = true;
				isDefaultValue = value;
			}
		}
		if (isTypeValue == "str") {
			StringKey s1(name, isDefaultValue);
			keysList.push_back(s1);
		}
		if (isTypeValue == "int") {
			IntegerKey t1(name, isDefaultValue);
			keysList.push_back(t1);
		}
	}

	for (const auto& a : keysList) {
		std::cout << a.getName() << std::endl;
		std::cout << a.getDefault() << std::endl;
	}



}



int main() {

	std::cout << "" << std::endl;

	std::string path = "C\\Test\\sh010\\cmp\\nuke\\sh010-cmp-base-v2.nk";

	std::vector <TemplateKey > keysList{};
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	std::map<std::string, std::map<std::string, std::string>> pathsdict;

	keydict["keys"]["Root"]["type"] = "str";
	keydict["keys"]["Shot"]["type"] = "str";
	keydict["keys"]["Task"]["type"] = "str";
	keydict["keys"]["dir"]["type"] = "str";
	keydict["keys"]["version"]["type"] = "str";
	keydict["keys"]["version"]["default"] = "1";

	for (auto outerIt = keydict["keys"].begin(); outerIt != keydict["keys"].end(); ++outerIt) {

		bool isType;
		bool isDefault;
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string name = outerIt->first;

		for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt) {
			std::string key = innerIt->first;
			std::string value = innerIt->second;
			if (key == "type") {
				isType = true;
				isTypeValue = value;
			}
			else if (key == "default") {
				isDefault = true;
				isDefaultValue = value;
			}
		}
		if(isTypeValue == "str"){
			StringKey s1(name, isDefaultValue);
			keysList.push_back(s1);
		}
		if (isTypeValue == "int") {
			IntegerKey t1(name, isDefaultValue);
			keysList.push_back(t1);
		}
	}

	for (const auto& a : keysList) {
		std::cout << a.getName() << std::endl;
		std::cout << a.getDefault() << std::endl;
	}



	/*
	pathsdict["paths"]["desk"]        = "@rootDir\\{dir}";
	pathsdict["paths"]["nuke"]        = "@test\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	pathsdict["paths"]["rootDir"]     = "C";
	pathsdict["paths"]["test"]        = "@desk\\{Shot}\\{Task}";
	pathsdict["paths"]["test_diff"]   = "@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	*/

}


