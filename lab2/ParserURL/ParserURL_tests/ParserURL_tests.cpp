#define CATCH_CONFIG_MAIN
#include "../ParserURL/ParserURL.h"
#include "../../../../catch/catch.hpp"

SCENARIO("Check function of protocol identification")
{
	std::string str;
	Protocol protocol;
	WHEN("Protocol is 'http'")
	{
		str = "http";
		protocol = IdentifyProtocol(str);
		THEN("Protocol is Protocol::HTTP")
		{
			REQUIRE(protocol == Protocol::HTTP);
		}
	}

	WHEN("Protocol is 'https' in upper case")
	{
		str = "HTTPS";
		protocol = IdentifyProtocol(str);
		THEN("Protocol is Protocol::HTTPS")
		{
			REQUIRE(protocol == Protocol::HTTPS);
		}
	}

	WHEN("Protocol is 'ftp' in different cases")
	{
		str = "FtP";
		protocol = IdentifyProtocol(str);
		THEN("Protocol is Protocol::FTP")
		{
			REQUIRE(protocol == Protocol::FTP);
		}
	}
}

SCENARIO("Check function of port identification from protocol")
{
	int port;
	Protocol protocol;
	WHEN("Protocol is 'http'")
	{
		protocol = Protocol::HTTP;
		port = IdentifyPortFromProtocol(protocol);
		THEN("Port is 80")
		{
			REQUIRE(port == 80);
		}
	}

	WHEN("Protocol is 'https'")
	{
		protocol = Protocol::HTTPS;
		port = IdentifyPortFromProtocol(protocol);
		THEN("Port is 443")
		{
			REQUIRE(port == 443);
		}
	}

	WHEN("Protocol is 'ftp'")
	{
		protocol = Protocol::FTP;
		port = IdentifyPortFromProtocol(protocol);
		THEN("Port is 21")
		{
			REQUIRE(port == 21);
		}
	}

	WHEN("Protocol is not identified")
	{
		port = IdentifyPortFromProtocol(protocol);
		THEN("Port is 0")
		{
			REQUIRE(port == 0);
		}
	}
}

SCENARIO("When input is incorrect")
{
	std::string str;
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	WHEN("Input is an empty string")
	{
		str = "";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Not parsed")
		{
			REQUIRE(!isParsed);
		}
	}

	WHEN("Input is url without protocol")
	{
		str = "www.vk.com";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Not parsed")
		{
			REQUIRE(!isParsed);
		}
	}

	WHEN("Input is incorrect url")
	{
		str = "https:/www.vk.com";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Not parsed")
		{
			REQUIRE(!isParsed);
		}
	}

	WHEN("Input is url without with empty host")
	{
		str = "https://";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Not parsed")
		{
			REQUIRE(!isParsed);
		}
	}
}

SCENARIO("When input is correct")
{
	std::string str;
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	WHEN("Input is correct url without document")
	{
		str = "https://vk.com";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Parsed")
		{
			REQUIRE(isParsed);
		}
	}

	WHEN("Input is correct url with port")
	{
		str = "https://localhost:8000";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Parsed")
		{
			REQUIRE(isParsed);
		}
	}

	WHEN("Input is correct url")
	{
		str = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Parsed")
		{
			REQUIRE(isParsed);
		}
	}
}

SCENARIO("Check returned values of parsing url")
{
	std::string str;
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	WHEN("Input is correct url")
	{
		str = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		bool isParsed = ParseURL(str, protocol, port, host, doc);
		THEN("Return correct host, port and doc")
		{
			REQUIRE(protocol == Protocol::HTTP);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(port == 80);
			REQUIRE(doc == "docs/document1.html?page=30&lang=en#title");
		}
	}
}

// TODO: проверить : после протокола
// TODO: https://localhost:/dfgj
// TODO: min/max for port