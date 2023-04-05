#include <map>
#include <string>
#include <vector>

#include "tank_obj.h"

// to compile
// g++ *.cpp -o hello

// "{'keys': {'Root': {'type': 'str'}, 'Shot': {'type': 'str'}, 'Task': {'type': 'str'}, 'dir': {'type': 'str'}, 'version': {'type': 'int'}}, 
// 'paths': {'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"
// g++ *.cpp -o hello -I"D:\Desk\python\Tank\lib\rapidjson\include" & hello.exe "{'keys': {'Root': {'type': 'str'}, 'Shot': {'type': 'str'}, 'Task': {'type': 'str'}, 'dir': {'type': 'str'}, 'version': {'type': 'int'}}, 'paths': {'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}"
// g++ *.cpp -o hello -I"D:\\Desk\\python\\Tank\\lib\\json\\include" & hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}'}"
// g++ *.cpp -o hello -I"D:\\Desk\\python\\Tank\\lib\\yaml-cpp\\include" & hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}'}"
// hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}"


int main(int argc, char *argv[]) {
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

	std::string keys  = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str'}, 'version' : {'type': 'int', 'default': '1'}, 'test' : {'type': 'str', 'default': 'aa'}}";
	std::string paths = "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}}";

	/*    
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> pathsDict;
	pathsDict = generateKeysDictionnaryFromString(keys);

	for (const auto& key : pathsDict["keys"]) {
        std::cout << key.first << ":" << std::endl;
        for (const auto& subkey : key.second) {
            std::cout << "    " << subkey.first << ":" << subkey.second << std::endl;
        }
	}
	*/
	//for (auto a = tank.templates.begin(); a != tank.templates.end(); ++a) {
	//	std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	//}

    // créer le dictionnaire "keys"

	//std::string keys = argv[1];
    //Templates templatesTest(pathsdict, keydict);
	//for (auto a = templatesTest.templates.begin(); a != templatesTest.templates.end(); ++a) {
	//	std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	//}

	Tank tank = Tank(paths, keys);
    std::map<std::string, Template> templatesObj = tank.templates;
    
    for (auto a = tank.templates.begin(); a != tank.templates.end(); ++a) {
		std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	}
    
    //if (argc>2) return 0;

    return 1;

}

