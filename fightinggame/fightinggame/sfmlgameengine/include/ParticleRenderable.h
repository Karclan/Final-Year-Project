#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <vector>
#include <glm\glm.hpp>

#include <memory>

#include "particleData.h"
#include "particleEmitters.h"
#include "particleGenerators.h"
#include "particleUpdaters.h"
#include "particleSystem.h"

#include "component.h"
#include "shader.h"
#include "transfrom.h"

/*! \brief  ParticleRenderable Class

ParticleRenderable Class. Renders all the alive particles and manages the particle buffers which are sent to the shader

*/
class ParticleRenderable
{ 
public:
	ParticleRenderable();
	~ParticleRenderable();

	void generate	  (SP_ParticleSystem s, size_t particlePool); //!< generates the vertex array object and vertex position buffers for position and colour values
	void render		  (SP_ParticleSystem s); //!< Renders all alive particles
	void updateBuffers(SP_ParticleSystem s); //!< Updates the buffers based upon the alive particles which exist within the particle system

	bool _generatedFlag; //!< Flag to determin if the vertex array objects and vertex buffers are generated or not

private:

	GLuint _vao;
	GLuint _particlePositionBuffer;
	GLuint _particleColourBuffer;
};

typedef std::shared_ptr<ParticleRenderable> SP_ParticleRenderable;

#endif