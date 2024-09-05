#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include "../Html Decode/Decoder.h"

SCENARIO("Decode special symbols")
{
	WHEN("Symbol is encoded")
	{
		std::string decoded = HtmlDecode(DOUBLE_QUOTE);
		REQUIRE(decoded == "\"");

		decoded = HtmlDecode(APOSTROPHE);
		REQUIRE(decoded == "\'");

		decoded = HtmlDecode(LESS);
		REQUIRE(decoded == "<");
	
		decoded = HtmlDecode(MORE);
		REQUIRE(decoded == ">");
	
		decoded = HtmlDecode(AMPERSAND);
		REQUIRE(decoded == "&");
	}

	WHEN("Symbol is not encoded")
	{
		std::string str = HtmlDecode("1234");
		REQUIRE(str == "1234");

		str = HtmlDecode("");
		REQUIRE(str.empty());
	}
}

SCENARIO("Input string is empty")
{
	std::string str = StringProcessing("");
	REQUIRE(str == "");
}

SCENARIO("Decode encoded string")
{
	std::string decoded = StringProcessing("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	REQUIRE(decoded == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("Decode not encoded string")
{
	std::string str = StringProcessing("1234&gt3;;");
	REQUIRE(str == "1234&gt3;;");
}