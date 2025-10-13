#include<iostream>
#include "shader.h"

using namespace std;

Shader::Shader(const string& vertexSource, const string& fragmentSource) 
{
	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	// Vérifie le lien du programme
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) 
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cerr << "Erreur linkage shader program:\n" << infoLog << endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

unsigned int Shader::getID() const { return ID; }

//active le shader
void Shader::use() const 
{
	glUseProgram(ID);
}
// Compilation d'un shader
unsigned int Shader::compileShader(unsigned int type, const std::string& source) 
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) 
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cerr << "Erreur compilation " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n" << infoLog << endl;
	}
	return shader;
}


// Controle des shaders: transformations, couleurs, lumières, textures
void Shader::setBool(const std::string& name, bool value) const 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}
void Shader::setInt(const std::string& name, int value) const 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const 
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

