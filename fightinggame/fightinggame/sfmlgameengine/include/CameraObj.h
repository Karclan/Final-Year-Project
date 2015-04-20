#ifndef CAMERAOBJ_H
#define CAMERAOBJ_H

#include <GameObject.h>

#include "Transfrom.h"
#include "Camera.h"

/*! \brief  CameraObj

Camera Object class. Camera object used to give a view within 3d space within scene. Has Camera and transform component

*/
class CameraObj : public GameObject
{
public:
	CameraObj();
	CameraObj(SPC_Camera c, SPC_Transform t);
	void update(float dt); //!< empty function
	void renderUpdate(); //!< empty function

private:

	SPC_Camera m_Camera;
	SPC_Transform m_Transform;
};
#endif

