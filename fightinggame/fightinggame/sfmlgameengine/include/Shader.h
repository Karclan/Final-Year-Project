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

namespace ShaderTypes
{
	enum type{ VERTEX, FRAGMENT };
}
class Shader
{
public:
	void createShader(string vertFile, string fragFile);
	void linkMe();

	GLuint getHandle(){return m_ProgID;}

	void useProgram();

	void setUniform(const char *name, float x, float y, float z);
    void setUniform(const char *name, const glm::vec2	 &v);
    void setUniform(const char *name, const glm::vec3	 &v);
    void setUniform(const char *name, const glm::vec4	 &v);
	void setUniform(const char *name, const sf::Vector3f &v);
    void setUniform(const char *name, const glm::mat4	 &m);
    void setUniform(const char *name, const glm::mat3	 &m);
    void setUniform(const char *name, float  val );
    void setUniform(const char *name, int	 val );
    void setUniform(const char *name, bool	 val );
    void setUniform(const char *name, GLuint val );

	void setSubroutine(const char *name, ShaderTypes::type type);
private:
	std::map<std::string, int>	  uniformLocations;
	std::map<std::string, GLuint> subroutineLocations;
    GLint  getUniformLocation(const char * name  );
	GLuint getSubroutineLocation(const char *name, ShaderTypes::type type);
	GLuint m_vertShader, m_fragShader;
	GLuint m_ProgID;
};
#endif