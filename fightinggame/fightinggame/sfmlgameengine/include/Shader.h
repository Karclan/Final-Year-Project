#ifndef SHADER_H
#define SHADER_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <sfml\OpenGL.hpp>

#include <map>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
using std::string;

#include <glm\gtx\transform.hpp>

class Shader
{
public:
	void createShader(string vertFile, string fragFile);
	void linkMe();

	GLuint getHandle(){return shaderProgID;}

	void setUniform(const char *_name, float _x, float _y, float _z);
    void setUniform(const char *_name, const glm::vec2 &_v);
    void setUniform(const char *_name, const glm::vec3 &_v);
    void setUniform(const char *_name, const glm::vec4 &_v);
	void setUniform(const char *_name, const sf::Vector3f &_v);
    void setUniform(const char *_name, const glm::mat4 &_m);
    void setUniform(const char *_name, const glm::mat3 &_m);
    void setUniform(const char *_name, float _val );
    void setUniform(const char *_name, int _val );
    void setUniform(const char *_name, bool _val );
    void setUniform(const char *_name, GLuint _val );


private:
	std::map<std::string, int> uniformLocations;
    GLint  getUniformLocation(const char * name );

	GLuint vertShader, fragShader;
	GLuint shaderProgID;
};
#endif