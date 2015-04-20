#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>
#include <iostream>

namespace ComponentType
{
	enum type{COMPONENT, TRANSFORM, COLLIDABLE, LIGHT, CAMERA, RENDERABLE, PARTICLE, PHYSICSBODY, COMPONENTTYPES};
}
namespace ComponentState
{
	enum state{ON,OFF,SLEEP,TEARDOWN,DEAD};
}

/*! \brief  Component Class

Component class, all systems have components they manage. The component class is a generic component which is inherited from and
never instantiated as a basic component. Component pointers are dynamically cast into different pointers of different classes which inherit from the component class

*/
class Component
{
public:

	Component();
	~Component();

	virtual	ComponentType::type getType()=0; //!< Pure Virtual function all child components must implement. Function is used when getting getting components from game objects
	virtual void				tearDown()=0; //!<Pure Virtual function to set the state to teardown. Currently unused, idea was to set a flag that managers detect and handle the realloctaion of memory at runtime instead of at the end of program

	void setState(ComponentState::state state); //!< Unused function meant to be used to determin if a component is active or not

	ComponentState::state getState(); //!< Returns current state of component

protected:

	ComponentType::type m_type; //!< Type of component
	ComponentState::state m_state; //!< State of component

};

typedef	std::shared_ptr<Component> SPC_Component; //!< Type define of Shared Component pointer, all components define similar types, as it makes it easier to read and code

#endif