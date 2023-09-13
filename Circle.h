#pragma once

#include "Polygon.h"
#include <string>

// Put the shape name here:
#define ShapeType Circle

namespace P
{
	class ShapeType;
}

class P::ShapeType : public P::Polygon
{
public:
	virtual void AskDimensions() override;
	virtual void CalculateArea() override;
};