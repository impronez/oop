#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:

	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
		: m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
	{
		if (startPoint.x == endPoint.x && startPoint.y == endPoint.y)
		{
			throw std::invalid_argument("Invalid line segment points");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;

	CPoint GetEndPoint() const;

private:

	CPoint m_startPoint, m_endPoint;

	uint32_t m_outlineColor;
};

