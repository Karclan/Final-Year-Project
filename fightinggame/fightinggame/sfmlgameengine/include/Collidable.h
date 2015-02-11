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

namespace CollisionType
{
	enum type{top,botton,left,right, basiccollision,noCollision};
}

class Collidable : public Component
{

public:

	Collidable();
	Collidable(float _size /*Size*/, sf::Vector2f _position /*Position*/, int _owner);

	ComponentType::type getType();
	void tearDown();

	void move(glm::vec2 newPos);
	bool Interesects(Collidable* other);
	int  InteresectsDetailed(Collidable* other);
	int  getCurrentCollision(){return m_currentCollision;}
	int  getOwner(){return m_Owner;}


	glm::vec2 getPos(){return glm::vec2(m_Transform->getPosition());}
	float getSize(){return m_Size;}
	Collidable* getCollisionTatget(){return m_CollisionTarget;}

	int m_currentCollision;

	Collidable& operator= (Collidable& newC){
		m_Transform->setPosition(newC.m_Transform->getPosition());
		m_Size = newC.m_Size;
		m_UpperPos = glm::vec2(newC.m_Transform->getPosition().x+m_Size/2, newC.m_Transform->getPosition().y+m_Size/2);
		m_LowerPos = glm::vec2(newC.m_Transform->getPosition().x-m_Size/2, newC.m_Transform->getPosition().y-m_Size/2);
		return *this;
	};
private:

	glm::vec2 m_UpperPos, m_LowerPos;
	float m_Size;
	int m_Owner;
	

	Collidable *m_CollisionTarget;
	SPC_Transform m_Transform;
};

typedef	std::shared_ptr<Collidable> SPC_Collidable;

#endif