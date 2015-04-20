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

//! enum for shader types
namespace ShaderTypes
{
	enum type{ VERTEX, FRAGMENT };
}
/*! \brief  Renderer

Renderer class. Renderer class which renders all renderables and all particles. Updates particles

*/
class Shader
{
public:
	void createShader(string vertFile, string fragFile); //!< creates shader program
	void linkMe();

	GLuint getHandle(){return m_ProgID;}
	 
	void useProgram(); //!< binds shader to be used

	void setUniform(const char *name, float x, float y, float z); //!< Sends unifrom to shader
    void setUniform(const char *name, const glm::vec2	 &v); //!< Sends uniform to shader
    void setUniform(const char *name, const glm::vec3	 &v); //!< Sends uniform to shader
    void setUniform(const char *name, const glm::vec4	 &v); //!< Sends uniform to shader
	void setUniform(const char *name, const sf::Vector3f &v); //!< Sends uniform to shader
    void setUniform(const char *name, const glm::mat4	 &m); //!< Sends uniform to shader
    void setUniform(const char *name, const glm::mat3	 &m); //!< Sends uniform to shader
    void setUniform(const char *name, float  val ); //!< Sends uniform to shader
    void setUniform(const char *name, int	 val ); //!< Sends uniform to shader
    void setUniform(const char *name, bool	 val ); //!< Sends uniform to shader
    void setUniform(const char *name, GLuint val ); //!< Sends uniform to shader

	void setSubroutine(const char *name, ShaderTypes::type type); //!< Sets the current subroutine within the shader 
private:
	std::map<std::string, int>	  uniformLocations; //!<Map of uniform locations, every time a uniform is sent to shader the location is saved for efficeny purposes
	std::map<std::string, GLuint> subroutineLocations; //!<Map of subrountine locations, everytime a subroutine is set the subroutine location is saved
    GLint  getUniformLocation(const char * name  ); //!< gets uniform location. If not found in map it looks for it in shader then adds to map
	GLuint getSubroutineLocation(const char *name, ShaderTypes::type type); //!< gets subroutine location. If not found in map it looks for it in shader then adds to map
	GLuint m_vertShader, m_fragShader; 
	GLuint m_ProgID;
};
#endif