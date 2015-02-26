#include "TransformManager.h"

TransformManager::TransformManager()
{
	m_TransformComponents.clear();
}
void TransformManager::update()
{


}
SPC_Transform TransformManager::createTransform()
{
	Transform *n = new Transform();
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}
SPC_Transform TransformManager::createTransform(glm::vec3 position)
{
	Transform *n = new Transform(position, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}
SPC_Transform TransformManager::createTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 velocity)
{
	Transform *n = new Transform(position,rotation,scale,velocity);
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}