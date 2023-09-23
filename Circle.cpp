#include "Circle.h"
#include <iostream>

#define Pi 3.14159265358979323846

using std::cout; using std::endl; using std::cin;

// Intellisense will glitch sometimes about not being able to find overloaded instance
P::Circle::Circle(P::PolygonMenu* MenuRef) {
	ShapeName.assign("Circle");
	ShapeDataStruct ShapeData;
	ShapeData.ShapeName = &ShapeName;
	ShapeData.BaseClassPointer = this;
	ShapeData.MemberPointer = static_cast<void (P::Polygon::*)()> (&P::Circle::ShapeMethod);
	MenuRef->AddShapeData(ShapeData);
}

void P::Circle::ShapeMethod()
{
	int radius, area;

	// Ask for dimensions
	cout << "How big radius do you want the " << ShapeName << " to have?" << endl;
	cin >> radius;

	// Calculate area and print out
	area = round(Pi * radius * radius / 2);
	cout << "The area of your " << ShapeName << " is: " << area << endl;
}