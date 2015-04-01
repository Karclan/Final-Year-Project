#include "Particle.h"

Particle::Particle()
{
	m_transform		 = nullptr;
	m_shader		 = nullptr;
	m_particleSystem = nullptr;
	m_particlePool	 = 0;
	std::cout << "Particle created with nullptrs\n";
}
Particle::Particle(SPC_Transform t, size_t poolSize, Shader* s)
{
	m_transform = t;
	m_particlePool = poolSize;
	m_shader = s;
	m_particleSystem.reset(new ParticleSystem(poolSize));
	std::cout << "Particle created with pointers\n";
}
ComponentType::type Particle::getType()
{
	return ComponentType::PARTICLE;
}
void Particle::tearDown()
{

}
void Particle::init()
{
	m_particleRenderable->generate(m_particleSystem,m_particlePool);
}
void Particle::render()
{
	if (!m_renderFlag)return;
	m_shader->useProgram();
	glEnable(GL_PROGRAM_POINT_SIZE);
	m_particleRenderable->render(m_particleSystem);
	glDisable(GL_PROGRAM_POINT_SIZE);
}
void Particle::animate(float t)
{
	if (!m_playFlag)return;
	m_particleSystem->update(t);
	m_particleRenderable->updateBuffers(m_particleSystem);
}
void Particle::setParticlePointSize(float size)
{
	m_shader->setUniform("u_PointSize", size);
}
void Particle::setPoolSize(size_t poolSize)
{
	m_particlePool = poolSize;
}
int Particle::getPoolSize()
{
	return m_particlePool;
}
void Particle::addEmitter(SP_ParticleEmitter em)
{
	m_emitter = em;
	m_particleSystem->addEmitter(em);
}
void Particle::addUpdater(SP_ParticleUpdater up)
{
	m_updaters.push_back(up);
	m_particleSystem->addUpdater(up);
}
void Particle::setAnimFlag(bool f)
{
	m_playFlag = f;
}
void Particle::setDispFlag(bool f)
{
	m_renderFlag = f;
}
void Particle::setEmitFlag(bool f)
{
	m_particleSystem->_emitFlag = f;
}
bool Particle::getEmitFlag()
{
	return m_particleSystem->_emitFlag;
}
void Particle::clear()
{
	m_updaters.clear();
}
void Particle::resetParticles()
{
	m_particleSystem.reset();
}