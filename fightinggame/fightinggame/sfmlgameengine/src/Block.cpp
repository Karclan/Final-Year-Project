#include "Block.h"
//whenever mytransform is changed, change the collision box position also
Block::Block()
{
	m_Collidable=nullptr;
	m_Transform=nullptr;
	m_Renderable=nullptr;
}
Block::Block(SPC_Transform t, SPC_Collidable c, SPC_Renderable r)
{
	m_Transform  =t;
	m_Collidable =c;
	m_Renderable =r;
	m_components.push_back(m_Transform);
	m_components.push_back(m_Collidable);
	m_components.push_back(m_Renderable);
}
void Block::update(float dt)
{
	m_Renderable->renderUpdate();
}
void Block::renderUpdate()
{
	
}

//void Block::updateCycle()
//{
//	myTransform += myVelocity;
//	myCollidable->move(sf::Vector2f(getTransform().x,getTransform().y));
//}
Block::~Block()
{
	m_Collidable=nullptr;
	m_Transform=nullptr;
	m_Renderable=nullptr;
}