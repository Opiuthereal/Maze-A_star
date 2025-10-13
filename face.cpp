#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"face.h"

using namespace std;

	Face::Face(Vertex v0, Vertex v1, Vertex v2, Vertex v3)
    : Renderable({}, {}) // on initialise Renderable vide, setupMesh() sera appelé plus tard
{
    // Remplir les vertices
    faceVertices[0] = v0;
    faceVertices[1] = v1;
    faceVertices[2] = v2;
    faceVertices[3] = v3;

    // Remplir les indices
    vIndices[0] = 0; 
    vIndices[1] = 1; 
    vIndices[2] = 2;
    vIndices[3] = 2; 
    vIndices[4] = 3; 
    vIndices[5] = 0;

    // Copier les données locales dans les vectors de Renderable
    vertices.assign(begin(faceVertices), end(faceVertices));
    indices.assign(begin(vIndices), end(vIndices));

    // Initialiser VAO/VBO/EBO
    setupMesh();
}

Vertex*		Face::getVertices()	{ return faceVertices;}
unsigned int*	Face::getIndices()	{ return vIndices;}
