#ifndef COMPONENT_COLLIDABLE_H
#define COMPONENT_COLLIDABLE_H

#include <SFML/system.hpp>
#include <SFML/graphics.hpp>

#include <iostream>
using namespace std;

#include "Component.h"
#include "GS.h"

namespace col
{
	enum collisionTypes{top,botton,left,right, basiccollision,noCollision};
}

class Collidable : public Component
{
private:

	sf::Vector2f myPosition, upperPos, lowerPos;
	sf::CircleShape upper,lower, center;
	sf::RectangleShape hitBoxDisp;
	float size;

	void setUpDisp();
	int _myOwner;
	

	Collidable *_collisionTarget;

public:

	Collidable();
	Collidable(float _size /*Size*/, sf::Vector2f _position /*Position*/, int _owner);

	Collidable& operator= (Collidable& newC){
		myPosition = newC.myPosition;
		size = newC.size;
		upperPos = sf::Vector2f(newC.myPosition.x+size/2, newC.myPosition.y+size/2);
		lowerPos = sf::Vector2f(newC.myPosition.x-size/2, newC.myPosition.y-size/2);
		setUpDisp();
	
		return *this;
	};

	void move(sf::Vector2f newPos);
	bool Interesects(Collidable* other);
	int  InteresectsDetailed(Collidable* other);
	int  getCurrentCollision(){return _currentCollision;}
	int  getOwner(){return _myOwner;}


	sf::Vector2f getPos(){return myPosition;}
	float getSize(){return size;}
	Collidable* getCollisionTatget(){return _collisionTarget;}

	int _currentCollision;
};
#endif