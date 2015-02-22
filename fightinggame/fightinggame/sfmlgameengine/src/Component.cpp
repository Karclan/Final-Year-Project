#include "Component.h"

Component::Component(){
	std::cout << "C| Component: ";
}
Component::~Component(){
	std::cout << "D| Component: ";
}
void Component::setState(ComponentState::state state)
{
	m_state = state;
}
ComponentState::state Component::getState()
{
	return m_state;
}