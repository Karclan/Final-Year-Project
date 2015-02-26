#include "Input.h"

void Input::init()
{
	for(int i=0; i<256; i++)
	{
		m_KEYS[i] = false;
	}
	for(int i=0; i<256; i++)
	{
		m_KEYHELDTIME[i] = 0.f;
	}
}
void Input::update()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_KEYS[i] == true)
		{
			m_KEYHELDTIME[i] += Timer::getTime().asMilliseconds();
		}
	}
}
bool Input::isKeyPressed(int key_code)
{
	return m_KEYS[key_code];
}
void Input::keyPressed(int key_code)
{
	if (m_KEYS[key_code] == false)
	{
		m_KEYS[key_code] = true;
	}
}
void Input::keyReleased(int key_code)
{
	if (m_KEYS[key_code] == true)
	{
		m_KEYS[key_code] = false;
		m_KEYHELDTIME[key_code] = 0;
	}
}