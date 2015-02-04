#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>


class Renderer
{
public:
	void init();
	void render();
	void addToRender();
private:

	
};
#endif