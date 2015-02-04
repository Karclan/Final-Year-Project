#ifndef FIGHTER_H
#define FIGHTER_H

#include "GameObject.h"
#include "GS.h"

namespace fsp
{
	 enum fighterStates{hit,jump,run,walk,attack,idle,dodge, FIGHTERSTATES};
}

class Fighter : public GameObject
{
public:
	Fighter(float _size, glm::vec3 _position, Mesh*);

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
};
#endif