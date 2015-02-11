#ifndef SCENETEST_H
#define SCENETEST_H

#include "Scene.h"
class SceneTest : public Scene
{
public:
	void init();
	void update();
	void handleInput();
	void handleController();

private:
};
#endif