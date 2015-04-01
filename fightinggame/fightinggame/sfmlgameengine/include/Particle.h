#ifndef PARTICLE_H
#define PARTICLE_H

#include "Component.h"

#include "ParticleRenderable.h"
#include "particleSystem.h"

class Particle : public Component
{
public:
	Particle();
	Particle(SPC_Transform t, size_t poolSize, Shader* s);

	ComponentType::type getType();
	void tearDown();

	void init();
	void render();
	void animate(float t);

	void setParticlePointSize(float size);

	void setPoolSize(size_t poolSize);
	int  getPoolSize();

	void addEmitter (SP_ParticleEmitter em);
	void addUpdater (SP_ParticleUpdater up);

	void setAnimFlag(bool f);
	void setDispFlag(bool f);
	void setEmitFlag(bool f);
	bool getEmitFlag();

	void clear();
	void resetParticles();

	SPC_Transform getTransform(){ return m_transform; }
private:

	bool m_renderFlag;
	bool m_playFlag;

	Shader*							m_shader;
	int								m_particlePool;
	SP_ParticleEmitter				m_emitter;
	std::vector<SP_ParticleUpdater>	m_updaters;
	SP_ParticleRenderable			m_particleRenderable;
	SP_ParticleSystem				m_particleSystem;

	SPC_Transform m_transform; //The origin of the particleEmitter
};

typedef std::shared_ptr<Particle> SPC_Particle;

#endif 