#include "stdafx.h"

#pragma once
class CUrlParsingError : public std::invalid_argument
{
public:

	CUrlParsingError(const std::string& message)
		: std::invalid_argument(message) {}
};

