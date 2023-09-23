#pragma once

#include "Polygon.h"
#include <iostream>
#include <string>
#include <vector>

namespace P
{
	class PolygonMenu;
}

struct ShapeDataStruct {
	std::string* ShapeName;
	P::Polygon* BaseClassPointer = nullptr;
	void (P::Polygon::*MemberPointer)() = nullptr;
};

class P::PolygonMenu {
public:
	// Constructor
	PolygonMenu();

	// Main functioning. Can loop.
	void Main();
	
	// Ask user to select shape. Runs recursively until a valid key is pressed
	void AskForShape();
	
	// Adder function for shape data list
	void AddShapeData(ShapeDataStruct& ShapeData);

private:
	// A vector holding data locally inside main menu about the polygons. This is going to be used for the execution flow.
	std::vector<ShapeDataStruct> ShapeData;

	// A list of keys for binding yes and no for the question if user wants to try again
	std::vector<int> Keys_TryAgain;
};