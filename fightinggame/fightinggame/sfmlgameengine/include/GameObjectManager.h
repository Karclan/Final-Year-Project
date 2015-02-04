#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <list>

#include "GameObject.h"
#include "Block.h"
#include "Fighter.hpp"
#include "Collidable.h"
#include "CollisionManager.h"

class GameObjectManager
{
public:
	GameObjectManager(void);
	~GameObjectManager(void);
	std::list<GameObject*>& getObjectList(){return m_lstOfGameObjects;}
	
	void update();

	void newGO(int type/*position*/);
private:
	GameObject* newObj();

	std::list<GameObject *> m_lstOfGameObjects;
	CollisionManager* m_cm;
};
#endif