#include "exception.h"

// Implémentation du constructeur
TankMatchingTemplatesError::TankMatchingTemplatesError(const std::string& error_message)
    : m_error_message(error_message) {}

// Implémentation de la méthode what()
const char* TankMatchingTemplatesError::what() const noexcept
{
    return m_error_message.c_str();
}
