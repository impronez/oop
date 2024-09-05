#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
		: m_center(center),
		m_radius(radius),
		m_outlineColor(outlineColor),
		m_fillColor(fillColor) 
	{
		if (radius <= 0)
		{
			throw std::invalid_argument("Invalid radius");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetCenter() const;

	double GetRadius() const;

private:
	CPoint m_center;

	double m_radius;

	uint32_t m_outlineColor, m_fillColor;
};

