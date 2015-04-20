#ifndef PARTICLEUPDATERS_H
#define PARTICLEUPDATERS_H

#include <glm/glm.hpp>
#include <iostream>

#include "particleData.h"

//! Enum for types of updaters
namespace Updaters
{
	enum type{EULERUPDATER, FLOORUPDATER, ATTRACTORUPDATER, BASICCOLOURUPDATER, POSITIONCOLOURUPDATER, VELOCITYCOLOURUPDATER, BASICTIMEUPDATER, UPDATERS};
}

/*! \brief  ParticleUpdater

ParticleUpdater Class. Updates particle data based on a certain singular element

*/
class ParticleUpdater
{
private: 
	bool _active;
public:
	ParticleUpdater();
	virtual ~ParticleUpdater();

	virtual Updaters::type getType()=0;

	virtual void update(float t, ParticleData *p)=0; //!<Updates particle data. Pure virtual function which is inherited and defined by child classes
	virtual bool isActive(){return _active;}
	virtual void setActiveFlag(bool f){_active = f;}
};

typedef std::shared_ptr<ParticleUpdater> SP_ParticleUpdater;

/*! \brief  EulerUpdater

EulerUpdater Class. Updates particle velocities using euler method

*/
class EulerUpdater : public ParticleUpdater
{
private:
	glm::vec4 _globalAcceleration;
public:
	
	EulerUpdater(){_globalAcceleration=glm::vec4(0.f);}

	EulerUpdater(glm::vec4 globalAcceleration){_globalAcceleration=globalAcceleration;}

	Updaters::type getType(){return Updaters::EULERUPDATER;}

	virtual void update(float dt, ParticleData *p);

	glm::vec4 getGlobalAcc(){return _globalAcceleration;}
	void setGlobalAcc(glm::vec4 acc){_globalAcceleration=acc;}

};

typedef std::shared_ptr<EulerUpdater> SP_EulerUpdater;

/*! \brief  FloorUpdater

FloorUpdater Class. Makes paticles bounce when they hit a 'floor'

*/
class FloorUpdater : public ParticleUpdater
{
private:
	glm::vec3 _wall;
	float _bounceFactor;
public:
	FloorUpdater(){_wall=glm::vec3(0.f);_bounceFactor=0.5f;}
	Updaters::type getType(){return Updaters::FLOORUPDATER;}
	virtual void update(float dt, ParticleData *p);
};

typedef std::shared_ptr<FloorUpdater> SP_FloorUpdater;

/*! \brief  AttractorUpdater

AttractorUpdater Class. Makes paticles attract to points in space

*/
class AttractorUpdater : public ParticleUpdater
{
private:
	glm::vec4 _attractors[4];
	bool	  _attActFlags[4];
public:
	AttractorUpdater(){
		for(int i = 0; i < 4; ++i)
		{
			_attractors [i]=glm::vec4(0.f);
			_attActFlags[i]=false;
		}
	}

	Updaters::type getType(){return Updaters::ATTRACTORUPDATER;}
	virtual void update(float dt, ParticleData *p);
	size_t collectionSize() {return 4;}
	void addAttractor(int id, bool f, glm::vec4 &attractor){
		if(id<3)return;
		_attractors [id]=attractor;
		_attActFlags[id]=f;
	}
	void toggleAttractor(int id, bool flag){
		if(id<3)return;
		_attActFlags[id]=flag;
	}
	bool getAttractorState(int id)
	{
		if(id<3) return false;
		return _attActFlags[id];
	}
	glm::vec4 getAttractor(size_t id){
		if(id<3)return glm::vec4(0.f); 
		return _attractors[id];
	}
};

typedef std::shared_ptr<AttractorUpdater> SP_AttractorUpdater;

/*! \brief  BasicColourUpdater

BasicColourUpdater Class. Updates particle colour over particle lifespan

*/
class BasicColourUpdater : public ParticleUpdater
{
public:
	Updaters::type getType(){return Updaters::BASICCOLOURUPDATER;}
	virtual void update(float dt, ParticleData *p);
};

typedef std::shared_ptr<BasicColourUpdater> SP_BasicColourUpdater;

/*! \brief  PositionColourUpdater

PositionColourUpdater Class. Updates particle colour over particle lifespan and position

*/
class PositionColourUpdater : public ParticleUpdater
{
private:
	glm::vec4 _minPosition;
	glm::vec4 _maxPosition;
public:
	PositionColourUpdater()
	{
		_minPosition=glm::vec4(0.f);
		_maxPosition=glm::vec4(0.f);
	}

	Updaters::type getType(){return Updaters::POSITIONCOLOURUPDATER;}

	glm::vec4 getMinPos()
	{
		return _minPosition;
	}
	glm::vec4 getMaxPos()
	{
		return _maxPosition;
	}
	void setMinPos(glm::vec4 pos){_minPosition=pos;}
	void setMaxPos(glm::vec4 pos){_maxPosition=pos;}
	virtual void update(float dt, ParticleData *p);
};

typedef std::shared_ptr<PositionColourUpdater> SP_PositionColourUpdater;

/*! \brief  VelocityColourUpdater

VelocityColourUpdater Class. Updates particle colour over particle lifespan and velocity

*/
class VelocityColourUpdater : public ParticleUpdater
{
private:
	glm::vec4 _minVelocity;
	glm::vec4 _maxVelocity;
public:
	Updaters::type getType(){return Updaters::VELOCITYCOLOURUPDATER;}

	virtual void update(float dt, ParticleData *p);

	glm::vec4 getMinVel(){return _minVelocity;}
	glm::vec4 getMaxVel(){return _maxVelocity;}
	void setMinVel(glm::vec4 vel){_minVelocity = vel;}
	void setMaxVel(glm::vec4 vel){_maxVelocity = vel;}
};

typedef std::shared_ptr<VelocityColourUpdater> SP_VelocityColourUpdater;

/*! \brief  BasicTimeUpdater

BasicTimeUpdater Class. Updates particle age

*/
class BasicTimeUpdater : public ParticleUpdater
{
public:
	Updaters::type getType(){return Updaters::BASICTIMEUPDATER;}

	virtual void update(float dt, ParticleData *p);
};

typedef std::shared_ptr<BasicTimeUpdater> SP_BasicTimeUpdater;

#endif