#include <map>
#include <iostream>
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "tank_obj.h"

std::map<std::string, std::map<std::string, std::string>> generateKeysDictionnaryFromString(std::string config_path){
	std::map<std::string, std::map<std::string, std::string>> result;

	YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& keysNode = config["keys"];

    for (const auto& keyNode : keysNode) {
        std::string keyName = keyNode.first.as<std::string>();

        if (keyNode.second.IsMap()) {

            for (const auto& element : keyNode.second) {
                std::string subKeyName = element.first.as<std::string>();
                std::string subKeyValue = "";

                if(subKeyName == "choices") {
                    const YAML::Node& choicesNode = element.second;
                    std::stringstream choicesString;
                    for (std::size_t i = 0; i < choicesNode.size(); ++i) {
                        choicesString << choicesNode[i].as<std::string>();
                        if (i < choicesNode.size() - 1) {
                            choicesString << ", ";
                        }
                    }
                    subKeyValue = choicesString.str();
                } else{
                    subKeyValue = element.second.as<std::string>();
                }
                result[keyName][subKeyName] = subKeyValue;
            }
        }
    }

	return result;
}

std::map<std::string, std::string> generatePathsDictionnaryFromString(std::string config_path){
    std::map<std::string, std::string> pathsDict;

	YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& pathsNodes = config["paths"];

    for (const auto& pathNode : pathsNodes) {
        std::string pathName = pathNode.first.as<std::string>();
        std::string path = pathNode.second.as<std::string>();
        pathsDict[pathName] = path;
    }

	return pathsDict;
}

std::map<std::string, std::string> generateStringsDictionnaryFromString(std::string config_path)
{
	std::map<std::string, std::string> stringsOutput;

    YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& pathsNodes = config["strings"];

    for (const auto& pathNode : pathsNodes) {
        std::string pathName = pathNode.first.as<std::string>();
        std::string path = pathNode.second.as<std::string>();
        stringsOutput[pathName] = path;
    }

    return stringsOutput;
}

void processNode(const YAML::Node& node, const std::string& indent = "") {
    if (node.IsScalar()) {
        // Afficher la valeur si le nœud est une valeur scalaire
        std::cout << indent << "Valeur : " << node.as<std::string>() << std::endl;
    } else if (node.IsMap()) {
        // Traiter chaque paire clé-valeur du nœud map
        for (const auto& pair : node) {
            std::cout << indent << "Cle : " << pair.first.as<std::string>() << std::endl;
            processNode(pair.second, indent + "  "); // Appel récursif pour traiter la valeur
        }
    } else if (node.IsSequence()) {
        // Traiter chaque élément de la séquence
        for (const auto& element : node) {
            processNode(element, indent + "- "); // Ajouter un préfixe "- " pour indiquer un élément de séquence
        }
    }
}

int main() {

	std::string root = "D:\\Desk\\python\\Projects\\Project3";
    std::string config_path = "D:\\Desk\\python\\Tank\\config\\templates.yml";
    
    std::map<std::string, std::map<std::string, std::string>> keysDict;
    std::map<std::string, std::string> pathsDict;
    std::map<std::string, std::string> stringsDict;

    keysDict = generateKeysDictionnaryFromString(config_path);
    pathsDict = generatePathsDictionnaryFromString(config_path);
    stringsDict = generateStringsDictionnaryFromString(config_path);

	std::cout << "Keys" << std::endl;
	for (const auto& key : keysDict) {
        // std::cout << key.first << ":" << std::endl;
        // for (const auto& subkey : key.second) {
        //     std::cout << "    " << subkey.first << ":" << subkey.second << std::endl;
        // }
	}

	std::cout << "" << std::endl;
	std::cout << "Paths" << std::endl;
    for (const auto& key : pathsDict) {
        // std::cout << key.first << " " << key.second << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "Strings" << std::endl;
    for (const auto& key : stringsDict) {
        // std::cout << key.first << " " << key.second << std::endl;
	}

    Tank tank_test(config_path, root);

    return 1;
}