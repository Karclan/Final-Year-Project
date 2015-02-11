#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>

#include "Collidable.h"
#include "Timer.h"
#include "Renderable.h"

class HitBox : public Collidable
{
public:
	HitBox(SPC_Transform t,SPC_Renderable r,float timeToLive);
	~HitBox();
	void update(float dt);


private:
	float m_timeToLive;
	SPC_Renderable m_Renderable;
};
#endif