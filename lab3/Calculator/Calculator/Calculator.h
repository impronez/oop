#pragma once
#include <map>
#include <string>
#include "Var.h"
#include "Function.h"

class Calculator
{
public:
	void PrintVar(const std::string& key) const;
	void PrintVars() const;
	void PrintFunctions() const;

	bool NewVar(const std::string& name);
	bool VarIdentification(const std::string& key, const std::string& value);
	bool NewFunction(const std::string& name, const std::string& firstVar,
		const std::string& secondVar, Operation& operation);
private:
	std::map<std::string, Var> m_vars {};
	std::map<std::string, Function> m_funcs {};
};

