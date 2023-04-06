#include <map>
#include <string>
#include "utils.h"
#include "template_obj.h"
#include "templates_obj.h"

#ifndef TANK_H
#define TANK_H

class Tank
{
public:
    // prototypes
    Tank(std::string, std::string);
    std::map<std::string, Template> templates;

    Templates createTemplates(std::map<std::string, std::map<std::string, std::string>>, 
                              std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>);

private:
    
    std::string _templatePathsString;
    std::string _templateKeysString;
    std::map<std::string, std::string> templatesDict;
    
    std::map<std::string, std::map<std::string, std::string>> pathsdict;
    std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
    //std::map<std::string, std::map<std::string, std::string>> getPathsFromDict();
    //std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> getKeysFromDict();
};

#endif // TANK_H