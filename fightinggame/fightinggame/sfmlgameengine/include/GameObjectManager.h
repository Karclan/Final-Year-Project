#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <list>

#include "GameObject.h"
#include "Block.h"
#include "Fighter.hpp"
#include "Collidable.h"
#include "CollisionManager.h"

/*! \brief  GameObjectManager Class

GameObjectManager Class. A class which calls the update on all of the game objects within its list. Not all game objects are added to the list as not all objects need to be updated

*/

class GameObjectManager
{
public:
	GameObjectManager(void);
	~GameObjectManager(void);

	void addGO(GameObject* GO); //!< Adds game object to list
	std::list<GameObject*>& getObjectList(){ return m_GameObjects; } //!<returns pointer to game object list
	
	void update(); //!<updates all of the game objects within its list

	void newGO(GameObjectType::type); //!<unused function
private:
	GameObject* newObj();

	std::list<GameObject *> m_GameObjects; //!<List of game objects
	CollisionManager* m_collisionManagerPTR;
};
#endif