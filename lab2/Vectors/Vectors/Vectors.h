#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

std::vector<double> ReadData(std::istream& input, bool& isCorrectData);

void MultiplicationEachElementOnMinElement(std::vector<double>& numbers);