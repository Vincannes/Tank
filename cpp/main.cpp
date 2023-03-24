#include <map>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
#include "template_keys.h"
#include "template_obj.h"
#include <unordered_map>

//utilise <unordered_map> si pas besoin d ordre


void dictionnary() {

	std::map<std::string, int> mp;
	mp["a"] = 58;
	mp["b"] = 12;
	mp["c"] = 73;

	// Supprimer
	mp.erase("a");

	// Acces
	mp.find("c");

	for (const auto& it : mp) {

		std::cout << it.first << " : " << it.second << std::endl;

	}

	std::cout << "" << std::endl;

}

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

void apply_fields_test() {

	std::map<std::string, std::string> dictionnaire;
	dictionnaire["dir"] = "Test";
	dictionnaire["Shot"] = "sh010";
	dictionnaire["Task"] = "cmp";
	dictionnaire["version"] = "2";

	std::string path = "D:\\Desk\\python\\Tank\\config\\templates.yml";
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
	std::cout << "template1.apply_fields : " << template1.apply_fields(dictionnaire) << std::endl;

}

int main() {

	std::cout << "" << std::endl;

	std::string definition = "C\\{dir}\\{Shot}\\{Task}\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	std::vector<StringKey> keys = {StringKey("Root", ""),StringKey("Shot", ""), StringKey("dir", ""), StringKey("Task", "")};
	Template template1 = Template("test", keys, definition);

	std::string path = "C\\Test\\sh010\\cmp\\nuke\\sh010-cmp-base-v2.nk";

	std::cout << "Template Name : " << template1.getName() << std::endl;
	std::cout << "Full path with token : " << template1.getDefinition() << std::endl;

	for (const auto& s : template1.getStaticTokens()) {
		//std::cout << s << std::endl;
	}
	for (const auto& s : template1.getOrderedKeys()) {
		//std::cout << s << std::endl;
	}
	std::map<std::string, std::string> fields = template1.getFields(path);
	//std::cout << "template1.apply_fields : " << template1.apply_fields(fields) << std::endl;

	std::cout << "" << std::endl;
	for (const auto& elem : fields)
	{
		std::cout << elem.first << " " << elem.second << std::endl;
	}
}


