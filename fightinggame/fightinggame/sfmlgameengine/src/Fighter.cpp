#include "Fighter.hpp"

Fighter::Fighter(float _size,SPC_Transform t,SPC_Renderable r, SPC_Collidable c, SPC_PhysicsBody b)
{
	myState=fighterStates::idle;
	m_Transform = t;
	m_Collidable = c;
	m_Renderable = r;
	m_PhysicsBody = b;
	m_components.push_back(m_Transform);
	m_components.push_back(m_Collidable);
	m_components.push_back(m_Renderable);
	m_components.push_back(m_PhysicsBody);
	inAir=false;
	faceLeft=false;
	takingDamage=false;
}
void Fighter::update(float _dt)
{
	if (m_Collidable->getCurrentCollision() != CollisionType::noCollision)
	{
		if (m_Collidable->getCurrentCollision() == CollisionType::top)
		{
			std::cout << "top!\n";
		}
		if (m_Collidable->getCurrentCollision() == CollisionType::botton)
		{
			std::cout << "botton!\n";
		}
		if (m_Collidable->getCurrentCollision() == CollisionType::left)
		{
			std::cout << "left!\n";
		}
		if (m_Collidable->getCurrentCollision() == CollisionType::right)
		{
			std::cout << "right!\n";
		}
	}

	if (m_Transform->getPosition().y<0)
	{
		m_Transform->setPosition(glm::vec3(m_Transform->getPosition().x, 0.f, m_Transform->getPosition().z));
		m_PhysicsBody->setAcceleration(glm::vec3(0.f));
	}
	/*if(myTransform.y > GS::floor.y)
	{
		inAir=true;
	}
	else
	{
		inAir=false;
	}

	switch(myState)
	{
	case fsp::fighterStates::hit:
		{
			hit();
			takingDamage=false;
			break;
		}
	case fsp::fighterStates::jump:
		{
			jump();
			break;
		}
	case fsp::fighterStates::run:
		{
			run();
			break;
		}
	case fsp::fighterStates::walk:
		{
			walk();
			break;
		}
	case fsp::fighterStates::attack:
		{
			attack();
			break;
		}
	case fsp::fighterStates::idle:
		{
			idle();
			break;
		}
	}*/
}


void Fighter::idle()
{
	//myVelocity=glm::vec3(myVelocity.x-myVelocity.x*0.2,myVelocity.y,myVelocity.z);
}
void Fighter::hit()
{
	takingDamage=true;

	//myState=fsp::idle;
}
void Fighter::jump()
{
	/*if(inAir==false)
	{
		setVelocity(glm::vec3(getVelocity().x,GS::jumpSpeed,getVelocity().z));
		inAir=true;
	}*/
	myState=fighterStates::idle;
}
void Fighter::run()
{
	/*if(faceLeft==true)
	{
		setVelocity(glm::vec3(-GS::runSpeed,getVelocity().y,getVelocity().z));
	}
	else
	{
		setVelocity(glm::vec3(GS::runSpeed,getVelocity().y,getVelocity().z));
	}*/
	myState=fighterStates::idle;
}
void Fighter::walk()
{
	/*if(faceLeft==true)
	{
		setVelocity(glm::vec3(-GS::walkSpeed,getVelocity().y,getVelocity().z));
	}
	else
	{
		setVelocity(glm::vec3(GS::walkSpeed,getVelocity().y,getVelocity().z));
	}*/
	myState=fighterStates::idle;
}
void Fighter::attack()
{

	myState=fighterStates::idle;
}
void Fighter::fighterCollision()
{
	std::cout << "In collision!";
	//switch(myCollidable->getCurrentCollision())
	//{
	//case col::top:
	//	myVelocity.y =0.f;
	//	//myTransform.y=myCollidable->getCollisionTatget()->getPos().y - myCollidable->getCollisionTatget()->getSize();
	//	break;
	//case col::botton:
	//	myVelocity.y =0.f;
	//	myTransform.y=myCollidable->getCollisionTatget()->getPos().y + myCollidable->getCollisionTatget()->getSize();
	//	break;
	//case col::left:
	//	myTransform.x=myCollidable->getCollisionTatget()->getPos().x - myCollidable->getCollisionTatget()->getSize();
	//	break;
	//case col::right:
	//	myTransform.x=myCollidable->getCollisionTatget()->getPos().x + myCollidable->getCollisionTatget()->getSize();
	//	break;
	//}
}
void Fighter::blockCollision()
{
	/*switch(myCollidable->getCurrentCollision())
	{
	case col::top:
		myVelocity.y=0.f;
		myTransform.y=myCollidable->getCollisionTatget()->getPos().y - myCollidable->getCollisionTatget()->getSize();
		break;
	case col::botton:
		myVelocity.y=0.f;
		myTransform.y=myCollidable->getCollisionTatget()->getPos().y + myCollidable->getCollisionTatget()->getSize();
		break;
	case col::left:
		myVelocity.x=0.f;
		myTransform.x=myCollidable->getCollisionTatget()->getPos().x - myCollidable->getCollisionTatget()->getSize();
		break;
	case col::right:
		myVelocity.x=0.f;
		myTransform.x=myCollidable->getCollisionTatget()->getPos().x + myCollidable->getCollisionTatget()->getSize();
		break;
	}*/
}
void Fighter::hitboxCollision()
{
	/*switch(myCollidable->getCurrentCollision())
	{
	case col::top:
		break;
	case col::botton:
		break;
	case col::left:
		break;
	case col::right:
		break;
	}*/
}