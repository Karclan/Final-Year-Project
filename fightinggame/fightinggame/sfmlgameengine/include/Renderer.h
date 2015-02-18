#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <map>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Renderable.h"

class Renderer
{
public:
	void init();
	void render();
	void addToRender();
private:

	void setMaterials(Renderable*);
	void setLights(Shader *s);

	Shader* basic;

	std::map<std::string,Shader*> m_shaders;
	std::map<std::string,Mesh> m_meshes;
	std::vector<Camera*> m_cameras;
	std::vector<Renderable*> m_renderables;
};
#endif