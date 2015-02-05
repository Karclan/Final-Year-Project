#include "Component.h"

void Component::setState(ComponentState::state state)
{
	m_state = state;
}
ComponentState::state Component::getState()
{
	return m_state;
}