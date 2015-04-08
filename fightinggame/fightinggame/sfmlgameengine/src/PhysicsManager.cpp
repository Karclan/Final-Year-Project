#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	m_Gravity = -0.94f;
}
PhysicsManager::~PhysicsManager()
{

}
void PhysicsManager::init()
{

}
void PhysicsManager::update(float t)
{
	for (auto it : m_PhysicsBodies)
	{
		if (it->isAwake())
		{
			it->fixedUpdate(t);
		}
	}
}
void PhysicsManager::setGravity(float g)
{
	m_Gravity = g;
	for (auto it : m_PhysicsBodies)
	{
		it->setGravity(m_Gravity);
	}
}
SPC_PhysicsBody PhysicsManager::createPhysicsBody(SPC_Transform t)
{
	SPC_PhysicsBody b(new PhysicsBody(t));
	b->setGravity(m_Gravity);
	m_PhysicsBodies.push_back(b);
	return b;
}
SPC_PhysicsBody PhysicsManager::createPhysicsBody(SPC_Transform t, glm::vec3 vel, float mass, float drag)
{
	SPC_PhysicsBody b(new PhysicsBody(t,vel,mass,drag,m_Gravity));
	b->setGravity(m_Gravity);
	m_PhysicsBodies.push_back(b);
	return b;
}