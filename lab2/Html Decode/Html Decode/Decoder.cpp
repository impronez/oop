#include "Decoder.h"

std::string HtmlDecode(std::string const& str)
{
    std::string result;

    
    if (str == DOUBLE_QUOTE)
    {
        result = DOUBLE_QUOTE_SIGN;
    }
    else if (str == APOSTROPHE)
    {
        result = APOSTROPHE_SIGN;
    }
    else if (str == LESS)
    {
        result = LESS_SIGN;
    }
    else if (str == MORE)
    {
        result = MORE_SIGN;
    }
    else if (str == AMPERSAND)
    {
        result = AMPERSAND_SIGN;
    }
    else
    {
        result = str;
    }

    return result;
}

std::string StringProcessing(std::string const& html)
{
    size_t pos = 0;
    std::string decodeString;
    
    while (pos < html.length())
    {
        size_t ampPos = html.find(AMPERSAND_SIGN, pos);
        if (ampPos == std::string::npos)
        {
            decodeString.append(html, pos, html.length() - pos);
            break;
        }

        decodeString.append(html, pos, ampPos - pos);

        size_t semPos = html.find(SEMICOLON_SIGN, ampPos);
        if (semPos != std::string::npos)
        {
            semPos += 1; // добавляем позицию последнего символа
            if ((semPos - ampPos < MIN_LENGTH_OF_ENCODE_SYMBOLS)
                || (semPos - ampPos > MAX_LENGTH_OF_ENCODE_SYMBOLS))
            {
                decodeString.append(html, ampPos, semPos - ampPos);
            }
            else
            {
                decodeString.append(HtmlDecode(html.substr(ampPos, semPos - ampPos)));
            }
            pos = semPos;
        }
        else
        {
            decodeString.append(html, ampPos, html.length() - ampPos);
            break;
        }
    }
    return decodeString;
}
