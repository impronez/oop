#define CATCH_CONFIG_MAIN
#include "../Shapes/stdafx.h"
#include "../../../../catch/catch.hpp"
#include "../Shapes/CCircle.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CPoint.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/ShapesController.h"

TEST_CASE("Test circle")
{
	CPoint center({ 0, 0 });
	double radius = 10;
	uint32_t outlineColor = 132, fillColor = 145;
	CCircle circle(center, radius, outlineColor, fillColor);
	GIVEN("Check constructor")
	{
		WHEN("Incorrect radius")
		{
			radius = 0;
			REQUIRE_THROWS(CCircle(center, radius, outlineColor, fillColor));

			radius = -1;
			REQUIRE_THROWS(CCircle(center, radius, outlineColor, fillColor));
		}

		WHEN("Success construction")
		{
			REQUIRE_NOTHROW(CCircle(center, radius, outlineColor, fillColor));
		}
	}

	WHEN("Check area")
	{
		double area = M_PI * pow(radius, 2);
		THEN("area == circle.GetArea()")
		{
			REQUIRE(circle.GetArea() == area);
		}
	}

	WHEN("Check perimeter")
	{
		double perimeter = 2 * M_PI * radius;
		THEN("perimeter == circle.GetPerimeter()")
		{
			REQUIRE(circle.GetPerimeter() == perimeter);
		}
	}

	WHEN("Check colors")
	{
		REQUIRE(circle.GetOutlineColor() == outlineColor);
		REQUIRE(circle.GetFillColor() == fillColor);
	}

	WHEN("Check center")
	{
		REQUIRE(circle.GetCenter().x == center.x);
		REQUIRE(circle.GetCenter().y == center.y);
	}

	WHEN("Check radius")
	{
		REQUIRE(circle.GetRadius() == radius);
	}
}

TEST_CASE("Test triangle")
{
	CPoint v1({ 0, 0 }), v2({ 2, 3 }), v3({ -5, 7 });
	uint32_t outlineColor = 132, fillColor = 145;
	CTriangle triangle(v1, v2, v3, outlineColor, fillColor);
	GIVEN("Check constructor")
	{
		WHEN("Sides are equal")
		{
			v1 = { 0, 0 }, v2 = { 1, 1 }, v3 = { 2, 2 };
			THEN("Error")
			{
				REQUIRE_THROWS(CTriangle(v1, v2, v3, outlineColor, fillColor));
			}
		}

		WHEN("Success construction")
		{
			REQUIRE_NOTHROW(CTriangle(v1, v2, v3, outlineColor, fillColor));
		}
	}


	WHEN("Check area")
	{
		double area = 0.5 * fabs(((v2.x - v1.x) * (v3.y - v1.y)
			- (v3.x - v1.x) * (v2.y - v1.y)));
		THEN("area == triangle.GetArea()")
		{
			REQUIRE(triangle.GetArea() == area);
		}
	}

	WHEN("Check perimeter")
	{
		double side1 = sqrt(pow(v1.x - v2.x, 2) + pow((v1.y - v2.y), 2));
		double side2 = sqrt(pow(v2.x - v3.x, 2) + pow((v2.y - v3.y), 2));
		double side3 = sqrt(pow(v1.x - v3.x, 2) + pow((v1.y - v3.y), 2));
		double perimeter = side1 + side2 + side3;
		THEN("perimeter == triangle.GetPerimeter()")
		{
			REQUIRE(triangle.GetPerimeter() == perimeter);
		}
	}

	WHEN("Check colors")
	{
		REQUIRE(triangle.GetOutlineColor() == outlineColor);
		REQUIRE(triangle.GetFillColor() == fillColor);
	}

	WHEN("Check points")
	{
		REQUIRE(v1.x == triangle.GetVertex1().x);
		REQUIRE(v1.y == triangle.GetVertex1().y);
		REQUIRE(v2.x == triangle.GetVertex2().x);
		REQUIRE(v2.y == triangle.GetVertex2().y);
		REQUIRE(v3.x == triangle.GetVertex3().x);
		REQUIRE(v3.y == triangle.GetVertex3().y);
	}
}

TEST_CASE("Test rectangle")
{
	CPoint leftTop({ 0, 0 });
	double width = 10, height = 5;
	uint32_t outlineColor = 132, fillColor = 145;
	CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

	GIVEN("Check constructor")
	{
		WHEN("Incorrect values of height and width")
		{
			width = 0;
			REQUIRE_THROWS(CRectangle(leftTop, width, height, outlineColor, fillColor));

			width = 10, height = -1;
			REQUIRE_THROWS(CRectangle(leftTop, width, height, outlineColor, fillColor));

			width = 0, height = -1;
			REQUIRE_THROWS(CRectangle(leftTop, width, height, outlineColor, fillColor));
		}

		WHEN("Success")
		{
			REQUIRE_NOTHROW(CRectangle(leftTop, width, height, outlineColor, fillColor));
		}
	}

	WHEN("Check area")
	{
		double area = width * height;
		THEN("area == rectangle.GetArea()")
		{
			REQUIRE(rectangle.GetArea() == area);
		}
	}

	WHEN("Check perimeter")
	{
		double perimeter = (width + height) * 2;
		THEN("perimeter == triangle.GetPerimeter()")
		{
			REQUIRE(rectangle.GetPerimeter() == perimeter);
		}
	}

	WHEN("Check colors")
	{
		REQUIRE(rectangle.GetOutlineColor() == outlineColor);
		REQUIRE(rectangle.GetFillColor() == fillColor);
	}

	WHEN("Check point")
	{
		REQUIRE(leftTop.x == rectangle.GetLeftTop().x);
		REQUIRE(leftTop.y == rectangle.GetLeftTop().y);
	}

	WHEN("Check width")
	{
		REQUIRE(width == rectangle.GetWidth());
	}

	WHEN("Check height")
	{
		REQUIRE(height == rectangle.GetHeight());
	}
}

TEST_CASE("Check line segment")
{
	CPoint startPoint({ 0, 0 }), endPoint({ 5,5 });
	uint32_t outlineColor = 134;
	CLineSegment lineSegment(startPoint, endPoint, outlineColor);

	GIVEN("Check constructor")
	{
		WHEN("Coordinates of points are equal")
		{
			endPoint = startPoint;
			REQUIRE_THROWS(CLineSegment(startPoint, endPoint, outlineColor));
		}

		WHEN("Success")
		{

			REQUIRE_NOTHROW(CLineSegment(startPoint, endPoint, outlineColor));
		}
	}

	WHEN("Check area")
	{
		THEN("Area is 0")
		{
			REQUIRE(lineSegment.GetArea() == 0);
		}
	}

	WHEN("Check perimeter")
	{
		double perimeter = sqrt(pow((endPoint.x - startPoint.x), 2) + pow((endPoint.y - startPoint.y), 2));
		THEN("Perimeter = lineSegment.GetPerimeter()")
		{
			REQUIRE(lineSegment.GetPerimeter() == perimeter);
		}
	}
	
	WHEN("Check color")
	{
		REQUIRE(lineSegment.GetOutlineColor() == outlineColor);
	}

	WHEN("Check points")
	{
		REQUIRE(startPoint.x == lineSegment.GetStartPoint().x);
		REQUIRE(startPoint.y == lineSegment.GetStartPoint().y);
		REQUIRE(endPoint.x == lineSegment.GetEndPoint().x);
		REQUIRE(endPoint.y == lineSegment.GetEndPoint().y);
	}
}

TEST_CASE("Test shapes controller")
{
	ShapesController controller;

	GIVEN("Check reading data")
	{
		WHEN("Input data is correct")
		{
			std::istringstream circle("circle 70 -30 20 0xff0000 0x00ff00");
			THEN("Success adding shape")
			{
				controller.ReadingData(circle, std::cout);
				REQUIRE(controller.IsShapesExisting());
			}
			std::istringstream triangle("triangle 0 0 1.5 1.5 5 3 0xff0000 0x00ff00");
			THEN("Success adding shape")
			{
				controller.ReadingData(triangle, std::cout);
				REQUIRE(controller.IsShapesExisting());
			}
			std::istringstream lineSegment("linesegment 0 0 -50.23 -50.23 0xff0000");
			THEN("Success adding shape")
			{
				controller.ReadingData(lineSegment, std::cout);
				REQUIRE(controller.IsShapesExisting());
			}
			std::istringstream rectangle("rectangle -100 23 100 50 0xff0000 0x00ff00");
			THEN("Success adding shape")
			{
				controller.ReadingData(rectangle, std::cout);
				REQUIRE(controller.IsShapesExisting());
			}
		}
		WHEN("Input data is incorrect")
		{
			std::istringstream unknownShape("ball 0 0 30 0xff000");
			REQUIRE(!controller.IsShapesExisting());
		}
	}

	GIVEN("Test adding shapes")
	{
		WHEN("Adding circle with incorrect params")
		{
			std::istringstream params("0 0 0xff000 0x00ff00");
			THEN("Error adding")
			{
				REQUIRE_THROWS(controller.AddCircle(params));
			}
		}

		WHEN("Adding circle with correct params")
		{
			std::istringstream params("0 0 100 0xff000 0x00ff00");
			THEN("Adding success")
			{
				REQUIRE_NOTHROW(controller.AddCircle(params));
			}
		}

		WHEN("Adding triangle with incorrect params")
		{
			std::istringstream params("0 0 2 3 5.4 7.8 0xff000");
			THEN("Adding success")
			{
				REQUIRE_THROWS(controller.AddTriangle(params));
			}
		}

		WHEN("Adding triangle with correct params")
		{
			std::istringstream params("0 0 2 3 5.4 7.8 0xff000 0x00ff00");
			THEN("Adding success")
			{
				REQUIRE_NOTHROW(controller.AddTriangle(params));
			}
		}

		WHEN("Adding rectangle with incorrect params")
		{
			std::istringstream params("0 0 100 xD 0xff000 0x00ff00");
			THEN("Adding success")
			{
				REQUIRE_THROWS(controller.AddRectangle(params));
			}
		}

		WHEN("Adding rectangle with correct params")
		{
			std::istringstream params("0 0 100 50 0xff000 0x00ff00");
			THEN("Adding success")
			{
				REQUIRE_NOTHROW(controller.AddRectangle(params));
			}
		}

		WHEN("Adding line segment with incorrect params")
		{
			std::istringstream params("0 0 5 0xff0000");
			THEN("Adding success")
			{
				REQUIRE_THROWS(controller.AddLineSegment(params));
			}
		}

		WHEN("Adding line segment with correct params")
		{
			std::istringstream params("0 0 5 10 0xff0000");
			THEN("Adding success")
			{
				REQUIRE_NOTHROW(controller.AddLineSegment(params));
			}
		}
	}

	GIVEN("Check shape with min perimeter")
	{
		WHEN("There are not existing shapes")
		{
			ShapesController controller;
			REQUIRE(controller.GetShapeWithMinPerimeter() == nullptr);
		}

		WHEN("Check shape with min perimeter")
		{
			std::istringstream circleParams("0 0 100 0xff000 0x00ff00");
			std::istringstream triangleParams("0 0 2 3 5.4 7.8 0xff000 0x00ff00");
			controller.AddCircle(circleParams);
			controller.AddTriangle(triangleParams);
			REQUIRE(controller.GetShapeWithMinPerimeter() != nullptr);
		}
	}

	GIVEN("Check shape with max area")
	{
		WHEN("There are not existing shapes")
		{
			ShapesController controller;
			REQUIRE(controller.GetShapeWithMaxArea() == nullptr);
		}

		WHEN("Check shape with min perimeter")
		{
			std::istringstream circleParams("0 0 100 0xff000 0x00ff00");
			std::istringstream triangleParams("0 0 2 3 5.4 7.8 0xff000 0x00ff00");
			controller.AddCircle(circleParams);
			controller.AddTriangle(triangleParams);
			REQUIRE(controller.GetShapeWithMaxArea() != nullptr);
		}
	}

	WHEN("Check existing shapes")
	{
		REQUIRE(!controller.IsShapesExisting());

		std::istringstream triangleParams("0 0 2 3 5.4 7.8 0xff000 0x00ff00");
		controller.AddTriangle(triangleParams);
		REQUIRE(controller.IsShapesExisting());
	}
	
}