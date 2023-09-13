#pragma once

#include <string>
//#include "Square.h"

namespace P
{
	class Polygon;
}

class P::Polygon
{
public:

	// This calls back to base class to setup the polygon.
	void SetupPolygon();

	// Set the name of this shape in the string variable.
	void SetShapeName(std::string& shape);

	// Accesses and gets the private string variable.
	std::string& GetShapeName();

	// Asks the user for dimensions for shape.
	virtual void AskDimensions();

	// Set dimensions of shape.
	void SetDimensions(int length, int height);

	// Get a dimension in either "length" or "height" direction.
	int GetDimension(std::string& direction);

	// Calculates the area of the shape.
	virtual void CalculateArea();

	// Sets the private access area variable.
	void SetArea(int area);

private:
	std::string Shape = "Polygon";
	int Length = 0;
	int Height = 0;
	int Area = 0;
};