#include "Transfrom.h"

Transform::Transform()
{
	m_Position	= glm::vec3(0, 0, 0);
	m_Rotation	= glm::vec3(0, 0, 0);
	m_Scale		= glm::vec3(1, 1, 1);
	m_Velocity	= glm::vec3(0, 0, 0);
	std::cout << "Transform Component created!\n";
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

}
void Transform::scale(glm::vec3 scale)
{

}