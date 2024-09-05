#include <iostream>
#include <string>
#include "ShapesController.h"

void PrintShapeWithMaxArea(ShapesController& controller)
{
    std::shared_ptr<IShape> shape = controller.GetShapeWithMaxArea();
    std::cout << "Shape with max area:" << shape->ToString() << std::endl;
}

void PrintShapeWithMinPerimeter(ShapesController& controller)
{
    std::shared_ptr<IShape> shape = controller.GetShapeWithMinPerimeter();
    std::cout << "Shape with min perimeter:" << shape->ToString() << std::endl;
}

int main()
{
    ShapesController controller;
    controller.PrintCommandExamples(std::cout);
    controller.ReadingData(std::cin, std::cout);
    if (controller.IsShapesExisting())
    {
        std::cout << std::endl;
        PrintShapeWithMaxArea(controller);
        PrintShapeWithMinPerimeter(controller);
    }
    else
    {
        std::cout << "There are not existing shapes!\n";
    }
}