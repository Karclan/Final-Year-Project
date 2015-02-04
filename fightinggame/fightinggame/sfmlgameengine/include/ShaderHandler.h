#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\transform.hpp>

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class ShaderHandler
{
public:
	
	ShaderHandler(GLuint _newActiveShader){activeShader=_newActiveShader;}
	void setActiveShader(GLuint _newActiveShader){activeShader=_newActiveShader;}

	GLuint getActiveShader(){return activeShader;}

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

    void printActiveUniforms();
    void printActiveUniformBlocks();
    void printActiveAttribs();

private:
	
	GLuint activeShader;
	std::map<std::string, int> uniformLocations;
    GLint  getUniformLocation(const char * name );
  
};
#endif
