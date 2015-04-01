#include "ParticleBehaviour.h"

ParticleBehaviour::ParticleBehaviour()
{
	std::cout << "Made Particle Behaviour!\n";
}

SP_ParticleEmitter ParticleBehaviour::getEmitter()
{
	return m_emitter;
}