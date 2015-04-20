#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H


//This will be a mixture of sf joystick
//and the x360controller xinput wrapper

#include <sfml\Window.hpp>
#include "X360Controller.hpp"
#include <map>

#include "GS.h"

enum buttons{A,B,X,Y,LB,RB,UP,DOWN,LEFT,RIGHT,START,BACK,LS,RS,  _BUTTONS_};


/*! \brief  ControllerInput Class

ControllerInput. Class which is attached to a scene, used to handle all the controller input of a controller. Scene can have multiple controler inputs

*/


class ControllerInput
{
public:

	bool init(int controllerHandle); //!< checks to see if a controller is connected and if so then sets up class to use that controller to get input
	bool checkConnected(int controllerHandle);//!< checks to see if controller is connected

	void reset(); //!<Resets all the controller inputs to false and 0

	void update();//!< Checks to see what is pressed and what the axis values are

	bool _buttons[_BUTTONS_];

	float _leftT,_rightT; //!<Left and right trigger values
	sf::Vector2f _leftStick,_rightStick;//!<left and right stick values
private:

	void getInput(); //!<gets the current controler input values

	int _controllerHandle;
	bool _connected;

	

};
#endif