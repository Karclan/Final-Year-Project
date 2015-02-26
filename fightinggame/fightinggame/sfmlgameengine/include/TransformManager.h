#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include <vector>

#include "Component.h"
#include "Transfrom.h"

class TransformManager
{
public:
	TransformManager();
	void update();//<!currently unused
	SPC_Transform createTransform();
	SPC_Transform createTransform(glm::vec3 position);
	SPC_Transform createTransform(glm::vec3 position,  glm::vec3 rotation, glm::vec3 scale, glm::vec3 velocity);
private:

	std::vector<SPC_Transform>m_TransformComponents;
};
#endif