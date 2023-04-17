#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // Pour setw

#include "template_keys.h"

// ######## TemplateKey ######## 

TemplateKey::TemplateKey(std::string name, std::string default_value)
{
	this->_name = name;
	this->_value = default_value;
	this->_default_value = default_value;

}


std::string TemplateKey::getName() const {

	return this->_name;
}

std::string TemplateKey::getDefault() const {
	return this->_default_value;
};

void TemplateKey::setValue(std::string value)
{
	this->_value = value;
}

std::string TemplateKey::getValue()
{
	std::cout << "Template "<< std::endl;
	return this->_value;
}



// ######## StringTemplateKey ######## 

StringTemplateKey::StringTemplateKey(std::string name, std::string default_value) noexcept : TemplateKey(name, default_value)
{
	// this->_value = default_value;
}

void StringTemplateKey::setValue(std::string value)
{
	this->_value = value;
}

std::string StringTemplateKey::getValue() 
{
	std::cout << "StringTemplateKey "<< std::endl;
	return this->_value;
}



// ######## IntegerTemplateKey ######## 

IntegerTemplateKey::IntegerTemplateKey(std::string name, std::string default_value, std::string format_spec="2") noexcept : TemplateKey(name, default_value) //std::string format_spec
{
	// this->_value = default_value;
	this->_format_spec = format_spec;
}

void IntegerTemplateKey::setValue(std::string value)
{
	this->_value = _formatValue(value);
}

std::string IntegerTemplateKey::getValue()
{
	std::cout << "IntegerTemplateKey "<< std::endl;
	return _formatValue(this->_value);
}

std::string IntegerTemplateKey::_formatValue(std::string value) 
{
	int num = std::stoi(value);
    std::stringstream ss;
    ss << std::setw(std::stoi(this->_format_spec)) << std::setfill('0') << num;
    std::string formattedString = ss.str();
	return formattedString;
}
