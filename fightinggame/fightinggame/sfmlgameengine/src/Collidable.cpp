#include "Collidable.h"

Collidable::Collidable()
{
	m_Owner=NULL;
	m_CollisionTarget=nullptr;
	m_currentCollision = CollisionType::noCollision;
}
ComponentType::type Collidable::getType()
{
	return ComponentType::COLLIDABLE;
}
void Collidable::tearDown()
{

}
Collidable::Collidable(float _size /*Size*/, sf::Vector2f _position /*Position*/, int _owner)
{
	m_CollisionTarget=nullptr;
	m_Owner=_owner;
	m_Transform->setPosition(glm::vec3(_position.x,_position.y,m_Transform->getPosition().z));

	m_Size = _size;
	m_currentCollision = CollisionType::noCollision;

	m_UpperPos =glm::vec2(_position.x+m_Size/2, _position.y+m_Size/2);
	m_LowerPos =glm::vec2(_position.x-m_Size/2, _position.y-m_Size/2);
}
void Collidable::move(glm::vec2 _newPos)
{
	m_Transform->setPosition(glm::vec3(_newPos.x,_newPos.y,m_Transform->getPosition().z));
	m_UpperPos = glm::vec2(_newPos.x+m_Size/2, _newPos.y+m_Size/2);
	m_LowerPos = glm::vec2(_newPos.x-m_Size/2, _newPos.y-m_Size/2);
}
bool Collidable::Interesects(Collidable* _other)
{
	if (m_UpperPos.x< _other->m_LowerPos.x || m_LowerPos.x > _other->upperPos.x){_collisionTarget=nullptr; return false;}
	if (m_UpperPos.y< _other->m_LowerPos.y || m_LowerPos.y> _other->m_UpperPos.y){_collisionTarget=nullptr; return false;}
	return true;

};
int Collidable::InteresectsDetailed(Collidable* _other)
{
	if (m_UpperPos.x< _other->m_LowerPos.x || m_LowerPos.x > _other->m_UpperPos.x)
	{
		m_currentCollision = CollisionType::noCollision;
		m_CollisionTarget=nullptr;
		return CollisionType::noCollision;
	}
	if (m_UpperPos.y< _other->m_LowerPos.y || m_LowerPos.y> _other->m_UpperPos.y)
	{
		m_currentCollision = CollisionType::noCollision;
		m_CollisionTarget=nullptr;
		return CollisionType::noCollision;
	}

	m_CollisionTarget=_other;

	//difference in x and difference in y
	float dif_x = _other->m_Transform->getPosition().x - m_Transform->getPosition().x;
	float dif_y = _other->m_Transform->getPosition().y - m_Transform->getPosition().y;

	if(abs(dif_x) > abs(dif_y))
	{
		if(dif_x>0)
		{
			m_currentCollision =CollisionType::left;
			return CollisionType::left;
		}
		if(dif_x<0)
		{
			m_currentCollision =CollisionType::right;
			return CollisionType::right;
		}
	}
	else
	{
		if(dif_y>0)
		{
			m_currentCollision =CollisionType::top;
			return CollisionType::top;
		}
		if(dif_y<0)
		{
			m_currentCollision =CollisionType::botton;
			return CollisionType::botton;
		}
	}
	return CollisionType::basiccollision;
};