#pragma once
#include "IShape.h"
#include "stdafx.h"
class ShapesController
{
public:

	void ReadingData(std::istream& input, std::ostream& output);

	void AddShape(std::ostream& output, const std::string& line);

	void AddCircle(std::istringstream& params);

	void AddTriangle(std::istringstream& params);

	void AddRectangle(std::istringstream& params);

	void AddLineSegment(std::istringstream& params);

	void PrintCommandExamples(std::ostream& output) const;

	std::shared_ptr<IShape> GetShapeWithMaxArea() const;

	std::shared_ptr<IShape> GetShapeWithMinPerimeter() const;

	bool IsShapesExisting() const;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes{};
};