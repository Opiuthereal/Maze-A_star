#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
#include "vertex.h"

class Cube : public Renderable
{
	public:
		Cube(const Face& f1, const Face& f2, const Face& f3, const Face& f4, const Face& f5, const Face& f6);
};



/*
   +-----+
  /     /|
 +-----+ |
 |  +  | +
 |     |/
 +-----+*/
