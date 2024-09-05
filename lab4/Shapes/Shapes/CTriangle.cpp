#include "CTriangle.h"

const std::string TRIANGLE = "triangle";

double CTriangle::GetArea() const
{
    return 0.5 * fabs(((m_vertex2.x - m_vertex1.x) * (m_vertex3.y - m_vertex1.y)
        - (m_vertex3.x - m_vertex1.x) * (m_vertex2.y - m_vertex1.y)));
}

double CTriangle::GetPerimeter() const
{
    double side1 = GetSide(m_vertex1, m_vertex2);
    double side2 = GetSide(m_vertex2, m_vertex3);
    double side3 = GetSide(m_vertex3, m_vertex1);

    return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
    return std::format("\nName: {}"
        "\nArea: {}"
        "\nPerimeter: {}"
        "\nOutline color: #{:06x}"
        "\nFill color: #{:06x}"
        "\nVertex1: ({}, {})"
        "\nVertex2: ({}, {})"
        "\nVertex3: ({}, {})\n",
        TRIANGLE,
        CTriangle::GetArea(),
        CTriangle::GetPerimeter(),
        m_outlineColor,
        m_fillColor,
        m_vertex1.x, m_vertex1.y,
        m_vertex2.x, m_vertex2.y,
        m_vertex3.x, m_vertex3.y
    );
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}

double CTriangle::GetSide(CPoint vertex1, CPoint vertex2)
{
    return sqrt(pow(vertex1.x - vertex2.x,2) + pow((vertex1.y - vertex2.y), 2));
}
