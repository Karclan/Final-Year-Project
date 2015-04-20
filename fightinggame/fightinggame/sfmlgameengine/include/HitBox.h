#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>

#include "Collidable.h"
#include "Timer.h"
#include "Renderable.h"
/*! \brief  Hitbox Component Class

Hitbox Component Class, currently unused class. Intended to be used in the fighting game to create
attacks that the fighters could use to attack each other with.

*/
//!< 
class HitBox : public Collidable
{
public:
	HitBox(SPC_Transform t,SPC_Renderable r,float timeToLive); //!< Constructor of hitbox, meant to be created at runtime dynamically as fighters attack
	~HitBox();
	void update(float dt); //!< Updates the time the hitbox currently has to live. Once over time the should hitbox deallocate itself


private:
	float m_timeToLive;
	SPC_Renderable m_Renderable;
};
#endif