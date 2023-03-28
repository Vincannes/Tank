#include <map>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>

#include "utils.h"
#include "template_keys.h"
#include "template_obj.h"
#include "templates_obj.h"
#include "conform_path.h"



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
	/*
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
	*/

}



int main() {

	std::cout << "" << std::endl;

	std::map<std::string, Template> templates;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	std::map<std::string, std::map<std::string, std::string>> pathsdict;

	keydict["keys"]["Root"]["type"] = "str";
	keydict["keys"]["Shot"]["type"] = "str";
	keydict["keys"]["Task"]["type"] = "str";
	keydict["keys"]["dir"]["type"] = "str";
	keydict["keys"]["version"]["type"] = "str";
	keydict["keys"]["version"]["default"] = "1";

	pathsdict["paths"]["rootDir"]     = "C";
	pathsdict["paths"]["desk"]        = "@rootDir\\{dir}";
	pathsdict["paths"]["nuke"]        = "@test\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	pathsdict["paths"]["test"]        = "@desk\\{Shot}\\{Task}";
	pathsdict["paths"]["test_diff"]   = "@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk";


	Templates templatesObj(pathsdict, keydict);
	
	for (auto a = templatesObj.templates.begin(); a != templatesObj.templates.end(); ++a) {
		std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	}

	std::cout << "templatesObj.templa.getName()" << std::endl;
	auto it = templatesObj.templates.find("nuke");
	Template& x = it->second;
	std::string an = x.getName();
	std::cout << an << std::endl;
}


/*
	_templates = {}
	template_paths = self.__template_dict.get('paths')
	template_keys = self.get_keys(self.__template_dict.get("keys"))

	for name, definitions in template_paths.items() :
		print(definitions)
		path_definition = self._conform_path.get_definitions_path(definitions)
		_templates[name] = Template(name, template_keys, path_definition)
	*/