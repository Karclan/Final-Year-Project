#include "CollisionManager.h"

void CollisionManager::update()
{
	for (auto i : m_lstOfCollidables)
	{
		for (auto j : m_lstOfCollidables)
		{
			if(i!=j)
			{
				checkCollision(i, j);
			}
		}
	}

}

void CollisionManager::checkCollision(SPC_Collidable a, SPC_Collidable b)
{
	a->InteresectsDetailed(b);
}
SPC_Collidable CollisionManager::createCollidable(SPC_Transform t, float size, GameObjectType::type owner)
{
	Collidable* c = new Collidable(t,size,owner);
	m_lstOfCollidables.push_back(SPC_Collidable(c));
	return SPC_Collidable(c);
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