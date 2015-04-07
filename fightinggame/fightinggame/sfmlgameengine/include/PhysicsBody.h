#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include <memory>

#include <glm\glm.hpp>

#include "Component.h"
#include "Transfrom.h"

class PhysisBody
{
public:
	PhysisBody();
	PhysisBody(SPC_Transform t, glm::vec3 vel, float mass, float drag, float grav);
	~PhysisBody();

	void update(float t);

	void addForce(glm::vec3 f);
	void addImpulse(glm::vec3 i);

	glm::vec3 getVel();
	float getMass();
	float getDrag();
	float getGravity();

private:
	glm::vec3 m_Velocity;
	float m_Mass;
	float m_Drag;
	float m_Gravity;
	SPC_Transform m_Transform;
};

#endif