#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace P
{
	class PolygonMenu;
}

class P::PolygonMenu
{
public:
	// Constructor
	PolygonMenu();

private:
	// A struct for storing shape module data that was loaded from the disk
	struct ShapeModuleStruct
	{
		std::string Name;
		std::string Question;
		std::string Area;
	};

	// A vector holding data locally inside main menu about the polygons. This is going to be used for the execution flow.
	std::vector<ShapeModuleStruct> ShapeModuleData;

	// Number of items in ShapeModuleData list
	size_t size = 0;

	// If returned true, loads shape modules files from disk and propagate the ShapeModuleData list
	bool LoadShapeModules();

	// Setups keybindings for try-again question and shape selection. Requires shape modules to be loaded first
	void SetupKeybindings();

	// A list of keys for binding yes and no for the question if user wants to try again
	std::vector<int> KeyBindings_TryAgain;

	// Key-binding list for shape selection list
	std::vector<int> KeyBindings_ShapeList;

	// Main functioning. Can loop.
	void Main();
	
	// Ask user to select shape. Runs recursively until a valid key is pressed
	void AskForShape();

	size_t ChosenModuleIndex = 0;

	// Run the module of the chosen shape
	void RunChosenShape();

	// Runs the given area script. Returns area result or -1 on failure.
	int RunAreaScript(ShapeModuleStruct* Module, std::string* UserInput);

	bool IsWholeNumber(std::string* string);

	enum MathOperatorEnum
	{
		Null,
		Multiply,
		Divide,
		Power
	};

	MathOperatorEnum MathOperatorType = Null;

	void MathOperator(int* Buffer, int num);
};

// Converts wide character string to standard string
std::string WCharToNarrow(const wchar_t* s);