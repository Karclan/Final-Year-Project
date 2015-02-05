#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>

namespace ComponentType
{
	enum type{COMPONENT, TRANSFORM, COLLIDABLE, LIGHT, CAMERA, COMPONENTTYPES};
}
namespace ComponentState
{
	enum state{ON,OFF,SLEEP,TEARDOWN,DEAD};
}

class Component
{
public:

	Component();
	~Component();

	virtual	ComponentType::type getType()=0;
	virtual void				tearDown()=0; //! Function to set the state to teardown

	void setState(ComponentState::state state);

	ComponentState::state getState();

protected:

	ComponentType::type m_type;
	ComponentState::state m_state;

};

typedef	std::shared_ptr<Component> SPC_Component;

#endif