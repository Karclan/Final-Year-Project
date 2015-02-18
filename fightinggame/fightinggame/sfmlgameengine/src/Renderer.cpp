#include "Renderer.h"

void Renderer::init()
{
	//create shaders
	//set lights
	basic = new Shader();
	basic->createShader("shader/basic.vert","shader/basic.frag");
	m_shaders.emplace("basic",basic);

	for(auto it : m_shaders)
	{
		setLights(it.second);
	}
}
void Renderer::setMaterials(Renderable* r)
{
	r->getShader()->setUniform("material.diff",r->getDiff());
	r->getShader()->setUniform("material.spec",r->getSpec());
	r->getShader()->setUniform("material.specEx",r->getSpecEx());

	glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(glm::mat3(r->getMesh()->mModel))));
	r->getShader()->setUniform("NormalMatrix", normMat);
}
void Renderer::setLights(Shader* s)
{
	glm::vec3 lightPos[3];
	lightPos[0] = glm::vec3(-1.f,5.f,0.f);
	lightPos[1] = glm::vec3(1.f,5.f,0.f);
	lightPos[2] = glm::vec3(0.f,5.f,10.f);

	//SpotLight1
	s->setUniform("numOfSpotLights",2);
	s->setUniform("spotLight[0].position", lightPos[0]);
	s->setUniform("spotLight[0].spotDir", glm::vec3(-0.0f,-1.f,-0.f));
	s->setUniform("spotLight[0].spotOutCut",glm::cos(glm::radians(7.f)));
	s->setUniform("spotLight[0].spotInCut",glm::cos(glm::radians(5.5f)));
	s->setUniform("spotLight[0].constant",1.f);
	s->setUniform("spotLight[0].linear",0.014f);
	s->setUniform("spotLight[0].quadratic",0.0007f);
	s->setUniform("spotLight[0].amb",  0.2f, 0.2f, 0.2f);
	s->setUniform("spotLight[0].diff", 1.f, 0.0f, 0.0f);
	s->setUniform("spotLight[0].spec", 1.f, 0.0f, 0.0f);

	//SpotLight2
	s->setUniform("spotLight[1].position", lightPos[1]);
	s->setUniform("spotLight[1].spotDir", glm::vec3(-0.0f,-1.f,-0.f));
	s->setUniform("spotLight[1].spotOutCut",glm::cos(glm::radians(7.f)));
	s->setUniform("spotLight[1].spotInCut",glm::cos(glm::radians(5.5f)));
	s->setUniform("spotLight[1].constant",1.f);
	s->setUniform("spotLight[1].linear",0.014f);
	s->setUniform("spotLight[1].quadratic",0.0007f);
	s->setUniform("spotLight[1].amb",  0.2f, 0.2f, 0.2f);
	s->setUniform("spotLight[1].diff", 0.0f, 1.0f, 0.0f);
	s->setUniform("spotLight[1].spec", 0.f,  1.f,  0.f);

	//PointLight1
	s->setUniform("numOfPointLights",1);
	s->setUniform("pointLight[0].position", lightPos[2]);
	s->setUniform("pointLight[0].constant",1.f);
	s->setUniform("pointLight[0].linear",0.014f);
	s->setUniform("pointLight[0].quadratic",0.0007f);
	s->setUniform("pointLight[0].amb",  0.2f, 0.2f, 0.2f);
	s->setUniform("pointLight[0].diff", 0.5f, 0.5f, 0.5f);
	s->setUniform("pointLight[0].spec", 0.f,  1.f,  0.f);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto it: m_renderables)
	{
		it->renderUpdate();
	
		it->getShader()->useProgram();
		//set camera
		setMaterials(it); //!< currently sets the normal matrix as well

		glBindVertexArray(it->getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size(), GL_UNSIGNED_INT,NULL);
		glBindVertexArray(0);
	}
}
void Renderer::addToRender()
{

}

