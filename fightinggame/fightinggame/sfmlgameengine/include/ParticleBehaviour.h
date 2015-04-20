#ifndef PARTICLEBEHAVIOUR_H
#define PARTICLEBEHAVIOUR_H

#include <memory>

#include "Particle.h"

/*! \brief  ParticleBehaviour Class

ParticleBehaviour Class. A class to be used to define particle system behaviour. Used in game implementation

*/

class ParticleBehaviour 
{
public:
	ParticleBehaviour();

	virtual void init()			 = 0;  //!< Pure virtaul function
	virtual void update(float t) = 0;  //!< Pure virtual function
	
	SP_ParticleEmitter  getEmitter();
protected:
	SP_ParticleEmitter	m_emitter;
	SPC_Particle		m_particle;
};

#endif