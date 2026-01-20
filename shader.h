#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shader {
	private:
		unsigned int ID; // identifiant du programme shader

		// Compile un shader (vertex ou fragment)
		unsigned int compileShader(unsigned int type, const std::string& source);
		//lire le fichier du shader
		std::string readFile(const std::string& path);

	public:
		// Constructeur à partir du code source des shaders
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		// Active ce shader
		void use() const;
		// Accès à l'ID si nécessaire
		unsigned int getID() const;
		// Méthodes pour passer des uniformes
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;
		~Shader();
};
