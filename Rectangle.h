#pragma once

#include "Polygon.h"
#include "PolygonMenu.h"
#include <string>

namespace P {
	class Rectangle;
}

class P::Rectangle : public P::Polygon {
public:
	Rectangle();
	// Constructor that should be run from Main Menu. It will add its ShapeData into the list in main menu and then return.
	Rectangle(P::PolygonMenu* MenuRef);
private:
	// The method for this type of shape
	void ShapeMethod();
};