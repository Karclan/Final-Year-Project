#ifndef PARTICLE_GENERATORS_H
#define PARTICLE_GENERATORS_H

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>

#include "particleData.h"

#define _USE_MATH_DEFINES
#include <math.h>


//! Enum for types of generators
namespace Generators
{
	enum type{BOXPOSGEN, ROUNDPOSGEN, BASICCOLOURGEN, BASICVELGEN, SPHEREVELGEN, BASICTIMEGEN, GENERATORS};
}

/*! \brief  ParticleGenerator Class

ParticleGenerator Class. Abstract generator class for classes to inherit from.

*/

class ParticleGenerator
{
private:
	bool _active; //!< Bool to toggle a generator being active or not
public:
	ParticleGenerator();
	virtual ~ParticleGenerator();
	virtual void generate(float dt, ParticleData *p, size_t startId, size_t endId)=0; //!< Generates data of what ever subtype of generator is inheriting and defining this function
	virtual Generators::type getType()=0; //!< Returns the generator type of whatever subtype of generator is inheriting and defining this function
	bool isActive(){return _active;} 
	void setActiveFlag(bool f){_active=f;}
};

typedef std::shared_ptr<ParticleGenerator> SP_ParticleGenerator;

/*! \brief  BoxPosGen Class

BoxPosGen Class. BoxPosGen generator class whichs generates position values within a defined area.

*/
class BoxPosGen :public ParticleGenerator
{
private:
	glm::vec4 _position;
	glm::vec4 _maxStartPositionOffset;
public:
	BoxPosGen(){_position=glm::vec4(0.0); _maxStartPositionOffset = glm::vec4(0.0);}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::BOXPOSGEN;}
	glm::vec4 getStartOffset(){return _maxStartPositionOffset;}
	void setStartOffset(glm::vec4 offset){_maxStartPositionOffset=offset;}
	void setPosition(glm::vec4 pos){_position=pos;}
};

typedef std::shared_ptr<BoxPosGen> SP_BoxPosGen;

/*! \brief  RoundPosGen Class

RoundPosGen Class. RoundPosGen generator class whichs generates position values within a defined area, a circle.

*/
class RoundPosGen : public ParticleGenerator
{
private:
	glm::vec4 _center;
	float _radiusX;
	float _radiusY;
public:
	RoundPosGen(){_center=glm::vec4(0.f);_radiusX=0.f;_radiusY=0.f;}

	RoundPosGen(const glm::vec4 &center, float radX, float radY){_center = center, _radiusX = radX, _radiusY = radY;}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::ROUNDPOSGEN;}
	glm::vec2 getRadius(){return glm::vec2(_radiusX,_radiusY);}
	void setXRadius(float x){_radiusX = x;}
	void setYRadius(float y){_radiusY = y;}
	void setCenter(glm::vec4 pos){_center=pos;}
};

typedef std::shared_ptr<RoundPosGen> SP_RoundPosGen;

/*! \brief  BasicColourGen Class

BasicColourGen Class. BasicColourGen generator class whichs generates colour values within defined maximums and minimums for the start and end of a particle's alive time

*/
class BasicColourGen : public ParticleGenerator
{
private:
	glm::vec4 _minStartColour;
	glm::vec4 _maxStartColour;
	glm::vec4 _minEndColour;
	glm::vec4 _maxEndColour;
public:
	BasicColourGen(){_minStartColour=glm::vec4(0.f); _maxStartColour=glm::vec4(0.f); _minEndColour=glm::vec4(0.f); _maxEndColour=glm::vec4(0.f);}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::BASICCOLOURGEN;}

	glm::vec4 getMinStartColour(){return _minStartColour;}
	glm::vec4 getMaxStartColour(){return _maxStartColour;}
	glm::vec4 getMinEndColour  (){return _minEndColour;}
	glm::vec4 getMaxEndColour  (){return _maxEndColour;}
	void setMinStartColour(glm::vec4 col){_minStartColour=col;}
	void setMaxStartColour(glm::vec4 col){_maxStartColour=col;}
	void setMinEndColour  (glm::vec4 col){_minEndColour=col;}
	void setMaxEndColour  (glm::vec4 col){_maxEndColour=col;}
};

typedef std::shared_ptr<BasicColourGen> SP_BasicColourGen;


/*! \brief  BasicVelGen Class

BasicVelGen Class. BasicVelGen generator class whichs generates velocity values within defined maximums and minimums

*/
class BasicVelGen : public ParticleGenerator
{
private:
	glm::vec4 _minStartVel;
	glm::vec4 _maxStartVel;
public:
	BasicVelGen(){_minStartVel=glm::vec4(0.f); _maxStartVel=glm::vec4(0.f);}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::BASICVELGEN;}
	glm::vec4 getMinStartVel(){return _minStartVel;}
	glm::vec4 getMaxStartVel(){return _maxStartVel;}
	void setMinStartVel(glm::vec4 vel){_minStartVel=vel;}
	void setMaxStartVel(glm::vec4 vel){_maxStartVel=vel;}
};

typedef std::shared_ptr<BasicVelGen> SP_BasicVelGen;

/*! \brief  SphereVelGen Class

SphereVelGen Class. SphereVelGen generator class whichs generates velocity values within defined maximums and minimums in a sphere

*/
class SphereVelGen : public ParticleGenerator
{
private:
	float _minVelocity;
	float _maxVelocity;
public:
	SphereVelGen(){_minVelocity=0.f;_maxVelocity=0.f;}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::SPHEREVELGEN;}
	float getMinVelocity(){return _minVelocity;}
	float getMaxVelocity(){return _maxVelocity;}
	void setMinVelocity(float vel){_minVelocity=vel;}
	void setMaxVelocity(float vel){_maxVelocity=vel;}
};

typedef std::shared_ptr<SphereVelGen> SP_SphereVelGen;

/*! \brief  BasicTimeGen Class

BasicTimeGen Class. BasicTimeGen generator class whichs generates time values within defined maximums and minimums

*/
class BasicTimeGen : public ParticleGenerator
{
private:
	float _minTime;
	float _maxTime;
public:

	BasicTimeGen(){_minTime=0.f;_maxTime=0.f;}

	virtual void generate(float t, ParticleData *p, size_t startId, size_t endId);
	Generators::type getType(){return Generators::BASICTIMEGEN;}
	float getMinTime(){return _minTime;}
	float getMaxTime(){return _maxTime;}
	void setMinTime(float t){_minTime = t;}
	void setMaxTime(float t){_maxTime = t;}
};

typedef std::shared_ptr<BasicTimeGen> SP_BasicTimeGen;

#endif