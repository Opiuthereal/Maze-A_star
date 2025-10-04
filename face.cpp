#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<"face.h">
		Face::Face(Vertex v0, Vertex v1, Vertex v2, Vertex v3)
{
	faceVertices[0] = v0;
	faceVertices[1] = v1;
	faceVertices[2] = v2;
	faceVertices[3] = v3;
}

Vertex*		Face::getVertices()	{ return faceVertices;}
unsigned int*	Face::getIndices()	{ return indices;} 

int main()
{
	Face myFace(
        Vertex{{-0.5f,-0.5f,0.0f}, {1.0f,0.0f,0.0f}},
        Vertex{{0.5f,-0.5f,0.0f},  {0.0f,1.0f,0.0f}},
        Vertex{{0.5f,0.5f,0.0f},   {0.0f,0.0f,1.0f}},
        Vertex{{-0.5f,0.5f,0.0f},  {1.0f,1.0f,0.0f}}
    );
	return 0;
}
