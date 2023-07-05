#include <regex>

#include "utils.h"
#include "tank_obj.h"
#include "template_obj.h"
#include "conform_path.h"
#include "template_keys.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

Tank::Tank(std::string _templatePathsString, std::string _templateKeysString, std::string _templateStringsString)
{
	this->_root_path           = "D:/Desk/";
    this->keydict              = generateKeysDictionnaryFromString(_templateKeysString);
    this->pathsdict            = generatePathsDictionnaryFromString(_templatePathsString);
    this->stringsdict          = generateStringsDictionnaryFromString(_templateStringsString);

	// Merge StringsDict with PathsDict
	for (const auto& kvp : this->stringsdict) {
        this->pathsdict.insert(kvp);
    }
	
    this->_allKeys             = dictOfAllKeys();
    this->_templates           = _getTemplates();

}

std::map<std::string, TemplatePath> Tank::getTemplates()
{
    return this->_templates;
}


std::map<std::string, TemplateKey*> Tank::getAllKeys()
{
	return this->_allKeys;
}


TemplatePath Tank::templateFromPath(std::string path)
{
	std::vector<TemplatePath> matched_templates = templatesFromPath(path);

	if(matched_templates.size() == 0 ) {
        throw TankMatchingTemplatesError("No Template find for this path : " + path);
    } else if (matched_templates.size() > 1) {
		std::string msg = std::to_string(matched_templates.size()) + " templates are matching the path : "+ path + "\n";
		for (auto it = matched_templates.begin(); it != matched_templates.end(); ++it) {
			msg +=it->getDefinition() + "\n";
		}
        throw TankMatchingTemplatesError(msg);
	} else {
		return matched_templates[0];
	}
}


std::vector<TemplatePath> Tank::templatesFromPath(std::string path)
{
	std::vector<TemplatePath> matched_templates;
	for (auto a = this->_templates.begin(); a != this->_templates.end(); ++a) {
		if(!a->second.validate(path)) continue;
		matched_templates.push_back(a->second);
	}
	return matched_templates;
}


std::vector<std::string> Tank::getAbstractPathsFromTemplate(TemplatePath templatePath, std::map<std::string, std::string> fields)
{
	std::map<std::string, std::string> local_fields;
	std::vector<std::string> missing_keys = templatePath.missingKeys(fields);

	for(auto a = fields.begin(); a !=fields.end(); ++a) {
		local_fields[a->first] = a->second;
	}

	for(int i=0; i<missing_keys.size(); i++){
		std::string key = missing_keys[i];
		local_fields[key] =  ".*";
	}
	std::string outputPattern     = templatePath.apply_fields(local_fields, missing_keys);
	std::string directoryToSearch = this->pathsdict.at("rootDir");
	std::vector<std::string> abstract_paths = listFilesFromPathPattern(directoryToSearch, outputPattern);
	return abstract_paths;
}


std::map<std::string, TemplateKey*> Tank::dictOfAllKeys()
{
	std::map<std::string, TemplateKey*> keysList;

	for (auto outerIt = this->keydict.begin(); outerIt != this->keydict.end(); ++outerIt) {

		bool hasAlias = false;
		bool isDefault = false;
		std::string aliasKey = "";
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string hasFormatSpec = "2"; 
		std::string name = removeSpaceInString(outerIt->first);
		std::vector<std::string> choices={};

		for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt) {

			std::string key = innerIt->first;
			std::string value = innerIt->second;
			key   = removeSpaceInString(key); // remove space if exist in key
			value = removeSpaceInString(value); // remove space if exist in key
			if (key == "type") {
				isTypeValue = value;
			}
			else if (key == "default") {
				isDefault = true;
				isDefaultValue = value;
			}
			else if (key == "format_spec"){
				hasFormatSpec = value;
			}
			else if (key == "choices"){
				choices = listFromString(value);
			}
			else if (key == "filter_by"){}
			else if (key == "shotgun_entity_type"){}
			else if (key == "shotgun_field_name"){}

			if (key == "alias"){
				hasAlias = true;
				aliasKey = value;
			}
		}

		if(hasAlias){
			name = aliasKey;
		}

		if (isTypeValue == "str") {
			StringTemplateKey* s1 = new StringTemplateKey(name, isDefaultValue, choices);
			keysList[name] = s1;
		}
		if (isTypeValue == "int") {
			IntegerTemplateKey* t1 = new IntegerTemplateKey(name, isDefaultValue, hasFormatSpec);
			keysList[name] = t1;
		}
		if (isTypeValue == "sequence") {
			SequenceTemplateKey* sq1 = new SequenceTemplateKey(name, hasFormatSpec);
			keysList[name] = sq1;
		}	
	}

	return keysList;
}


std::map<std::string, TemplatePath> Tank::_getTemplates(){

	ConformPath _conform_path(this->pathsdict);
	std::map<std::string, TemplatePath> templates;

	for (auto outerIt = this->pathsdict.begin(); outerIt != this->pathsdict.end(); ++outerIt) {
		std::string template_name = outerIt->first;
		std::string template_path = this->pathsdict[template_name];
		std::string path_conformed = _conform_path.buildDefinitionPath(template_path);
		TemplatePath templateObj(template_name, this->_allKeys, path_conformed, this->_root_path);
		templates.insert(std::make_pair(template_name, templateObj));
	}

	return templates;
}


PYBIND11_MODULE(tank_module, m) 
{
    m.doc() = "Tank module";

    py::class_<Tank>(m, "Tank")
        .def(py::init<std::string, std::string, std::string>())
        .def("templates", &Tank::getTemplates, "Get all templates")
        .def("templates_from_path", &Tank::templatesFromPath)
        .def("template_from_path", &Tank::templateFromPath)
        .def("abstract_paths_from_template", &Tank::getAbstractPathsFromTemplate)
        .def("keys", &Tank::getAllKeys)
        ;

	py::class_<ConformPath>(m, "ConformPath")
		.def(py::init<std::map<std::string, std::string>>());

	py::class_<TemplatePath>(m, "TemplatePath")
        .def(py::init<std::string, std::map<std::string, TemplateKey*>, std::string, std::string>())
        .def("name", &TemplatePath::getName)
        .def("definition", &TemplatePath::getDefinition)
        .def("static_token", &TemplatePath::getStaticTokens)
        .def("ordered_keys", &TemplatePath::getOrderedKeys)
		.def("apply_fields", &TemplatePath::apply_fields, 
				py::arg("fields"), py::arg("missing_keys") = std::vector<std::string>())
        .def("get_fields", &TemplatePath::getFields)
        .def("missing_keys", &TemplatePath::missingKeys)
		;

	py::class_<TemplateKey>(m, "TemplateKey")
        .def(py::init<std::string, std::string>())
        .def("name", &TemplateKey::getName, "Get key name")
        .def("default_value", &TemplateKey::getDefault, "Get default value");
    py::class_<StringTemplateKey>(m, "StringTemplateKey")
        .def(py::init<std::string, std::string>());
    py::class_<IntegerTemplateKey>(m, "IntegerTemplateKey")
        .def(py::init<std::string, std::string, std::string>());

	py::register_exception<TankMatchingTemplatesError>(m, "TankMatchingTemplatesError");
	py::register_exception<TankApplyFieldsTemplateError>(m, "TankApplyFieldsTemplateError");
	py::register_exception<TankTemplateWrongValue>(m, "TankTemplateWrongValue");

}
