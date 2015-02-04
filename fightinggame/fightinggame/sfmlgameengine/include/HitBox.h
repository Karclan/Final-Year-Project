#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>

#include "Collidable.h"
#include "Timer.h"
#include "Mesh.h"

class HitBox : public Collidable
{
public:
	HitBox(Mesh *m,float timeToLive);
	~HitBox();
	void update(float dt);


private:
	float m_timeToLive;
	Mesh *m_mesh;
};
#endif