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
namespace CollisionType
{
	enum type{top,botton,left,right, basiccollision,noCollision};
}

struct CollisionInstance
{
public:
	glm::vec3 m_CollisionNormal;
	glm::vec2 m_PenetrationDepth;
};


class Collidable : public Component
{
	
public:

	Collidable();
	Collidable(SPC_Transform t, float sizeX,float sizeY, GameObjectType::type owner);

	ComponentType::type getType();
	void tearDown();

	void update();
	bool Interesects(SPC_Collidable other);
	int  InteresectsDetailed(SPC_Collidable other);
	int  getCurrentCollision(){return m_currentCollision;}

	GameObjectType::type  getOwner(){ return m_Owner; }
	SPC_Transform getTransform(){ return m_Transform; }
	glm::vec2 getUpperBounds(){ return m_UpperPos; }
	glm::vec2 getLowerBounds(){ return m_LowerPos; }
	glm::vec2 getSize(){return m_Size;}
	SPC_Collidable getCollisionTatget(){ return m_CollisionTarget; }

	CollisionInstance getCollisionInstance(){ return m_colInstance; }
private:

	GameObjectType::type  m_Owner;
	CollisionType::type   m_currentCollision;
	glm::vec2 m_UpperPos, m_LowerPos;

	glm::vec2  m_Size;

	CollisionInstance m_colInstance;
	SPC_Collidable m_CollisionTarget;
	SPC_Transform  m_Transform;
};


#endif