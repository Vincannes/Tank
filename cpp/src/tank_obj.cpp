#include "tank_obj.h"
#include "utils.h"
#include "template_obj.h"
#include "templates_obj.h"

Tank::Tank(std::string _templatePathsString, std::string _templateKeysString) 
{
    this->_templatePathsString = _templatePathsString;
    this->_templateKeysString  = _templateKeysString;
    this->pathsdict            = generatePathsDictionnaryFromString(this->_templatePathsString);;
    this->keydict              = generateKeysDictionnaryFromString(this->_templateKeysString);
    Templates templateObj      = createTemplates(this->pathsdict, this->keydict);
    this->templates            = templateObj.getTemplates();
}

Templates Tank::createTemplates(std::map<std::string, std::map<std::string, std::string>> pathsdict, 
                                std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict)
{
    Templates templatesObj(pathsdict, keydict);
    return templatesObj;
}
