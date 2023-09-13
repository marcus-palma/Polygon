#pragma once

#include <iostream>
#include <string>

namespace P
{
	class PolygonMenu;
}

class P::PolygonMenu
{
public:
	// Constructor
	PolygonMenu();

	// Main functioning. Can loop.
	void Main();

	// Ask user for shape. Note: The pointer to the Polygon object is not accessible outside this function.
	void AskForShape();

	// Listens for keyboard input, and doesn't stop until a valid key has been pressed.

private:
	std::string Shape;
};