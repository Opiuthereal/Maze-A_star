#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
#include "vertex.h"

class Face : public Renderable //Renderable est parent de Face
{
	private:
		Vertex		faceVertices[4]; //gère sommet et couleurs
		unsigned int	vIndices[6]; //gère agencement des sommets
	public:
				Face(Vertex v0, Vertex v1, Vertex v2, Vertex v3);
		Vertex*		getVertices();
		unsigned int*	getIndices();
};
