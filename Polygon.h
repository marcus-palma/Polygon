#pragma once

#include <string>

// Namespace is necessary because identifier "Polygon" conflicts with the standard library
namespace P {
	class Polygon;
}

class P::Polygon {
protected:
	std::string ShapeName = "Polygon";
};