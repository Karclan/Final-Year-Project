#ifndef PARTICLEBEHAVIOUR_H
#define PARTICLEBEHAVIOUR_H

#include <memory>

#include "Particle.h"

class ParticleBehaviour 
{
public:
	ParticleBehaviour();

	virtual void init()			 = 0;
	virtual void update(float t) = 0;
	
	SP_ParticleEmitter  getEmitter();
protected:
	SP_ParticleEmitter	m_emitter;
	SPC_Particle		m_particle;
};

#endif