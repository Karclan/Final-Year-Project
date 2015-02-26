#ifndef INPUT_H
#define INPUT_H

#include "Timer.h"

class Input
{
public:
	void init();
	void update(); //<! called at the end of each loop to increment every keyheld time
	bool isKeyPressed(int key_code);

	void keyPressed(int key_code);
	void keyReleased(int key_code);
private:
	bool m_KEYS[256];
	double  m_KEYHELDTIME[256];

};
#endif 