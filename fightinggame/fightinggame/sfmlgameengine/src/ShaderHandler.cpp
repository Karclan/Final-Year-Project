#include "ShaderHandler.h"

void ShaderHandler::setUniform(const char *name, float x, float y, float z)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc,x,y,z);
}

void ShaderHandler::setUniform(const char *name, const glm::vec3 &_v)
{
	this->setUniform(name,_v.x,_v.y,_v.z);
}

void ShaderHandler::setUniform(const char *name, const glm::vec4 &_v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc,_v.x,_v.y,_v.z,_v.w);
}

void ShaderHandler::setUniform(const char *name, const glm::vec2 &_v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc,_v.x,_v.y);
}
void ShaderHandler::setUniform(const char *_name, const sf::Vector3f &_v)
{
	GLint loc = getUniformLocation(_name);
	glUniform3f(loc,_v.x,_v.y,_v.z);
}
void ShaderHandler::setUniform(const char *name, const glm::mat4 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, FALSE, &m[0][0]);
}

void ShaderHandler::setUniform(const char *name, const glm::mat3 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, FALSE, &m[0][0]);
}

void ShaderHandler::setUniform(const char *name, float _val )
{
	GLint loc = getUniformLocation(name);
	glUniform1f(loc, _val);
}

void ShaderHandler::setUniform(const char *name, int __val )
{
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, __val);
}

void ShaderHandler::setUniform(const char *name, GLuint __val )
{
	GLint loc = getUniformLocation(name);
	glUniform1ui(loc, __val);
}

void ShaderHandler::setUniform(const char *name, bool _val )
{
	int loc = getUniformLocation(name);
	glUniform1i(loc, _val);
}

int ShaderHandler::getUniformLocation(const char * _name )
{
	std::map<std::string, int>::iterator pos;
	pos = uniformLocations.find(_name);

	if( pos == uniformLocations.end() ) {
		uniformLocations[_name] = glGetUniformLocation(activeShader, _name);
	}

	return uniformLocations[_name];
}
