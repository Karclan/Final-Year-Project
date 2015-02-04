#ifndef MAINRENDERER_HPP
#define MAINRENDERER_HPP

#include "Scene.h"
class MainRenderer
{
private:
	Scene s;
	sf::RenderWindow* _myRenderWindow;
public:
	void init(HWND& hwnd);
	void handleMenuInput(int _menuInput);
	bool update();
	sf::Vector2i oldMousePos, mousePos;
	float deltaX, deltaY;
};

#endif