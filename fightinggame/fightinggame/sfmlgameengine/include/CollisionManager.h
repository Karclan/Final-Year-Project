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
public:
	SPC_Collidable createCollidable	(SPC_Transform t, float size, GameObjectType::type owner);
	void addCollisionObject			(SPC_Collidable newCollidable){ m_lstOfCollidables.push_back(newCollidable); }
	void addToCheck					(SPC_Collidable);
	void removeFromCheck			(SPC_Collidable);
	void removeFromCheck();
	void update();
private:
	std::list<SPC_Collidable> m_lstOfCollidables;
	void checkCollision(SPC_Collidable, SPC_Collidable);
};
#endif
