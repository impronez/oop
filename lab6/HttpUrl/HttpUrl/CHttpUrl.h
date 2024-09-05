#include "stdafx.h"

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL()const;

    // возвращает доменное им€
    std::string GetDomain()const;

    /*
        ¬озвращает им€ документа. ѕримеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // возвращает тип протокола
    Protocol GetProtocol()const;

    // возвращает номер порта
    unsigned short GetPort()const;

private:
    unsigned short m_port;
    Protocol m_protocol;
    std::string m_domain;
    std::string m_document;

    static const unsigned short MIN_PORT;
    static const unsigned short MAX_PORT;
    static const std::map<std::string, Protocol> STRING_TO_PROTOCOL;
    static const std::map<Protocol, std::string> PROTOCOL_TO_STRING;
    static const std::map<Protocol, unsigned short> PORT_OF_PROTOCOLS;
    static const std::string VALID_PROTOCOL_FOR_REGEX;
    static const std::string VALID_DOMAIN_FOR_REGEX;
    static const std::string VALID_PORT_FOR_REGEX;
    static const std::string VALID_DOCUMENT_FOR_REGEX;
    static const std::string SLASH_REGEX;
    static const char START_OF_STRING;
    static const char END_OF_STRING;
    static const std::regex VALID_URL_REGEX;
    static const std::regex VALID_DOMAIN_REGEX;
    static const std::regex VALID_DOCUMENT_REGEX;

    static bool IsValidDomain(std::string const& domain);
    static bool IsValidDocument(std::string const& document);
    static bool IsCorrectProtocol(Protocol protocol);
    static bool IsCorrectPort(unsigned short port);
    static Protocol GetProtocolByString(const std::string& str);

    unsigned short ParsePort(const std::string& str);
    std::string ParseDocument(std::string const& document);
};