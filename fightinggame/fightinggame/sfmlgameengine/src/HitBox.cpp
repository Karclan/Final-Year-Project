#include "HitBox.h"

HitBox::HitBox(SPC_Transform t,SPC_Renderable r,float timeToLive)
{
	m_Renderable = r;
	m_timeToLive = timeToLive;
}
HitBox::~HitBox()
{
	
	m_Renderable = nullptr;
}
void HitBox::update(float dt)
{
	m_timeToLive -=Timer::getTime().asSeconds();
	if(m_timeToLive < 0)
	{
		std::cout<<"Hitbox destoryed";
	 delete this;
	}
	else
	{

	}
}