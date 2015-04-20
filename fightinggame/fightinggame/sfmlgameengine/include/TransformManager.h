#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include <vector>

#include "Component.h"
#include "Transfrom.h"

/*! \brief  GameObjectManager Class

GameObjectManager Class. A class which calls the update on all of the game objects within its list. Not all game objects are added to the list as not all objects need to be updated

*/
class TransformManager
{
public:
	TransformManager(); 
	void update();//!< updates all of the transform components
	SPC_Transform createTransform(); //!< creates a transform shared pointer with default values. Adds to vector
	SPC_Transform createTransform(glm::vec3 position); //!< creates a transform shared pointer with defined position. Adds to vector
	SPC_Transform createTransform(glm::vec3 position,  glm::vec3 rotation, glm::vec3 scale);//!< creates a transform shared pointer with defined position, rotation and scale. Adds to vector
private:

	std::vector<SPC_Transform>m_TransformComponents;
};
#endif