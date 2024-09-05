#pragma once

#include <iostream>
#include <string>

const char AMPERSAND_SIGN = '&';
const char SEMICOLON_SIGN = ';';
const char DOUBLE_QUOTE_SIGN = '"';
const char APOSTROPHE_SIGN = '\'';
const char LESS_SIGN = '<';
const char MORE_SIGN = '>';
const std::string DOUBLE_QUOTE = "&quot;";
const std::string APOSTROPHE = "&apos;";
const std::string LESS = "&lt;";
const std::string MORE = "&gt;";
const std::string AMPERSAND = "&amp;";
const int MIN_LENGTH_OF_ENCODE_SYMBOLS = 4;
const int MAX_LENGTH_OF_ENCODE_SYMBOLS = 6;

std::string HtmlDecode(std::string const& str);

std::string StringProcessing(std::string const& html);