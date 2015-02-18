#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(void)
{

}
GameObjectManager::~GameObjectManager(void)
{

}
void GameObjectManager::update()
{
	for (auto it : m_GameObjects)
	{ 
		it->update(Timer::getTime());
	}
}
void GameObjectManager::newGO(int type)
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
