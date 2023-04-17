#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // Pour setw

#include "template_obj.h"
#include "tank_obj.h"

// to compile
// g++ *.cpp -o hello

// "{'keys': {'Root': {'type': 'str'}, 'Shot': {'type': 'str'}, 'Task': {'type': 'str'}, 'dir': {'type': 'str'}, 'version': {'type': 'int'}}, 
// 'paths': {'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"
// g++ *.cpp -o hello -I"D:\Desk\python\Tank\lib\rapidjson\include" & hello.exe "{'keys': {'Root': {'type': 'str'}, 'Shot': {'type': 'str'}, 'Task': {'type': 'str'}, 'dir': {'type': 'str'}, 'version': {'type': 'int'}}, 'paths': {'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"
// g++ *.cpp -o hello -I"D:\\Desk\\python\\Tank\\lib\\json\\include" & hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}'}"
// g++ *.cpp -o hello -I"D:\\Desk\\python\\Tank\\lib\\yaml-cpp\\include" & hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}'}"
// hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}"


int main() {
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	std::map<std::string, std::map<std::string, std::string>> pathsdict;
	std::map<std::string, std::string> fields;
	fields["dir"] = "test";
	fields["Shot"] = "sh_020";
	// fields["Task"] = "cmp";
	fields["version"] = "1";
	// fields["Root"] = "bleu";

	keydict["keys"]["Root"]["type"] = "str";
	keydict["keys"]["Shot"]["type"] = "str";
	keydict["keys"]["Task"]["type"] = "str";
	keydict["keys"]["dir"]["type"] = "str";
	keydict["keys"]["version"]["type"] = "int";
	keydict["keys"]["version"]["default"] = "1";
	keydict["keys"]["version"]["format_spec"] = "03";

	pathsdict["paths"]["rootDir"]     = "C";
	pathsdict["paths"]["desk"]        = "@rootDir\\{dir}";
	pathsdict["paths"]["nuke"]        = "@test\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	pathsdict["paths"]["test"]        = "@desk\\{Shot}\\{Task}";
	pathsdict["paths"]["test_diff"]   = "@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk";

	std::string keys  = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str'}, 'version' : {'type': 'int', 'default': '1', 'format_spec: '03'}, 'Task' : {'type': 'str', 'default': 'aa'}";
	std::string paths = "{'rootDir': 'D:\\Desk\\python\\Tank\\tests\\project', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}";

	std::map<std::string, std::map<std::string, std::string>> pathsDict;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keysDict;
	// pathsDict = generatePathsDictionnaryFromString(paths);
	// keysDict  = generateKeysDictionnaryFromString(keys);

	// for (const auto& key : pathsDict["paths"]) {
    //     std::cout << key.first << ":" << key.second << std::endl;
	// }
	
	// std::cout << " " << std::endl;

	// for (const auto& key : keysDict["keys"]) {
    //     std::cout << key.first << ":" << std::endl;
    //     for (const auto& subkey : key.second) {
    //         std::cout << "    " << subkey.first << ":" << subkey.second << std::endl;
    //     }
	// }

	std::cout << "    " << std::endl;
	std::string name = "version";
	std::string defaultV = "1";
	std::string format_spec = "03";
	IntegerTemplateKey intKey(name, defaultV, format_spec);

    // std::cout << intKey.getValue() << std::endl;
    // intKey.setValue("2");
    // std::cout << intKey.getValue() << std::endl;
	
	Tank tank_test(paths, keys);

	TemplatePath nuke_tpl = tank_test.getTemplates()["nuke"];
	std::string testpath = nuke_tpl.apply_fields(fields);
	std::cout << testpath << std::endl;
	// std::string testpathNot = "D:\\Desk\\python\\Tank\\tests\\project\\test\\sh_010\\cmp\\sh_010-cmp-base-v1.nk";

	// std::vector<std::string> test = nuke_tpl.missingKeys(fields);
	// for(int i=0; i<test.size(); i++){
	// 	std::cout << test[i] << std::endl;
	// }


	// std::string path = "D:\\Desk\\python\\Tank\\tests\\project\\test\\sh_010\\cmp\\nuke\\sh_010-cmp-base-v1.nk";
	// std::string pattern_test = "D:\\Desk\\python\\Tank\\tests\\project\\test\\sh_020\\.*\\nuke\\sh_020-.*-base-v1.nk";

	// std::cout << "D:\\Desk\\python\\Tank\\tests\\project" << std::endl;
	// std::cout << pattern_test << std::endl;
	// std::vector<std::string> abspathsTest2 = listFilesFromPathPattern("D:\\Desk\\python\\Tank\\tests\\project", pattern_test);

	// std::vector<std::string> abspathsTest = tank_test.getAbstractPathsFromTemplate(nuke_tpl, fields);
	// for(int i=0; i<abspathsTest.size(); i++){
	// 	std::cout << "match  " << abspathsTest[i] << std::endl;
	// }
	// std::cout << "" << std::endl;
    
	// std::string patternStr = "D:\\\\Desk\\\\python\\\\Tank\\\\tests\\\\project\\\\test\\\\.*\\\\cmp\\\\nuke\\\\.*-cmp-base-v1.nk";
    // std::regex regexPattern(patternStr);

    // std::cout << "path: " << path << std::endl;
    // std::cout << "patternStr: " << patternStr << std::endl;
    // std::cout << "" << std::endl;

    // if (std::regex_match(path, regexPattern))
    // {
    //     std::cout << "Match: " << path << std::endl;
    // }
    // else
    // {
    //     std::cout << "No Match" << std::endl;
    // }


	// TemplatePath aTesty = tank_test.templateFromPath(testpath);
	// std::cout << aTesty.getName() << std::endl;
	// TemplatePath aTestya = tank_test.templateFromPath(testpathNot);
	// std::cout << aTestya.getName() << std::endl;
	// TemplatePath aTestyaa = tank_test.templateFromPath(testpathGood);
	// std::cout << aTestyaa.getName() << std::endl;

	// std::cout << nuke_tpl.validate(testpathNot) << std::endl;
	
	// std::cout << nuke_tpl.getName() << " " << nuke_tpl.getDefinition() << std::endl;
	// tank_test.getAbstractPathsFromTemplate()

    // créer le dictionnaire "keys"

	//std::string keys = argv[1];
    //Templates templatesTest(pathsdict, keydict);
	//for (auto a = templatesTest.templates.begin(); a != templatesTest.templates.end(); ++a) {
	//	std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	//}
    
    //if (argc>2) return 0;

    return 1;

}

