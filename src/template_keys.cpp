#include "template_keys.h"
#include <iostream>
#include <string>
#include <vector>


// ######## TemplateKey ######## 

TemplateKey::TemplateKey(std::string name, std::string default_value)
{
	this->_name = name;
	this->_default_value = default_value;

}


std::string TemplateKey::getName() const {

	return this->_name;
}

std::string TemplateKey::getDefault() const {
	return this->_default_value;
};


// ######## StringKey ######## 

StringKey::StringKey(std::string name, std::string default_value) noexcept : TemplateKey(name, default_value), _istype(1)
{

}


int StringKey::getType() {

	return this->_istype;
}


// ######## IntegerKey ######## 

IntegerKey::IntegerKey(std::string name, std::string default_value) noexcept : TemplateKey(name, default_value), _istype(2)
{

}


int IntegerKey::getType() {

	return this->_istype;
}