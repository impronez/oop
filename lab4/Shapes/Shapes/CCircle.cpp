#include "CCircle.h"
#include <format>

const std::string CIRCLE = "circle";

double CCircle::GetArea() const
{
    return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
    return std::format("\nName: {}"
        "\nArea: {}"
        "\nPerimeter: {}"
        "\nOutline color: #{:06x}"
        "\nFill color: #{:06x}"
        "\nCenter: ({}, {})"
        "\nRadius: {}\n",
        CIRCLE,
        CCircle::GetArea(),
        CCircle::GetPerimeter(),
        m_outlineColor,
        m_fillColor,
        m_center.x, m_center.y,
        m_radius
    );
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}
