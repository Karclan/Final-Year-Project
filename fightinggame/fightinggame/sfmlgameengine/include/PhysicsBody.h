#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include <memory>

#include <glm\glm.hpp>

#include "Component.h"
#include "Transfrom.h"
#include "Collidable.h"

class PhysicsBody : public Component
{
public:
	PhysicsBody();
	PhysicsBody(SPC_Transform t, SPC_Collidable c);
	PhysicsBody(SPC_Transform t, SPC_Collidable c, glm::vec3 vel, float mass, float drag, float grav);
	~PhysicsBody();

	ComponentType::type getType();
	void tearDown();

	void fixedUpdate(float t);

	void addForce(glm::vec3 f);
	void addImpulse(glm::vec3 i);

	void	  setVelocity(glm::vec3 vel){m_Velocity = vel;}
	glm::vec3 getVelocity(){ return m_Velocity; }

	void	  setAcceleration(glm::vec3 acc){ m_Acceleration = acc; }
	glm::vec3 getAcceleration(){ return m_Acceleration; }

	void  setGravity(float g);
	float getGravity(){ return m_Gravity; }

	void  setMass(float m);
	float getMass(){ return m_Mass; }

	void  setDrag(float d);
	float getDrag(){ return m_Drag; }

	void wakeUp();
	bool isAwake();

private:

	bool m_Awake;

	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	float m_Mass;
	float m_Drag;
	float m_Gravity;
	SPC_Transform m_Transform;
	SPC_Collidable m_Collidable;
	std::map<ComponentType::type, CollisionInstance> m_Collisions;
};

typedef std::shared_ptr<PhysicsBody> SPC_PhysicsBody;

#endif