#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(void)
{
	m_GameObjects.clear();
	m_collisionManagerPTR = nullptr;
}
GameObjectManager::~GameObjectManager(void)
{
	for (auto it : m_GameObjects)
	{
		delete it;
	}
	m_GameObjects.clear();
}
void GameObjectManager::addGO(GameObject *GO)
{
	m_GameObjects.push_back(GO);
}
void GameObjectManager::update()
{
	for (auto it : m_GameObjects)
	{ 
		it->update(Timer::getTime().asSeconds());
	}
}
void GameObjectManager::newGO(GameObjectType::type)
{
	/*GameObject *n = newObj();
	switch(type)
	{
	case GS::gameObjType::block:
		n = dynamic_cast<Block*>(n);
		break;
	case GS::gameObjType::Fighter:
		n = dynamic_cast<Fighter*>(n);
		break;
	}
	*/
}
