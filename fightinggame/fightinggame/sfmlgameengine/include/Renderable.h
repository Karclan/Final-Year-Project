#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Component.h"
#include "Transfrom.h"
#include "Mesh.h"

/*
	Renderable Component.
	Game Objects that wish to be rendered will have one of these components
*/

class Renderable : public Component
{
public:
	Renderable();
	ComponentType::type getType();
	void tearDown();

	void renderUpdate();

	void giveMesh(Mesh *mesh);
	void setShaderHandle(GLuint shaderID);

	void setAmb (glm::vec3 ambientReflection);
	void setDiff(glm::vec3 diffuseReflection);
	void setSpec(glm::vec3 specularReflection);
	void setSpecEx(GLfloat exponent);

	Mesh* getMesh();
	GLuint getShaderHandle();
	glm::vec3 getAmb();
	glm::vec3 getDiff();
	glm::vec3 getSpec();
	float getSpecEx();

private:

	GLuint m_ShaderHandle;
	GLuint m_ModelMatrixID;
	glm::mat4 m_ModelMatrix;

	glm::vec3 m_ColourTint;
	glm::vec3 m_AmbientReflection;
	glm::vec3 m_DiffuseReflection;
	glm::vec3 m_SpecularReflection;
	GLfloat m_SpecularExponent;
	
	Mesh *m_Mesh;
	SPC_Transform m_Transform;
};

typedef std::shared_ptr<Renderable> SPC_Renderable;

#endif