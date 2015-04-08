#include "CollisionManager.h"

void CollisionManager::update()
{
	for (auto i : m_lstOfCollidables)
	{
		i->update();
		for (auto j : m_lstOfCollidables)
		{
			checkCollision(i, j);
		}
	}

}

void CollisionManager::checkCollision(SPC_Collidable a, SPC_Collidable b)
{
	a->InteresectsDetailed(b);
}
SPC_Collidable CollisionManager::createCollidable(SPC_Transform t, float sizeX, float sizeY, GameObjectType::type owner)
{
	SPC_Collidable c(new Collidable(t, sizeX, sizeY, owner));
	m_lstOfCollidables.push_back(c);
	return c;
}
void CollisionManager::addToCheck(SPC_Collidable n)
{
	m_lstOfCollidables.push_back(n);
}
void CollisionManager::removeFromCheck()
{
	for(auto it: m_lstOfCollidables)
	{
		if(it==nullptr) m_lstOfCollidables.remove(it);
	}
}
void CollisionManager::removeFromCheck(SPC_Collidable c)
{
	for(auto it: m_lstOfCollidables)
	{
		if (it == c) it = nullptr;
	}
}