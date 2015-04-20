#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "GS.h"
#include "Component.h"
#include "Transfrom.h"
#include "Mesh.h"
#include "Shader.h"


/*! \brief Camera Component Class

	Camera component

*/
class Camera : public Component
{
public:
	Camera(); 
	Camera(SPC_Transform t); //!< Constructor taking a Transform Shared Pointer
	~Camera();

	ComponentType::type getType(); 

	void tearDown();

	void init(SPC_Transform t); //!< Sets all the camera values to defaults and sets up view and projection matricies
	void update(); //!< Recalculates Camera forward, right, up, and view matrix

	void setPostion	(glm::vec3 newPos); //!< Sets position of camera
	void setTarget	(glm::vec3 newTarg);//!< Sets camera's target

	void pan	(glm::vec3 pan);	//!< Camera Pan function
	void zoom	(float zoomAmount); //!< Camera Zoom function along Z axis
	void orbit	(glm::vec3 rot);	//!< Camera orbits around an object
	void rotate(glm::vec3 rot);		//!< Camera's target rotates around the camera

	glm::vec3 getPosition()	{ return m_Transform->getPosition();}
	glm::vec3 getRotation()	{return m_Transform->getRotation();}
	glm::vec3 getTarget()	{return m_Target;}

	glm::mat4 getProjectionMatrix()	{ return m_mProj; }
	glm::mat4 getViewMatrix()		{ return m_mView; }

private:
	glm::mat4 m_mProj; //!< Projection matrix which translates from world to screen space
	glm::mat4 m_mView; //!< Made up of the up, right and forward vector to give it position in space

	glm::vec3 m_Target; //!< Camera's target, what the camera is looking at
	glm::vec3 m_Up; //!< Camera's up vector
	glm::vec3 m_Right; //!< Camera's right vector
	glm::vec3 m_Forward;//!< Camera's Forward Vector

	SPC_Transform m_Transform;
};
typedef std::shared_ptr<Camera> SPC_Camera;
#endif