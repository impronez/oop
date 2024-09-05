#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height,
		uint32_t outlineColor, uint32_t fillColor) 
		: m_leftTop(leftTop),
		m_width(width),
		m_height(height),
		m_outlineColor(outlineColor),
		m_fillColor(fillColor)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Invalid rectangle sizes");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;

	double GetWidth() const;

	double GetHeight() const;

private:
	CPoint m_leftTop;

	double m_width, m_height;

	uint32_t m_outlineColor, m_fillColor;
};

