#include "ControllerInput.h"

bool ControllerInput::init(int controllerHandle)
{
	reset();
	if(checkConnected(controllerHandle)==true)
	{
	_controllerHandle=controllerHandle;
	_connected=true;
	return true;
	}
	else
	{
		_controllerHandle=-1;
		_connected=false;
		return false;
	}
}
bool ControllerInput::checkConnected(int controllerHandle)
{
	return sf::Joystick::isConnected(controllerHandle);
}
void ControllerInput::reset()
{
	_leftStick=sf::Vector2f(0.f,0.f);
	_rightStick=sf::Vector2f(0.f,0.f);
	_leftT=0.f;
	_rightT=0.f;
	for(int i=0;i<_BUTTONS_;++i)
	{
		_buttons[i]=false;
	}
}
void ControllerInput::getInput()
{
	xb::Joystick::getSticksPosition(_controllerHandle,_leftStick,_rightStick);
	xb::Joystick::getTriggers(_controllerHandle,_leftT,_rightT);
	_buttons[A]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::A);
	_buttons[B]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::B);
	_buttons[X]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::X);
	_buttons[Y]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::Y);
	_buttons[LB]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::LB);
	_buttons[RB]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::RB);
	_buttons[UP]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::DPAD_UP);
	_buttons[DOWN]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::DPAD_DOWN);
	_buttons[LEFT]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::DPAD_LEFT);
	_buttons[RIGHT]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::DPAD_RIGHT);
	_buttons[START]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::START);
	_buttons[BACK]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::BACK);
	_buttons[LS]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::LEFT_THUMB);
	_buttons[RS]=xb::Joystick::isButtonPressed(_controllerHandle,xb::Joystick::RIGHT_THUMB);
}
void ControllerInput::update()
{
	if(checkConnected(_controllerHandle)==true  && _controllerHandle != -1)
	{
		getInput();
	}
	else
	{
		_controllerHandle=-1;
		reset();
	}
}