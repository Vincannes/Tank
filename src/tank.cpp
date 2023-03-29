#include <fstream>
//#include <yaml-cpp/yaml.h>
#include "tank.h"


Tank::Tank(std::string configPath) {

	this->_configPath = configPath;
	//this->pathsdict = ;
	//this->keydict = ;
	//this->_templatesObj(this->pathsdict, this->keydict);
	//this->templates = this->_templatesObj;
}
/*
Templates& Tank::_templatesObj(std::map<std::string, std::map<std::string, std::string>> pathsdict,
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict)
{
	// TODO: insérer une instruction return ici
	return;
}*/
