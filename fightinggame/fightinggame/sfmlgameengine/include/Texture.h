#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew\GL\glew.h>

#include <glm\gtx\transform.hpp>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include "Shader.h"

namespace TextureType
{
	enum type{ DIFFUSE=1, SPECULAR ,TYPES};
}
class Texture
{
public:
	Texture();
	bool load(std::string filename, TextureType::type type);
	void bind(Shader *s);
	void unbind();
private:
	GLuint m_TextureHandle;
	sf::Image m_Image;
	TextureType::type m_TexType;
};
#endif