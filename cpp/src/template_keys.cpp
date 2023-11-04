#include <regex>
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

StringTemplateKey::StringTemplateKey(std::string name, std::string default_value, std::vector<std::string>choices, std::string filter_by) noexcept : TemplateKey(name, default_value)
{
	this->_choices = choices;
	this->_filter_by = filter_by;
}

void StringTemplateKey::setValue(std::string value)
{
	// Check if value is valid from filter filter
	if(!_filter_value(value)){
		throw TankTemplateWrongValue(getName(), value, this->_filter_by, this->_choices);
	}

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
			throw TankTemplateWrongValue(getName(), value, this->_filter_by, this->_choices);
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

bool StringTemplateKey::_filter_value(std::string value)
{
	std::cout << "this->_filter_by   "<< this->_filter_by << std::endl;
	// if not filter
	if(this->_filter_by.empty()) return true;

	std::regex pattern(this->_filter_by);
	if(std::regex_search(value, pattern)){
		return true;
	}
	else {
		return false;
	}
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
    ss << std::setw(std::stoi(this->_format_spec)-1) << std::setfill('0') << num;
    std::string formattedString = ss.str();
	return formattedString;
}


// ######## SequenceTemplateKey ######## 

SequenceTemplateKey::SequenceTemplateKey(std::string name, std::string format_spec="4") noexcept : TemplateKey(name, "#") //std::string format_spec
{
	// this->_value = default_value;
	this->_format_spec = format_spec;
}

void SequenceTemplateKey::setValue(std::string value)
{
	std::string result;
	if(value.size() == 0 || value == this->_format_spec ){
		int num = std::stoi(this->_format_spec);
		for (int i = 0; i < num; i++) {
			result.append(this->_value);
		}
	}
	else{
		result = value;
	}
	this->_value = result;
}

std::string SequenceTemplateKey::getValue()
{
	return this->_value;
}

