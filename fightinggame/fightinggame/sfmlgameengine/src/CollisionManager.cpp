#include "CollisionManager.h"

void CollisionManager::update()
{
	removeFromCheck();
	for(auto i : m_lstOfCollidables)
	{
		for(auto j : m_lstOfCollidables)
		{
			if(i!=j)
			{
				checkCollision(SPC_Collidable(i),SPC_Collidable(j));
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
	m_lstOfCollidables.push_back(c);
	return SPC_Collidable(c);
}
void CollisionManager::addToCheck(Collidable *n)
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
void CollisionManager::removeFromCheck(Collidable *c)
{
	for(auto it: m_lstOfCollidables)
	{
		if(it==c) it=nullptr;
	}
}