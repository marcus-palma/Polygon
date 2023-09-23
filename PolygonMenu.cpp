// This will be the driving menu for making polygons and calculating their area.

#include <iostream>
#include "PolygonMenu.h"
#include "Polygon.h"

// Keyboard direct input
#include "KeyListener.h" // Handles keyboard input
#include <Windows.h>  // Windows API/library for keyboard input

// Modular shapes
#include "Square.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

using std::cout; using std::cin; using std::endl;

// Constructor
P::PolygonMenu::PolygonMenu() {
	// Setup before going into the recursing Main function
	// Setup the collection of Virtual Keys for asking user for trying again
	P::PolygonMenu::KeyBindings_TryAgain.push_back('Y');
	P::PolygonMenu::KeyBindings_TryAgain.push_back('N');

	// "Load modules" by constructing each shape
	// The constructors need a reference to this main menu
	P::Square Square_Instance(this);
	P::Rectangle Rectangle_Instance(this);
	P::Triangle Triangle_Instance(this);
	P::Circle Circle_Instance(this);

	// Prepare key bindings for choosing shape in a list
	// Get the size of ShapeData list
	size = ShapeData.size();

	// Check if size is valid
	if (size <= 0 && size <= 9) {
		cout << "Error: ShapeData list is empty, or its size is invalid or too big";
		return;
	}

	// Propagate key-binding list
	for (int i = 0; i <= size-1; i++) {
		// char '1' numerical value is 49. We count from there
		KeyBindings_ShapeList.push_back(49 + i);
	}

	P::PolygonMenu::Main();
}

void P::PolygonMenu::Main() {
	P::PolygonMenu::AskForShape();

	// Ask for doing it again.
	cout << "Do you want to make a new shape? (Y/N)" << endl;

	// Listen for key presses.
	P::KeyListener KeyListener;
	int Key = 0;
	Key = KeyListener.ListenForKeys(&(P::PolygonMenu::KeyBindings_TryAgain));
	
	// But 'N' will continue towards program end
	if (Key == 'Y') {
		P::PolygonMenu::Main();
	}
}

void P::PolygonMenu::AskForShape() {

	
	// This is a while-loop for asking until the user input is valid
	bool ShapeIsValid = false;
	bool FirstIteration = true;
	while (!ShapeIsValid) {
		// Display the question.
		// The first line of the question is different after the user input has been invalid.
		if (FirstIteration) {
			cout << "Please choose a shape:" << endl;
			FirstIteration = false;
		}
		else {
			cout << "The pressed key is not valid. Please try again:" << endl;
		}

		// Display the list of shapes to choose from
		for (int i = 0; i <= size - 1; i++) {
			// Format: #. Name
			cout << i + 1 << ". " << *ShapeData.at(i).ShapeName << endl;
		}

		// Listen for user key input
		P::KeyListener KeyListener;
		int Key = 0;
		Key = KeyListener.ListenForKeys(&KeyBindings_ShapeList);

		// Check if returned pressed key is valid
		// char numerical values for 1-9 are 49-58
		if (Key >= '1' && Key - 49 <= size - 1) {
			// Attempt calling the chosen shape's method

			// Declare new variables
			ShapeDataStruct Data;
			void (P::Polygon::*MemberPointer)() = nullptr;

			// Get values
			Data = ShapeData.at(Key - 49);
			P::Polygon* BaseClassPointer = Data.BaseClassPointer;
			MemberPointer = Data.MemberPointer;

			// Check if collected pointers are valid before calling with them
			if (BaseClassPointer != nullptr && MemberPointer != nullptr) {
				ShapeIsValid = true;
				(BaseClassPointer->*MemberPointer)();
			}
		}
	}
}

void P::PolygonMenu::AddShapeData(ShapeDataStruct& ShapeData) {
	P::PolygonMenu::ShapeData.push_back(ShapeData);
}