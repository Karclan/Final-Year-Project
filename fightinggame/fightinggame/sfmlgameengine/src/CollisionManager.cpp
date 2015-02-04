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
				checkCollision(i,j);
			}
		}
	}

}

void CollisionManager::checkCollision(Collidable *_a, Collidable *_b)
{
	_a->InteresectsDetailed(_b);
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

void CollisionManager::createHitBox(Mesh *m, float timeToLive)
{
	HitBox *newHitBox = addHitBox(m,timeToLive);
	addToCheck(newHitBox->getCollidable());
}
HitBox* CollisionManager::addHitBox(Mesh *m, float timeToLive)
{
	HitBox *nHB = new HitBox(m,timeToLive);
	return nHB;
}