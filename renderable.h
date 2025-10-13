#pragma once
#include <glad/glad.h>
#include <vector>
#include "shader.h"
#include "vertex.h"
#include <glm/glm.hpp>


class Renderable {
	protected: //public pour les fils mais private pour le reste des classes
		unsigned int VAO, VBO, EBO;
		//le type vector peut contenir x valeur et gère dynamiquement la mémoire ce qui me permet donc de mettre tout objet que je veux représenter en 3d quelque soit son nombre de points
		std::vector<Vertex> vertices; 
		std::vector<unsigned int> indices;

		void setupMesh();

	public:
		Renderable(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds);
		virtual void draw(const Shader& shader) const;
		~Renderable(); //Destructeur
};
