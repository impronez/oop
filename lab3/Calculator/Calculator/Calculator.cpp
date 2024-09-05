#include "Calculator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace 
{
    const int PRECISION = 2;

    bool IsDouble(const std::string& str)
    {
        if (str.empty())
        {
            return false;
        }

        char* ptr;
        double val = strtod(str.c_str(), &ptr);
        return (*ptr) == '\0';
    }

    Var* VariableSearching(std::map<std::string, Var>& vars,
        const std::string& key)
    {
        if ((vars.find(key) != vars.end()) && !key.empty())
        {
            return &vars.at(key);
        }
        return nullptr;
    }

    Function* FunctionSearching(std::map<std::string, Function>& funcs,
        const std::string& key)
    {
        if ((funcs.find(key) != funcs.end()) && !key.empty())
        {
            return &funcs.at(key);
        }
        return nullptr;
    }

    bool IsExist(std::map<std::string, Function>& funcs,
        std::map<std::string, Var>& vars, const std::string& name)
    {
        return ((vars.find(name) != vars.end()) || (funcs.find(name) != funcs.end()));
    }

    void AddFunctionPtrToVar(Var* firstVar, Var* secondVar, Function* function)
    {
        if (firstVar != nullptr)
        {
            firstVar->AddPtrToReferencingFunction(function);
        }
        if (secondVar != nullptr)
        {
            secondVar->AddPtrToReferencingFunction(function);
        }
    }

    bool AddFunction(const std::string& key, std::map<std::string, Function>& functions,
        Operation& operation, Var* firstVar, Var* secondVar, Function* firstFunc, Function* secondFunc)
    {
        if (firstVar != nullptr && secondVar != nullptr)
        {
            Function func(firstVar, secondVar, operation);
            functions.insert({ key, func });
        }
        else if (firstVar != nullptr && secondFunc != nullptr)
        {
            Function func(firstVar, secondFunc, operation);
            functions.insert({ key, func });
        }
        else if (firstFunc != nullptr && secondVar != nullptr)
        {
            Function func(firstFunc, secondVar, operation);
            functions.insert({ key, func });
        }
        else if (firstFunc != nullptr && secondFunc != nullptr)
        {
            Function func(firstFunc, secondFunc, operation);
            functions.insert({ key, func });
        }
        else if (firstFunc != nullptr)
        {
            Function func(firstFunc);
            functions.insert({ key, func });
        }
        else if (firstVar != nullptr)
        {
            Function func(firstVar);
            functions.insert({ key, func });
        }
        AddFunctionPtrToVar(firstVar, secondVar, &functions.at(key));
        return true;
    }
}

void Calculator::PrintVar(const std::string& key) const
{
    double value;
    if ((m_vars.find(key) != m_vars.end()))
    {
        value = m_vars.at(key).GetValue();
    }
    else if (m_funcs.find(key) != m_funcs.end())
    {
        value = m_funcs.at(key).GetValue();
    }
    else
    {
        throw std::invalid_argument("A non-existent variable!");
    }
    std::cout << key << std::fixed << ':' <<
        std::setprecision(PRECISION) << value << std::endl;
}

void Calculator::PrintVars() const
{
    for (auto& item : m_vars)
    {
        std::cout << item.first << ':' << std::fixed << 
            std::setprecision(PRECISION) << item.second.GetValue() << std::endl;
    }
}

void Calculator::PrintFunctions() const
{
    for (auto& item : m_funcs)
    {
        std::cout << item.first << ':' << std::fixed <<
            std::setprecision(PRECISION) << item.second.GetValue() << std::endl;
    }
}

bool Calculator::NewVar(const std::string& name)
{
    if (m_vars.find(name) == m_vars.end() && m_funcs.find(name) == m_funcs.end())
    {
        Var var;
        m_vars.insert({ name, var });;
        std::cout << "Variable '" << name << "' added!\n";
        return true;
    }
    else
    {
        throw std::logic_error("Such a variable already exists!");
    }
}

bool Calculator::VarIdentification(const std::string& key, const std::string& value)
{
    bool isExistingVar = m_vars.find(key) != m_vars.end();
    bool isNumValue = IsDouble(value);
    double num = NAN;
    if (isNumValue)
    {
        num = std::stod(value);
    }
    else if (!isNumValue && (m_vars.find(value) != m_vars.end()))
    {
        num = m_vars.at(value).GetValue();
    }
    else if (!isNumValue && (m_funcs.find(value) != m_funcs.end()))
    {
        num = m_funcs.at(value).GetValue();
    }
    else if (!isNumValue && (m_vars.find(value) == m_vars.end()))
    {
        throw std::invalid_argument("Variable" + value + "is not existing!");
        return false;
    }
    
    if (isExistingVar)
    {
        m_vars.at(key).SetValue(num);
    }
    else
    {
        Var var(num);
        m_vars.insert({ key, var });
    }
    std::cout << "Variable '" << key << "' = " << num << std::endl;
    return true;
}

bool Calculator::NewFunction(const std::string& name, const std::string& firstVar,
    const std::string& secondVar, Operation& operation)
{
    if (IsExist(m_funcs, m_vars, name))
    {
        throw std::invalid_argument("Name '" + name + "' already exist!");
    }
    Var* firstVarPtr = VariableSearching(m_vars, firstVar);
    Var* secondVarPtr = VariableSearching(m_vars, secondVar);
    Function* firstFuncPtr = FunctionSearching(m_funcs, firstVar);
    Function* secondFuncPtr = FunctionSearching(m_funcs, secondVar);

    if (firstVarPtr == nullptr && secondVarPtr == nullptr
        && firstFuncPtr == nullptr && secondFuncPtr == nullptr)
    {
        throw std::invalid_argument("Incorrect identificator(s)!");
    }

    if (!AddFunction(name, m_funcs, operation, firstVarPtr, secondVarPtr, firstFuncPtr, secondFuncPtr))
    {
        return false;
    }

    return true;
}