#include "Renderer.h"

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
//===PUBLIC  FUNCTIONS===//
//_______________________//
Renderer::Renderer()
{

}
Renderer::~Renderer()
{
	for (auto it : m_shaders)
	{
		delete it.second;
	}
	m_shaders.clear();
}

void Renderer::init()
{
	glViewport(0, 0, GS::SCREENWIDTH, GS::SCREENHEIGHT);
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

	particle = new Shader();
	particle->createShader("shader/particle.vert", "shader/particle.frag");
	m_shaders.emplace("particle", particle);

	std::cout << "C| Initalized Renderer!\n";
}
void Renderer::loadMesh(std::string filename)
{
	Mesh* newMesh = new Mesh(filename, basic->getHandle());
	m_meshes.emplace(filename, newMesh);
}
void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (auto it : m_cameras)
	{
		it->update();
	}

	for(auto it: m_renderables)
	{
		it->getShader()->useProgram();
		setLights(it->getShader());
	
		updateMatricies(it, m_cameras[m_ActiveCamera]);

		setMaterials(it);

		glBindVertexArray(it->getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}

	particle->useProgram();
	particle->setUniform("u_PointSize", 10.f);
	particle->setUniform("u_ViewMatrix",	 m_cameras[0]->getViewMatrix());
	particle->setUniform("u_ProjectionView", m_cameras[0]->getProjectionMatrix());
	
	for (auto it : m_particles)
	{
		particle->setUniform("u_ModelMatrix", it->getTransform()->getMatrix());
		it->render();
	}
}
void Renderer::updateParticles(float t)
{
	for (auto it : m_particles)
	{
		it->animate(t);
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
	static unsigned int frameTime	 = 0;
	static unsigned int fps			 = 0;
	frameCounter++;
	frameTime += Timer::getTime().asMilliseconds();
	if (frameTime >= 1000)
	{
		fps = frameCounter;
		frameCounter = 0;
		frameTime	-= 1000;
	}
	return fps;
}
SPC_Camera Renderer::createCamera(SPC_Transform sT)
{
	SPC_Camera c(new Camera(sT));
	m_cameras.push_back(c);
	return c;
}
SPC_Renderable Renderer::createRenderable(SPC_Transform sT,std::string filename)
{
	std::map<std::string, Mesh*>::iterator it;
	it = m_meshes.find(filename);
	if (it == m_meshes.end())
	{
		loadMesh(filename);
	}
	SPC_Renderable r (new Renderable(sT, m_meshes.find(filename)->second, basic));
	m_renderables.push_back(r);
	return r;
}
SPC_Particle Renderer::createParticle(SPC_Transform t, size_t poolSize)
{
	SPC_Particle p(new Particle(t, poolSize, particle));
	m_particles.push_back(p);
	return p;
}
//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
//===PRIVATE FUNCTIONS===//
//_______________________//

void Renderer::updateMatricies(SPC_Renderable r, SPC_Camera c)
{
	glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(glm::mat3(r->getTransform()->getMatrix()))));
	r->getShader()->setUniform("NormalMatrix",  normMat);
	r->getShader()->setUniform("mModel",		r->getTransform()->getMatrix());
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
