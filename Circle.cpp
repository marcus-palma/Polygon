#include "Circle.h"
#include <iostream>

// Put the shape name here:
#define ShapeType Circle

#define Pi 3.14159265358979323846

using std::cout; using std::endl; using std::cin;

void P::ShapeType::AskDimensions()
{
	int length;

	cout << "How big radius do you want the " << P::Polygon::GetShapeName() << " to have?" << endl;
	cin >> length;

	P::Polygon::SetDimensions(length, 0);
}

void P::ShapeType::CalculateArea()
{
	int radius, area;

	std::string direction_l = "length";
	radius = P::Polygon::GetDimension(direction_l);

	area = round(Pi * radius * radius * 0.5);

	P::Polygon::SetArea(area);
}
