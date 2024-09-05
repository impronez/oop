#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <cctype>

// TODO: using std ������ ������������ � h-������ � ��������� �������
/*��� ����� ���������� �������� �������� ���� � ����� ������ ������, 
������� �������� ���� ���������. ��� ������� �������� a using namespace, 
��� �������� ��� ����� ��������, �� ������� ��� ��� ������. */

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