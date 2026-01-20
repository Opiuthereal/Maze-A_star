#include<iostream>
#include "renderMaze.h"
#include <vector>
#include "vertex.h"
#include "shader.h"
#include "maze.h"
#include "vertex.h"

using namespace std;


RenderMaze::RenderMaze(const Maze& maze, float cubeSize) {
	float half = cubeSize / 2.0f;
	unsigned int indexOffset = 0;

	for (int i = 0; i < 21*12; ++i) {
		if (maze.getTab(i) != 1) continue; 
		//seulement les murs
		int row = i / 21;
		int col = i % 21;

		glm::vec3 pos(col * cubeSize, 0.0f, row * cubeSize);
		//Création des 8 vertices du cube
		Vertex v0{{-half,0,-half}, {1,0,0}};
		Vertex v1{{ half,0,-half}, {1,0,0}};
		Vertex v2{{ half,cubeSize,-half}, {1,0,0}};
		Vertex v3{{-half,cubeSize,-half}, {1,0,0}};
		Vertex v4{{-half,0, half}, {1,0,0}};
		Vertex v5{{ half,0, half}, {1,0,0}};
		Vertex v6{{ half,cubeSize, half}, {1,0,0}};
		Vertex v7{{-half,cubeSize, half}, {1,0,0}};

		//placement des vertices au bon endroit
		array<Vertex,8> cubeVerts = {v0,v1,v2,v3,v4,v5,v6,v7};
		for (auto &v : cubeVerts) {
			v.pos += pos;
			vertices.push_back(v);
		}

		//indices du cube (6 faces * 2 triangles = 12 indices par face)
		array<unsigned int,36> cubeIndices = {
			0,1,2, 2,3,0,    //back
			4,5,6, 6,7,4,    //front
			0,4,7, 7,3,0,    //left
			1,5,6, 6,2,1,    //right
			3,7,6, 6,2,3,    //top
			0,1,5, 5,4,0     //bottom
		};

		for (auto index : cubeIndices) {
			indices.push_back(index + indexOffset);
		}

		indexOffset += 8; //on ajoute 8 nouveaux vertices pour le prochain cube
	}

	//création des buffers OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	//couleur
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (void*)offsetof(Vertex,color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RenderMaze::draw(const Shader& shader) const {
	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

RenderMaze::~RenderMaze() {
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
}


