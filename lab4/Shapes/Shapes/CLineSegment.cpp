#include "CLineSegment.h"

const std::string LINE_SEGMENT = "line segment";

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return sqrt(pow((m_endPoint.x - m_startPoint.x), 2) + pow((m_endPoint.y - m_startPoint.y), 2));
}

std::string CLineSegment::ToString() const
{
    return std::format("\nName: {}"
        "\nArea: {}"
        "\nPerimeter: {}"
        "\nOutline color: #{:06x}"
        "\nStart point: ({}, {})"
        "\nEnd point: ({}, {})"
        "\nLength: \n",
        LINE_SEGMENT,
        CLineSegment::GetArea(),
        CLineSegment::GetPerimeter(),
        m_outlineColor,
        m_startPoint.x, m_startPoint.y,
        m_endPoint.x, m_endPoint.y
    );
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}