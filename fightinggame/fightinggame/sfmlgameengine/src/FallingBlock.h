#ifndef GAMEOBJECT_FALLINGBLOCK_H
#define GAMEOBJECT_FALLINGBLOCK_H

#include "Block.h"

class FallingBlock : public Block
{
public:
	FallingBlock(float _size, glm::vec3 _position, Mesh *_mesh, sf::Vector3f _colour);
	FallingBlock();
	~FallingBlock();
	void update(float _dt){updateCycle();}

private:
};
#endif