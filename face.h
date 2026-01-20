#pragma once
#include "vertex.h"
#include <array>
#include <glad/glad.h>
#include <vector>

class Face {
public:
    std::array<Vertex, 4> vertices;           // 4 sommets
    std::array<unsigned int, 6> indices = {0,1,2, 2,3,0}; // triangles

    // VAO/VBO/EBO propres à la face
    unsigned int VAO, VBO, EBO;

    Face() = default;

    Face(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3);

    void setupMesh();   // configure VAO/VBO/EBO
    void draw() const;  // dessiner la face

    Vertex* getVertices() { return vertices.data(); }
    unsigned int* getIndices() { return indices.data(); }
    ~Face();
};

