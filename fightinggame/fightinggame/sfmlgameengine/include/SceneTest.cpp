#include "SceneTest.h"

//SPC_Transform test = std::dynamic_pointer_cast<Transform>(m_rotatingCube->findComponent(ComponentType::TRANSFORM));
//test->setPosition(glm::vec3(0.f, 0.f, -40.f));
//if (test != nullptr)
//{
//	test->setPosition(glm::vec3(0.f, 0.f, 5.f));
//}

void SceneTest::init()
{
	m_Renderer.init();
	m_inputHandler.init();
	m_Renderer.loadMesh("hexagonprism.obj");
	
	SPC_Transform  rct(m_TransformManager.createTransform(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1, 1, 1), glm::vec3(0.f, 0.f, 0.f)));
	SPC_Collidable rcc(m_CollisionManager.createCollidable(rct, 5.0, GameObjectType::BLOCK));
	SPC_Renderable rcr(m_Renderer.createRenderable(rct));

	rcr->setDiff(glm::vec3(0.8f, 0.8f, 0.8f));
	rcr->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));
	rcr->setSpecEx(64.f);
	m_rotatingCube = new Block(rct, rcc, rcr);

	SPC_Transform  st(m_TransformManager.createTransform(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1, 1, 1), glm::vec3(0.f, 0.f, 0.f)));
	SPC_Camera	   sc(m_Renderer.createCamera(st));
	m_camera = new CameraObj(sc, st);
	

	//m_Renderer.setActiveCamera(0);

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
	//non fixed update
	m_CollisionManager.update();
	SPC_Transform t = std::dynamic_pointer_cast<Transform>(m_rotatingCube->findComponent(ComponentType::TRANSFORM));
	t->rotate(glm::vec3(45.f, 0.f, 0.f));
	//fixed update
	m_GameObjectManager.update();
	m_Renderer.render();
}
void SceneTest::handleInput()
{

}
void SceneTest::handleController()
{

}


