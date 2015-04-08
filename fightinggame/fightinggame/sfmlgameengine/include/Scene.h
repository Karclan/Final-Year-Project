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
#include "TransformManager.h"
#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"
#include "Input.h"
#include "ControllerInput.h"
#include "FTInterface.h"
#include "PhysicsManager.h"

//!< Interface Scene class

class Scene
{
public:
	Scene();
	~Scene();

	virtual void init()				=0;
	virtual void update()			=0;
	virtual void handleInput()		=0;
	virtual void handleController()	=0;

	void keyDown (int key_code);
	void keyUp	 (int key_code);	

protected:
	float m_FixedFrameTimer;
	float m_FrameDelay;

	Input				m_InputHandler;
	ControllerInput		m_ControllerInput;
	CollisionManager	m_CollisionManager;
	GameObjectManager	m_GameObjectManager;
	Renderer			m_Renderer;
	TransformManager	m_TransformManager;
	PhysicsManager		m_PhysicsManager;
};
#endif // !SCENE_H
