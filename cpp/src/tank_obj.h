#include <map>
#include <string>
#include "utils.h"

#include "exception.h"
#include "template_obj.h"
#include "conform_path.h"
#include "template_keys.h"

#ifndef TANK_H
#define TANK_H

class Tank
{
public:
    // prototypes
    Tank(std::string config_path, std::string root_path);
    std::map<std::string, TemplatePath> getTemplates();
    TemplatePath templateFromPath(std::string);
    std::vector<TemplatePath> templatesFromPath(std::string);
    std::vector<std::string> getAbstractPathsFromTemplate(TemplatePath, std::map<std::string, std::string>);
    std::map<std::string, TemplateKey*> getAllKeys();

private:

    std::string _config_path;
    std::string _root_path;
    std::map<std::string, TemplateKey*> _allKeys;
    std::map<std::string, TemplatePath> _templates;
    std::map<std::string, std::string> templatesDict;
    std::map<std::string, std::string> pathsdict;
    std::map<std::string, std::string> stringsdict;
    std::map<std::string, std::map<std::string, std::string>> keydict;

    std::map<std::string, TemplateKey*> dictOfAllKeys();
    std::map<std::string, TemplatePath> _getTemplates();
};

#endif // TANK_H

