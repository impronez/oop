#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:	
	CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor)
		: m_vertex1(v1),
		m_vertex2(v2),
		m_vertex3(v3),
		m_outlineColor(outlineColor),
		m_fillColor(fillColor) 
	{
		double side1 = GetSide(m_vertex1, m_vertex2);
		double side2 = GetSide(m_vertex2, m_vertex3);
		double side3 = GetSide(m_vertex1, m_vertex3);

		if ((side1 + side2 <= side3) || (side1 + side3 <= side2) || (side2 + side3 <= side1))
		{
			throw std::invalid_argument("Invalid triangle points");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;

	CPoint GetVertex2() const;

	CPoint GetVertex3() const;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;

	uint32_t m_outlineColor, m_fillColor;
	
	static double GetSide(CPoint vertex1, CPoint vertex2);
};

