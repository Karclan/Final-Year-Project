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
}
void Block::update()
{

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