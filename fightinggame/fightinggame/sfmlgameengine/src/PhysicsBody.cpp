#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
{
	m_Transform = nullptr;
	m_Collidable = nullptr;
	m_Velocity	= glm::vec3(0);
	m_Gravity	= 0.f;
	m_Drag		= 0.94f;
	m_Mass		= 1.f;
	m_Awake = false;
}
PhysicsBody::PhysicsBody(SPC_Transform t, SPC_Collidable c)
{
	m_Transform = t;
	m_Collidable = c;
	m_Velocity	= glm::vec3(0);
	m_Gravity	= 0.f;
	m_Drag		= 0.94f;
	m_Mass		= 1.f;
	m_Awake		= true;
}
PhysicsBody::PhysicsBody(SPC_Transform t, SPC_Collidable c, glm::vec3 vel, float mass, float drag, float grav)
{
	m_Transform = t;
	m_Collidable = c;
	m_Velocity	= vel;
	m_Mass		= mass;
	m_Drag		= drag;
	m_Gravity	= grav;
	m_Awake = true;
}
PhysicsBody::~PhysicsBody()
{

}
ComponentType::type PhysicsBody::getType()
{
	return ComponentType::PHYSICSBODY;
}
void PhysicsBody::tearDown()
{

}
void PhysicsBody::fixedUpdate(float t)
{
	if (!m_Collisions.empty()) //Unimplemented system, for if I was to have complex collisions
	{
		
	}
	
	if (m_Collidable->getCurrentCollision() == CollisionType::botton)
	{
		m_Transform->setPosition(glm::vec3(
			m_Transform->getPosition().x,
			m_Transform->getPosition().y - m_Collidable->getCollisionInstance().m_PenetrationDepth.y / 128,
			m_Transform->getPosition().z));
		//return;
	}
	if (m_Collidable->getCurrentCollision() == CollisionType::left)
	{
		m_Transform->setPosition(glm::vec3(
			m_Transform->getPosition().x + m_Collidable->getCollisionInstance().m_PenetrationDepth.x / 128,
			m_Transform->getPosition().y,
			m_Transform->getPosition().z));
		//return;
	}
	if (m_Collidable->getCurrentCollision() == CollisionType::right)
	{
		m_Transform->setPosition(glm::vec3(
			m_Transform->getPosition().x - m_Collidable->getCollisionInstance().m_PenetrationDepth.x / 128,
			m_Transform->getPosition().y,
			m_Transform->getPosition().z));
		//return;
	}
	if (m_Collidable->getCurrentCollision() == CollisionType::top)
	{
		m_Transform->setPosition(glm::vec3(
			m_Transform->getPosition().x,
			m_Transform->getPosition().y - m_Collidable->getCollisionInstance().m_PenetrationDepth.y / 128,
			m_Transform->getPosition().z));
		m_Velocity.y = 0.f;
		//return;
	}
	//Physics Calculations go here

	m_Transform->translate(m_Velocity*t);

	m_Acceleration += glm::vec3(0, m_Gravity, 0);
	m_Velocity += (m_Acceleration - m_Velocity) * t;

	m_Acceleration = glm::vec3(0);

	

	if (!m_Collisions.empty())
	{
		m_Collisions.clear();
	}
	// need to be able to sort out collision stuff still
}
void PhysicsBody::addForce(glm::vec3 f)
{

}
void PhysicsBody::addImpulse(glm::vec3 i)
{
	m_Velocity += i;
}
void PhysicsBody::setMass(float m)
{
	m_Mass = m;
}
void PhysicsBody::setGravity(float g)
{
	m_Gravity = g;
}
void PhysicsBody::setDrag(float d)
{
	m_Drag = d;
}
void PhysicsBody::wakeUp()
{
	m_Awake = true;
}
bool PhysicsBody::isAwake()
{
	return m_Awake;
}