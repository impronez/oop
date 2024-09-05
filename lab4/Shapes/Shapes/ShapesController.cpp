#include "ShapesController.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

const std::string CIRCLE = "circle";
const std::string TRIANGLE = "triangle";
const std::string RECTANGLE = "rectangle";
const std::string LINE_SEGMENT = "linesegment";

void ShapesController::ReadingData(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		try
		{
			AddShape(output, line);
		}
		catch (const std::exception& e)
		{
			output << e.what() << std::endl;
		}
	}
}

void ShapesController::AddShape(std::ostream& output, const std::string& line)
{
	std::istringstream str(line);
	std::string shape;
	str >> shape;

	if (shape == CIRCLE)
	{
		AddCircle(str);
		output << "Circle added!\n";
	}
	else if (shape == TRIANGLE)
	{
		AddTriangle(str);
		output << "Triangle added!\n";
	}
	else if (shape == RECTANGLE)
	{
		AddRectangle(str);
		output << "Rectangle added!\n";
	}
	else if (shape == "linesegment")
	{
		AddLineSegment(str);
		output << "Line segment added!\n";
	}
	else
	{
		output << "Unknown shape!\n";
	}
}

void ShapesController::AddCircle(std::istringstream& params)
{
	double centerX, centerY, radius;
	uint32_t outlineColor, fillColor;
	if (!(params >> centerX >> centerY >> radius >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid parameters!");
	}
	CPoint center({ centerX, centerY });

	m_shapes.emplace_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));
}

void ShapesController::AddTriangle(std::istringstream& params)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t outlineColor, fillColor;
	if (!(params >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid parameters");
	}
	CPoint vertex1({ x1, y1 }), vertex2({ x2, y2 }), vertex3({ x3, y3 });

	m_shapes.emplace_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
}

void ShapesController::AddRectangle(std::istringstream& params)
{
	double x, y, width, height;
	uint32_t outlineColor, fillColor;
	if (!(params >> x >> y >> width >> height >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid parameters");
	}
	CPoint leftTop({ x, y });

	m_shapes.emplace_back(std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor));
}

void ShapesController::AddLineSegment(std::istringstream& params)
{
	double x1, y1, x2, y2;
	uint32_t outlineColor;
	if (!(params >> x1 >> y1 >> x2 >> y2 >> std::hex >> outlineColor))
	{
		throw std::invalid_argument("Invalid parameters");
	}
	CPoint startPoint({ x1, y1 }), endPoint({ x2, y2 });

	m_shapes.emplace_back(std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor));
}

void ShapesController::PrintCommandExamples(std::ostream& output) const
{
	output << "Commands:\n";
	output << "linesegment 'x1' 'y1' 'x2' 'y2' 'outline color'\n";
	output << "circle 'x(center)' 'y(center)' 'radius' 'outline color' 'fill color'\n";
	output << "triangle 'x1' 'y1' 'x2' 'y2' 'x3' 'y3' 'outline color' 'fill color'\n";
	output << "rectangle 'x(left top)' 'y(left top) 'width' 'height' 'outline color' 'fill color'\n";
}

std::shared_ptr<IShape> ShapesController::GetShapeWithMaxArea() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto maxAreaShape = *std::max_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& first, const auto& second) { return first->GetArea() < second->GetArea(); });

	return maxAreaShape;
}

std::shared_ptr<IShape> ShapesController::GetShapeWithMinPerimeter() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto minPerimeterShape = *std::min_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& first, const auto& second) { return first->GetPerimeter() < second->GetPerimeter(); });

	return minPerimeterShape;
}

bool ShapesController::IsShapesExisting() const
{
	return !m_shapes.empty();
}
