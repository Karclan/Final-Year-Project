#ifndef SCENETEST_H
#define SCENETEST_H

#include "Scene.h"
#include "Block.h"
#include "CameraObj.h"
class SceneTest : public Scene
{
public:
	void init();
	void update();
	void handleInput();
	void handleController();

private:
	//Transform t;
	//Collidable c;
	//Transform ct;
	//camera ca;

	Block *m_rotatingCube;
	CameraObj *m_camera;
};
#endif