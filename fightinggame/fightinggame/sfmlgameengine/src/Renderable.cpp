#include "Renderable.h"

Renderable::Renderable()
{
	m_Transform = nullptr;
	m_Mesh = nullptr;
	m_Shader = nullptr;

	m_ColourTint			= glm::vec3(1,1,1);
	m_DiffuseReflection		= glm::vec3(1,1,1);
	m_SpecularReflection	= glm::vec3(1,1,1);
	m_SpecularExponent		= 128.f;
	std::cout << "Renderable Created!\n";
}
Renderable::Renderable(SPC_Transform sT,Mesh* m,Shader *s)
{
	m_Transform = sT;
	m_Mesh = m;
	m_Shader = s;
	m_ColourTint			= glm::vec3(1, 1, 1);
	m_DiffuseReflection		= glm::vec3(1, 1, 1);
	m_SpecularReflection	= glm::vec3(1, 1, 1);
	m_SpecularExponent		= 128.f;
	std::cout << "Renderable Created!\n";
}
ComponentType::type Renderable::getType()
{
	return ComponentType::RENDERABLE;
}
void Renderable::tearDown()
{

}
void Renderable::giveMesh(Mesh *mesh)
{
	m_Mesh = mesh;
}
void Renderable::setShader(Shader* shader)
{
	m_Shader = shader;
	setShaderHandle();
}
void Renderable::setShaderHandle()
{
	m_ShaderHandle = m_Shader->getHandle();
}
void Renderable::setDiff(glm::vec3 diffuseReflection)
{
	m_DiffuseReflection = diffuseReflection;
}
void Renderable::setSpec(glm::vec3 specularReflection)
{
	m_SpecularReflection = specularReflection;
}
void Renderable::setSpecEx(GLfloat exponent)
{
	m_SpecularExponent = exponent;
}
Mesh* Renderable::getMesh()
{
	return m_Mesh;
}
Shader* Renderable::getShader()
{
	return m_Shader;
}
glm::vec3 Renderable::getDiff()
{
	return m_DiffuseReflection;
}
glm::vec3 Renderable::getSpec()
{
	return m_SpecularReflection;
}
GLfloat Renderable::getSpecEx()
{
	return m_SpecularExponent;
}


