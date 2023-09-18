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

	P::PolygonMenu::Main();
}

void P::PolygonMenu::Main()
{
	P::PolygonMenu::AskForShape();

	// Ask for doing it again.
	cout << "Do you want to make a new shape? (Y/N)" << endl;

	// Listen for key presses.
	P::KeyListener KeyListener;
	int Key = 0;
	Key = KeyListener.ListenForKeys(&(P::PolygonMenu::Keys_TryAgain));
	
	// But 'N' does nothing.
	if (Key == 'Y')
	{
		P::PolygonMenu::Main();
	}
}

void P::PolygonMenu::AskForShape()
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
}