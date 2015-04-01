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

class ParticleRenderable
{ 
public:
	ParticleRenderable();
	~ParticleRenderable();

	void generate	  (SP_ParticleSystem s, size_t particlePool);
	void render		  (SP_ParticleSystem s);
	void updateBuffers(SP_ParticleSystem s);

	bool _generatedFlag;

private:

	GLuint _vao;
	GLuint _particlePositionBuffer;
	GLuint _particleColourBuffer;
};

typedef std::shared_ptr<ParticleRenderable> SP_ParticleRenderable;

#endif