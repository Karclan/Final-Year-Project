#include "Transfrom.h"

Transform::Transform()
{
	m_Position	= glm::vec3(0, 0, 0);
	m_Rotation	= glm::vec3(0, 0, 0);
	m_Scale		= glm::vec3(1, 1, 1);
	m_Velocity	= glm::vec3(0, 0, 0);
	std::cout << "Transform Component created!\n";
}
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 velocity)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale    = scale;
	m_Velocity = velocity;
	std::cout << "Transfrom Component created!\n";
}
ComponentType::type Transform::getType()
{
	return ComponentType::TRANSFORM;
}
void Transform::tearDown()
{

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
}
void Transform::scale(glm::vec3 scale)
{
	m_Scale = scale;
}