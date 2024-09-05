#include "ParserURL.h"

void PrintInfoAboutURL(bool& isValid, const std::string& host, const int& port, const std::string& document)
{
    if (isValid)
    {
        std::cout << "HOST: " << host << "\nPORT: " << port << "\nDOC: " << document << std::endl;
        
    }
    else
    {
        std::cout << "Entered URL-address is not valid.\n";
    }
}

int main()
{
    std::string url;
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    while (1)
    {
        std::cout << "Enter URL-address:\n";
        std::getline(std::cin, url);
        if (std::cin.eof() || url.empty())
        {
            break;
        }
        bool isValideURL = ParseURL(url, protocol, port, host, document);
        PrintInfoAboutURL(isValideURL, host, port, document);
    }
}