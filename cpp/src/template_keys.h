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
		TemplateKey() = default;
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


class StringTemplateKey : public TemplateKey
{

	public:

		StringTemplateKey(std::string name, std::string default_value) noexcept;

	private:
		
};


class IntegerTemplateKey : public TemplateKey
{

public:

	IntegerTemplateKey(std::string name, std::string default_value, std::string format_spec) noexcept;
	void setValue(std::string);
	std::string getValue();

private:
	std::string _value;
	std::string _format_spec;
	std::string _formatValue(std::string);
};


