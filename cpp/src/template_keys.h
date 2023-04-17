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
		
		std::string _value;
		
		// accesseurs
		std::string getName() const;
		std::string getDefault() const;
		virtual std::string getValue();

		// manipulateurs
		void setValue(std::string);

	private:
		std::string _name;
		std::string _default_value="";
};


class StringTemplateKey : public TemplateKey
{

public:

	StringTemplateKey(std::string name, std::string default_value) noexcept;
	std::string getValue();
	void setValue(std::string);

private:
	// std::string _value;
		
};


class IntegerTemplateKey : public TemplateKey
{

public:

	IntegerTemplateKey(std::string name, std::string default_value, std::string format_spec) noexcept;
	std::string getValue();
	void setValue(std::string);

private:
	// std::string _value;
	std::string _format_spec;
	std::string _formatValue(std::string);
};


