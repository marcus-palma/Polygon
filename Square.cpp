#include "Square.h"
#include <iostream>

// Put the shape name here:
#define ShapeType Square

using std::cout; using std::endl; using std::cin;

void P::ShapeType::AskDimensions()
{
	int length;

	cout << "How long sides do you want the " << P::Polygon::GetShapeName() << " to have?" << endl;
	cin >> length;

	P::Polygon::SetDimensions(length, 0);
}

void P::ShapeType::CalculateArea()
{
	int length;

	std::string direction_l = "length";
	length = P::Polygon::GetDimension(direction_l);

	P::Polygon::SetArea(length * length);
}
