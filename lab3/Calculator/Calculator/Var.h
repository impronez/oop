#pragma once
#include "Function.h"

class Function;

class Var
{
public:
	Var(const double value = NAN);
	void AddPtrToReferencingFunction(Function* function);
	void SetValue(const double value);

	double GetValue() const;
private:
	double m_value;
	std::vector<Function*> m_refFuncs{};
};
