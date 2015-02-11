#include "FallingBlock.h"

FallingBlock::FallingBlock()
{

}
FallingBlock::FallingBlock(SPC_Transform t, SPC_Collidable c, SPC_Renderable r)
{
	m_Transform = t;
	m_Collidable = c;
	m_Renderable = r;
}
void FallingBlock::update(float _dt)
{

}

