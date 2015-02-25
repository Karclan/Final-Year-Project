#include "Renderer.h"

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
//===PUBLIC  FUNCTIONS===//
//_______________________//
void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	//create shaders
	//set lights
	basic = new Shader();
	basic->createShader("shader/basic.vert","shader/basic.frag");
	m_shaders.emplace("basic",basic);
	
	
	for(auto it : m_shaders)
	{
		setLights(it.second);
	}
	std::cout << "C| Initalized Renderer!\n";
}
void Renderer::loadMesh(const char* filename)
{
	Mesh* newMesh = new Mesh(filename, basic->getHandle());
	m_meshes.emplace(filename, newMesh);
}
void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setLights(basic);
	for (auto it : m_cameras)
	{
		it->update();
	}
	for(auto it: m_renderables)
	{
		it->getShader()->useProgram();
		it->renderUpdate();
	
		updateMatricies(it, m_cameras[m_ActiveCamera]);

		setMaterials(it); //!< currently sets the normal matrix as well

		glBindVertexArray(it->getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
}

void Renderer::setActiveCamera(int i)
{
	size_t j = i;
	if (j > m_cameras.size())
	{
		return;
	}
	else
	{
		m_ActiveCamera = i;
		for (auto it : m_shaders)
		{
			it.second->setUniform("mView",		 m_cameras[i]->getViewMatrix());
			it.second->setUniform("mProjection", m_cameras[i]->getProjectionMatrix());
			it.second->setUniform("viewPos",	 m_cameras[i]->getPosition());
		}
	}
}
int Renderer::calculateFrameRate()
{
	static unsigned int frameCounter = 0;
	static unsigned int frameTime = 0;
	static unsigned int fps = 0;
	frameCounter++;
	frameTime += Timer::getTime().asMilliseconds();
	if (frameTime >= 1000)
	{
		fps = frameCounter;
		frameCounter = 0;
		frameTime -= 1000;
	}
	return fps;
}
SPC_Camera Renderer::createCamera(SPC_Transform sT)
{
	Camera* c = new Camera(sT);
	m_cameras.push_back(SPC_Camera(c));
	return SPC_Camera(c);
}
SPC_Renderable Renderer::createRenderable(SPC_Transform sT)
{
	Renderable* r = new Renderable(sT, m_meshes.find("hexagonprism.obj")->second, basic);
	m_renderables.push_back(SPC_Renderable(r));
	return SPC_Renderable(r);
}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
//===PRIVATE FUNCTIONS===//
//_______________________//

void Renderer::updateMatricies(SPC_Renderable r, SPC_Camera c)
{
	glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(glm::mat3(r->getMesh()->mModel))));
	r->getShader()->setUniform("NormalMatrix",  normMat);
	r->getShader()->setUniform("mModel",	    r->getMesh()->mModel);
	r->getShader()->setUniform("mView",			c->getViewMatrix());
	r->getShader()->setUniform("mProjection",	c->getProjectionMatrix());
	r->getShader()->setUniform("viewPos",		c->getPosition());
}
void Renderer::setMaterials(SPC_Renderable r)
{
	r->getShader()->setUniform("material.diff",   r->getDiff());
	r->getShader()->setUniform("material.spec",   r->getSpec());
	r->getShader()->setUniform("material.specEx", r->getSpecEx());
}
void Renderer::setLights(Shader* s)
{
	glm::vec3 lightPos[3];
	lightPos[0] = glm::vec3(-1.f,  5.0f,  0.0f);
	lightPos[1] = glm::vec3( 1.0f, 5.0f,  0.0f);
	lightPos[2] = glm::vec3( 0.0f, 5.0f, 10.0f);

	//SpotLight1
	s->setUniform("numOfSpotLights", 2);
	s->setUniform("spotLight[0].position"  , lightPos[0]);
	s->setUniform("spotLight[0].spotDir"   , glm::vec3(-0.0f, -1.f, -0.f));
	s->setUniform("spotLight[0].spotOutCut", glm::cos(glm::radians(7.f)));
	s->setUniform("spotLight[0].spotInCut" , glm::cos(glm::radians(5.5f)));
	s->setUniform("spotLight[0].constant"  , 1.f);
	s->setUniform("spotLight[0].linear"    , 0.014f);
	s->setUniform("spotLight[0].quadratic" , 0.0007f);
	s->setUniform("spotLight[0].amb"       , 0.2f, 0.2f, 0.2f);
	s->setUniform("spotLight[0].diff"      , 1.0f, 0.0f, 0.0f);
	s->setUniform("spotLight[0].spec"      , 1.0f, 0.0f, 0.0f);

	//SpotLight2
	s->setUniform("spotLight[1].position"  , lightPos[1]);
	s->setUniform("spotLight[1].spotDir"   , glm::vec3(-0.0f, -1.f, -0.f));
	s->setUniform("spotLight[1].spotOutCut", glm::cos(glm::radians(7.f)));
	s->setUniform("spotLight[1].spotInCut" , glm::cos(glm::radians(5.5f)));
	s->setUniform("spotLight[1].constant"  , 1.f);
	s->setUniform("spotLight[1].linear"	   , 0.014f);
	s->setUniform("spotLight[1].quadratic" , 0.0007f);
	s->setUniform("spotLight[1].amb"       , 0.2f, 0.2f, 0.2f);
	s->setUniform("spotLight[1].diff"      , 0.0f, 1.0f, 0.0f);
	s->setUniform("spotLight[1].spec"      , 0.0f, 1.0f, 0.0f);

	//PointLight1
	s->setUniform("numOfPointLights", 1);
	s->setUniform("pointLight[0].position" , lightPos[2]);
	s->setUniform("pointLight[0].constant" , 1.f);
	s->setUniform("pointLight[0].linear"   , 0.014f);
	s->setUniform("pointLight[0].quadratic", 0.0007f);
	s->setUniform("pointLight[0].amb"      , 0.2f, 0.2f, 0.2f);
	s->setUniform("pointLight[0].diff"     , 0.5f, 0.5f, 0.5f);
	s->setUniform("pointLight[0].spec"     , 0.0f, 1.0f, 0.0f);
}
