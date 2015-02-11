#ifndef FIGHTER_H
#define FIGHTER_H

#include "GameObject.h"
#include "Collidable.h"
#include "Transfrom.h"
#include "Renderable.h"
#include "Collidable.h"

namespace fighterStates
{
	 enum states{hit,jump,run,walk,attack,idle,dodge, FIGHTERSTATES};
}

class Fighter : public GameObject
{
public:
	Fighter(float _size,SPC_Transform t,SPC_Renderable r, SPC_Collidable c);

	void update(float _dt);
	void switchState(int _newState){myState=_newState;}
	void changeDirection(bool _faceleft){faceLeft=_faceleft;}

	void fighterCollision();
	void blockCollision();
	void hitboxCollision();

private:
	void idle();
	void hit();
	void jump();
	void run();
	void walk();
	void attack();
protected:
	int myState;
	bool inAir;
	bool faceLeft;
	bool takingDamage;

	SPC_Renderable m_Renderable;
	SPC_Transform m_Transform;
	SPC_Collidable m_Collidable;
};
#endif