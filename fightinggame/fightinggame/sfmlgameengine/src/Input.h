#ifndef INPUT_H
#define INPUT_H

class Input
{
private:
	
public:
	bool _KEYS[256];
	int _KEYHELDTIME[256];
	void init();
	void keyPressed(int key_code);
	void keyReleased(int key_code);
	void keyHeld();
};
#endif 