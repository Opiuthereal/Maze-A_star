#include<iostream>
#include "renderable.h"

using namespace std;

void Renderable::setupMesh()
{
 	glGenVertexArrays(1, &VAO);
 	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// couleurs
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
 
 // :vertices(verts), indices(inds) permets d'automatiquement mettre vertices = verts san avoir a initialiser vertices en tant qu'élément vide.
Renderable::Renderable(const vector<Vertex>& verts, const vector<unsigned int>& inds) : vertices(verts), indices(inds)
{
	setupMesh(); //initialise les VAO, VBO et EBO 
}

//virtual permet le polymorphisme
void Renderable::draw(const Shader& shader) const 
{
	shader.use();
	glBindVertexArray(VAO);
	//il faut explicitement convertir en type GLsizei sinon potentiel perte de données avec seulement indices.size
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0);
}

Renderable::~Renderable() 
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
