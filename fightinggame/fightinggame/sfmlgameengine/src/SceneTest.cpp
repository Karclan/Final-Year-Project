#include "SceneTest.h"

void SceneTest::init()
{
	m_FrameDelay		= 1 / GS::FRAMERATE;
	m_FixedFrameTimer	= 0;
	
	m_Renderer.init();
	m_InputHandler.init();

	//DECORATION BLOCKS

	float step = -4.5f;
	for (int i = 0; i < 5; i++)
	{
		SPC_Transform  t(m_TransformManager.createTransform(glm::vec3(step,0.f,-4.f)));
		SPC_Collidable c(m_CollisionManager.createCollidable(t,5.0,GameObjectType::BLOCK));
		SPC_Renderable r(m_Renderer.createRenderable(t, "pillar.obj"));
		m_decorBlocks[i] = new Block(t, c, r);
		step += 2.0f;
	}
	
	/*step = -4.5f;
	for (int i = 5; i < 10; i++)
	{
		SPC_Transform  t(m_TransformManager.createTransform(glm::vec3(step, 1.f, -4.f)));
		t->scale(glm::vec3(0.5f, 1, 0.5f));
		SPC_Collidable c(m_CollisionManager.createCollidable(t, 5.0, GameObjectType::BLOCK));
		SPC_Renderable r(m_Renderer.createRenderable(t, "pillarcap.obj"));
		m_decorBlocks[i] = new Block(t, c, r);
		step += 2.0f;
	}*/

	////ROTATING CUBE
	//SPC_Transform  rct(m_TransformManager.createTransform(glm::vec3(0.f, 0.f, 0.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(5.f, 5.f, 0.5f), glm::vec3(0.f, 0.f, 0.f)));
	//SPC_Collidable rcc(m_CollisionManager.createCollidable	(rct, 5.0, GameObjectType::BLOCK));
	//SPC_Renderable rcr(m_Renderer.createRenderable			(rct, "torus.obj"));
	//rcr->setDiff	(glm::vec3(0.8f, 0.2f, 0.8f));
	//rcr->setSpec	(glm::vec3(0.5f, 0.5f, 0.5f));
	//rcr->setSpecEx	(64.f);
	//m_rotatingCube = new Block(rct, rcc, rcr);

	//Floor
	SPC_Transform  ft(m_TransformManager.createTransform	(glm::vec3(0.f,-3.f,0.f), glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f)));
	SPC_Collidable fc(m_CollisionManager.createCollidable	(ft, 5.0, GameObjectType::BLOCK));
	SPC_Renderable fr(m_Renderer.createRenderable			(ft, "bridge.obj","resources/texture.png"));
	fr->setDiff(glm::vec3(0.7f, 0.2f, 0.4f));
	fr->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	fr->setSpecEx(64.f);
	m_floorPlatform = new Block(ft, fc, fr);

	//Platform 1
	SPC_Transform  pft0(m_TransformManager.createTransform(glm::vec3(3.f, 2.f, 0.f), glm::vec3(0.f), glm::vec3(1.f,0.3f,1.f), glm::vec3(0.f)));
	SPC_Collidable pfc0(m_CollisionManager.createCollidable(pft0, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr0(m_Renderer.createRenderable(pft0, "cube2.obj"));
	pfr0->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr0->setSpecEx(64.f);
	m_platform[0] = new Block(pft0, pfc0, pfr0);

	//Platform 2
	SPC_Transform  pft1(m_TransformManager.createTransform(glm::vec3(0.f, 4.f, 0.f), glm::vec3(0.f), glm::vec3(1.f, 0.3f, 1.f), glm::vec3(0.f)));
	SPC_Collidable pfc1(m_CollisionManager.createCollidable(pft1, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr1(m_Renderer.createRenderable(pft1, "cube2.obj"));
	pfr1->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr1->setSpecEx(64.f);
	m_platform[1] = new Block(pft1, pfc1, pfr1);

	//Platform 3
	SPC_Transform  pft2(m_TransformManager.createTransform(glm::vec3(-3.f, 2.f, 0.f), glm::vec3(0.f), glm::vec3(1.f, 0.3f, 1.f), glm::vec3(0.f)));
	SPC_Collidable pfc2(m_CollisionManager.createCollidable(pft2, 5.0, GameObjectType::BLOCK));
	SPC_Renderable pfr2(m_Renderer.createRenderable(pft2, "cube2.obj"));
	pfr2->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	pfr2->setSpecEx(64.f);
	m_platform[2] = new Block(pft2, pfc2, pfr2);

	//Fighter 1 
	SPC_Transform  f1t(m_TransformManager.createTransform(glm::vec3(0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	SPC_Collidable f1c(m_CollisionManager.createCollidable(f1t, 5.0, GameObjectType::FIGHTER));
	SPC_Renderable f1r(m_Renderer.createRenderable(f1t, "roller.obj"));
	f1r->setDiff(glm::vec3(0.7f, 0.2f, 0.4f));
	f1r->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	f1r->setSpecEx(64.f);
	m_player1 = new Fighter(5.f, f1t, f1r, f1c);

	//CAMERA
	SPC_Transform  st(m_TransformManager.createTransform(glm::vec3(0.f, 0.f, 12.f), glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f)));
	SPC_Camera	   sc(m_Renderer.createCamera(st));
	m_camera = new CameraObj(sc, st);

	m_Renderer.setActiveCamera(0);
	

	//WARNING ABOUT PARTICLE SHADER
	//WHEN IT COMES TO RENDERING THIS PARTICLE SHADER
	//THE DISPLAY DRIVER CRASHES, NO IDEA WHAT IS HAPPENING RIGHT NOW

	//SPC_Transform fireworkT(m_TransformManager.createTransform(glm::vec3(0.f, 2.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f)));
	//SPC_Particle fireworkP(m_Renderer.createParticle(f1t, 1000));
	//m_firework = new Firework(fireworkP);
	//m_firework->init();
	/*lstOfMeshes.push_back(cube);

	flat_plane = new Block(5.f, glm::vec3(GS::floor.x, GS::floor.y - 0.2f, 0.f), cube, sf::Vector3f(1.f, 0.2f, 0.2f));
	rotating_3Dcube = new Block(5.f, glm::vec3(GS::floor.x, GS::floor.y + 2.f, -5.f), cube, sf::Vector3f(4.f, 0.8f, 0.4f));
	distanceBlock = new Block(5.f, glm::vec3(GS::floor.x, GS::floor.y, -8.f), cube, sf::Vector3f(0.8f, 0.2f, 0.8f));

	flat_cube = new Fighter(0.1f, glm::vec3(GS::floor.x, GS::floor.y, 0.f), cube);
	test_fighter = new Fighter(0.1f, glm::vec3(GS::floor.x - 0.5f, GS::floor.y, 0.f), cube);

	flat_plane->scale(glm::vec3(5.f, 0.1f, 0.5f));
	flat_plane->setMaterials(glm::vec3(0.6f, 0.7f, 0.2f), glm::vec3(0.8, 0.5f, 1.f), glm::vec3(1.f, 0.f, 0.f), 8.f);

	rotating_3Dcube->scale(glm::vec3(2.f, 2.f, 2.f));
	rotating_3Dcube->rotate(glm::vec3(0.45f, 0.f, 0.f));
	rotating_3Dcube->setMaterials(glm::vec3(0.4f, 0.4f, 0.2f), glm::vec3(0.5, 0.7f, 0.5f), glm::vec3(0.f, 0.f, 8.f), 16.f);

	distanceBlock->scale(glm::vec3(10.f, 10.f, 0.1f));
	distanceBlock->setMaterials(glm::vec3(0.8f, 0.5f, 0.8f), glm::vec3(0.5, 0.1f, 0.5f), glm::vec3(1.f, 1.f, 1.f), 8.f);

	flat_cube->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	flat_cube->setColour(sf::Vector3f(0.2f, 0.8f, 0.8f));
	flat_cube->setMaterials(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8, 0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), 32.f);

	test_fighter->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	test_fighter->setColour(sf::Vector3f(1.f, 0.f, 1.f));
	test_fighter->setMaterials(glm::vec3(0.2f, 0.5f, 0.8f), glm::vec3(0.0, 0.5f, 0.5f), glm::vec3(1.f, 1.f, 1.f), 32.f);

	lstOfGameObj.push_back(test_fighter);
	m_collisionManager.addToCheck(test_fighter->getCollidable());
	lstOfGameObj.push_back(flat_plane);
	lstOfGameObj.push_back(flat_cube);
	m_collisionManager.addToCheck(flat_cube->getCollidable());
	lstOfGameObj.push_back(rotating_3Dcube);
	lstOfGameObj.push_back(distanceBlock);*/
}
void SceneTest::update()
{
	handleInput();
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
		m_Renderer.updateParticles((float)Timer::getTime().asMilliseconds());

		SPC_Camera t = std::dynamic_pointer_cast<Camera>(m_camera->findComponent(ComponentType::CAMERA));
		//t->orbit(glm::vec3(0, glm::radians(Timer::getTime().asSeconds()*15.f), 0));

		SPC_Transform k = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		k->rotate(glm::vec3(0.f, Timer::getTime().asSeconds()*45.f, 0.f));

		t->setTarget(k->getPosition());
		m_GameObjectManager.update();

		m_FixedFrameTimer = 0;
	}
	m_TransformManager.update();
	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//  Render Scene  //
	//________________//
	m_Renderer.render();

	//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
	//  Render Text   //
	//________________//
	std::string fps = "FPS: " + std::to_string(m_Renderer.calculateFrameRate());
	FTInterface::renderText(fps, 0, GS::SCREENHEIGHT*0.97f, 0.5, glm::vec3(0.f, 1.f, 0.f));
}
void SceneTest::handleInput()
{
	if (m_InputHandler.isKeyPressed(sf::Keyboard::W))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(0.f, 0.f, -5.0f*Timer::getTime().asSeconds()));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::S))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(0.f,0.f, 5.0f*Timer::getTime().asSeconds()));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::A))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(-5.0f*Timer::getTime().asSeconds(), 0.f, 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::D))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(5.0f*Timer::getTime().asSeconds(), 0.f, 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::LShift))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(0.f, -5.0f*Timer::getTime().asSeconds(), 0.f));
	}
	if (m_InputHandler.isKeyPressed(sf::Keyboard::Space))
	{
		SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_player1->findComponent(ComponentType::TRANSFORM));
		t->translate(glm::vec3(0.f, 5.0f*Timer::getTime().asSeconds(),0.f));
	}
}
void SceneTest::handleController()
{

}


