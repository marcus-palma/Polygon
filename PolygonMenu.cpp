// This will be the driving menu for making polygons and calculating their area.

#include <iostream>
#include "PolygonMenu.h"
#include "Polygon.h"
#include "Square.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "KeyListener.h" // Handles keyboard input
#include <Windows.h>  // Windows API/library for keyboard input


using std::cout; using std::cin; using std::endl;

// Constructor
P::PolygonMenu::PolygonMenu()
{
	// Setup before recursion loop
	// Setup the collection of Virtual Keys for asking user for trying again
	P::PolygonMenu::Keys_TryAgain.push_back('Y');
	P::PolygonMenu::Keys_TryAgain.push_back('N');

	// "Load modules" by constructing each shape
	// The constructors need a reference to this main menu
	P::Square Square_Instance(this);
	P::Rectangle Rectangle_Instance(this);
	P::Triangle Triangle_Instance(this);
	P::Circle Circle_Instance(this);

	P::PolygonMenu::Main();
}

void P::PolygonMenu::Main()
{
	//P::PolygonMenu::AskForShape();
	P::PolygonMenu::AskForShape2();

	// Ask for doing it again.
	cout << "Do you want to make a new shape? (Y/N)" << endl;

	// Listen for key presses.
	P::KeyListener KeyListener;
	int Key = 0;
	Key = KeyListener.ListenForKeys(&(P::PolygonMenu::Keys_TryAgain));
	
	// But 'N' will continue towards program end
	if (Key == 'Y')
	{
		P::PolygonMenu::Main();
	}
}

void P::PolygonMenu::AddShapeData(ShapeDataStruct& ShapeData) {
	P::PolygonMenu::ShapeData.push_back(ShapeData);
}

/* void P::PolygonMenu::AskForShape()
{
	// Declare a pointer that's going to be used for the Polygon object later.
	std::unique_ptr<P::Polygon> Polygon_Instance;


	// This is a while-loop for asking the question again if the user input is invalid.

	bool ShapeIsValid = false;
	bool FirstIteration = true;

	while (!ShapeIsValid)
	{
		// To avoid repetetive typing, let's assume it's valid until else is proven.
		ShapeIsValid = true;


		// Display the question.
		// The first line of the question is different after the user input has been invalid.
		if (FirstIteration)
		{
			cout << "Choose a shape:" << endl;
			FirstIteration = false;
		}
		else
		{
			cout << "The entered name is not available. Try choosing again:" << endl;
		}
		cout << "1: Square" << endl << "2: Rectangle" << endl << "3: Triangle" << endl << "4: Circle" << endl;
		
		// Get user text input.
		//cin >> Shape;

		// Process the user's input (old).
		//if (Shape == "Square")
		//{
		//	Polygon_Instance = std::make_unique<P::Square>();
		//}

		//else if (Shape == "Rectangle")
		//{
		//	Polygon_Instance = std::make_unique<P::Rectangle>();
		//}

		//else if (Shape == "Triangle")
		//{
		//	Polygon_Instance = std::make_unique<P::Triangle>();
		//}

		//else if (Shape == "Circle")
		//{
		//	Polygon_Instance = std::make_unique<P::Circle>();
		//}

		// When the user input didn't match anything valid, we'll just mark it as invalid again.
		//else
		//{
		//	ShapeIsValid = false;
		//}


		// Listen for key presses.
		// Create a collection of Virtual Keys.
		std::vector<int> Keys;
		Keys.push_back('1');
		Keys.push_back('2');
		Keys.push_back('3');
		Keys.push_back('4');

		P::KeyListener KeyListener;
		int Key = 0;
		Key = KeyListener.ListenForKeys(&Keys);


		switch (Key)
		{
		case '1': Polygon_Instance = std::make_unique<P::Square>(); Shape = "Square"; break;

		case '2': Polygon_Instance = std::make_unique<P::Rectangle>(); Shape = "Rectangle"; break;

		case '3': Polygon_Instance = std::make_unique<P::Triangle>(); Shape = "Triangle"; break;

		case '4': Polygon_Instance = std::make_unique<P::Circle>(); Shape = "Circle"; break;
			
		default: ShapeIsValid = false; break;
		}


		// Now when one Derived Polygon Class has been chosen and constructed, run setup on them that we weren't able to automate from Base Class.
		if (ShapeIsValid)
		{
			Polygon_Instance->SetShapeName(Shape);
			Polygon_Instance->SetupPolygon();
		}
	}
} */

void P::PolygonMenu::AskForShape2() {

	// Get the size of ShapeData list
	size_t size = ShapeData.size();

	// Check if size is valid
	if (size <= 0 && size <= 9) {
		cout << "Error: ShapeData list is empty, or its size is invalid or too big";
		return;
	}

	// Create the key-binding list
	std::vector<int> KeyBindings;

	// Propagate key-binding list
	for (int i = 0; i <= size-1; i++) {
		// char '1' numerical value is 49. We count from there
		KeyBindings.push_back(49 + i);
	}
	
	// This is a while-loop for asking until the user input is valid
	bool ShapeIsValid = false;
	bool FirstIteration = true;
	while (!ShapeIsValid)
	{
		// Display the question.
		// The first line of the question is different after the user input has been invalid.
		if (FirstIteration)
		{
			cout << "Please choose a shape:" << endl;
			FirstIteration = false;
		}
		else
		{
			cout << "The pressed key is not valid. Please try again:" << endl;
		}

		// Display the list of shapes to choose from
		for (int i = 0; i <= size - 1; i++) {
			// Format: #. Name
			// Bug: it displays the address of string rather than text
			cout << i + 1 << ". " << *ShapeData.at(i).ShapeName << endl;
		}

		// Listen for user key input
		P::KeyListener KeyListener;
		int Key = 0;
		Key = KeyListener.ListenForKeys(&KeyBindings);

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