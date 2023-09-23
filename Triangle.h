#pragma once

#include "Polygon.h"
#include "PolygonMenu.h"
#include <string>

namespace P
{
	class Triangle;
}

class P::Triangle : public P::Polygon
{
public:
	Triangle();
	// Constructor that should be run from Main Menu. It will add its ShapeData into the list in main menu and then return.
	Triangle(P::PolygonMenu* MenuRef);
	virtual void AskDimensions() override;
	virtual void CalculateArea() override;
private:
	std::string ShapeName = "Triangle";
	// The method for this type of shape
	void ShapeMethod();
};