#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // Pour setw

#include "template_obj.h"
#include "tank_obj.h"



int main() {
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	std::map<std::string, std::map<std::string, std::string>> pathsdict;
	std::map<std::string, std::string> fields;
	fields["dir"] = "test";
	fields["Shot"] = "sh_020";
	fields["Task"] = "cmp";
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
	pathsDict = generatePathsDictionnaryFromString(paths);
	keysDict  = generateKeysDictionnaryFromString(keys);

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
	// std::cout << "    " << std::endl;


	// std::string name = "version";
	// std::string defaultV = "1";
	// std::string format_spec = "03";
	// IntegerTemplateKey intKey(name, defaultV, format_spec);

    // std::cout << intKey.getValue() << std::endl;
    // intKey.setValue("2");
    // std::cout << intKey.getValue() << std::endl;
	
	Tank tank_test(paths, keys);
	std::map<std::string, TemplatePath> templates =  tank_test.getTemplates();

	for (const auto& paire : templates) {
		const std::string& cle = paire.first;
        const std::string& valeur = paire.second.getDefinition();
		// std::cout << cle << " : " << valeur << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "applyfields" << std::endl;
	std::cout << "" << std::endl;
	TemplatePath nuke_tpl = templates["nuke"];
	std::string testpath = nuke_tpl.apply_fields(fields);
	std::cout << "" << std::endl;
	std::cout << "testpath" << std::endl;
	std::cout << testpath << std::endl;
	// std::cout << "definition" << std::endl;
	// std::cout << nuke_tpl.getDefinition() << std::endl;

	// std::cout << "" << std::endl;
	// std::vector<std::string> test = nuke_tpl.missingKeys(fields);
	// std::cout << "Missing keys" << std::endl;
	// for(int i=0; i<test.size(); i++){
	// 	std::cout << test[i] << std::endl;
	// }


	// std::string path = "D:/Desk/python/Tank/tests/project/test/sh_010/cmp/nuke/sh_010-cmp-base-v1.nk";
	
	// std::cout << "" << std::endl;
	// std::cout << "Get Fields" << std::endl;
	// std::map<std::string, std::string> get_fields = nuke_tpl.getFields(path);
	// for (const auto& paire : get_fields) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	


	// std::cout << "D:\\Desk\\python\\Tank\\tests\\project" << std::endl;
	// std::cout << pattern_test << std::endl;
	// std::vector<std::string> abspathsTest2 = listFilesFromPathPattern("D:\\Desk\\python\\Tank\\tests\\project", pattern_test);

	// std::cout << "" << std::endl;
	// std::vector<std::string> abspathsTest = tank_test.getAbstractPathsFromTemplate(nuke_tpl, fields);
	// std::cout << "" << std::endl;
	// for(int i=0; i<abspathsTest.size(); i++){
	// 	std::cout << "match  " << abspathsTest[i] << std::endl;
	// }
	// std::cout << "" << std::endl;
    

	// TemplatePath aTesty = tank_test.templateFromPath(testpath);
	// std::cout << testpath << std::endl;
	// std::cout << aTesty.getName() << std::endl;
	// std::cout << aTesty.getDefinition() << std::endl;
	// // std::cout << aTesty.getOrderedKeys() << std::endl;
	// std::cout << " " <<std::endl;

	// std::vector<std::string> etfiel = aTesty.getStaticTokens();
	// for (int i=0; i<etfiel.size(); i++) {
    //     std::cout << etfiel[i] << std::endl ;
    // }
	// std::cout << " " <<std::endl;
	// for (const auto& paire : aTesty.getFields(testpath)) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	// TemplatePath aTestya = tank_test.templateFromPath(testpathNot);
	// std::cout << aTestya.getName() << std::endl;
	// TemplatePath aTestyaa = tank_test.templateFromPath(testpathGood);
	// std::cout << aTestyaa.getName() << std::endl;

	// std::cout << nuke_tpl.validate(testpathNot) << std::endl;
	
	// std::cout << nuke_tpl.getName() << " " << nuke_tpl.getDefinition() << std::endl;

    // créer le dictionnaire "keys"
	//std::string keys = argv[1];
    //Templates templatesTest(pathsdict, keydict);
	//for (auto a = templatesTest.templates.begin(); a != templatesTest.templates.end(); ++a) {
	//	std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	//}
    
    //if (argc>2) return 0;

    return 1;

}

