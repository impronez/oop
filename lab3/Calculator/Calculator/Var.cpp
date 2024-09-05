#include "Var.h"

Var::Var(const double value)
{
	m_value = value;
}

void Var::AddPtrToReferencingFunction(Function* function)
{
	m_refFuncs.push_back(function);
}

void Var::SetValue(const double value)
{
	m_value = value;
	for (int i = 0; i < m_refFuncs.size(); i++)
	{
		m_refFuncs.at(i)->Recalculation();
	}
}

double Var::GetValue() const
{
	return m_value;
}
