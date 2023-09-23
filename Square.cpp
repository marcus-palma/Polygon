#include "Square.h"
#include "PolygonMenu.h"
#include <iostream>

using std::cout; using std::endl; using std::cin;

// Intellisense will glitch sometimes about not being able to find overloaded instance
P::Square::Square(P::PolygonMenu* MenuRef) {
	ShapeName.assign("Square");
	ShapeDataStruct ShapeData;
	ShapeData.ShapeName = &ShapeName;
	ShapeData.BaseClassPointer = this;
	ShapeData.MemberPointer = static_cast<void (P::Polygon::*)()> (&P::Square::ShapeMethod);
	MenuRef->AddShapeData(ShapeData);
}

void P::Square::AskDimensions()
{
	int length;

	cout << "How long sides do you want the " << P::Polygon::GetShapeName() << " to have?" << endl;
	cin >> length;

	P::Polygon::SetDimensions(length, 0);
}

void P::Square::CalculateArea()
{
	int length;

	std::string direction_l = "length";
	length = P::Polygon::GetDimension(direction_l);

	P::Polygon::SetArea(length * length);
}

void P::Square::ShapeMethod()
{
	int length, area;

	// Ask for dimensions
	cout << "How long sides do you want the " << ShapeName << " to have?" << endl;
	cin >> length;

	// Calculate area and print out
	area = length * length;
	cout << "The area of your " << ShapeName << " is: " << area << endl;
}