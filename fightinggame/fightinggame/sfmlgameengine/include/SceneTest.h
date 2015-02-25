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

	Block *m_decorBlocks[10];
	Block *m_rotatingCube;
	Block *m_floor;
	Block *m_levelBlocks[10];
	Fighter *player1;
	Fighter *player2;
	CameraObj *m_camera;

	float m_UpdateTimer;
};
#endif