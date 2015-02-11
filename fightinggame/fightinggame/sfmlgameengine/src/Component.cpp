#include "Component.h"

Component::Component(){}
Component::~Component(){}
void Component::setState(ComponentState::state state)
{
	m_state = state;
}
ComponentState::state Component::getState()
{
	return m_state;
}