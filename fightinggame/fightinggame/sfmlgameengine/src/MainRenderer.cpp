#include "stdafx.h"

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <iostream>

#include "MainRenderer.hpp"

#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"

void MainRenderer::init(HWND& hwnd)
{
	// create the window
	_myRenderWindow = new sf::RenderWindow(hwnd);
	_myRenderWindow->setVerticalSyncEnabled(false);
	_myRenderWindow->setFramerateLimit(60);
	_myRenderWindow->setActive();

	glEnable(GL_DEPTH_TEST);


	glewExperimental=GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		std::cout<<"GLEW Didn't Init"<<std::endl;
		system("pause");
	}
	// load resources, initialize the OpenGL states, ...
	s.init();

	glClearDepth(1.0f);
	glClearColor(0.5f,0.5f,0.5f,1.0f);
}

void MainRenderer::handleMenuInput(int _menuInput)
{
	/*switch (_menuInput)
	{
	case ID_CAMERA1:
		s.switchCamera(1);
		break;
	case ID_CAMERA2:
		s.switchCamera(2);
		break;
	case ID_OBJECT_CUBE:
		s.switchPrivDrawStates(1);
		break;
	case ID_OBJECT_TRIANGLE:
		s.switchPrivDrawStates(2);
		break;
	}*/
}

bool MainRenderer::update()
{
	// handle events
	sf::Event event;
	while (_myRenderWindow->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			_myRenderWindow->close();
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Escape)
			{
				_myRenderWindow->close();
				return false;
			}
			EngineInput::keyboardInput.nowKeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			EngineInput::keyboardInput.nowKeyReleased(event.key.code);
			break;
		case sf::Event::Resized:
			glViewport(0, 0, event.size.width, event.size.height);
			break;
		case sf::Event::MouseMoved:
			{
				//mousePos=sf::Mouse::getPosition( *(_myRenderWindow) );
				//deltaX = (float)(oldMousePos.x - mousePos.x);
				//deltaY = (float)(oldMousePos.y - mousePos.y);
				//DELTA IS THE DIFFERENCE BETWEEN THE OLD AND NEW POSITIONS, ESSENTIALLY A vector2f
				
				//NEED TO FIND THE DIFFERENCE FROM THE CENTER OF THE SCREEN TO THE MOUSE POS RELATIVE
				//TO 3D SPACE
			}
		case sf::Event::MouseButtonPressed :
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mousePos=sf::Mouse::getPosition( *(_myRenderWindow) );
					s.addObject(mousePos.x,mousePos.y);
					//left click
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{

					//right click
				}

			}
		}
		oldMousePos = mousePos;
	}

	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw...
	s.update();
	// end the current frame (internally swaps the front and bac	k buffers)
	_myRenderWindow->display();
	return true;
}
