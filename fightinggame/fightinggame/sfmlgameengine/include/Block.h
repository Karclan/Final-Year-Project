#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"
#include "Collidable.h"
#include "Renderable.h"
#include "Transfrom.h"

/*! \brief  Block

Block class. Generic block within a level. Has collidable, renderable and transform components

*/
class Block : public GameObject
{
public:
	Block(SPC_Transform t, SPC_Collidable c, SPC_Renderable r);
	Block();
	~Block();
	
	void update(float dt); //!< empty function
	void renderUpdate(); //!< empty function
protected:

	SPC_Collidable m_Collidable;
	SPC_Transform m_Transform;
	SPC_Renderable m_Renderable;
};
#endif