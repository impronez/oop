#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <cctype>

// TODO: using std нельзя использовать в h-файлах и объяснить поочему
/*Это может неожиданно изменить значение кода в любых других файлах, 
которые включают этот заголовок. Нет способа отменить a using namespace, 
что является еще одной причиной, по которой это так опасно. */

const int DEFAULT_PORT_OF_HTTP = 80;
const int DEFAULT_PORT_OF_HTTPS = 443;
const int DEFAULT_PORT_OF_FTP = 21;

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);

Protocol IdentifyProtocol(std::string line);

int IdentifyPortFromProtocol(Protocol protocol);