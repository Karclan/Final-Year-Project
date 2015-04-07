#include "TransformManager.h"

TransformManager::TransformManager()
{
	m_TransformComponents.clear();
}
void TransformManager::update()
{
	for (auto it : m_TransformComponents)
	{
		it->update();
	}
}
SPC_Transform TransformManager::createTransform()
{
	Transform *n = new Transform();
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}
SPC_Transform TransformManager::createTransform(glm::vec3 position)
{
	Transform *n = new Transform(position, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}
SPC_Transform TransformManager::createTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	Transform *n = new Transform(position,rotation,scale);
	m_TransformComponents.push_back(SPC_Transform(n));
	return SPC_Transform(n);
}