// This file will be the Base Class Polygon, while the other Polygon-files will simply derive from this and override how the geometrical area is calculated.
// It will ask for dimensions.

#include "Polygon.h"
#include <iostream>

using std::cout; using std::endl;

void P::Polygon::SetupPolygon()
{
	// Using "this" keyword to call virtual function properly.

	//P::Polygon::AskDimensions();
	this->AskDimensions();

	//P::Polygon::CalculateArea();
	this->CalculateArea();
	cout << "Area of " << Shape << " is " << Area << "." << endl;
}

void P::Polygon::SetShapeName(std::string& shape)
{
	P::Polygon::Shape = shape;
}

std::string& P::Polygon::GetShapeName()
{
	return Shape;
}

void P::Polygon::AskDimensions()
{
	cout << "Polygon Base Class - AskDimensions" << endl;
}

void P::Polygon::SetDimensions(int length, int height)
{
	P::Polygon::Length = length;
	P::Polygon::Height = height;
}

int P::Polygon::GetDimension(std::string& direction)
{
	if (direction == "length")
	{
		return P::Polygon::Length;
	}

	else if (direction == "height")
	{
		return P::Polygon::Height;
	}

	return 0;
}

void P::Polygon::CalculateArea()
{
	P::Polygon::SetArea(123);
}

void P::Polygon::SetArea(int area)
{
	P::Polygon::Area = area;
}