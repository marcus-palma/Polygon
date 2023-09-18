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

	// Main functioning. Can loop.
	void Main();

	// Ask user for shape. Note: The pointer to the Polygon object is not accessible outside this function.
	void AskForShape();

private:
	// Name of shape
	std::string Shape;

	// A list of keys for binding yes and no for the question if user wants to try again
	std::vector<int> Keys_TryAgain;
};