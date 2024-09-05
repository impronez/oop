#include "CHttpUrl.h"
#include "CUrlParsingError.h"

const char SLASH = '/';

const std::map<std::string, Protocol> CHttpUrl::STRING_TO_PROTOCOL =
{
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS }
};

const std::map<Protocol, std::string> CHttpUrl::PROTOCOL_TO_STRING =
{
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" }
};

const std::map<Protocol, unsigned short> CHttpUrl::PORT_OF_PROTOCOLS =
{
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 }
};

const unsigned short CHttpUrl::MIN_PORT = 1;
const unsigned short CHttpUrl::MAX_PORT = 65535;
const std::string CHttpUrl::VALID_PROTOCOL_FOR_REGEX = "(https?):\\/\\/";
const std::string CHttpUrl::VALID_DOMAIN_FOR_REGEX = "((www\\.)?(\\w+\\d*)(\\.\\w+)*)";
const std::string CHttpUrl::VALID_PORT_FOR_REGEX = "(:(\\d{1,5}))?";
const std::string CHttpUrl::VALID_DOCUMENT_FOR_REGEX = "(\\/\\S*)?";
const char CHttpUrl::START_OF_STRING = '^';
const char CHttpUrl::END_OF_STRING = '$';

const std::regex CHttpUrl::VALID_URL_REGEX = std::regex(START_OF_STRING + VALID_PROTOCOL_FOR_REGEX
	+ VALID_DOMAIN_FOR_REGEX + VALID_PORT_FOR_REGEX + VALID_DOCUMENT_FOR_REGEX + END_OF_STRING,
	std::regex::icase);
const std::regex CHttpUrl::VALID_DOMAIN_REGEX = std::regex(START_OF_STRING + VALID_DOMAIN_FOR_REGEX + END_OF_STRING);
const std::regex CHttpUrl::VALID_DOCUMENT_REGEX = std::regex(START_OF_STRING + VALID_DOCUMENT_FOR_REGEX + END_OF_STRING);

bool CHttpUrl::IsValidDomain(std::string const& domain)
{
	std::cmatch match;
	if (std::regex_match(domain.c_str(), match, VALID_DOMAIN_REGEX))
	{
		return true;
	}
	return false;
}

bool CHttpUrl::IsValidDocument(std::string const& document)
{
	std::cmatch match;
	if (std::regex_match(document.c_str(), match, VALID_DOCUMENT_REGEX))
	{
		return true;
	}
	return false;
}

bool CHttpUrl::IsCorrectProtocol(Protocol protocol)
{
	for (auto it = STRING_TO_PROTOCOL.begin(); it != STRING_TO_PROTOCOL.end(); it++)
	{
		if (protocol == it->second)
		{
			return true;
		}
	}
	return false;
}

bool CHttpUrl::IsCorrectPort(unsigned short port)
{
	return port >= MIN_PORT && port <= MAX_PORT;
}

std::string StringToLowerCase(const std::string& str)
{
	std::string lowerStr = "";
	for (auto ch : str)
	{
		lowerStr += tolower(ch);
	}
	return lowerStr;
}

std::string CHttpUrl::ParseDocument(std::string const& document)
{
	std::string doc;
	if (document.empty())
	{
		return std::string(1, SLASH);
	}
	if (document[0] != SLASH)
	{
		doc = SLASH + document;
	}
	else
	{
		doc = document;
	}

	if (!IsValidDocument(doc))
	{
		throw std::invalid_argument("Invalid document!");
	}

	return doc;
}

Protocol CHttpUrl::GetProtocolByString(const std::string& str)
{
	std::string protocol = StringToLowerCase(str);
	if (STRING_TO_PROTOCOL.find(protocol) != STRING_TO_PROTOCOL.end())
	{
		return STRING_TO_PROTOCOL.at(protocol);
	}

	throw CUrlParsingError("Invalid protocol!");
}

unsigned short CHttpUrl::ParsePort(const std::string& str)
{
	if (str.empty())
	{
		return PORT_OF_PROTOCOLS.at(m_protocol);
	}
	int port = 0;
	try
	{
		port = std::stoi(str);
	}
	catch(...)
	{
		throw CUrlParsingError("Invalid port! The port must be in the range from 1 to 65535!");
	}
	return static_cast<unsigned short>(port);
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::cmatch match;
	if (!std::regex_match(url.c_str(), match, VALID_URL_REGEX))
	{
		throw CUrlParsingError("Invalid URL!");
	}

	m_protocol = GetProtocolByString(match[1]);
	m_port = ParsePort(match[7]);
	m_domain = match[2];
	m_document = ParseDocument(match[8]);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, PORT_OF_PROTOCOLS.at(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (!IsValidDomain(domain))
	{
		throw std::invalid_argument("Invalid domain!");
	}
	if (!IsCorrectProtocol(protocol))
	{
		throw std::invalid_argument("Invalid protocol!");
	}
	if (!IsCorrectPort(port))
	{
		throw std::invalid_argument("Invalid port!");
	}

	m_document = ParseDocument(document);
	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	return PROTOCOL_TO_STRING.at(m_protocol) + "://" + m_domain + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
