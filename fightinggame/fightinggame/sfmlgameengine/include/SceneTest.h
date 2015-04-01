#ifndef SCENETEST_H
#define SCENETEST_H

#include "Scene.h"
#include "Block.h"
#include "CameraObj.h"
#include "Firework.h"

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
	Block *m_platform[3];
	Block *m_floorPlatform;
	Block *m_levelBlocks[10];
	Fighter *m_player1;
	Fighter *m_player2;
	CameraObj *m_camera;
	Firework* m_firework;

	float m_UpdateTimer;
};
#endif