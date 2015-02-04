#include "HitBox.h"

HitBox::HitBox(Mesh *m, float timeToLive)
{
	m_mesh = m;
	m_timeToLive = timeToLive;
}
HitBox::~HitBox()
{
	
	m_mesh=nullptr;
}
void HitBox::update(float dt)
{
	m_timeToLive -=Timer::getTime();
	if(m_timeToLive < 0)
	{
		std::cout<<"Hitbox destoryed";
	 delete this;
	}
	else
	{

	}
}