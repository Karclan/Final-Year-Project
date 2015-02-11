#include "GameObject.h"

SPC_Component GameObject::findComponent(ComponentType::type t)
{
	for(size_t i = 0; i < m_components.size(); ++i)
	{
		if(m_components[i]->getType() == t) return m_components[i];
	}
	return SPC_Component();
}

//void GameObject::init(Mesh *m,sf::Vector3f c)
//{
//	myRotation.x=0.f;
//	myRotation.y=0.f;
//	myRotation.z=0.f;
//
//	myScale.x=1.f;
//	myScale.y=1.f;
//	myScale.z=1.f;
//
//	myTransform.x=0.f;
//	myTransform.y=0.f;
//	myTransform.z=0.f;
//
//	myVelocity.x=0.f;
//	myVelocity.y=0.f;
//	myVelocity.z=0.f;
//
//	collisionString = "No Collision";
//
//	giveMesh(m);
//
//	if(c.x==0.f && c.y==0.f && c.z==0.f)
//	{
//		setColour(m->getColour());
//	}
//	else
//	{
//		setColour(c);
//	}
//}
//
//void GameObject::renderUpdate()
//{
//	getMesh()->mModel = glm::mat4(1.f);
//	getMesh()->mModel = glm::translate(getTransform());
//
//	getMesh()->mModel = glm::rotate(getMesh()->mModel, glm::radians(getRotation().x), glm::vec3(1.f,0.f,0.f));
//	getMesh()->mModel = glm::rotate(getMesh()->mModel, glm::radians(getRotation().y), glm::vec3(0.f,1.f,0.f));
//	getMesh()->mModel = glm::rotate(getMesh()->mModel, glm::radians(getRotation().z), glm::vec3(0.f,0.f,1.f));
//
//	getMesh()->mModel = glm::scale(getMesh()->mModel,getScale());
//}
//void GameObject::rotate(glm::vec3 _rot)
//{
//	myPitch += _rot.y;
//	myYaw += _rot.x;
//	myRoll += _rot.z;
//
//	if ((myPitch>360) || (myPitch<-360)) myPitch=0;
//	if ((myYaw>360) || (myYaw<-360)) myYaw=0;
//	if ((myRoll>360) || (myRoll<-360)) myRoll=0;
//
//	myRotation += glm::vec3(_rot.x,_rot.y,_rot.z);
//}
//
//void GameObject::scale(glm::vec3 _newScale)
//{
//	myScale = _newScale;
//}
//
//void GameObject::giveMesh(Mesh *_newMesh)
//{
//	myMesh = _newMesh;
//}
//void GameObject::setColour(sf::Vector3f _newColour)
//{
//	myColour = _newColour;
//}
//void GameObject::inCollision()
//{
//	if(myCollidable->getCollisionTatget() != nullptr)
//	{
//		switch(myCollidable->getCollisionTatget()->getOwner())
//		{
//		case GS::gameObjType::block:
//			blockCollision();
//			break;
//		case GS::gameObjType::Fighter:
//			fighterCollision();
//			break;
//		case GS::gameObjType::hitBox:
//			hitboxCollision();
//			break;
//		}
//		//myCollidable->_currentCollision=col::noCollision;
//	}
//	switch(myCollidable->getCurrentCollision())
//	{
//	case col::top:
//		collisionString = "Top Collision";
//		break;
//	case col::botton:
//		collisionString = "Bottom Collision";
//		break;
//	case col::left:
//		collisionString = "Left Collision";
//		break;
//	case col::right:
//		collisionString = "Right Collision";
//		break;
//	case col::noCollision:
//		collisionString = "No Collision";
//		break;
//	}
//}
//void GameObject::fighterCollision()
//{
//	switch(myCollidable->getCurrentCollision())
//	{
//	case col::top:
//		break;
//	case col::botton:
//		break;
//	case col::left:
//		break;
//	case col::right:
//		break;
//	}
//}
//void GameObject::blockCollision()
//{
//	switch(myCollidable->getCurrentCollision())
//	{
//	case col::top:
//		break;
//	case col::botton:
//		break;
//	case col::left:
//		break;
//	case col::right:
//		break;
//	}	
//}
//void GameObject::hitboxCollision()
//{
//	switch(myCollidable->getCurrentCollision())
//	{
//	case col::top:
//		break;
//	case col::botton:
//		break;
//	case col::left:
//		break;
//	case col::right:
//		break;
//	}
//}