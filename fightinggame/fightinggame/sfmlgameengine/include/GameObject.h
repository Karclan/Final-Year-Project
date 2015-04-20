#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Component.h"
#include "GS.h"
#include <vector>

//! Gameobject type enum, used to determin what game objects are what
namespace GameObjectType
{
	enum type{ BLOCK, FIGHTER, GAMEOBJECTTYPES };
}

/*! \brief  GameObject Class

GameObject Class. A container class which holds components. These components make up a entity within the game

*/

class GameObject
{
public:

	virtual void update(float dt)=0; //!< Pure virtual function for all game object child classes to define

	SPC_Component findComponent(ComponentType::type);//!< Tries to find a component that the gameObject owns and then returns a Shared Component pointer to be dynamically cast into a subtype

protected:

	std::vector<SPC_Component> m_components;
	
};
#endif
