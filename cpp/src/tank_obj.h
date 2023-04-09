#include <map>
#include <string>
#include "utils.h"

#include "template_keys.h"
//#include "template_obj.h"


#ifndef TANK_H
#define TANK_H

class Tank
{
public:
    // prototypes
    Tank() = default;
    Tank(std::string, std::string);
    std::map<std::string, int> getTemplates();

private:

    std::vector <TemplateKey> _allKeys;
    std::map<std::string, int> _templates;
    std::map<std::string, std::string> templatesDict;
    std::map<std::string, std::map<std::string, std::string>> pathsdict;
    std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;

    std::vector <TemplateKey> listOfALlKeys();
    std::map<std::string, int> _getTemplates();
};

#endif // TANK_H

