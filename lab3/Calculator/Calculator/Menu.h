#pragma once
#include "Calculator.h"

bool IdentifyCommand(const std::string& str, std::string& key, std::string& value);

bool IsCorrectNameOfVariable(const std::string& str);

bool IdentifyAssignment(const std::string& str, std::string& var, std::string& value);

bool IdentifyFunction(const std::string& str, std::string& name,
    std::string& firstVar, std::string& secondVar, Operation& operation);

void AddFunction(Calculator& calc, const std::string& value);

void VarIdentification(Calculator& calc, const std::string& value);

void AddVar(Calculator& calc, const std::string& value);

void PrintVar(Calculator& calc, const std::string& value);

void CommandIdentification(Calculator& calc, std::string& command, const std::string& value);

void Menu(Calculator& calc);