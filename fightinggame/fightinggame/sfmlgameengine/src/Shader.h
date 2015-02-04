#ifndef SHADER_H
#define SHADER_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <sfml\OpenGL.hpp>

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>

using std::ifstream;

#include <sstream>
#include <string>

using std::string;

class Shader
{
public:
	void createShader(string vertFile, string fragFile);
	void linkMe();

	GLuint vertShader, fragShader;
	GLuint shaderProgID;
private:

};
#endif