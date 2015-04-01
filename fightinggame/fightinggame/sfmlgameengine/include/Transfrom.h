#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>
#include "Component.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

/*
	Transform Component
	Every Game Object that wishes to have a position in the game
	Will want to have one of these components
*/

class Transform : public Component
{
public:
	Transform();
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 transform);

	ComponentType::type getType();
	void tearDown();

	void update();
	void setPosition(glm::vec3 newPosition) {m_Position=newPosition;}
	void translate	(glm::vec3 newTransform){m_Position+=newTransform;}
	void rotate		(glm::vec3 rot);
	void scale		(glm::vec3 newScale);
	void setVelocity(glm::vec3 velocity){m_Velocity=velocity;}
	void modVelocity(glm::vec3 velocity){m_Velocity+=velocity;}

	glm::vec3 getPosition(){ return m_Position;    }
	glm::vec3 getRotation(){ return m_Rotation;    }
	glm::vec3 getScale	 (){ return m_Scale;       }
	glm::vec3 getVelocity(){ return m_Velocity;	   }
	glm::mat4 getMatrix	 (){ return m_ModelMatrix; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::vec3 m_Velocity;
	glm::mat4 m_ModelMatrix;
};

typedef std::shared_ptr<Transform> SPC_Transform;

#endif