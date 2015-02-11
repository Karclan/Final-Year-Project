#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\matrix_transform_2d.hpp>

#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Shader.h"
#include "Input.h"
#include "ControllerInput.h"
#include "FTInterface.h"

//!< Interface Scene class
class Scene
{
public:

	virtual void init()=0;
	virtual void update()=0;
	virtual void handleInput()=0;
	virtual void handleController()=0;

	void keyDown(int key_code);
	void keyUp(int key_code);	

private:
	Input _inputHandler;
	ControllerInput _controllerInput;

	Shader s;
	CollisionManager m_CollisionManager;
	GameObjectManager m_GameObjectManager;
};
#endif // !SCENE_H
