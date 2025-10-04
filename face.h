#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};

class Face
{
	private:
		Vertex		faceVertices[4]; //gère sommet et couleurs
		unsigned int	indices[6]; //gère agencement des sommets
	public:
				Face(Vertex v0, Vertex v1, Vertex v2, Vertex v3);
		Vertex*		getVertices();
		unsigned int*	getIndices();
};
