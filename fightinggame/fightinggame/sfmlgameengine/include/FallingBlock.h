#ifndef GAMEOBJECT_FALLINGBLOCK_H
#define GAMEOBJECT_FALLINGBLOCK_H

#include "Block.h"

/*! \brief  FallingBlock

FallingBlock  class. Unimplemented class intended to be used as a block which falls when nothing is supporting it. Has transform, collidable and renderable components

*/
class FallingBlock : public Block
{
public:
	FallingBlock(SPC_Transform t, SPC_Collidable c, SPC_Renderable r);
	FallingBlock();
	~FallingBlock();
	void update(float _dt); //!< empty function

private:
};
#endif