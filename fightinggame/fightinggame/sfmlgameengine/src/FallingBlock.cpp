#include "FallingBlock.h"

FallingBlock::FallingBlock()
{

}
FallingBlock::FallingBlock(float _size, glm::vec3 _position, Mesh* _mesh, sf::Vector3f _colour)
{
	myCollidable=new Collidable(_size,sf::Vector2f(_position.x,_position.y),GS::gameObjType::fallingBlock);
	myTransform = _position;
	giveMesh(_mesh);
	myColour=_colour;
}
