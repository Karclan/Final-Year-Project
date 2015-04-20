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

/*! \brief  CollisionManager Class

CollisionManager Class which manages all collidables and checks them against other to test for intersection
*/

class CollisionManager
{
public:
	SPC_Collidable createCollidable	(SPC_Transform t, float sizeX,float sizeY, GameObjectType::type owner); //!< Creates a collidable Shared Pointer to be returned and put into a game object. Also adds the shared pointer to its own vector
	void addCollisionObject			(SPC_Collidable newCollidable){ m_lstOfCollidables.push_back(newCollidable); }
	void addToCheck					(SPC_Collidable);//!<Adds collidable to check
	void removeFromCheck			(SPC_Collidable);//!<Removes collidable from check
	void removeFromCheck();//!<Clears all collidables which removes them from the check
	void update();//!<updates all collidables and then checks them against each other
private:
	std::list<SPC_Collidable> m_lstOfCollidables; //!<List of collidables which is also the check list
	void checkCollision(SPC_Collidable, SPC_Collidable);//!<Checks for interesction between two collidables
};
#endif
