#include "Texture.h"

Texture::Texture()
{

}
bool Texture::load(std::string filename, TextureType::type type)
{
	if (m_Image.loadFromFile(filename))
	{
		m_Image.flipVertically();
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_TextureHandle);
		glBindTexture  (GL_TEXTURE_2D, m_TextureHandle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGBA, m_Image.getSize().x, m_Image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.getPixelsPtr());
		glBindTexture  (GL_TEXTURE_2D, 0);
		m_TexType = type;
		std::cout << "Loaded Texture\n";
		return true;
	}
	return false;
}
void Texture::bind(Shader *s)
{
	glActiveTexture(GL_TEXTURE0+m_TexType);
	glBindTexture  (GL_TEXTURE_2D, m_TextureHandle);
	switch (m_TexType)
	{
	case TextureType::DIFFUSE:
		s->setUniform("u_DiffuseTexture", m_TexType);
		break;
	case TextureType::SPECULAR:
		s->setUniform("u_SpecularTexture", m_TexType);
		break;
	default:
		break;
	}
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE0, 0);
}