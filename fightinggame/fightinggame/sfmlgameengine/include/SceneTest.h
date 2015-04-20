#ifndef SCENETEST_H
#define SCENETEST_H

#include "Scene.h"
#include "Block.h"
#include "CameraObj.h"
#include "Firework.h"

/*! \brief  SceneTest

SceneTest  class. Game implementaiton, has all the stuff within the scene.

*/
class SceneTest : public Scene
{
public:
	void init(); //!< function which creates all the scene objets and sets their values
	void update(); //!< function which updates the game objects and managers
	void handleInput(); //!< function which handles keyboard input
	void handleController(); //!< function which handles controller input
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