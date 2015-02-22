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

#include "Component.h"
#include "Transfrom.h"
#include "Mesh.h"
#include "Shader.h"

class Camera : public Component
{
public:
	Camera();
	Camera(SPC_Transform t);
	~Camera();

	ComponentType::type getType();

	void tearDown();

	void init(SPC_Transform t);
	void update();

	void setPostion(glm::vec3 newPos);
	void setTarget(glm::vec3 newTarg);

	void pan(glm::vec3 pan);
	void zoom(float zoomAmount);
	//void rotate(float angleX, float angleY, float angleZ);

	glm::vec3 getPosition(){ return m_Transform->getPosition();}
	glm::vec3 getRotation(){return m_Transform->getRotation();}
	glm::vec3 getTarget(){return m_Target;}

	glm::mat4 getProjectionMatrix(){ return m_mProj; }
	glm::mat4 getViewMatrix(){ return m_mView; }

private:

	glm::mat4 m_mProj;
	glm::mat4 m_mView;

	glm::vec3 m_Target;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_Forward;

	SPC_Transform m_Transform;
};
typedef std::shared_ptr<Camera> SPC_Camera;
#endif