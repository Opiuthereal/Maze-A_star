#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "maze.h"
#include "shader.h"
#include "vertex.h"

class RenderMaze 
{
	public:
		unsigned int VAO, VBO, EBO;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		
		RenderMaze(const Maze& maze, float cubeSize = 0.5f);
		void draw(const Shader& shader) const;
		~RenderMaze();
};
