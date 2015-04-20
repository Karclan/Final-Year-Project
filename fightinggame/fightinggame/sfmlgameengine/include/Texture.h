#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew\GL\glew.h>

#include <glm\gtx\transform.hpp>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include "Shader.h"

//! Enum for texture types
namespace TextureType
{
	enum type{ DIFFUSE=1, SPECULAR ,TYPES};
}

/*! \brief  Texture

Texture class. Class used to store the texture information of a texture. Is then bound and unbound as and when needed during rendering

*/
class Texture
{
public:
	Texture();
	bool load(std::string filename, TextureType::type type); //!< loads texture
	void bind(Shader *s);//!< binds texutre for rendering
	void unbind();//!< unbinds texture after rendering
private:
	GLuint m_TextureHandle;
	sf::Image m_Image;
	TextureType::type m_TexType;
};
#endif