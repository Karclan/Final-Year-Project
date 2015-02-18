#include "Scene.h"


//TEXTURES --Pretty much already implemented just not used yet, will do that soon
//SIMPLE Fighting - hitboxes are in, collision detection is in. Can just make states to fight 
//as no resoultion is really needed, just impulses of velocity to be made
//PARTICLES --not implemented or designed
//concept - manager which creates particles at a location which will
//fly off for a period of time and then destory after the have existed for a bit of time
//the death will be a show through being scaled down untill the scale is 0
//once then the object will be deleted? OR maybe just taken out of render loops
//and kept in a predefined array of particles for efficency purposes

//HITBOX NOTES//
// Dynamic hitboxes or just hitboxes which are predefined and just brought into
//scene and checks as and when I need them? 

//----To Do / Bug fixes ----//
//==Collisions work==//
//Collision Resoultion is an issue
//Currently difficult to get objects to stop and then
//to be prevented from moving into each other 
//without both objects being 'pushed' although this may be because its a fighter vs fighter collision
//as these are two dymanic objects and will move

//==Gravity==//
//Need to change the way gravity is done, need to do it outside of the scene
//by a controller of sorts

//==Controls==//
//Need to change the way the player is controlled
//need to make sure my state system is working
//  IF the player is colliding with left on a block
//it can only move right, and, up and down
//  IF a player is colliding with a block on the right
//it can only move left, up, and down
//  IF a player is colliding with a block on top
//it can only go down, left, and right
//  IF a player is colliding with a block on the bottom
//it can only go up, left, and right

//==Structure==//
//Change GameObject and derived classes to have no custom constructors
//design so all gameobjects need to be set up through a virtual init function
//So dynamic casting can work properly

//==Current Task==//
//Reworking gameobjects to be component based
//so that it is easier to make the game and have
//elments modular and more OO
Scene::Scene()
{
}
Scene::~Scene()
{

}

void Scene::init()
{
	/*ActiveController=false;
	grav = 2.f;
	_inputHandler.init();

	s.createShader("shader/basic.vert", "shader/basic.frag");

	setUpCameras();
	setUpGameObjects();	

	shaderHandler = new ShaderHandler(s.shaderProgID);
	
	ActiveController=_controllerInput.init(0);*/
}

void Scene::update()
{
	//
	//gravity(dt);
	//handleInput(dt);
	//if(ActiveController==true)
	//{
	//	handleController(dt);
	//}
	//uiPos = ActiveCamera->getPosition();
	//test();
	//lightPos[0] = glm::vec3(flat_cube->getTransform().x,5.f,0.f);

	//m_collisionManager.update();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBindVertexArray(0);
	//ActiveCamera->update();

	//for(auto it : lstOfGameObj )
	//{
	//	//---Update---//
	//	it->update(dt);		
	//	
	//	it->renderUpdate();	

	//	//--Render--//

	//	glUseProgram(it->getMesh()->myShaderHandle);

	//	shaderHandler->setActiveShader(it->getMesh()->myShaderHandle);
	//	shaderHandler->setUniform("mModel",	it->getMesh()->mModel);
	//	setUpLighting();
	//	setCamera(ActiveCamera);

	//	glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(glm::mat3(it->getMesh()->mModel))));
	//	shaderHandler->setUniform("NormalMatrix",normMat);

	//	setMaterials(it);

	//	glBindVertexArray(it->getMesh()->getVAO());
	//	glDrawElements(GL_TRIANGLES, it->getMesh()->getIndices()->size() ,GL_UNSIGNED_INT, NULL);
	//	glBindVertexArray(0);
	//}

	////Render all text
	////This is done after due to the blending 
	//FTInterface::renderText("FightingGame PreAlpha",0.f,5.f,0.5f,glm::vec3(0.5f,0.2f,0.5f));
	//FTInterface::renderText(flat_cube->collisionString,0.f,500.f,0.5f,glm::vec3(0.8f,0.5f,0.0f));
}

void Scene::keyDown(int key_code)
{
	m_inputHandler.keyPressed(key_code);
}
void Scene::keyUp(int key_code)
{
	m_inputHandler.keyReleased(key_code);
}
//This will be a state swapping function only eventually
//void Scene::handleController(float dt)
//{
//	////If the controller left stick is beyond the threshhold
//	////try to move the fighter
//	//if(_controllerInput._leftStick.x != 0)
//	//{
//	//flat_cube->translate(glm::vec3(glm::radians((_controllerInput._leftStick.x))*dt,0.0f,0.0f));	
//	//}
//	//if(_controllerInput._buttons[buttons::A]==true)
//	//{
//	//	if(flat_cube->getTransform().y==0.f)
//	//	{
//	//		flat_cube->modVelocity(glm::vec3(0,_controllerInput._leftT*1.f,0));
//	//	}
//	//	flat_cube->switchState(fsp::jump);
//	//}
//	//if(_controllerInput._leftT > 0)
//	//{
//	//	
//	//}
//}
////This will be a state swapping function only eventually
//void Scene::handleInput(float dt)
//{
//	//_controllerInput.update();
//	//if(_inputHandler._KEYS[sf::Keyboard::A]	== true)
//	//{
//	//	flat_cube->translate(glm::vec3(-2.5f*dt,0.0f*dt,0.0f));
//	//}
//	//if(_inputHandler._KEYS[sf::Keyboard::D]==true)
//	//{
//	//	flat_cube->translate(glm::vec3(2.5f*dt,0.0f,0.f));
//	//}
//	//if(_inputHandler._KEYS[sf::Keyboard::W]==true)
//	//{
//	//	if(flat_cube->getTransform().y==0.f)
//	//	{
//	//		flat_cube->modVelocity(glm::vec3(0,1.f,0));
//	//		flat_cube->switchState(fsp::jump);
//	//	}
//	//}
//	//if(_inputHandler._KEYS[sf::Keyboard::Num1]==true)
//	//{
//	//	rotating_3Dcube->setColour(sf::Vector3f((float)1.f*dt,0.f,(float)0.5*dt));
//	//}
//}
//
/////////////////////////
//////---TEMPFUNCS---////
/////////////////////////
////These functions will be moved out of the scene
//void Scene::test()
//{
//	//ActiveCamera->setTarget(glm::vec3(flat_cube->getTransform().x,ActiveCamera->getTarget().y,ActiveCamera->getTarget().z));
//	//distanceBlock->translate(glm::vec3(0.f,0.f,_controllerInput._leftT*dt));
//	//distanceBlock->translate(glm::vec3(0.f,0.f,-_controllerInput._rightT*dt));
//	//rotating_3Dcube->findComponent(ComponentType::TRANSFORM)->rotate(glm::vec3(_controllerInput._rightStick.y*Timer::getTime(),_controllerInput._rightStick.x*Timer::getTime(),0.f));
//}
//
//void Scene::setUpCameras()
//{
//	//C.init();
//	//C.setPostion(glm::vec3(GS::floor.x,GS::floor.y+0.7f,1.f));
//	//C.setTarget(glm::vec3(GS::floor.x,GS::floor.y+0.7f,0.f));
//	//ActiveCamera = &C;
//	//uiPos = ActiveCamera->findComponent(ComponentType::TRANSFORM)->getPosition();
//}
//void Scene::setUpGameObjects()
//{
//	/*cube = new Mesh(1,sf::Vector3f(1.f,0.5f,0.2f),s.shaderProgID);
//
//	lstOfMeshes.push_back(cube);
//
//	flat_plane = new Block(5.f,glm::vec3(GS::floor.x,GS::floor.y-0.2f,0.f),cube,sf::Vector3f(1.f,0.2f,0.2f));
//	rotating_3Dcube = new Block(5.f,glm::vec3(GS::floor.x,GS::floor.y+2.f,-5.f),cube,sf::Vector3f(4.f,0.8f,0.4f));
//	distanceBlock = new Block(5.f,glm::vec3(GS::floor.x,GS::floor.y,-8.f),cube,sf::Vector3f(0.8f,0.2f,0.8f));
//
//	flat_cube = new Fighter(0.1f,glm::vec3(GS::floor.x,GS::floor.y,0.f),cube);
//	test_fighter = new Fighter(0.1f,glm::vec3(GS::floor.x-0.5f,GS::floor.y,0.f),cube);
//
//	flat_plane->scale(glm::vec3(5.f,0.1f,0.5f));
//	flat_plane->setMaterials(glm::vec3(0.6f,0.7f,0.2f),glm::vec3(0.8,0.5f,1.f),glm::vec3(1.f,0.f,0.f),8.f);
//
//	rotating_3Dcube->scale(glm::vec3(2.f,2.f,2.f));
//	rotating_3Dcube->rotate(glm::vec3(0.45f,0.f,0.f));
//	rotating_3Dcube->setMaterials(glm::vec3(0.4f,0.4f,0.2f),glm::vec3(0.5,0.7f,0.5f),glm::vec3(0.f,0.f,8.f),16.f);
//
//	distanceBlock->scale(glm::vec3(10.f,10.f,0.1f));
//	distanceBlock->setMaterials(glm::vec3(0.8f,0.5f,0.8f),glm::vec3(0.5,0.1f,0.5f),glm::vec3(1.f,1.f,1.f),8.f);
//
//	flat_cube->scale(glm::vec3(0.1f,0.1f,0.1f));
//	flat_cube->setColour(sf::Vector3f(0.2f,0.8f,0.8f));
//	flat_cube->setMaterials(glm::vec3(0.8f,0.8f,0.8f),glm::vec3(0.8,0.8f,0.8f),glm::vec3(1.f,1.f,1.f),32.f);
//
//	test_fighter->scale(glm::vec3(0.1f,0.1f,0.1f));
//	test_fighter->setColour(sf::Vector3f(1.f,0.f,1.f));
//	test_fighter->setMaterials(glm::vec3(0.2f,0.5f,0.8f),glm::vec3(0.0,0.5f,0.5f),glm::vec3(1.f,1.f,1.f),32.f);
//
//	lstOfGameObj.push_back(test_fighter);
//	m_collisionManager.addToCheck(test_fighter->getCollidable());
//	lstOfGameObj.push_back(flat_plane);
//	lstOfGameObj.push_back(flat_cube);
//	m_collisionManager.addToCheck(flat_cube->getCollidable());
//	lstOfGameObj.push_back(rotating_3Dcube);
//	lstOfGameObj.push_back(distanceBlock);*/
//}
//
//void Scene::setCamera(Camera *c)
//{
//	/*shaderHandler->setUniform("mView",c->mView);
//	shaderHandler->setUniform("mProjection",c->mProj);
//	shaderHandler->setUniform("viewPos",c->getPosition());*/
//}
//void Scene::gravity(float dt)
//{
//	/*if(flat_cube->getTransform().y > 0.f)
//	{
//		flat_cube->modVelocity(glm::vec3(0,-grav*dt,0));
//	}
//	else
//	{
//		flat_cube->setVelocity(glm::vec3(flat_cube->getVelocity().x,0.f,0.f));
//		flat_cube->setPosition(glm::vec3(flat_cube->getTransform().x,0.f,flat_cube->getTransform().z));
//	}*/
//}
//void Scene::checkCollisions()
//{
//	//flat_cube->getCollidable()->InteresectsDetailed(test_fighter->getCollidable());
//	
//}
//void Scene::setUpLighting()
//{
//	////SpotLight1
//	////lightPos[0] = glm::vec3(-1.f,5.f,0.f);
//	//shaderHandler->setUniform("numOfSpotLights",2);
//	//shaderHandler->setUniform("spotLight[0].position", lightPos[0]);
//	//shaderHandler->setUniform("spotLight[0].spotDir", glm::vec3(-0.0f,-1.f,-0.f));
//	//shaderHandler->setUniform("spotLight[0].spotOutCut",glm::cos(glm::radians(7.f)));
//	//shaderHandler->setUniform("spotLight[0].spotInCut",glm::cos(glm::radians(5.5f)));
//	//shaderHandler->setUniform("spotLight[0].constant",1.f);
//	//shaderHandler->setUniform("spotLight[0].linear",0.014f);
//	//shaderHandler->setUniform("spotLight[0].quadratic",0.0007f);
//	//shaderHandler->setUniform("spotLight[0].amb",  0.2f, 0.2f, 0.2f);
//	//shaderHandler->setUniform("spotLight[0].diff", 1.f, 0.0f, 0.0f);
//	//shaderHandler->setUniform("spotLight[0].spec", 1.f, 0.0f, 0.0f);
//
//	////SpotLight2
//	//lightPos[1] = glm::vec3(1.f,5.f,0.f);
//	//shaderHandler->setUniform("spotLight[1].position", lightPos[1]);
//	//shaderHandler->setUniform("spotLight[1].spotDir", glm::vec3(-0.0f,-1.f,-0.f));
//	//shaderHandler->setUniform("spotLight[1].spotOutCut",glm::cos(glm::radians(7.f)));
//	//shaderHandler->setUniform("spotLight[1].spotInCut",glm::cos(glm::radians(5.5f)));
//	//shaderHandler->setUniform("spotLight[1].constant",1.f);
//	//shaderHandler->setUniform("spotLight[1].linear",0.014f);
//	//shaderHandler->setUniform("spotLight[1].quadratic",0.0007f);
//	//shaderHandler->setUniform("spotLight[1].amb",  0.2f, 0.2f, 0.2f);
//	//shaderHandler->setUniform("spotLight[1].diff", 0.0f, 1.0f, 0.0f);
//	//shaderHandler->setUniform("spotLight[1].spec", 0.f,  1.f,  0.f);
//
//	////PointLight1
//	//lightPos[2] = glm::vec3(0.f,5.f,10.f);
//	//shaderHandler->setUniform("numOfPointLights",1);
//	//shaderHandler->setUniform("pointLight[0].position", lightPos[2]);
//	//shaderHandler->setUniform("pointLight[0].constant",1.f);
//	//shaderHandler->setUniform("pointLight[0].linear",0.014f);
//	//shaderHandler->setUniform("pointLight[0].quadratic",0.0007f);
//	//shaderHandler->setUniform("pointLight[0].amb",  0.2f, 0.2f, 0.2f);
//	//shaderHandler->setUniform("pointLight[0].diff", 0.5f, 0.5f, 0.5f);
//	//shaderHandler->setUniform("pointLight[0].spec", 0.f,  1.f,  0.f);
//
//}
//
//void Scene::setMaterials(GameObject *it)
//{
//	//shaderHandler->setUniform("material.diff",it->getDiff());
//	//shaderHandler->setUniform("material.spec",it->getSpec());
//	//shaderHandler->setUniform("material.specEx",it->getSpecEx());
//}