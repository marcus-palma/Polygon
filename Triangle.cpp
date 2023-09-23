#include "Triangle.h"
#include <iostream>

using std::cout; using std::endl; using std::cin;

// Intellisense will glitch sometimes about not being able to find overloaded instance
P::Triangle::Triangle(P::PolygonMenu* MenuRef) {
	ShapeDataStruct ShapeData;
	ShapeData.ShapeName = &ShapeName;
	ShapeData.BaseClassPointer = this;
	ShapeData.MemberPointer = static_cast<void (P::Polygon::*)()> (&P::Triangle::ShapeMethod);
	MenuRef->AddShapeData(ShapeData);
}

void P::Triangle::AskDimensions()
{
	int length, height;

	cout << "How long do you want the " << P::Polygon::GetShapeName() << " to be?" << endl;
	cin >> length;
	cout << "How high do you want the " << P::Polygon::GetShapeName() << " to be?" << endl;
	cin >> height;

	P::Polygon::SetDimensions(length, height);
}

void P::Triangle::CalculateArea()
{
	int length, height;

	std::string direction_l = "length";
	std::string direction_h = "height";
	length = P::Polygon::GetDimension(direction_l);
	height = P::Polygon::GetDimension(direction_h);

	P::Polygon::SetArea(length * height / 2);
}

void P::Triangle::ShapeMethod()
{
	int length, height, area;

	// Ask for dimensions
	cout << "How long do you want " << ShapeName << " to be?" << endl;
	cin >> length;
	cout << "How high do you want the " << ShapeName << " to be?" << endl;
	cin >> height;

	// Calculate area and print out
	area = length * height / 2;
	cout << "The area of your " << ShapeName << " is: " << area << endl;
}