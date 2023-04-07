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


// ######## StringTemplateKey ######## 

StringTemplateKey::StringTemplateKey(std::string name, std::string default_value) noexcept : TemplateKey(name, default_value)
{

}


// ######## IntegerTemplateKey ######## 

IntegerTemplateKey::IntegerTemplateKey(std::string name, std::string default_value) noexcept : TemplateKey(name, default_value)
{

}
