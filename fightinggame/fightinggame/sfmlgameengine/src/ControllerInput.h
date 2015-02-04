#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H


//This will be a mixture of sf joystick
//and the x360controller xinput wrapper

#include <sfml\Window.hpp>
#include "X360Controller.hpp"
#include <map>

#include "GS.h"

enum buttons{A,B,X,Y,LB,RB,UP,DOWN,LEFT,RIGHT,START,BACK,LS,RS,  _BUTTONS_};

class ControllerInput
{
public:

	bool init(int controllerHandle);
	bool checkConnected(int controllerHandle);

	void reset();

	void update();//Checks to see what is pressed and what the axis values are

	bool _buttons[_BUTTONS_];

	float _leftT,_rightT;
	sf::Vector2f _leftStick,_rightStick;
private:

	void getInput();

	int _controllerHandle;
	bool _connected;

	

};
#endif