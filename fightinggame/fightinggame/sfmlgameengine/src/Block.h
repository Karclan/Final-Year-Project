#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"
#include "Collidable.h"

class Block : public GameObject
{
public:
	Block(float _size, glm::vec3 _position, Mesh *_mesh, sf::Vector3f _colour);
	Block();
	~Block();
	
	void update(float _dt);
	void updateCycle();
protected:
	Collidable *myCollidable;
};
#endif