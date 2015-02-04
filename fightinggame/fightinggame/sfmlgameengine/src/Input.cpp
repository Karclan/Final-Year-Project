#include "Input.h"

void Input::init()
{
	for(int i=0; i<256; i++)
	{
		_KEYS[i] = false;
	}
	for(int i=0; i<256; i++)
	{
		_KEYHELDTIME[i] = 0;
	}
}
void Input::keyPressed(int key_code)
{
	if(_KEYS[key_code]==false)
	{
		_KEYS[key_code]=true;
		_KEYHELDTIME[key_code] ++;
	}
}
void Input::keyReleased(int key_code)
{
	if(_KEYS[key_code]==true)
	{
		_KEYS[key_code]=false;
		_KEYHELDTIME[key_code] =0;
	}
}
void Input::keyHeld()
{
	for(int i=0;i<256;i++)
	{
		if(_KEYS[i]==true)
		{
			_KEYHELDTIME[i] ++;
		}
	}

}