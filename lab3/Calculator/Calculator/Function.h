#pragma once
#include <string>
#include <vector>
#include "Var.h"

class Var;

struct Value;

enum class Operation
{
	Addition, Subtraction, Multiplication, Division, Undefined
};

class Function
{
public:
	Function(Var* value);
	Function(Function* value);
	Function(Function* firstVal, Var* secondVal, const Operation oper);
	Function(Var* firstVal, Function* secondVal, const Operation oper);
	Function(Function* firstVal, Function* secondVal, const Operation oper);
	Function(Var* firstVal, Var* secondVal, const Operation oper);
	void AddPtrToReferencingFunction(Function* function);
	void NullingValue();
	
	double GetValue() const;
	void Recalculation();
private:
	std::vector<Value> m_varPtrs{};
	std::vector<Function*> m_refPtrs{};
	double m_value = NULL;
	Operation m_operation = Operation::Undefined;
};

struct Value
{
	Function* func;
	Var* var;
};