#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <memory>

#include "particleData.h"
#include "particleEmitters.h"
#include "particleGenerators.h"
#include "ParticleUpdaters.h"

/*! \brief  ParticleSystem Class

ParticleSystem Class. Manages the emitter, updates and the particle data

*/

class ParticleSystem
{
public:
	ParticleData _particles;

	size_t _particleCount;

	std::vector<SP_ParticleEmitter> _emitters; //!< Particle Emitters
	std::vector<SP_ParticleUpdater> _updaters; //!< Particle Updaters

	bool _emitFlag;	//!< Flag to toggle if system wants to emit or not to emit
	
	ParticleSystem(size_t maxCount); //!< Consturctor which generates the particles
	virtual ~ParticleSystem();
	 
	void clear();
    virtual void update(float t); //!< depending on which flags are set it'll update emitters, particles and updaters
	virtual void reset(); //!< resets alive particle count to 0. Gives the Apperance of particles resetting
	virtual size_t getParticleCount(){return _particles._particleCount;}
	virtual size_t getAliveParticleCount(){return _particles._aliveParticleCount;}
	void addEmitter(SP_ParticleEmitter emitter); //!< Adds particle emitter to particle system
	void addUpdater(SP_ParticleUpdater updater); //!< Adds particle updater to particle system
	SP_ParticleEmitter getEmitter(unsigned int id);
	SP_ParticleUpdater getUpdater(Updaters::type type);

	ParticleData *getFinalData(){return &_particles;} //!< Gets the final data of the particle data. The data after updating and emitting has happened. Used for rendering
};

typedef std::shared_ptr<ParticleSystem> SP_ParticleSystem;

#endif