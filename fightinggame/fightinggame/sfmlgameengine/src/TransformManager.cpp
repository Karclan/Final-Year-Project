#include "TransformManager.h"

TransformManager::TransformManager()
{
	m_TransformComponents.clear();
}
void TransformManager::update()
{


}
SPC_Transform TransformManager::createTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 velocity)
{
	Transform *n = new Transform(position,rotation,scale,velocity);
	m_TransformComponents.push_back(n);
	return SPC_Transform(n);
}