#include "Function.h"

namespace
{
	double ValueCalculating(Operation operation, double firstVal, double secondVal)
	{
		double value = NAN;
		switch (operation)
		{
		case (Operation::Addition):
			value = firstVal + secondVal;
			break;
		case (Operation::Subtraction):
			value = firstVal - secondVal;
			break;
		case (Operation::Multiplication):
			value = firstVal * secondVal;
			break;
		case (Operation::Division):
			value = firstVal / secondVal;
			break;
		case (Operation::Undefined): break;
		default: break;
		}
		return value;
	}

	void ValuesInitialisating(double& firstValue, double& secondValue,
		std::vector<Value> values)
	{
		if (values.size() == 1 && values.front().func != nullptr)
		{ 
			firstValue = values.front().func->GetValue();
		}
		else if (values.size() == 1 && values.front().var != nullptr)
		{
			firstValue = values.front().var->GetValue();
		}
		else if (values.size() == 2)
		{
			if (values.front().func != nullptr)
			{
				firstValue = values.front().func->GetValue();
			}
			else
			{
				firstValue = values.front().var->GetValue();
			}
			if (values.back().func != nullptr)
			{
				secondValue = values.back().func->GetValue();
			}
			else
			{
				secondValue = values.back().var->GetValue();
			}
		}
	}
}

Function::Function(Var* valuePtr)
{
	Value value{nullptr, valuePtr};
	m_varPtrs.push_back(value);
	m_value = valuePtr->GetValue();
}

Function::Function(Function* valuePtr)
{
	Value value{ valuePtr, nullptr };
	m_varPtrs.push_back(value);
	m_value = valuePtr->GetValue();
}

Function::Function(Function* firstValuePtr, Var* secondValuePtr, const Operation operation)
{
	Value firstValue { firstValuePtr, nullptr };
	Value secondValue{ nullptr, secondValuePtr };
	m_varPtrs.push_back(firstValue);
	m_varPtrs.push_back(secondValue);
	m_operation = operation;
	m_value = ValueCalculating(operation, firstValuePtr->GetValue(), secondValuePtr->GetValue());
}

Function::Function(Var* firstValuePtr, Function* secondValuePtr, const Operation operation)
{
	Value firstValue{ nullptr, firstValuePtr };
	Value secondValue{ secondValuePtr, nullptr };
	m_varPtrs.push_back(firstValue);
	m_varPtrs.push_back(secondValue);
	m_operation = operation;
	m_value = ValueCalculating(operation, firstValuePtr->GetValue(), secondValuePtr->GetValue());
}

Function::Function(Function* firstValuePtr, Function* secondValuePtr, const Operation operation)
{
	Value firstValue{ firstValuePtr, nullptr };
	Value secondValue{ secondValuePtr, nullptr };
	m_varPtrs.push_back(firstValue);
	m_varPtrs.push_back(secondValue);
	m_operation = operation;
	m_value = ValueCalculating(operation, firstValuePtr->GetValue(), secondValuePtr->GetValue());
}

Function::Function(Var* firstValuePtr, Var* secondValuePtr, const Operation operation)
{
	Value firstValue{ nullptr, firstValuePtr };
	Value secondValue{ nullptr, secondValuePtr };
	m_varPtrs.push_back(firstValue);
	m_varPtrs.push_back(secondValue);
	m_operation = operation;
	m_value = ValueCalculating(operation, firstValuePtr->GetValue(), secondValuePtr->GetValue());
}

double Function::GetValue() const
{
	if (m_value != NULL)
	{
		return m_value;
	}
	double firstValue = NULL, secondValue = NULL;
	ValuesInitialisating(firstValue, secondValue, m_varPtrs);
	
	if (secondValue)
	{
		return ValueCalculating(m_operation, firstValue, secondValue);
	}
	return firstValue;
}

void Function::Recalculation()
{
	double firstValue = NULL, secondValue = NULL;
	ValuesInitialisating(firstValue, secondValue, m_varPtrs);
	if (secondValue)
	{
		m_value = ValueCalculating(m_operation, firstValue, secondValue);
	}
	else
	{
		m_value = firstValue;
	}
	for (int i = 0; i < m_refPtrs.size(); i++)
	{
		m_refPtrs.at(i)->NullingValue();
	}
}

void Function::AddPtrToReferencingFunction(Function* function)
{
	m_refPtrs.push_back(function);
}

void Function::NullingValue()
{
	m_value = NULL;
}
