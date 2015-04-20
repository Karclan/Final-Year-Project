#ifndef FTINTERFACE_H
#define FTINTERFACE_H

#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Shader.h"
#include "GS.h"

//! Character struct used for glyphing
struct Character
{
	GLuint		TextureID;
	glm::ivec2	Size;
	glm::ivec2	Bearing;
	GLuint		Advance;
};

/*! \brief  FTInterface

FTInterface Singleton. The Freetype interface used to render text onto screen in openGL retained mode. Uses a glyphing technique

*/
class FTInterface
{
public:

	static void init(); //!< Inits freetype, loads text, creates glyphs, generates vertex buffer objects
	static void renderText(std::string, GLfloat x,GLfloat y,GLfloat scale, glm::vec3 colour); //!< Renders text on screen based on x and y positions, scale, and colour

private:

	 FTInterface();
	~FTInterface();

	static FTInterface* get(); //!< Private static function to get singleton

	void genChars(); //!< Generates glyphs of characters within TTF file
	void genVBO();	 //!< Generates vertex buffer object
	void genShader();//!<Creates shader

	Shader textShader;
	GLuint VAO, VBO;
	std::map<GLchar,Character> m_Characters;
	FTInterface *m_this;
	FT_Library	 m_ftLib;
	FT_Face		 m_ftFace;
};

#endif