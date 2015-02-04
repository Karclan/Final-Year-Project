#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SFML/system.hpp>
#include <SFML/graphics.hpp>

#include <iostream>
#include <list>
using namespace std;

#include "Collidable.h"
#include "GameObject.h"
#include "GS.h"
#include "HitBox.h"

class CollisionManager
{
private:
	std::list<Collidable*> m_lstOfCollidables;

	void checkCollision(Collidable* , Collidable*);
	HitBox* addHitBox(Mesh *m, float timeToLive);
	
public:
	void addCollisionObject(Collidable *_newCollidable){m_lstOfCollidables.push_back(_newCollidable);}
	void createHitBox(Mesh *m, float timeToLive);
	void addToCheck(Collidable*);
	void removeFromCheck(Collidable*);
	void removeFromCheck();
	void update();
};
#endif
