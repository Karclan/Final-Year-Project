#include "Block.h"
//whenever mytransform is changed, change the collision box position also
Block::Block()
{
	myCollidable=nullptr;
	setPosition(glm::vec3(0,0,0));
	setColour(sf::Vector3f(0,0,0));
	giveMesh(nullptr);
}
Block::Block(float _size, glm::vec3 _position, Mesh *_mesh, sf::Vector3f _colour)
{
	myCollidable=new Collidable(_size,sf::Vector2f(_position.x,_position.y),GS::gameObjType::block);
	init(_mesh,_colour);
	setPosition(_position);
}
void Block::update(float _dt)
{
	updateCycle();
}
void Block::updateCycle()
{
	myTransform += myVelocity;
	myCollidable->move(sf::Vector2f(getTransform().x,getTransform().y));
}
Block::~Block()
{
	myCollidable=nullptr;
	delete myCollidable;
}