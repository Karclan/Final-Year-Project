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
	~Camera();

	ComponentType::type getType();

	void tearDown();

	void init();
	void update();

	void setPostion(glm::vec3 newPos);
	void setTarget(glm::vec3 newTarg);

	void pan(glm::vec3 pan);
	void zoom(float zoomAmount);
	void rotate(float angleX, float angleY, float angleZ);

	glm::vec3 getRotation(){return glm::vec3(m_Yaw,m_Pitch,m_Roll);}
	glm::vec3 getTarget(){return m_Target;}

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();

private:

	GLuint  m_viewMatrixID;
	GLuint	m_projectionMatrixID;

	glm::mat4 m_mProj;
	glm::mat4 m_mView;

	float m_Yaw;
	float m_Pitch;
	float m_Roll;

	glm::vec3 m_Target;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_Forward;

	SPC_Transform m_Transform;
};
typedef std::shared_ptr<Camera> SPC_Camera;
#endif