#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <vector>

class TankMatchingTemplatesError : public std::exception
{
public:
    // Constructeur prenant un message d'erreur en argument
    TankMatchingTemplatesError(const std::string& error_message);

    // Redéfinition de la méthode what() pour retourner le message d'erreur
    const char* what() const noexcept override;

private:
    std::string m_error_message; // Message d'erreur
};

class TankApplyFieldsTemplateError : public std::exception
{
public:
    // Constructeur prenant un message d'erreur en argument
    TankApplyFieldsTemplateError(const std::string& template_name, const std::string& definition, const std::vector<std::string> fields);

    // Redéfinition de la méthode what() pour retourner le message d'erreur
    const char* what() const noexcept override;

private:
    std::string m_definition; // Message d'erreur
    std::string m_template_name; // Message d'erreur
    std::vector<std::string> m_fields; // Message d'erreur
};

class TankTemplateWrongValue : public std::exception
{
public:
    // Constructeur prenant un message d'erreur en argument
    TankTemplateWrongValue(const std::string& key, const std::string& value, std::vector<std::string> choices);

    // Redéfinition de la méthode what() pour retourner le message d'erreur
    const char* what() const noexcept override;

private:
    std::string m_key; // Message d'erreur
    std::string m_value; // Message d'erreur
    std::vector<std::string> m_choices; // Message d'erreur
};

#endif // EXCEPTION_H