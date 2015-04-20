#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include <memory>

#include <glm\glm.hpp>

#include "Component.h"
#include "Transfrom.h"
#include "Collidable.h"
/*! \brief  PhysicsBody Component Class

Physics Body Component class, component class for the physics system, contains all physics data needed to give physics to an object

*/

class PhysicsBody : public Component
{
public:
	PhysicsBody();
	PhysicsBody(SPC_Transform t, SPC_Collidable c); //!<Constructor which sets physics data to default basic values
	PhysicsBody(SPC_Transform t, SPC_Collidable c, glm::vec3 vel, float mass, float drag, float grav); //!<Constructor which gives more specific physics values to object
	~PhysicsBody();

	ComponentType::type getType();
	void tearDown();

	void fixedUpdate(float t); //!< fixed update which updates velocity and acceleration of object, then translates the transform component

	void addForce(glm::vec3 f); //!<Unused function, intended to be used to add a force to an object
	void addImpulse(glm::vec3 i);//!<Function which adds an instant impulse to an object 

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

	bool m_Awake; //!<Awake flag of physics object, intended to be used to check if object should be counted in collision checks or not

	glm::vec3 m_Acceleration; 
	glm::vec3 m_Velocity;
	float m_Mass; //!<Unused placeholder variable for more complex physics implementation
	float m_Drag; //!<Unused placeholder variable for more complex physics implementation
	float m_Gravity; 
	SPC_Transform m_Transform;
	SPC_Collidable m_Collidable;
	std::map<ComponentType::type, CollisionInstance> m_Collisions;
};

typedef std::shared_ptr<PhysicsBody> SPC_PhysicsBody;

#endif