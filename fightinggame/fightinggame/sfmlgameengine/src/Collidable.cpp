#include "Collidable.h"

Collidable::Collidable()
{
	m_Owner=GameObjectType::GAMEOBJECTTYPES;
	m_CollisionTarget=nullptr;
	m_currentCollision = CollisionType::noCollision;
	m_Size = NULL;
	m_UpperPos = glm::vec2(NULL, NULL);
	m_LowerPos = glm::vec2(NULL, NULL);
	std::cout << "Collidable Component created!\n";
}
ComponentType::type Collidable::getType()
{
	return ComponentType::COLLIDABLE;
}
void Collidable::tearDown()
{

}
Collidable::Collidable(SPC_Transform t, float size, GameObjectType::type owner)
{
	m_CollisionTarget	= nullptr;
	m_Owner				= owner;
	m_Transform			= t;
	m_Size				= size;
	m_currentCollision  = CollisionType::noCollision;

	m_UpperPos = glm::vec2(m_Transform->getPosition().x + m_Size / 2, m_Transform->getPosition().y + m_Size / 2);
	m_LowerPos = glm::vec2(m_Transform->getPosition().x - m_Size / 2, m_Transform->getPosition().y - m_Size / 2);

	std::cout << "Collidable Component created!\n";
}

void Collidable::update()
{
	m_UpperPos = glm::vec2(m_Transform->getPosition().x +  m_Size / 2, m_Transform->getPosition().y + m_Size / 2);
	m_LowerPos = glm::vec2(m_Transform->getPosition().x -  m_Size / 2, m_Transform->getPosition().y - m_Size / 2);
}
bool Collidable::Interesects(SPC_Collidable _other)
{
	if (m_UpperPos.x< _other->getLowerBounds().x || m_LowerPos.x > _other->getUpperBounds().x){ m_CollisionTarget = nullptr; return false; }
	if (m_UpperPos.y< _other->getLowerBounds().y || m_LowerPos.y> _other->getUpperBounds().y){ m_CollisionTarget = nullptr; return false; }
	return true;
};

int Collidable::InteresectsDetailed(SPC_Collidable _other)
{
	if (m_UpperPos.x< _other->getLowerBounds().x || m_LowerPos.x > _other->getUpperBounds().x)
	{
		m_currentCollision = CollisionType::noCollision;
		m_CollisionTarget=nullptr;
		return CollisionType::noCollision;
	}
	if (m_UpperPos.y< _other->getLowerBounds().y || m_LowerPos.y> _other->getUpperBounds().y)
	{
		m_currentCollision = CollisionType::noCollision;
		m_CollisionTarget=nullptr;
		return CollisionType::noCollision;
	}

	m_CollisionTarget=_other;

	//difference in x and difference in y
	float dif_x = _other->getTransform()->getPosition().x - m_Transform->getPosition().x;
	float dif_y = _other->getTransform()->getPosition().y - m_Transform->getPosition().y;

	if(abs(dif_x) > abs(dif_y))
	{
		if(dif_x>0)
		{
			m_currentCollision = CollisionType::left;
			return CollisionType::left;
		}
		if(dif_x<0)
		{
			m_currentCollision = CollisionType::right;
			return CollisionType::right;
		}
	}
	else
	{
		if(dif_y>0)
		{
			m_currentCollision = CollisionType::top;
			return CollisionType::top;
		}
		if(dif_y<0)
		{
			m_currentCollision = CollisionType::botton;
			return CollisionType::botton;
		}
	}
	return CollisionType::basiccollision;
};