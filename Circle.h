#pragma once

#include "Polygon.h"
#include "PolygonMenu.h"
#include <string>

namespace P
{
	class Circle;
}

class P::Circle : public P::Polygon
{
public:
	Circle();
	// Constructor that should be run from Main Menu. It will add its ShapeData into the list in main menu and then return.
	Circle(P::PolygonMenu* MenuRef);
	virtual void AskDimensions() override;
	virtual void CalculateArea() override;
private:
	// The method for this type of shape
	void ShapeMethod();
};