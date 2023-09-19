#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace P
{
	class PolygonMenu;
}

struct ShapeDataStruct {
	std::string* ShapeName;
	void (*ShapeMethod)() = nullptr;
};

class P::PolygonMenu {
public:
	// Constructor
	PolygonMenu();

	// Main functioning. Can loop.
	void Main();

	// (Deprecated) Ask user for shape. Note: The pointer to the Polygon object is not accessible outside this function.
	//void AskForShape();
	
	// Ask user to select shape. Runs recursively until a valid key is pressed
	void AskForShape2();
	
	// Adder function for shape data list
	void AddShapeData(ShapeDataStruct& ShapeData);

private:
	// Name of shape (deprecated)
	std::string Shape;

	// A vector holding data locally inside main menu about the polygons. This is going to be used for the execution flow.
	std::vector<ShapeDataStruct> ShapeData;

	// A list of keys for binding yes and no for the question if user wants to try again
	std::vector<int> Keys_TryAgain;
};