#ifndef CAMERAOBJ_H
#define CAMERAOBJ_H

#include <GameObject.h>

#include "Transfrom.h"
#include "Camera.h"

class CameraObj : public GameObject
{
public:
	CameraObj();
	CameraObj(SPC_Camera c, SPC_Transform t);
	void update(float dt);
	void renderUpdate();

private:

	SPC_Camera m_Camera;
	SPC_Transform m_Transform;
};
#endif

