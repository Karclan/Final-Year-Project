#include "Renderable.h"

Renderable::Renderable()
{
	m_Transform = nullptr;
	m_Mesh = nullptr;
	m_Shader = nullptr;
	std::cout << "Renderable Created!\n";
}
Renderable::Renderable(SPC_Transform sT,Mesh* m,Shader *s)
{
	m_Transform = sT;
	m_Mesh = m;
	m_Shader = s;
	std::cout << "Renderable Created!\n";
}
ComponentType::type Renderable::getType()
{
	return ComponentType::RENDERABLE;
}
void Renderable::tearDown()
{

}
void Renderable::renderUpdate()
{
	m_Mesh->mModel = glm::mat4(1.f);
	m_Mesh->mModel = glm::translate(m_Transform->getPosition()); // glm::translate(getTransform());

	m_Mesh->mModel = glm::rotate(m_Mesh->mModel, glm::radians(m_Transform->getRotation().x), glm::vec3(1.f,0.f,0.f));
	m_Mesh->mModel = glm::rotate(m_Mesh->mModel, glm::radians(m_Transform->getRotation().y), glm::vec3(0.f,1.f,0.f));
	m_Mesh->mModel = glm::rotate(m_Mesh->mModel, glm::radians(m_Transform->getRotation().z), glm::vec3(0.f,0.f,1.f));

	m_Mesh->mModel = glm::scale(m_Mesh->mModel,m_Transform->getScale());
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


