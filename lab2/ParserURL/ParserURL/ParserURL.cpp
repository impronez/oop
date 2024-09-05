#include "ParserURL.h"
#include <map>

using namespace std;

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

const map<Protocol, int> PORTS = {
    { Protocol::HTTP, DEFAULT_PORT_OF_HTTP },
    { Protocol::HTTPS, DEFAULT_PORT_OF_HTTPS },
    { Protocol::FTP, DEFAULT_PORT_OF_FTP }
};

const map<std::string, Protocol> PROTOCOLS =
{
    { "http", Protocol::HTTP },
    { "https", Protocol::HTTPS },
    { "ftp", Protocol::FTP }
};

void ToLowerCase(std::string& str)
{
    for (auto& ch : str)
    {
        ch = tolower(ch);
    }
}

int IdentifyPortFromProtocol(Protocol protocol)
{
    return PORTS.at(protocol);
}

bool IsCorrectPort(int port)
{
    return (port >= MIN_PORT && port <= MAX_PORT);
}

Protocol IdentifyProtocol(std::string line)
{
    ToLowerCase(line);
    return PROTOCOLS.at(line);
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    std::regex validUrl(R"((https?|ftp)://([^:/!]+)(?::(\d+))?(?:/(.*))?)", std::regex::icase);
    // TODO: узнать, что означает ?:, .*
    std::cmatch what;
    if (std::regex_match(url.c_str(), what, validUrl))
    {
        protocol = IdentifyProtocol(std::string(what[1]));
        if (std::string(what[3]).empty())
        {
            port = IdentifyPortFromProtocol(protocol);
        }
        else
        {
            port = std::stoi(std::string(what[3]));
        }
        if (!IsCorrectPort)
        {
            return false;
        }
        host = std::string(std::string(what[2]));
        document = std::string(std::string(what[4]));
        if (document.empty())
        {
            document += '/';
        }
        return true;
    }

    return false;
}

