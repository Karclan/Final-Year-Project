#ifndef FIGHTER_H
#define FIGHTER_H

#include "GameObject.h"
#include "Collidable.h"
#include "Transfrom.h"
#include "Renderable.h"
#include "Collidable.h"
#include "PhysicsBody.h"

//! enum of fighter states, not all states implemented. Used 
namespace fighterStates
{
	 enum states{hit,jump,run,walk,attack,idle,dodge, FIGHTERSTATES};
}

/*! \brief  Fighter

Fighter  class. Not fully implemented class. The 'fighting' entity within the game implementation. has transform, renderable, collidable and physicbody components

*/
class Fighter : public GameObject
{
public:
	Fighter(float _size, SPC_Transform t, SPC_Renderable r, SPC_Collidable c, SPC_PhysicsBody b);

	void update(float _dt); //!< function which acts a basic behaviour on the fighter. Keeps it above 0 on y axis and outputs to console which side its colliding with
	void switchState(int _newState){myState=_newState;}
	void changeDirection(bool _faceleft){faceLeft=_faceleft;}

	void fighterCollision(); //!< empty function, meant to give some specialization for the collisions
	void blockCollision(); //!< empty function, meant to give some specialization for the collisions
	void hitboxCollision(); //!< empty function, meant to give some specialization for the collisions

private:
	void idle(); //!< empty state function
	void hit(); //!< empty state function
	void jump(); //!< empty state function
	void run(); //!< empty state function
	void walk(); //!< empty state function
	void attack(); //!< empty state function
protected:
	int myState;
	bool inAir;
	bool faceLeft;
	bool takingDamage;

	SPC_Renderable m_Renderable;
	SPC_Transform m_Transform;
	SPC_Collidable m_Collidable;
	SPC_PhysicsBody m_PhysicsBody;
};
#endif