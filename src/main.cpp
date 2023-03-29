#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

//#include "templates_obj.h"
using namespace rapidjson;

int main() {
	std::map<std::string, std::map<std::string, std::string>> templatePaths;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> templateKeys;
	//Templates templateObj(templatePaths, templateKeys);

    std::string path = "D:\\Desk\\python\\Tank\\config\\template.yaml";

    const char* json = "{\"project\":\"rapidjson\",\"stars\":\"10\"}";
    Document config;
    config.Parse(json);

    for (auto& m : config.GetObject()){
        std::cout << "m.name.GetStrin)" << std::endl;
        std::cout << m.name.GetString() << "   " << m.value.GetString() << std::endl;
    }
    std::cout << "end" << std::endl;
    /*
    // 2. Modify it by DOM.
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    config.Accept(writer);
    */
    // Output {"project":"rapidjson","stars":11}

    /*
    // Conversion du noeud YAML en dictionnaire
    std::map<std::string, std::string> dictionnaire = noeud.as<std::map<std::string, std::string>>();

    // Affichage du contenu du dictionnaire
    for (auto it = dictionnaire.begin(); it != dictionnaire.end(); ++it) {
        std::string cle = it->first;
        std::string valeur = it->second;
        std::cout << cle << "  " << valeur << std::endl;
    }*/

    return 1;

}

