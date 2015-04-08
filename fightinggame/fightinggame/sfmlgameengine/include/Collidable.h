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

class CollisionInstance
{
public:
	glm::vec3 m_CollisionNormal;
	float m_PenetrationDepth;
};


class Collidable : public Component
{
	
public:

	Collidable();
	Collidable(SPC_Transform t, float size, GameObjectType::type owner);

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
	float getSize(){return m_Size;}
	SPC_Collidable getCollisionTatget(){ return m_CollisionTarget; }

	//Collidable& operator= (Collidable& newC){
	//	m_Transform->setPosition(newC.m_Transform->getPosition());
	//	m_Size = newC.m_Size;
	//	m_UpperPos = glm::vec2(newC.m_Transform->getPosition().x+m_Size/2, newC.m_Transform->getPosition().y+m_Size/2);
	//	m_LowerPos = glm::vec2(newC.m_Transform->getPosition().x-m_Size/2, newC.m_Transform->getPosition().y-m_Size/2);
	//	return *this;
	//};

private:

	GameObjectType::type  m_Owner;
	CollisionType::type   m_currentCollision;
	glm::vec2 m_UpperPos, m_LowerPos;

	float m_Size;

	SPC_Collidable m_CollisionTarget;
	SPC_Transform  m_Transform;
};


#endif