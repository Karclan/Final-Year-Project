#ifndef FIREWORK_H
#define FIREWORK_H

#include "GameObject.h"
#include "Particle.h"

class Firework : public GameObject
{
public:
	Firework();
	Firework(SPC_Particle p);
	void init();
	void update(float t);

private:
	float m_fireworkTime;
	float m_time;
	bool  m_explode;
	bool  m_exploding;
	
	SP_ParticleEmitter m_emitter;

	SP_RoundPosGen		  m_posGenerator;
	SP_BasicColourGen	  m_colGenerator;
	SP_BasicVelGen		  m_velGenerator;
	SP_BasicTimeGen		  m_timeGenerator;

	SP_EulerUpdater		  m_eulerUpdater;
	SP_FloorUpdater		  m_floorUpdater;
	SP_BasicTimeUpdater	  m_timeUpdater;
	SP_BasicColourUpdater m_colourUpdater;

	SPC_Transform m_Transform;
	SPC_Particle  m_particle;
};

#endif