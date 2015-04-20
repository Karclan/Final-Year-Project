#ifndef PARTICLEEMITTERS_H
#define PARTICLEEMITTERS_H

#include <memory>
#include <algorithm>

#include "particleData.h"
#include "particleGenerators.h"

//! Unused enum
namespace Emitters
{
	enum type{BASEEMITTER, EMITTERS};
}

/*! \brief  ParticleEmitter Class

ParticleEmitter Class. Emitter class which is used to wake and emit particles

*/ 
class ParticleEmitter
{
protected:
	std::vector<SP_ParticleGenerator> _generators; //!< vector of particle generators
	float _emitRate; //!< emit rate, how fast it emits particles
	float _emitScalar; //!< emit scalar used to calculate the emit rate
public:
	ParticleEmitter();

	virtual ~ParticleEmitter();  
	virtual Emitters::type getType(){return Emitters::BASEEMITTER;}

	virtual void emit(float t, ParticleData *p);  //!< Emit function to emit particles
	virtual void init(size_t particlePool); //!< sets emit rate based on pool size. To be used after the scalar has been defined
	virtual void init(size_t particlePool,float emitScalar); //!< sets emit rate based on pool size and scalar
	virtual void clear();  //!< clears list of generators

	void addGenerator(SP_ParticleGenerator gen); //!< adds generator to emitter
	SP_ParticleGenerator getGenerator(Generators::type type); //!< returns generator based upon type specifed
	
	float getEmitScalar(){return _emitScalar;}
	float getEmitRate(){return _emitRate;}
	void setEmitScalar(float scalar){_emitScalar=scalar;}
};

typedef std::shared_ptr<ParticleEmitter> SP_ParticleEmitter;
#endif