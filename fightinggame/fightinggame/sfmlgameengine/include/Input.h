#ifndef INPUT_H
#define INPUT_H

#include "Timer.h"

/*! \brief  Input Class

Input. Class which is attached to a scene, used to handle all the keyboard inputs 
*/
class Input
{
public:
	void init(); //!< sets all input values to false to prevent issues with bools having strange data from when they were created
	void update(); //<! called at the end of each loop to increment every keyheld time
	bool isKeyPressed(int key_code); //!< returns true if a key is pressed/held

	void keyPressed(int key_code); //!< function called when key is pressed
	void keyReleased(int key_code);//!< function called when key is released
private:
	bool m_KEYS[256]; //!< array of bools representing keys on keyboard
	double  m_KEYHELDTIME[256];//!< array of doubles representing the time a key is held

};
#endif 