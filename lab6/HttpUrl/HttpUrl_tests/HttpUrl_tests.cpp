#define CATCH_CONFIG_MAIN
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"
#include "../../../../catch/catch.hpp"


TEST_CASE("Constructor")
{
	GIVEN("Constructor is set by URL-address")
	{
		WHEN("With port")
		{
			std::string protocol = "htTps";
			std::string domain = "www.mystr.com";
			std::string port = ":88";
			std::string document = "/images/search?img_url=https%3A%2F%2Fliderpoiska.ru%2Fupload%2Fblog_post_block%2Fhtml_t%2F10-25-01_lp_regexp_poster.jpg&lr=41&pos=2&rpt=simage&source=serp&text=обозначения%20regexp";
			std::string url = protocol + "://" + domain + port + document;
			std::string urlWithoutPort = "https://" + domain + document;

			REQUIRE_NOTHROW(CHttpUrl(url));
			CHttpUrl URL(url);
			REQUIRE(URL.GetDocument() == document);
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetPort() == 88);
			REQUIRE(URL.GetProtocol() == Protocol::HTTPS);
			REQUIRE(URL.GetURL() == urlWithoutPort);
		}

		WHEN("Without port")
		{
			std::string protocol = "htTps";
			std::string domain = "www.mystr.com";
			std::string document = "/images/search?img_url=https%3A%2F%2Fliderpoiska.ru%2Fupload%2Fblog_post_block%2Fhtml_t%2F10-25-01_lp_regexp_poster.jpg&lr=41&pos=2&rpt=simage&source=serp&text=обозначения%20regexp";
			std::string url = protocol + "://" + domain + document;
			std::string urlWithoutPort = "https://" + domain + document;

			REQUIRE_NOTHROW(CHttpUrl(url));
			CHttpUrl URL(url);
			REQUIRE(URL.GetDocument() == document);
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetPort() == 443);
			REQUIRE(URL.GetProtocol() == Protocol::HTTPS);
			REQUIRE(URL.GetURL() == urlWithoutPort);
		}

		WHEN("Document is empty")
		{
			std::string protocol = "htTps";
			std::string domain = "www.mystr.com";
			std::string document = "";
			std::string url = protocol + "://" + domain + document;

			REQUIRE_NOTHROW(CHttpUrl(url));
			CHttpUrl URL(url);
			REQUIRE(URL.GetDocument() == "/");
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetPort() == 443);
			REQUIRE(URL.GetProtocol() == Protocol::HTTPS);
			REQUIRE(URL.GetURL() == ("https://" + domain + "/"));
		}
	}

	GIVEN("Constructor is set by domain and document")
	{
		WHEN("Document is empty")
		{
			std::string domain = "string.com";
			std::string document = "";

			REQUIRE_NOTHROW(CHttpUrl(domain, document));
			CHttpUrl URL(domain, document);
			REQUIRE(URL.GetDocument() == "/");
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == Protocol::HTTP);
		}

		WHEN("Document is not empty")
		{
			std::string domain = "string.com";
			std::string document = "main/page=1";

			REQUIRE_NOTHROW(CHttpUrl(domain, document));
			CHttpUrl URL(domain, document);
			REQUIRE(URL.GetDocument() == ("/" + document));
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("Constructor is set by domain, document and protocol")
	{
		WHEN("Document is empty")
		{
			Protocol protocol = Protocol::HTTPS;
			std::string domain = "string.com";
			std::string document = "";

			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
			CHttpUrl URL(domain, document, protocol);
			REQUIRE(URL.GetDocument() == "/");
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == protocol);
		}

		WHEN("Document is not empty, protocol is https")
		{
			Protocol protocol = Protocol::HTTPS;
			std::string domain = "string.com";
			std::string document = "/home/task=1";

			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
			CHttpUrl URL(domain, document, protocol);
			REQUIRE(URL.GetDocument() == document);
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == protocol);
		}

		WHEN("Document is not empty, protocol is http")
		{
			Protocol protocol = Protocol::HTTP;
			std::string domain = "string.com";
			std::string document = "/isdog#12";

			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
			CHttpUrl URL(domain, document, protocol);
			REQUIRE(URL.GetDocument() == document);
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == protocol);
		}
	}

	GIVEN("Constructor is set by domain, document, protocol and port")
	{
		WHEN("Document is empty")
		{
			Protocol protocol = Protocol::HTTP;
			std::string domain = "www.string.com";
			std::string document = "/";
			unsigned short port = 88;

			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol, port));
			CHttpUrl URL(domain, document, protocol, port);
			REQUIRE(URL.GetDocument() == document);
			REQUIRE(URL.GetDomain() == domain);
			REQUIRE(URL.GetProtocol() == protocol);
			REQUIRE(URL.GetPort() == port);
		}

		WHEN("Document is not empty")
		{
			WHEN("Document is empty")
			{
				Protocol protocol = Protocol::HTTP;
				std::string domain = "www.string.com";
				std::string document = "/main-page";
				unsigned short port = 88;

				REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol, port));
				CHttpUrl URL(domain, document, protocol, port);
				REQUIRE(URL.GetDocument() == document);
				REQUIRE(URL.GetDomain() == domain);
				REQUIRE(URL.GetProtocol() == protocol);
				REQUIRE(URL.GetPort() == port);
			}
		}
	}

	GIVEN("Incorrect port")
	{
		std::string url = "https://sd:4w";
		REQUIRE_THROWS_AS(CHttpUrl(url), CUrlParsingError);
	}

	GIVEN("Incorrect domain")
	{
		WHEN("Domain is '...'")
		{
			std::string url = "http://...";
			REQUIRE_THROWS_AS(CHttpUrl(url), CUrlParsingError);
		}

		WHEN("Domain is empty")
		{
			std::string url = "http://";
			REQUIRE_THROWS_AS(CHttpUrl(url), CUrlParsingError);
		}
	}

	GIVEN("Incorrect document (with spaces)")
	{
		std::string url = "https://google.com/dog cat";
		REQUIRE_THROWS_AS(CHttpUrl(url), CUrlParsingError);
	}

	GIVEN("Protocol in different cases")
	{
		std::string url = "hTTPs://google.com/dogcat";
		REQUIRE_NOTHROW(CHttpUrl(url));
	}
}

TEST_CASE("Getting URL-address")
{
	GIVEN("URL is set by URL")
	{
		WHEN("Port is set")
		{
			std::string url = "https://drok.com:56/home";
			std::string urlWithoutPort = "https://drok.com/home";
			CHttpUrl URL(url);
			THEN("Return without port")
			{
				REQUIRE(URL.GetURL() == urlWithoutPort);
			}
		}

		WHEN("Document with port and without '/'")
		{
			std::string url = "https://drok.com:56";
			std::string urlWithoutPort = "https://drok.com/";
			CHttpUrl URL(url);
			THEN("Return correct url")
			{
				REQUIRE(URL.GetURL() == urlWithoutPort);
			}
		}

		WHEN("Document without port and '/'")
		{
			std::string url = "https://drok.com";
			std::string urlWithoutPort = "https://drok.com/";
			CHttpUrl URL(url);
			THEN("Return correct url")
			{
				REQUIRE(URL.GetURL() == urlWithoutPort);
			}
		}
	}

	GIVEN("URL is set by params")
	{
		WHEN("Port is set")
		{
			std::string domain = "drok.com";
			Protocol protocol = Protocol::HTTP;
			std::string document = "/home-page";
			unsigned short port = 120;
			CHttpUrl URL(domain, document, protocol, port);
			std::string url = "http://drok.com/home-page";
			THEN("Return without port")
			{
				REQUIRE(URL.GetURL() == url);
			}
		}

		WHEN("Document without '/'")
		{
			std::string domain = "drok.com";
			Protocol protocol = Protocol::HTTP;
			std::string document = "home-page";
			unsigned short port = 120;
			CHttpUrl URL(domain, document, protocol, port);
			std::string url = "http://drok.com/home-page";
			THEN("Return correct url")
			{
				REQUIRE(URL.GetURL() == url);
			}
		}
	}
}

TEST_CASE("Getting protocol")
{
	WHEN("Protocol is HTTP")
	{
		std::string url = "http://google.com";
		CHttpUrl URL(url);
		REQUIRE(URL.GetProtocol() == Protocol::HTTP);
	}

	WHEN("Protocol is HTTPS")
	{
		std::string url = "https://google.com";
		CHttpUrl URL(url);
		REQUIRE(URL.GetProtocol() == Protocol::HTTPS);
	}
}

TEST_CASE("Getting domain")
{
	WHEN("URL is set by URL-string")
	{
		std::string url = "https://google.com";
		CHttpUrl URL(url);
		REQUIRE(URL.GetDomain() == "google.com");
	}

	WHEN("URL is set by params")
	{
		std::string domain = "google.com";
		std::string document = "";

		CHttpUrl URL(domain, document);
		REQUIRE(URL.GetDomain() == domain);
	}
}

TEST_CASE("Getting document")
{
	WHEN("Document is set without slash")
	{
		std::string domain = "google.com";
		std::string document = "home-page";

		CHttpUrl URL(domain, document);
		REQUIRE(URL.GetDocument() == ("/" + document));
	}

	WHEN("Document is set with slash")
	{
		std::string domain = "google.com";
		std::string document = "/home-page";

		CHttpUrl URL(domain, document);
		REQUIRE(URL.GetDocument() == document);
	}
}

TEST_CASE("Getting port")
{
	WHEN("Port is not set (from params), protocol is http")
	{
		Protocol protocol = Protocol::HTTP;
		std::string domain = "drom.ru";
		std::string document = "";
		CHttpUrl URL(domain, document, protocol);
		THEN("Protocol is 80")
		{
			REQUIRE(URL.GetPort() == 80);
		}
	}

	WHEN("Port is not set (from params), protocol is https")
	{
		Protocol protocol = Protocol::HTTPS;
		std::string domain = "drom.ru";
		std::string document = "";
		CHttpUrl URL(domain, document, protocol);
		THEN("Protocol is 443")
		{
			REQUIRE(URL.GetPort() == 443);
		}
	}

	WHEN("Port is min")
	{
		Protocol protocol = Protocol::HTTPS;
		std::string domain = "drom.ru";
		std::string document = "";
		unsigned port = 1;
		CHttpUrl URL(domain, document, protocol, port);
		THEN("Protocol is 443")
		{
			REQUIRE(URL.GetPort() == port);
		}
	}

	WHEN("Port is max")
	{
		Protocol protocol = Protocol::HTTPS;
		std::string domain = "drom.ru";
		std::string document = "";
		unsigned port = 65535;
		CHttpUrl URL(domain, document, protocol, port);
		THEN("Protocol is 65535")
		{
			REQUIRE(URL.GetPort() == port);
		}
	}

	WHEN("Port is < min")
	{
		Protocol protocol = Protocol::HTTPS;
		std::string domain = "drom.ru";
		std::string document = "";
		unsigned port = 0;
		THEN("Except")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol, port), std::invalid_argument);
		}
	}

	WHEN("Port is > max")
	{
		Protocol protocol = Protocol::HTTPS;
		std::string domain = "drom.ru";
		std::string document = "";
		unsigned port = 65536;
		THEN("Except")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol, port), std::invalid_argument);
		}
	}
}