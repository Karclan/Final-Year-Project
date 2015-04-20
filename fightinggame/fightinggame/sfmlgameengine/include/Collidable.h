#ifndef COMPONENT_COLLIDABLE_H
#define COMPONENT_COLLIDABLE_H

#include <SFML/system.hpp>
#include <SFML/graphics.hpp>

#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include <iostream>
using namespace std;

#include "Component.h"
#include "Transfrom.h"
#include "GameObject.h"


class Collidable;
typedef	std::shared_ptr<Collidable> SPC_Collidable;

//! Collision Types, part of the collision data accquired during a intersection 
namespace CollisionType
{
	enum type{top,botton,left,right, basiccollision,noCollision};
}

//! Unused Struct, a non-finished element meant to improve the collison system
struct CollisionInstance
{
public:
	glm::vec3 m_CollisionNormal;
	glm::vec2 m_PenetrationDepth;
};

/*! \brief Collidable Component Class

Collidable component, used to determin intersections between collidables

*/
class Collidable : public Component
{
	
public:

	Collidable();
	Collidable(SPC_Transform t, float sizeX,float sizeY, GameObjectType::type owner); //!< Constructor which sets up all the data required to specify a collidable object

	ComponentType::type getType();
	void tearDown();

	void update(); //!< updates the bounds of the AABB box
	bool Interesects(SPC_Collidable other); //!< Simple intersection test, returns yes or no on intersections
	int  InteresectsDetailed(SPC_Collidable other); //!< More complex intersection test, returns the side the intersection is occuring on
	int  getCurrentCollision(){return m_currentCollision;} //!< returns the current collision type

	GameObjectType::type  getOwner(){ return m_Owner; } //!< Gets the owner of the collidable, used for the basic collision resolution, the idea was to determin resolution of collisions based upon behaviours and object types
	SPC_Transform getTransform(){ return m_Transform; }
	glm::vec2 getUpperBounds(){ return m_UpperPos; }
	glm::vec2 getLowerBounds(){ return m_LowerPos; }
	glm::vec2 getSize(){return m_Size;}
	SPC_Collidable getCollisionTatget(){ return m_CollisionTarget; }//!< Gets the current object the collidable is intersecting with

	CollisionInstance getCollisionInstance(){ return m_colInstance; }//!< Unused function, non-finished element meant to improve the collision system. The intention was to be able to resolve multiple collisions per update cycle
private:

	GameObjectType::type  m_Owner; //!< Owner of collidable 
	CollisionType::type   m_currentCollision; //!< current collision type 
	glm::vec2 m_UpperPos, m_LowerPos;//!< AABB 

	glm::vec2  m_Size; //!< Size of AABB along X and Y 

	CollisionInstance m_colInstance; //!< Unused Collision instance, non-finished element meant to improve the collision system
	SPC_Collidable m_CollisionTarget;//!< Collision Target, nullptr if no intersection
	SPC_Transform  m_Transform;
};


#endif