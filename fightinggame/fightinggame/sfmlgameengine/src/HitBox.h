#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>

#include "Collidable.h"
#include "GameObject.h"
#include "Timer.h"
#include "Mesh.h"

class HitBox : public GameObject
{
public:
	HitBox(Mesh *m,float timeToLive);
	~HitBox();
	void update(float dt);


private:
	Mesh * m_mesh;
	float m_timeToLive;
};
#endif