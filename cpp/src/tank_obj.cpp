#include "utils.h"
#include "tank_obj.h"
#include "template_obj.h"
#include "conform_path.h"
#include "template_keys.h"

// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>

// namespace py = pybind11;

Tank::Tank(std::string _templatePathsString, std::string _templateKeysString)
{
    this->pathsdict            = generatePathsDictionnaryFromString(_templatePathsString);
    this->keydict              = generateKeysDictionnaryFromString(_templateKeysString);
    this->_allKeys             = dictOfAllKeys();
    this->_templates           = _getTemplates();
}

std::map<std::string, TemplatePath> Tank::getTemplates()
{
    return this->_templates;
}


// std::vector<TemplatePath> Tank::templatesFromPath(std::string path)
// {
// 	std::vector<TemplatePath> matched_templates;

// 	for (auto a = this->_templates.begin(); a != this->_templates.end(); ++a) {
// 		if(!a.validate(path)) continue;
// 		matched_templates.push_back(a)
// 	}
	
// 	return matched_templates;
// }

std::vector<std::string> Tank::getAbstractPathsFromTemplate(std::string, std::map<std::string, std::string>)
{
	std::vector<std::string> abstract_paths;

	return abstract_paths;
}


std::vector <TemplateKey> Tank::listOfALlKeys()
{
	std::vector <TemplateKey> keysList{};

	for (auto outerIt = this->keydict["keys"].begin(); outerIt != this->keydict["keys"].end(); ++outerIt) {

		bool isType;
		bool isDefault;
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string name = outerIt->first;

		for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt) {
			std::string key = innerIt->first;
			std::string value = innerIt->second;
			if (key == "type") {
				isType = true;
				isTypeValue = value;
			}
			else if (key == "default") {
				isDefault = true;
				isDefaultValue = value;
			}
		}
		if (isTypeValue == "str") {
			StringTemplateKey s1(name, isDefaultValue);
			keysList.push_back(s1);
		}
		if (isTypeValue == "int") {
			IntegerTemplateKey t1(name, isDefaultValue);
			keysList.push_back(t1);
		}
	}

	return keysList;
}


std::map<std::string, TemplateKey> Tank::dictOfAllKeys()
{
	std::map<std::string, TemplateKey> keysList;

	for (auto outerIt = this->keydict["keys"].begin(); outerIt != this->keydict["keys"].end(); ++outerIt) {

		// bool isType;
		bool isDefault;
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string name = removeSpaceInString(outerIt->first);

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

			if (isTypeValue == "str") {
				StringTemplateKey s1(name, isDefaultValue);
				keysList.insert(std::make_pair(name, s1));
			}
			if (isTypeValue == "int") {
				IntegerTemplateKey t1(name, isDefaultValue);
				keysList.insert(std::make_pair(name, t1));
			}
		}

	}

	return keysList;
}


std::map<std::string, TemplatePath> Tank::_getTemplates(){

	ConformPath _conform_path(this->pathsdict);
	std::map<std::string, TemplatePath> templates;

	for (auto outerIt = this->pathsdict["paths"].begin(); outerIt != this->pathsdict["paths"].end(); ++outerIt) {
		std::string template_name = outerIt->first;
		std::string template_path = this->pathsdict["paths"][template_name];
		std::string path_conformed = _conform_path.buildDefinitionPath(template_path);
		TemplatePath templateObj(template_name, this->_allKeys, path_conformed);
		templates.insert(std::make_pair(template_name, templateObj));
	}

	return templates;
}


// PYBIND11_MODULE(tank_module, m) 
// {
//     m.doc() = "Tank module";

//     py::class_<Tank>(m, "Tank")
//         .def(py::init<std::string, std::string>())
//         .def("get_templates", &Tank::getTemplates, "Get all templates");
//         .def("templates_from_path", &TemplatePath::templatesFromPath)
//         .def("abstract_paths_from_template", &TemplatePath::getAbstractPathsFromTemplate)
//         ;

// 	py::class_<ConformPath>(m, "ConformPath")
// 		.def(py::init<std::map<std::string, std::map<std::string, std::string>>>());

// 	py::class_<TemplatePath>(m, "TemplatePath")
//         .def(py::init<std::string, std::vector<TemplateKey>, std::string>())
//         .def("name", &TemplatePath::getName)
//         .def("definition", &TemplatePath::getDefinition)
//         .def("static_token", &TemplatePath::getStaticTokens)
//         .def("ordered_keys", &TemplatePath::getOrderedKeys)
//         .def("apply_fields", &TemplatePath::apply_fields)
//         .def("get_fields", &TemplatePath::getFields);

// 	py::class_<TemplateKey>(m, "TemplateKey")
//         .def(py::init<std::string, std::string>())
//         .def("name", &TemplateKey::getName, "Get key name")
//         .def("default_value", &TemplateKey::getDefault, "Get default value");
//     py::class_<StringTemplateKey>(m, "StringTemplateKey")
//         .def(py::init<std::string, std::string>());
//     py::class_<IntegerTemplateKey>(m, "IntegerTemplateKey")
//         .def(py::init<std::string, std::string>());
// }
