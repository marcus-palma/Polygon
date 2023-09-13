#include "Rectangle.h"
#include <iostream>

// Put the shape name here:
#define ShapeType Rectangle

using std::cout; using std::endl; using std::cin;

void P::ShapeType::AskDimensions()
{
	int length, height;

	cout << "How long do you want " << P::Polygon::GetShapeName() << " to be?" << endl;
	cin >> length;
	cout << "How high do you want the " << P::Polygon::GetShapeName() << " to be?" << endl;
	cin >> height;

	P::Polygon::SetDimensions(length, height);
}

void P::ShapeType::CalculateArea()
{
	int length, height;

	std::string direction_l = "length";
	std::string direction_h = "height";
	length = P::Polygon::GetDimension(direction_l);
	height = P::Polygon::GetDimension(direction_h);

	P::Polygon::SetArea(length * height);
}
