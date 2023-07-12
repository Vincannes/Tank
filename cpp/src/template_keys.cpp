#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // Pour setw

#include "utils.h"
#include "exception.h"
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
	return this->_value;
}



// ######## StringTemplateKey ######## 

StringTemplateKey::StringTemplateKey(std::string name, std::string default_value, std::vector<std::string>choices) noexcept : TemplateKey(name, default_value)
{
	this->_choices = choices;
}

void StringTemplateKey::setValue(std::string value)
{
	if(value.empty() && !getDefault().empty()){
		this->_value = getDefault();
	}
	else if(this->_choices.size() > 0){
		this->_value = "";
		for(int i=0; i < this->_choices.size(); i++){
			std::string choice_value =  this->_choices[i];
			if(choice_value == value){
				this->_value = value;
			}
		}
		if(this->_value.empty()){
			throw TankTemplateWrongValue(getName(), value, this->_choices);
		}
	}
	else{
		this->_value = value;
	}
}

std::string StringTemplateKey::getValue() 
{
	return this->_value;
}



// ######## IntegerTemplateKey ######## 

IntegerTemplateKey::IntegerTemplateKey(std::string name, std::string default_value, std::string format_spec="2") noexcept : TemplateKey(name, default_value) //std::string format_spec
{

	this->_format_spec = format_spec;
}

void IntegerTemplateKey::setValue(std::string value)
{
	std::string _value;
	if(!getDefault().empty()){
		_value = getDefault();
	}
	else{
		_value = value;
	}
	this->_value = _formatValue(_value);
}

std::string IntegerTemplateKey::getValue()
{
	return _formatValue(this->_value);
}

std::string IntegerTemplateKey::_formatValue(std::string value) 
{
	std::string value_reformat = removePatternInString(value, "v", "");
	int num = std::stoi(value_reformat);
    std::stringstream ss;
    ss << std::setw(std::stoi(this->_format_spec)) << std::setfill('0') << num;
    std::string formattedString = ss.str();
	return formattedString;
}


// ######## SequenceTemplateKey ######## 

SequenceTemplateKey::SequenceTemplateKey(std::string name, std::string format_spec="4") noexcept : TemplateKey(name, "#") //std::string format_spec
{
	// this->_value = default_value;
	this->_format_spec = format_spec;
}

std::string SequenceTemplateKey::getValue()
{
	std::string result;
	int num = std::stoi(this->_format_spec);
	for (int i = 0; i < num; i++) {
        result.append(this->_value);
    }
	return result;
}

