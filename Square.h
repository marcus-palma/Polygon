#pragma once

#include "Polygon.h"
#include "PolygonMenu.h"
#include <string>

namespace P
{
	class Square;
}

class P::Square : public P::Polygon
{
public:
	Square();
	// Constructor that should be run from Main Menu. It will add its ShapeData into the list in main menu and then return.
	Square(P::PolygonMenu* MenuRef);
	virtual void AskDimensions() override;
	virtual void CalculateArea() override;
private:
	std::string ShapeName = "Square";
	// The method for this type of shape
	void ShapeMethod();
};