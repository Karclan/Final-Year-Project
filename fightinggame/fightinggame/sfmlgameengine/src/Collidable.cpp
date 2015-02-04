#include "Collidable.h"

Collidable::Collidable()
{
	myTag=GS::componentTag::collision;
	_myOwner=NULL;
	_collisionTarget=nullptr;
	_currentCollision = col::collisionTypes::noCollision;
}
Collidable::Collidable(float _size /*Size*/, sf::Vector2f _position /*Position*/, int _owner)
{
	myTag=GS::componentTag::collision;
	_collisionTarget=nullptr;
	_myOwner=_owner;
	myPosition = _position;
	size = _size;

	_currentCollision = col::collisionTypes::noCollision;

	upperPos = sf::Vector2f(_position.x+size/2, _position.y+size/2);
	lowerPos = sf::Vector2f(_position.x-size/2, _position.y-size/2);
	setUpDisp();
}
void Collidable::move(sf::Vector2f _newPos)
{
	myPosition = _newPos;
	upperPos = sf::Vector2f(_newPos.x+size/2, _newPos.y+size/2);
	lowerPos = sf::Vector2f(_newPos.x-size/2, _newPos.y-size/2);

	hitBoxDisp.setPosition(myPosition);
	upper.setPosition(upperPos);
	lower.setPosition(lowerPos);
	center.setPosition(myPosition);
}
bool Collidable::Interesects(Collidable* _other)
{
	if (upperPos.x< _other->lowerPos.x || lowerPos.x > _other->upperPos.x){_collisionTarget=nullptr; return false;}
	if (upperPos.y< _other->lowerPos.y || lowerPos.y> _other->upperPos.y){_collisionTarget=nullptr; return false;}
	return true;

};
int Collidable::InteresectsDetailed(Collidable* _other)
{
	if (upperPos.x< _other->lowerPos.x || lowerPos.x > _other->upperPos.x)
	{
		_currentCollision = col::collisionTypes::noCollision;
		_collisionTarget=nullptr;
		return col::collisionTypes::noCollision;
	}
	if (upperPos.y< _other->lowerPos.y || lowerPos.y> _other->upperPos.y)
	{
		_currentCollision = col::collisionTypes::noCollision;
		_collisionTarget=nullptr;
		return col::collisionTypes::noCollision;
	}

	_collisionTarget=_other;

	//difference in x and difference in y
	float dif_x = _other->myPosition.x - myPosition.x;
	float dif_y = _other->myPosition.y - myPosition.y;

	if(abs(dif_x) > abs(dif_y))
	{
		if(dif_x>0)
		{
			_currentCollision =col::collisionTypes::left;
			return col::collisionTypes::left;
		}
		if(dif_x<0)
		{
			_currentCollision =col::collisionTypes::right;
			return col::collisionTypes::right;
		}
	}
	else
	{
		if(dif_y>0)
		{
			_currentCollision =col::collisionTypes::top;
			return col::collisionTypes::top;
		}
		if(dif_y<0)
		{
			_currentCollision =col::collisionTypes::botton;
			return col::collisionTypes::botton;
		}
	}
	return col::collisionTypes::basiccollision;
};
void Collidable::setUpDisp()
{
	hitBoxDisp.setSize(sf::Vector2f(upperPos.x - lowerPos.x,upperPos.y - lowerPos.y));
	hitBoxDisp.setPosition(myPosition);
	hitBoxDisp.setOrigin(hitBoxDisp.getSize().x/2,hitBoxDisp.getSize().x/2);
	hitBoxDisp.setFillColor(sf::Color::Transparent);
	hitBoxDisp.setOutlineColor(sf::Color::Red);
	hitBoxDisp.setOutlineThickness(1.f);

	upper.setPosition(upperPos);
	upper.setRadius(2.f);
	upper.setFillColor(sf::Color::Magenta);
	upper.setOrigin(3.5f,3.5f);

	lower.setPosition(lowerPos);
	lower.setRadius(2.f);
	lower.setFillColor(sf::Color::Green);

	center.setPosition(myPosition);
	center.setRadius(2.f);
	center.setFillColor(sf::Color::Cyan);
	center.setOrigin(2.f,2.f);
}