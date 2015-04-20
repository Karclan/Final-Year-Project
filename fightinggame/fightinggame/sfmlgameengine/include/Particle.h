#ifndef PARTICLE_H
#define PARTICLE_H

#include "Component.h"

#include "ParticleRenderable.h"
#include "particleSystem.h"
/*! \brief  Particle Component Class

Particle Component class, contains objects used in the particle system. Mostly a self managing component except
the renderer manages the particle components. The particle manages the particle system contained in itself

*/
class Particle : public Component
{
public:
	Particle(); 
	Particle(SPC_Transform t, size_t poolSize, Shader* s); //!<Constructor which sets the size of the particle pool as well as transform and the shader pointer
	~Particle();
	ComponentType::type getType();
	void tearDown();

	void init(); //!< Generates the particles based upon the particle pool size
	void render(); //!<Renders the alive particles
	void animate(float t); //!<Updates the alive particles

	void setParticlePointSize(float size);//!< sets the size of the particle point within the shader and on the screen

	void setPoolSize(size_t poolSize); 
	int  getPoolSize();

	void addEmitter (SP_ParticleEmitter em); //!<Adds emitter to particle system
	void addUpdater (SP_ParticleUpdater up); //!<Adds updater to particle system

	void setAnimFlag(bool f); //!<Sets animation flag, true animate, false no animation
	void setDispFlag(bool f); //!<Set display flag, true it renders, false it doesn't render
	void setEmitFlag(bool f); //!<Sets emit flag, true it emits, false it doesn't emit
	bool getEmitFlag(); 

	void clear();
	void resetParticles(); //!<Resets alive particle count to 0 so the system looks like it restarted, more efficent than reseting particle pool data

	SPC_Transform getTransform(){ return m_transform; }
private:

	bool m_renderFlag; //!<Render flag
	bool m_playFlag;   //!<Animation flag

	Shader*							m_shader; //!<Pointer to particle shader
	int								m_particlePool; //!<Pool size
	SP_ParticleEmitter				m_emitter; //!<Emitter, currently only one emitter per particle system. Can't see why you'd want more than one emitter?
	std::vector<SP_ParticleUpdater>	m_updaters; //!<Updaters, they are held in here and within the particle system incase we would want to do something with the in an interesting way
	SP_ParticleRenderable			m_particleRenderable; //!<Particle renderer
	SP_ParticleSystem				m_particleSystem; //!<Particle system

	SPC_Transform m_transform; //The origin of the particleEmitter
};

typedef std::shared_ptr<Particle> SPC_Particle;

#endif 