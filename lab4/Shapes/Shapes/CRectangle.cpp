#include "CRectangle.h"

const std::string RECTANGLE = "rectangle";

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return (m_width + m_height) * 2;
}

std::string CRectangle::ToString() const
{
    return std::format("\nName: {}"
        "\nArea: {}"
        "\nPerimeter: {}"
        "\nOutline color: #{:06x}"
        "\nFill color: #{:06x}"
        "\nLeft top: ({}, {})"
        "\nWidth: {}"
        "\nHeight: {}\n",
        RECTANGLE,
        CRectangle::GetArea(),
        CRectangle::GetPerimeter(),
        m_outlineColor,
        m_fillColor,
        m_leftTop.x, m_leftTop.y,
        m_width,
        m_height
    );
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}
