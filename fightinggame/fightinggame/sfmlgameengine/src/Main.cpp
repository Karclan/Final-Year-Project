
#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <iostream>
#include "FTInterface.h"
#include "Timer.h"
#include "ControllerInput.h"
#include "X360Controller.hpp"
#include "Scene.h"


#include "SceneTest.h"

int initGlew()
{
	glewExperimental=GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		std::cout<<"GLEW Didn't Init"<<std::endl;
		system("pause");
		return 1;
	}
	else return 0;
}
void initFTLib()
{
	FTInterface::init();
}
int main()
{
	sf::Window window(sf::VideoMode(GS::SCREENWIDTH, GS::SCREENHEIGHT), "FightingGame", sf::Style::Close, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);
	window.setActive();

	initGlew();
	initFTLib();
	Scene *s = new SceneTest();
	s->init();

	//--MAIN LOOP--//
	while (window.isOpen())
	{
		Timer::update();
		s->update();

		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				{
					window.close();
					break;
				}
			case sf::Event::KeyPressed:
				{
					if(event.key.code == sf::Keyboard::Escape)
					{
						window.close();
						break;
					}
					s->keyDown(event.key.code);
					break;
				}
			case sf::Event::KeyReleased:
				{
					s->keyUp(event.key.code);
					break;
				}
			case sf::Event::Resized:
				{
					glViewport(0, 0, event.size.width, event.size.height);
					GS::SCREENWIDTH = event.size.width;
					GS::SCREENHEIGHT = event.size.height;
					break;
				}
			}
		}
		window.display();
	}
	return 0;
}

