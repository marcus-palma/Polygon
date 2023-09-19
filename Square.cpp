#include "Square.h"
#include "PolygonMenu.h"
#include <iostream>

using std::cout; using std::endl; using std::cin;

// Intellisense will glitch sometimes about not being able to find overloaded instance
P::Square::Square(P::PolygonMenu* MenuRef) {
	ShapeDataStruct ShapeData;
	ShapeData.ShapeName = &ShapeName;
	ShapeData.ShapeMethod = &P::Square::ShapeMethod;
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
	// Ask for dimensions
	int length;
	cout << "How long sides do you want the " << "Square" << " to have?" << endl;
	cin >> length;

	// Calculate area and print out
	int area = length * length;
	cout << "The area of your Square is: " << area << endl;
}