#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <memory>
#include <vector>

#include <glm\glm.hpp>

#include "PhysicsBody.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void init(); 
	void update(float t);
	void setGravity(float g);
	glm::vec3 getGravity();

	SPC_PhysicsBody createPhysicsBody(SPC_Transform t);
	SPC_PhysicsBody createPhysicsBody(SPC_Transform t, glm::vec3 vel, float mass, float drag);
private:
	std::vector<SPC_PhysicsBody> m_PhysicsBodies;
	float m_Gravity;
};

#endif