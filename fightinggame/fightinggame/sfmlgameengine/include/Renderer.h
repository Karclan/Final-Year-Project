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
#include "ParticleRenderable.h"
#include "ParticleBehaviour.h"

/*! \brief  Renderer

Renderer class. Renderer class which renders all renderables and all particles. Updates particles

*/
class Renderer
{
public:
	Renderer();
	~Renderer();
	void init(); //!< Sets OpenGL states, the view port, clear colour and clear depth. Loads shaders and sends the lights to the shaders as uniforms. Adds shaders to map
	void loadMesh(std::string filename); //!< Loads mesh and adds to map of meshes
	void render(); 	//!< Renders all renderables and particles in scene
	void updateParticles(float t);	//!< Updates particles
	void setActiveCamera(int i);  	//!< Sets the active camera to use when rendering the scene
	int  calculateFrameRate(); 	//!< Calculates the frame rate of the game

	SPC_Camera		createCamera	(SPC_Transform t); 	//!< Creates Camera component
	SPC_Renderable	createRenderable(SPC_Transform t, std::string meshFilename); //!< Creates Renderable component
	SPC_Renderable  createRenderable(SPC_Transform t, std::string meshFilename, std::string diffuse); //!< Creates Renderable component with diffuse texture
	SPC_Renderable  createRenderable(SPC_Transform t, std::string meshFilename, std::string diffuse, std::string specular); //!< Creates Renderable component with diffuse and specular texture
	SPC_Particle	createParticle	(SPC_Transform t, size_t poolSize); //!< Creates Particle Component
private:
	void setupShadows(); //!< Sets up frame buffer objects for shadow mapping. Shadow mapping doesn't work currently

	int m_ActiveCamera; //!< Value which is the current active camera used in rendering

	void updateMatricies	 (SPC_Renderable, SPC_Camera); //!< Updates the matricies within the shader
	void setMaterials		 (SPC_Renderable); //!<Sets the material values within the shader
	void setLights			 (Shader *s); //!< sets the light values within the shader

	Shader* basic; //!< Basic shader used to render all renderables
	Shader* particle; //!< Particle Shader used to render all particles

	GLuint m_ShadowFrameBufferObject; //!< Shadow map frame buffer object. Shadow mapping doens't work currently
	int m_ShadowMapWidth, m_ShadowMapHeight; //!< Shadow mapping values for width and height of shadow map. Shadow mapping doens't work currently
	glm::mat4 m_ShadowBias;  //!< Shadow bias matrix, used in shadow mapping to bias the shadow map. Shadow mapping doens't work currently
	glm::mat4 m_ShadowViewMat;  //!< Shadow map view matrix. Shadow mapping doens't work currently
	glm::mat4 m_ShadowProjectionMat;  //!< Shadow map projection matrix. Shadow mapping doens't work currently
	glm::mat4 m_LightPointViewMat;  //!< Shadow map view matrix from the ligth position. Shadow mapping doens't work currently
	glm::vec3 m_DirectionalLightDirection; //!< Directional light direction
	glm::vec3 m_DirectionalLightPosition; //!< Direcitonal light position, not used except for in shadow mapping which doesn't currently work
	glm::vec3 m_DirectionalLightAmbient; //!< Directional light ambient colour 
	glm::vec3 m_DirectionalLightDiffuse; //!< Directional light diffuse value
	glm::vec3 m_DirectionalLightSpecular; //!< Directional light specular value

	std::map<std::string,Shader*> m_shaders; //!< Map of shader
	std::map<std::string,Mesh*>	  m_meshes;  //!< Map of meshs
	std::vector<SPC_Camera>		  m_cameras;  //!< Vector of camerass
	std::vector<SPC_Renderable>	  m_renderables; //!< vecotor renderables
	std::vector<SPC_Particle>	  m_particles; //!< vector of particles
	glm::vec3 m_lightPos[3]; //!< Positions of the 3 lights in the scene
};
#endif