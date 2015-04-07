#include "Firework.h"

Firework::Firework()
{
	m_particle = nullptr;
	m_Transform = nullptr;
	std::cout << "created firework with nullptr!\n";
}
Firework::Firework(SPC_Particle p)
{
	m_particle = p;
	m_Transform = m_particle->getTransform();
	m_components.push_back(m_Transform);
	m_components.push_back(m_particle);
	std::cout << "created firework with pointers!\n";
	init();
}
void Firework::init()
{
	m_time			= 0.f;
	m_fireworkTime	= 1.5f;
	m_explode		= false;
	m_exploding		= false;

	m_posGenerator.reset(new RoundPosGen());
	m_posGenerator->setCenter(glm::vec4(0.0, 2.0, 0.0, 1.0));
	m_posGenerator->setXRadius(0.15f);
	m_posGenerator->setYRadius(0.15f);

	m_colGenerator.reset(new BasicColourGen());
	m_colGenerator->setMinStartColour(glm::vec4(0.7, 0.7, 0.7, 1.0));
	m_colGenerator->setMaxStartColour(glm::vec4(0.8, 0.8, 0.8, 1.0));
	m_colGenerator->setMinEndColour	 (glm::vec4(0.1, 0.1, 0.1, 0.0));
	m_colGenerator->setMaxEndColour	 (glm::vec4(0.2, 0.2, 0.2, 0.0));

	m_velGenerator.reset(new BasicVelGen());
	m_velGenerator->setMinStartVel(glm::vec4(-5.45f, -5.45f, -5.45f, 0.0f));
	m_velGenerator->setMaxStartVel(glm::vec4( 5.45f,  5.45f,  5.45f, 0.0f));

	m_timeGenerator.reset(new BasicTimeGen());
	m_timeGenerator->setMinTime(0.5f);
	m_timeGenerator->setMaxTime(3.5f);

	m_emitter.reset(new ParticleEmitter());
	m_emitter->init(m_particle->getPoolSize(), 0.45f);
	m_emitter->addGenerator(m_posGenerator);
	m_emitter->addGenerator(m_colGenerator);
	m_emitter->addGenerator(m_velGenerator);
	m_emitter->addGenerator(m_timeGenerator);
	m_particle->addEmitter (m_emitter);

	m_timeUpdater.reset  (new BasicTimeUpdater());
	m_eulerUpdater.reset (new EulerUpdater());
	m_colourUpdater.reset(new BasicColourUpdater());

	m_eulerUpdater->setGlobalAcc(glm::vec4(0.0, -45.0, 0.0, 0.0));

	//m_particle->clear();   //clears updaters
	m_particle->addUpdater(m_timeUpdater);
	m_particle->addUpdater(m_colourUpdater);
	m_particle->addUpdater(m_eulerUpdater);

	m_particle->init();
	//m_particle->setEmitFlag(true);
	//m_particle->resetParticles();
}

void Firework::update(float t)
{

	//if (Input::getKeyPressed(sf::Keyboard::Num1))
	//{
	//	_particleRenderer->setParticlePointSize(10.f);
	//	_explode = true;
	//}
	//if (m_explode)
	//{
	//	m_exploding = true;
	//}
	////do the explode
	//if (m_exploding)
	//{
	//	m_time += t;
	//	if (m_time >= m_fireworkTime)
	//	{
	//		m_time = 0.f;
	//		m_exploding = false;
	//		m_explode = false;
	//		//_particleRenderer->setEmitFlag(false);
	//	}
	//	else
	//	{
	//		//_particleRenderer->setEmitFlag(true);
	//	}
	//}

}

