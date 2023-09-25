#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace P {
	class PolygonMenu;
}

class P::PolygonMenu {
public:
	// Constructor
	PolygonMenu();

	// Main functioning. Can loop.
	void Main();
	
	// Ask user to select shape. Runs recursively until a valid key is pressed
	void AskForShape();

private:
	// A struct for storing shape module data that was loaded from the disk
	struct ShapeModuleStruct {
		std::string Name;
		std::string Question;
		std::string Area;
	};

	// A vector holding data locally inside main menu about the polygons. This is going to be used for the execution flow.
	std::vector<ShapeModuleStruct> ShapeModuleData;

	// Number of items in ShapeModuleData list
	size_t size = 0;

	// A list of keys for binding yes and no for the question if user wants to try again
	std::vector<int> KeyBindings_TryAgain;

	// Key-binding list for shape selection list
	std::vector<int> KeyBindings_ShapeList;
};