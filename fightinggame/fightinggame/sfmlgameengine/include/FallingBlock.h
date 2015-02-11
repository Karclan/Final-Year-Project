#ifndef GAMEOBJECT_FALLINGBLOCK_H
#define GAMEOBJECT_FALLINGBLOCK_H

#include "Block.h"


class FallingBlock : public Block
{
public:
	FallingBlock(SPC_Transform t, SPC_Collidable c, SPC_Renderable r);
	FallingBlock();
	~FallingBlock();
	void update(float _dt);

private:
};
#endif