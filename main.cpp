#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "face.h"
#include "shader.h"

using namespace std;

// Callback pour redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
	// 1. Initialiser GLFW
	if (!glfwInit()) 
	{
		cerr << "Erreur : impossible d'initialiser GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Labyrinthe 3D", NULL, NULL);
	if (!window) 
	{
		cerr << "Erreur : impossible de créer la fenêtre GLFW\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 2. Initialiser GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		cerr << "Erreur : impossible d'initialiser GLAD\n";
		return -1;
	}

	// 3. Créer le shader
	string vertexSource = R"(
		#version 330 core
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aColor;

		out vec3 ourColor;

		void main() {
			gl_Position = vec4(aPos, 1.0);
			ourColor = aColor;
		}
	)";

	string fragmentSource = R"(
		#version 330 core
		in vec3 ourColor;
		out vec4 FragColor;

		void main() {
			FragColor = vec4(ourColor, 1.0);
		}
	)";

	Shader shader(vertexSource, fragmentSource);

	// 4. Créer une Face
	Vertex v0{{-0.5f,-0.5f,0.0f},{1.0f,0.0f,0.0f}};
	Vertex v1{{ 0.5f,-0.5f,0.0f},{0.0f,1.0f,0.0f}};
	Vertex v2{{ 0.5f, 0.5f,0.0f},{0.0f,0.0f,1.0f}};
	Vertex v3{{-0.5f, 0.5f,0.0f},{1.0f,1.0f,0.0f}};
	Face myFace(v0, v1, v2, v3);

	// 5. Boucle principale
	while (!glfwWindowShouldClose(window)) 
	{
		// Nettoyer l'écran
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Dessiner la Face
		myFace.draw(shader);

		// Échanger les buffers et récupérer les événements
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

