#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <glm\gtx\matrix_transform_2d.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "ShaderHandler.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Input.h"
#include "ControllerInput.h"
#include "Block.h"
#include "Fighter.hpp"
#include "HitBox.h"
#include "FTInterface.h"

class Scene
{
public:

	void init();
	void update(float dt);
	void handleInput(float dt);
	void handleController(float dt);

	void keyDown(int key_code);
	void keyUp(int key_code);

	void test();
	void setUpCameras();
	void setUpGameObjects();
	void setCamera(Camera *);
	void checkCollisions();
	void setUpLighting();
	void setMaterials(GameObject *);
	void gravity(float dt);

	int one;
private:
	std::vector<GameObject *> lstOfGameObj;
	std::vector<Camera *> lstOfCam;
	std::vector<Mesh *> lstOfMeshes;

	Shader s, fs;
	ShaderHandler *shaderHandler;
	CollisionManager m_collisionManager;
	Camera C;
	Camera *ActiveCamera;
	Block *flat_plane,  *rotating_3Dcube, *distanceBlock;
	Fighter *flat_cube, *test_fighter;
	Mesh *cube,*line;
	Input _inputHandler;
	ControllerInput _controllerInput;

	bool ActiveController;

	glm::vec3 lightPos[3];
	glm::vec3 uiPos;
	float grav;
};
#endif // !SCENE_H
