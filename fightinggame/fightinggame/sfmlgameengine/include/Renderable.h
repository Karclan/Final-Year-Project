#ifndef RENDERABLE_H
#define RENDERABLE_H

#define GLM_FORCE_RADIANS
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Component.h"
#include "Transfrom.h"
#include "Mesh.h"
#include "Shader.h"

/*
	Renderable Component.
	Game Objects that wish to be rendered will have one of these components
*/

class Renderable : public Component
{
public:
	Renderable();
	Renderable(SPC_Transform t, Mesh *m, Shader* s);

	ComponentType::type getType();
	void tearDown();

	void giveMesh (Mesh *mesh);
	
	void setShader(Shader *shader);
	void setDiff  (glm::vec3 diffuseReflection);
	void setSpec  (glm::vec3 specularReflection);
	void setSpecEx(GLfloat exponent);

	Mesh*	  getMesh();
	Shader*	  getShader();
	glm::vec3 getDiff();
	glm::vec3 getSpec();
	GLfloat	  getSpecEx();
	glm::mat4 m_ModelMatrix;


	SPC_Transform getTransform(){ return m_Transform; }
private:
	void setShaderHandle();

	GLuint	  m_ShaderHandle;
	GLuint	  m_ModelMatrixID;
	

	glm::vec3 m_ColourTint;
	glm::vec3 m_DiffuseReflection;
	glm::vec3 m_SpecularReflection;
	GLfloat   m_SpecularExponent;
	
	Mesh*		  m_Mesh;
	Shader*		  m_Shader;
	SPC_Transform m_Transform;
};

typedef std::shared_ptr<Renderable> SPC_Renderable;

#endif