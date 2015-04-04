#include "Transfrom.h"

Transform::Transform()
{
	m_Position	  = glm::vec3(0, 0, 0);
	m_Rotation	  = glm::vec3(0, 0, 0);
	m_Scale		  = glm::vec3(1, 1, 1);
	m_Velocity	  = glm::vec3(0, 0, 0);
	//m_ModelMatrix = glm::mat4(1.f);
	//m_ModelMatrix = glm::scale	  (m_ModelMatrix, m_Scale);
	//m_ModelMatrix = glm::rotate	  (m_ModelMatrix, m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
	//m_ModelMatrix = glm::rotate	  (m_ModelMatrix, m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
	//m_ModelMatrix = glm::rotate	  (m_ModelMatrix, m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
	//m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	
	std::cout << "Transform Component created with defaults!\n";
}
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 velocity)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale    = scale;
	m_Velocity = velocity;
	//m_ModelMatrix = glm::mat4(1.f);
	std::cout << "Transfrom Component created with user data!\n";
}
ComponentType::type Transform::getType()
{
	return ComponentType::TRANSFORM;
}
void Transform::tearDown()
{

}
void Transform::update()
{
	glm::mat4 transMat(1.f);
	transMat = glm::translate(transMat, m_Position);

	glm::mat4 rotMat(1.f);
	glm::mat4 rX = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 rY = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 rZ = glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0.f, 0.f, 1.f));
	rotMat = rX*rY*rZ;
	glm::mat4 scaleMat(1.f);
	scaleMat = glm::scale(scaleMat, m_Scale);
	m_ModelMatrix = transMat * rotMat  * scaleMat;
}
void Transform::rotate(glm::vec3 rot)
{
	if (m_Rotation.x >= 360.f)
	{
		m_Rotation.x = 0.f;
	}
	if (m_Rotation.y >= 360.f)
	{
		m_Rotation.y = 0.f;
	}
	if (m_Rotation.y >= 360.f)
	{
		m_Rotation.y = 0.f;
	}
	m_Rotation += glm::vec3(rot.x,rot.y,rot.z);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
}
void Transform::scale(glm::vec3 scale)
{
	m_Scale = scale;
}