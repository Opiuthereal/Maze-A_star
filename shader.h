#pragma once
#include <string>
#include <glad/glad.h>
#include <iostream>

class Shader {
	private:
		unsigned int ID; // identifiant du programme shader

		// Compile un shader (vertex ou fragment)
		unsigned int compileShader(unsigned int type, const std::string& source);

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
};
