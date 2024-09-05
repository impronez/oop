#include "Menu.h"
#include <iostream>
#include <regex>

const std::map<std::string, Operation> OPERATIONS =
{
    { "+", Operation::Addition },
    { "-", Operation::Subtraction},
    { "*", Operation::Multiplication},
    { "/", Operation::Division}
};

const std::string VAR = "var";
const std::string LET = "let";
const std::string FUNCTION = "fn";
const std::string PRINT = "print";
const std::string PRINT_VARS = "printvars";
const std::string PRINT_FUNCTIONS = "printfns";

bool IdentifyCommand(const std::string& str, std::string& key, std::string& value)
{
    size_t space = str.find(' ');
    if (str == PRINT_VARS || str == PRINT_FUNCTIONS)
    {
        key = str;
        return true;
    }
    else if (space != std::string::npos)
    {
        key = str.substr(0, space);
        value = str.substr(space + 1, str.back());
        if (key == VAR || key == PRINT || key == LET || key == FUNCTION)
        {
            return true;
        }
    }
    std::cout << "Incorrect command!\n";
    return false;
}

bool IsCorrectNameOfVariable(const std::string& str)
{    
    std::regex validName(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    
    if (std::regex_match(str, validName))
    {
        return true;
    }

    std::cout << "Incorrect variable name!\n";
    return false;
}

bool IdentifyAssignment(const std::string& str, std::string& var, std::string& value)
{
    std::regex validAssignment(R"(^([a-zA-Z_][a-zA-Z0-9_]*)[\s]*[=][\s]*([\+\-]*[a-zA-Z0-9_\.]+)$)");
    std::cmatch what;
    if (std::regex_match(str.c_str(), what, validAssignment))
    {
        var = std::string(what[1]);
        value = std::string(what[2]);
        return true;
    }
    std::cout << "Incorrect expression!\n";
    return false;
}

bool IdentifyFunction(const std::string& str, std::string& name,
    std::string& firstVar, std::string& secondVar, Operation& operation)
{
    std::regex exp(R"(^([a-zA-Z0-9_]+)[\s]*[=][\s]*([a-zA-Z0-9_]+)[\s]*(([\+\-\*/])[\s]*([a-zA-Z0-9_]+))*$)");
    std::cmatch what;
    if (std::regex_match(str.c_str(), what, exp))
    {
        name = std::string(what[1]);
        firstVar = std::string(what[2]);
        if (!std::string(what[3]).empty())
        {
            operation = OPERATIONS.at(std::string(what[4]));
            secondVar = std::string(what[5]);
        }
        return true;
    }
    std::cout << "Incorrect expression!\n";
    return false;
}

void AddFunction(Calculator& calc, const std::string& value)
{
    std::string name, firstVar, secondVar;
    Operation operation;
    if (IdentifyFunction(value, name, firstVar, secondVar, operation))
    {
        try
        {
            calc.NewFunction(name, firstVar, secondVar, operation);
        }
        catch (const std::invalid_argument& ex)
        {
            std::cout << "Invalid argument: " << ex.what() << std::endl;
        }
    }
    std::cout << "Function '" << name << "' added!\n";
}

void VarIdentification(Calculator& calc, const std::string& value)
{
    std::string var, val;
    if (IdentifyAssignment(value, var, val))
    {
        try
        {
            calc.VarIdentification(var, val);
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << "Invalid argument: " << ex.what() << std::endl;
        }
    }
}

void AddVar(Calculator& calc, const std::string& value)
{
    try
    {
        calc.NewVar(value);
    }
    catch (const std::logic_error& ex)
    {
        std::cout << "Logic error: " << ex.what() << std::endl;
    }
}

void PrintVar(Calculator& calc, const std::string& value)
{
    try
    {
        calc.PrintVar(value);
    }
    catch (std::invalid_argument& ex)
    {
        std::cout << "Invalid argument: " << ex.what() << std::endl;
    }
}

void CommandIdentification(Calculator& calc, std::string& command, const std::string& value)
{
    if (command == VAR && IsCorrectNameOfVariable(value))
    {
        AddVar(calc, value);
    }
    else if (command == LET)
    {
        VarIdentification(calc, value);
    }
    else if (command == FUNCTION)
    {
        AddFunction(calc, value);
    }
    else if (command == PRINT)
    {
        PrintVar(calc, value);
    }
    else if (command == PRINT_VARS)
    {
        calc.PrintVars();
    }
    else if (command == PRINT_FUNCTIONS)
    {
        calc.PrintFunctions();
    }
}

void Menu(Calculator& calc)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            std::cout << "Exiting.\n";
            break;
        }

        std::string key, value;
        if (IdentifyCommand(line, key, value))
        {
            CommandIdentification(calc, key, value);
        }
    }
}