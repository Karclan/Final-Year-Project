#ifndef LIGHT_H
#define LIGHT_H

#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Component.h"

class Light : public Component
{
public:
	ComponentType::type getType();
	void tearDown();

	void setAmb (glm::vec3 Ka){m_ambient = Ka;}
	void setDiff(glm::vec3 Kd){m_diffuse = Kd;}
	void setSpec(glm::vec3 Ks){m_specular = Ks;}
	void setSpecEx(float specEx){m_specularExponent = specEx;}

	glm::vec3 getAmb(){return m_ambient;}
	glm::vec3 getDiff(){return m_diffuse;}
	glm::vec3 getSpec(){return m_specular;}
	float getSpecEx(){return m_specularExponent;}

private:
	glm::vec3 m_ambient,m_diffuse,m_specular;
	float m_specularExponent;
};
#endif 