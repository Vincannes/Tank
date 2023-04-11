#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

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

#endif // EXCEPTION_H