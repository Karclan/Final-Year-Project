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
	for (auto it : m_meshes)
	{
		delete it.second;
	}
	m_meshes.clear();
	m_particles.clear();
}

void Renderer::init()
{
	glViewport(0, 0, GS::SCREENWIDTH, GS::SCREENHEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glClearColor(0.8f, 1.f, 1.f, 1.0f);

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
	for (auto it : m_cameras)
	{
		it->update();
	}

	//Pass 1


	m_DirectionalLightPosition = glm::vec3(10.f);

	m_ShadowViewMat = glm::lookAt(m_DirectionalLightPosition, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

	//glCullFace(GL_FRONT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFrameBufferObject);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_ShadowMapWidth, m_ShadowMapHeight);
	for (auto it : m_renderables)
	{
		//updateMatricies(it, m_cameras[m_ActiveCamera]);
		it->getShader()->useProgram();
		it->getShader()->setSubroutine("shadowPass", ShaderTypes::FRAGMENT);

		m_LightPointViewMat = m_ShadowBias * m_ShadowProjectionMat * m_ShadowViewMat;
		
		it->getShader()->setUniform	  ("u_ShadowMatrix", m_LightPointViewMat * it->getTransform()->getMatrix());
		it->getShader()->setUniform   ("u_ShadowMap", 0);
		it->getShader()->setUniform	  ("mView",		  m_ShadowViewMat);
		it->getShader()->setUniform   ("mProjection", m_ShadowProjectionMat);
		it->getShader()->setUniform	  ("mModel",	  it->getTransform()->getMatrix());

		glBindVertexArray(it->getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
	glFlush();
	glFinish();

	//Pass 2
	//glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, GS::SCREENWIDTH, GS::SCREENHEIGHT);
	for(auto it: m_renderables)
	{
		it->getShader()->useProgram();
		it->getShader()->setUniform("u_ShadowMatrix", m_LightPointViewMat * it->getTransform()->getMatrix());
		updateMatricies(it, m_cameras[m_ActiveCamera]);

		setMaterials(it);
		if (it->textured(TextureType::SPECULAR) && it->textured(TextureType::DIFFUSE))
		{
			it->getShader()->setSubroutine("diffuseSpecular", ShaderTypes::FRAGMENT);
			it->bindTexture(TextureType::DIFFUSE);
			it->bindTexture(TextureType::SPECULAR);
		} else	if (it->textured(TextureType::DIFFUSE))
		{
			it->getShader()->setSubroutine("diffuse", ShaderTypes::FRAGMENT);
			it->bindTexture(TextureType::DIFFUSE);
		}
		else
		{
			it->getShader()->setSubroutine("noTexture", ShaderTypes::FRAGMENT);
		}
		glBindVertexArray(it->getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);

		if (it->textured())
		{
			it->unbindTextures();
		}
	}

	particle->useProgram();
	particle->setUniform("u_PointSize", 2.f);
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
SPC_Renderable Renderer::createRenderable(SPC_Transform sT, std::string meshFilename)
{
	std::map<std::string, Mesh*>::iterator it;
	it = m_meshes.find(meshFilename);
	if (it == m_meshes.end())
	{
		loadMesh(meshFilename);
	}
	SPC_Renderable r(new Renderable(sT, m_meshes.find(meshFilename)->second, basic));
	m_renderables.push_back(r);
	return r;
}
SPC_Renderable Renderer::createRenderable(SPC_Transform t, std::string meshFilename, std::string diffuse)
{
	SPC_Renderable r = createRenderable(t, meshFilename);
	r->assignTexture(diffuse, TextureType::DIFFUSE);
	m_renderables.push_back(r);
	return r;
}
SPC_Renderable Renderer::createRenderable(SPC_Transform t, std::string meshFilename, std::string diffuse, std::string specular)
{
	SPC_Renderable r = createRenderable(t, meshFilename);
	r->assignTexture(diffuse, TextureType::DIFFUSE);
	r->assignTexture(specular, TextureType::SPECULAR);
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
	s->useProgram();
	m_lightPos[0] = glm::vec3(-6.f, 5.0f, 0.0f);
	m_lightPos[1] = glm::vec3(6.0f, 5.0f, 0.0f);
	//m_lightPos[2] = glm::vec3(0.0f, 0.0f, -15.0f);


	m_DirectionalLightPosition = glm::vec3(0.f, 5.f, 10.f);
	//SpotLight1
	s->setUniform("numOfSpotLights", 2);
	s->setUniform("spotLight[0].position",   m_lightPos[0]);
	s->setUniform("spotLight[0].spotDir"   , glm::vec3(-0.0f, -1.f, -0.f));
	s->setUniform("spotLight[0].spotOutCut", glm::cos(glm::radians(28.f)));
	s->setUniform("spotLight[0].spotInCut" , glm::cos(glm::radians(15.5f)));
	s->setUniform("spotLight[0].constant"  , 1.f);
	s->setUniform("spotLight[0].linear"    , 0.014f);
	s->setUniform("spotLight[0].quadratic" , 0.0007f);
	s->setUniform("spotLight[0].diff"      , 1.0f, 0.0f, 0.0f);
	s->setUniform("spotLight[0].spec"      , 1.0f, 0.0f, 0.0f);

	//SpotLight2
	s->setUniform("spotLight[1].position",   m_lightPos[1]);
	s->setUniform("spotLight[1].spotDir"   , glm::vec3(-0.0f, -1.f, -0.f));
	s->setUniform("spotLight[1].spotOutCut", glm::cos(glm::radians(28.f)));
	s->setUniform("spotLight[1].spotInCut" , glm::cos(glm::radians(15.5f)));
	s->setUniform("spotLight[1].constant"  , 1.f);
	s->setUniform("spotLight[1].linear"	   , 0.14f);
	s->setUniform("spotLight[1].quadratic" , 0.007f);
	s->setUniform("spotLight[1].diff"      , 1.0f, 0.0f, 1.0f);
	s->setUniform("spotLight[1].spec"      , 1.0f, 0.0f, 1.0f);

	////PointLight1
	//s->setUniform("numOfPointLights", 1);
	//s->setUniform("pointLight[0].position",   m_lightPos[2]);
	//s->setUniform("pointLight[0].constant" , 1.f);
	//s->setUniform("pointLight[0].linear"   , 0.14f);
	//s->setUniform("pointLight[0].quadratic", 0.007f);
	//s->setUniform("pointLight[0].diff"     , 0.5f, 0.5f, 0.5f);
	//s->setUniform("pointLight[0].spec"     , 0.0f, 0.0f, 1.0f);

	
	s->setUniform("dirLight.direction", m_DirectionalLightPosition);
	s->setUniform("dirLight.amb",  0.2f, 0.2f, 0.2f);
	s->setUniform("dirLight.diff", 0.5f, 0.5f, 0.5f);
	s->setUniform("dirLight.spec", 0.0f, 0.8f, 0.8f);

}
void Renderer::setupShadows()
{
	GLfloat border[] = { 1.0f, 0.0f, 0.0f, 0.0f };


	// The depth buffer texture
	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture   (GL_TEXTURE_2D, depthTex);
	glTexImage2D    (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_ShadowMapWidth, m_ShadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	// Assign the depth buffer texture to texture channel 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTex);

	// Create and set up the FBO
	glGenFramebuffers(1, &m_ShadowFrameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFrameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
	GLenum drawBuffers[] = { GL_NONE };
	glDrawBuffers(1,drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result == GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer is complete.\n");
	}
	else {
		printf("Framebuffer is not complete.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	m_ShadowProjectionMat = glm::perspective(80.f, 1.f, 1.f, 50.f);

	m_ShadowBias = glm::mat4(
			glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
			glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
	);
}