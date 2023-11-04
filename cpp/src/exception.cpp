#include "exception.h"

// Implémentation du constructeur
TankMatchingTemplatesError::TankMatchingTemplatesError(const std::string& error_message)
    : m_error_message(error_message) {}

// Implémentation de la méthode what()
const char* TankMatchingTemplatesError::what() const noexcept
{
    return m_error_message.c_str();
}


// Implémentation du constructeur
TankApplyFieldsTemplateError::TankApplyFieldsTemplateError(
    const std::string& template_name, 
    const std::string& definition, 
    const std::vector<std::string> fields
    )
    // : m_template_name(template_name) {}#
    {
        m_definition = definition;
        m_template_name = template_name;
        m_fields = fields;
    }

// Implémentation de la méthode what()
const char* TankApplyFieldsTemplateError::what() const noexcept
{
    static std::string full_message;
    full_message = "Tried to resolve path from the template '" + m_template_name + "' : " + m_definition;
    full_message += " but the following required fields were missing from the input: ";
    for(int i=0; i<m_fields.size(); i++){
        full_message += "{" + m_fields[i] + "}";
        full_message += " ";
    }
    return full_message.c_str();
}

// Implémentation du constructeur
TankTemplateWrongValue::TankTemplateWrongValue(
    const std::string& key, 
    const std::string& value, 
    const std::string& filter_by, 
    std::vector<std::string> choices
    )
    {
        m_key = key;
        m_value = value;
        m_choices = choices;
        m_filter = filter_by;
    }

// Implémentation de la méthode what()
const char* TankTemplateWrongValue::what() const noexcept
{
    static std::string full_message;
    full_message = "Key '"+ this->m_key + "' has illegal value: '" + this->m_value + "' not in choices: [";
    for(int i=0; i<this->m_choices.size(); i++){
        full_message += this->m_choices[i];
        full_message += ", ";
    }
    full_message.erase(full_message.end() - 2, full_message.end());
    full_message += "]";
    if(!this->m_filter.empty()){
        full_message += "   filter is: ";
        full_message += this->m_filter;
    }
    return full_message.c_str();
}

