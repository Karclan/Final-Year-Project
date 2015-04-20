#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <memory>
#include <vector>

#include <glm\glm.hpp>

#include "PhysicsBody.h"

/*! \brief  PhysicsManager Class

PhysicsManager Class. A class which manages all the physics bodies within the scene

*/

class PhysicsManager
{
public:
	PhysicsManager(); //!< default constructor setting gravity to be -0.94f
	~PhysicsManager();

	void init(); //!< empty unused function
	void update(float t);//!< calls fixed update on all physics bodies
	void setGravity(float g); //!< sets gravity of all physics bodies
	glm::vec3 getGravity();

	SPC_PhysicsBody createPhysicsBody(SPC_Transform t, SPC_Collidable c); //!< creates physics body with default values. Adds to vector
	SPC_PhysicsBody createPhysicsBody(SPC_Transform t, SPC_Collidable c, glm::vec3 vel, float mass, float drag);//!<! creates physics body with define values for velocity, mass and drag
private:
	std::vector<SPC_PhysicsBody> m_PhysicsBodies;
	float m_Gravity;
};

#endif