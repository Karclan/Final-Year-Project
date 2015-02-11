#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Component.h"
#include "GS.h"
#include <vector>

class GameObject
{
public:

	virtual void update(float dt)=0;
	virtual void renderUpdate()=0;

	SPC_Component findComponent(ComponentType::type);//!< Tries to find a component that the gameObject owns

protected:

	std::vector<SPC_Component> m_components;
	
};
#endif
