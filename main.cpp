#include "affichage.h"
using namespace std;

int main() 
{
	Window window(800, 600, "Labyrinthe 3D");
	float floorVertices[] = 
	{
		// positions       // couleurs
		-1.0f, -0.5f, 0.0f,   1.0f, 0.8f, 0.3f,  // bas gauche
		1.0f, -0.5f, 0.0f,   1.0f, 0.8f, 0.3f,  // bas droite
		1.0f, -1.0f, 0.0f,   1.0f, 0.8f, 0.3f,  // bas-bas droite
		-1.0f, -1.0f, 0.0f,   1.0f, 0.8f, 0.3f   // bas-bas gauche
	};
	
	//comment les triangles sont relié pour former un carré
	unsigned int indices[] = { 0, 1, 2,  0, 2, 3 }; // ici carré 0-1-2 et 0-2-3
	/*
	v0 ---- v1
	|        |
	|        |
	v3 ---- v2
	*/
	
	// crée le VAO et deux buffers pour VBO et EBO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	//séléction du VBO qui contient les données pour le VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Initialise le VBO avec les données des vertices et couleurs
	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
	
	//pareil mais avec le EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Attribut position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Attribut couleur
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// active l'attribut 1 (couleur)
	glEnableVertexAttribArray(1);
	
	// Vertex Shader
	const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 ourColor;
	void main()
	{
		gl_Position = vec4(aPos, 1.0);
		ourColor = aColor;
	}
	)";

	// Fragment Shader
	const char* fragmentShaderSource = R"(
	#version 330 core
	in vec3 ourColor;
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(ourColor, 1.0);
	}
	)";
	
	// 1. Créer et compiler le vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Vérification des erreurs
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cerr << "Erreur compilation vertex shader:\n" << infoLog << endl;
	}

	// 2. Créer et compiler le fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cerr << "Erreur compilation fragment shader:\n" << infoLog << endl;
	}

	// 3. Créer le programme et lier
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Vérifier les erreurs de linkage
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cerr << "Erreur linkage shader program:\n" << infoLog << endl;
	}

	// 4. Nettoyer les shaders temporaires (ils sont déjà liés)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	while (window.isOpen()) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// clear le buffer d'affichage
		glClear(GL_COLOR_BUFFER_BIT);

		// A FAIRE: dessiner le labyrinthe ici

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.swapBuffers();
		window.pollEvents();
	}

	return 0; // glfwTerminate est déjà appelé par le destructeur
}
