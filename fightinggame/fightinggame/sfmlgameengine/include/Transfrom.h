#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>
#include "Component.h"

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

/*! \brief  Transform Component Class

Transform Component
Every Game Object that wishes to have a position in the game will want to have one of these components

*/

class Transform : public Component
{
public:
	Transform();//!<Default constructor which sets 0s position and rotation and sets scale to 1
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale); //!<Constructor which sets position, rotation and scale of transform

	ComponentType::type getType();
	void tearDown();

	void update(); //!< Updates the transform matrix
	void setPosition(glm::vec3 newPosition) {m_Position=newPosition;}
	void translate	(glm::vec3 newTransform){m_Position+=newTransform;}
	void rotate		(glm::vec3 rot); //!<Rotates object using euler rotation
	void scale		(glm::vec3 newScale);//!<Scales object

	glm::vec3 getPosition(){ return m_Position;    }
	glm::vec3 getRotation(){ return m_Rotation;    }
	glm::vec3 getScale	 (){ return m_Scale;       }
	glm::mat4 getMatrix	 (){ return m_ModelMatrix; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::mat4 m_ModelMatrix; //!<Model matrix used to give rendered elements model space transforms
};

typedef std::shared_ptr<Transform> SPC_Transform;

#endif