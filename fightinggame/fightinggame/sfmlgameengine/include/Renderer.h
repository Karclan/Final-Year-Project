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

#include "Timer.h"
#include "FTInterface.h"
#include "Transfrom.h"
#include "Renderable.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"


class Renderer
{
public:
	void init();
	void loadMesh(std::string filename);
	void render();
	void setActiveCamera(int i);
	int  calculateFrameRate();
	void updateRenderData();
	SPC_Camera		createCamera	(SPC_Transform t);
	SPC_Renderable	createRenderable(SPC_Transform t, std::string filename);

private:
	int m_ActiveCamera;

	void updateMatricies	 (SPC_Renderable, SPC_Camera);
	void setMaterials		 (SPC_Renderable);
	void setLights			 (Shader *s);

	Shader* basic;

	std::map<std::string,Shader*>	m_shaders;
	std::map<std::string,Mesh*>		m_meshes;
	std::vector<SPC_Camera>			m_cameras;
	std::vector<SPC_Renderable>		m_renderables;
};
#endif