#include "SceneTest.h"

void SceneTest::init()
{
	m_FrameDelay		= 1 / GS::FRAMERATE;
	m_FixedFrameTimer	= 0;
	
	m_Renderer.init();
	m_InputHandler.init();
	
	SPC_Transform  bT(m_TransformManager.createTransform(glm::vec3(0.0f, 15.0f, -15.0f), glm::vec3(0.f, 90.f, 0.f), glm::vec3(0.2f)));
	SPC_Collidable bC(m_CollisionManager.createCollidable(bT,5.0,GameObjectType::BLOCK));
	SPC_Renderable bR(m_Renderer.createRenderable(bT,"sphere.obj"));
	bR->setDiff(glm::vec3(1.f, 0.9f, 0.0f));
	m_decorBlocks[0] = new Block(bT, bC, bR);
	
	bT=(m_TransformManager.createTransform(glm::vec3(0.f, -24.f, 0.f), glm::vec3(0.f, -135.f, 0.f), glm::vec3(2.f)));
	bC=(m_CollisionManager.createCollidable(bT, 5.0, GameObjectType::BLOCK));
	bR=(m_Renderer.createRenderable(bT, "terrain2.obj"));
	
	bR->setDiff(glm::vec3(0.8f, 0.4f, 0.f));
	bR->setSpec(glm::vec3(0.4f));
	bR->setSpecEx(8.f);
	m_decorBlocks[1] = new Block(bT, bC, bR);
	
	bT=(m_TransformManager.createTransform(glm::vec3(0.f, -1.f, -5.f), glm::vec3(0.f, 14.f, 0.f), glm::vec3(0.02f)));
	bC=(m_CollisionManager.createCollidable(bT, 5.0, GameObjectType::BLOCK));
	bR=(m_Renderer.createRenderable(bT, "PlasmaGen.obj","diffuseflat.jpg","PlasmaGenSpec.jpg"));
	m_decorBlocks[2] = new Block(bT, bC, bR);

	//Floor
	SPC_Transform  ft(m_TransformManager.createTransform	(glm::vec3(0.f, -2.f, 0.f), glm::vec3(0.f), glm::vec3(1.f)));
	SPC_Collidable fc(m_CollisionManager.createCollidable	(ft, 5.0, GameObjectType::BLOCK));
	SPC_Renderable fr(m_Renderer.createRenderable(ft, "testplatform.obj", "platform.png", "platform.png"));
	fr->setSpecEx(64.f);
	m_floorPlatform = new Block(ft, fc, fr);

	//Platform 1
	SPC_Transform  pft0(m_TransformManager.createTransform(glm::vec3(8.f, 4.f, 0.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(0.07f, 0.01f, 0.08f)));
	SPC_Collidable pfc0(m_CollisionManager.createCollidable(pft0, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr0(m_Renderer.createRenderable(pft0, "blox.3ds"));
	pfr0->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr0->setSpecEx(64.f);
	m_platform[0] = new Block(pft0, pfc0, pfr0);

	//Platform 2
	SPC_Transform  pft1(m_TransformManager.createTransform(glm::vec3(0.f, 8.f, 0.f), glm::vec3(90.f,0.f,0.f), glm::vec3(0.07f,0.01f,0.08f)));
	SPC_Collidable pfc1(m_CollisionManager.createCollidable(pft1, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr1(m_Renderer.createRenderable(pft1, "blox.3ds"));
	pfr1->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr1->setSpecEx(64.f);
	m_platform[1] = new Block(pft1, pfc1, pfr1);

	//Platform 3
	SPC_Transform  pft2(m_TransformManager.createTransform(glm::vec3(-8.f, 4.f, 0.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(0.07f,0.01f,0.08f)));
	SPC_Collidable pfc2(m_CollisionManager.createCollidable(pft2, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr2(m_Renderer.createRenderable(pft2, "blox.3ds"));
	pfr2->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr2->setSpecEx(64.f);
	m_platform[2] = new Block(pft2, pfc2, pfr2);

	//Fighter 1 
	SPC_Transform  f1t(m_TransformManager.createTransform(glm::vec3(10.f,0.f,0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.f)));
	SPC_Collidable f1c(m_CollisionManager.createCollidable(f1t, 5.0, GameObjectType::FIGHTER));
	SPC_Renderable f1r(m_Renderer.createRenderable(f1t, "roller.obj"));
	f1r->setDiff(glm::vec3(0.7f, 0.2f, 0.4f));
	f1r->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	f1r->setSpecEx(64.f);
	SPC_PhysicsBody f1pb(m_PhysicsManager.createPhysicsBody(f1t));
	m_player1 = new Fighter(5.f, f1t, f1r, f1c,f1pb);

	//CAMERA
	SPC_Transform  st(m_TransformManager.createTransform(glm::vec3(0.f,5.f, 12.f), glm::vec3(0.f), glm::vec3(1.f)));
	SPC_Camera	   sc(m_Renderer.createCamera(st));
	m_camera = new CameraObj(sc, st);
	sc->setTarget(glm::vec3(0, -1.f, 0));
	m_Renderer.setActiveCamera(0);
	

	//Fixed issue
	/*found error with my shared pointers
	Currently if I assign give a component a component which is also being used with a different component 
	(i.e a particle assigned a transform also used with a renderable)
	it will cause strange issues with setting uniforms to shaders (NO IDEA WHY THIS IS THO)
	but the solution to this is to create a new Shared component pointer and give it the argument
	of anther shared pointer
	So like this;
	SPC_Transform a(<data>);
	<assign the transform to whatever ... >

	SPC_Transform b(a);
	<assign the transform to whatever ... >

	That is the fix, the error could be me using shared pointers wrong or maybe an issue with the structure of my code.

	Although worth noting, the error I had wasn't a crash but a break which if left to run would crash the display driver.
	Strange strange error 
	*/

	//SPC_Transform fireworkT(m_TransformManager.createTransform(glm::vec3(0.f, 2.f, 0.f), glm::vec3(0.f), glm::vec3(1.f)));
	SPC_Transform fireworkT(f1t);
	SPC_Particle  fireworkP(m_Renderer.createParticle(fireworkT, 1000));
	m_firework = new Firework(fireworkP);

}
void SceneTest::update()
{
	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//NON-FIXED UPDATE//
	//________________//
	m_CollisionManager.update();

	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//  FIXED UPDATE  //
	//________________//
	m_FixedFrameTimer = (float)Timer::getTime().asMilliseconds();

	if (m_FixedFrameTimer >= m_FrameDelay)
	{
		m_Renderer.updateParticles((float)Timer::getTime().asSeconds());
		
		SPC_Camera t = std::dynamic_pointer_cast<Camera>(m_camera->findComponent(ComponentType::CAMERA));
		SPC_Transform k = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		k->rotate(glm::vec3(0.f, Timer::getTime().asSeconds()*45.f, 0.f));
		
		m_GameObjectManager.update();

		m_FixedFrameTimer = 0;
	}
	
	m_TransformManager.update();
	m_PhysicsManager.update((float)Timer::getTime().asSeconds());
	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//  Render Scene  //
	//________________//
	m_Renderer.render();

	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//  Render Text   //
	//________________//
	std::string fps = "FPS: " + std::to_string(m_Renderer.calculateFrameRate());
	FTInterface::renderText(fps, 0, GS::SCREENHEIGHT*0.97f, 0.5, glm::vec3(0.f, 1.f, 0.f));

	handleInput();
	handleController();
}

void SceneTest::handleInput()
{
	if (m_InputHandler.isKeyPressed(sf::Keyboard::W))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, 0.f, -5.0f*Timer::getTime().asSeconds()));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::S))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, 0.f, 5.0f*Timer::getTime().asSeconds()));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::A))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(-5.0f*Timer::getTime().asSeconds(), 0.f, 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::D))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(5.0f*Timer::getTime().asSeconds(), 0.f, 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::LShift))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, -5.0f*Timer::getTime().asSeconds(), 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::Space))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_player1->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, 5.0f*Timer::getTime().asSeconds(), 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::Up))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_camera->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, 0.f, 5.f*Timer::getTime().asSeconds()));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::Down))
	{
		SPC_PhysicsBody t = std::dynamic_pointer_cast<PhysicsBody>(m_camera->findComponent(ComponentType::PHYSICSBODY));
		t->addImpulse(glm::vec3(0.f, 0.f, -5.f*Timer::getTime().asSeconds()));
	}
}
void SceneTest::handleController()
{
	if (m_ControllerInput.checkConnected(0))
	{
		m_ControllerInput.update();

		if (m_ControllerInput._buttons[buttons::A])
		{

		}
		if (m_ControllerInput._leftStick.x > 10.f || m_ControllerInput._leftStick.x < -10.f)
		{
			SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		}
	}
}


