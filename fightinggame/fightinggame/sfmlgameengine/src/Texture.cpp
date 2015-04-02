#include "Texture.h"

Texture::Texture()
{

}
bool Texture::load(std::string filename)
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
		std::cout << "Loaded Texture\n";
		return true;
	}
	return false;
}
void Texture::bind(Shader *s)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture  (GL_TEXTURE_2D, m_TextureHandle);
	s->setUniform("u_DiffuseTexture", 0);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE0, 0);
}