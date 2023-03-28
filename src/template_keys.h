#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Integer {};
struct String {};

class TemplateKey
{

	public:
		// prototypes
		TemplateKey(std::string name, std::string default_value);
		
		// accesseurs
		std::string getName() const;
		std::string getDefault() const;

		// manipulateurs
		//...

	private:
		std::string _name;
		std::string _default_value="";
};


class StringKey : public TemplateKey
{

	public:

		StringKey(std::string name, std::string default_value) noexcept;
		int getType();

	private:
		int _istype;
		
};


class IntegerKey : public TemplateKey
{

public:

	IntegerKey(std::string name, std::string default_value) noexcept;
	int getType();

private:
	int _istype;

};


