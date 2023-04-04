#include "tank.h"
#include "utils.h"
#include "template_obj.h"
#include "templates_obj.h"

Tank::Tank(std::string _templatePathsString, std::string _templateKeysString) 
{
    this->_templatePathsString = _templatePathsString;
    this->pathsdict            = generatePathsDictionnaryFromString(this->_templatePathsString);
    this->keydict              = generateKeysDictionnaryFromString(this->_templateKeysString);
    Templates templateObj      = createTemplates(this->pathsdict, this->keydict);
    this->templates            = templateObj.templates;
}

Templates Tank::createTemplates(std::map<std::string, std::map<std::string, std::string>> pathsdict, 
                                std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict)
{
    Templates templatesObj(pathsdict, keydict);
    return templatesObj;
}

/*
std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> Tank::getKeysFromDict()
{
    std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
    keydict["keys"]["Root"]["type"] = "str";
	keydict["keys"]["Shot"]["type"] = "str";
	keydict["keys"]["Task"]["type"] = "str";
	keydict["keys"]["dir"]["type"] = "str";
	keydict["keys"]["version"]["type"] = "str";
	keydict["keys"]["version"]["default"] = "1";
    return keydict;
}


std::map<std::string, std::map<std::string, std::string>> Tank::getPathsFromDict()
{
    std::map<std::string, std::map<std::string, std::string>> pathsdict;
    pathsdict["paths"]["rootDir"]     = "C";
	pathsdict["paths"]["desk"]        = "@rootDir\\{dir}";
	pathsdict["paths"]["nuke"]        = "@test\\nuke\\{Shot}-{Task}-base-v{version}.nk";
	pathsdict["paths"]["test"]        = "@desk\\{Shot}\\{Task}";
	pathsdict["paths"]["test_diff"]   = "@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk";
    return pathsdict;
}
*/
