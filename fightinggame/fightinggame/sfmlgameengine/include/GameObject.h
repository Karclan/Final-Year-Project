#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include <iostream>

#include "FTInterface.h"
#include "Mesh.h"
#include "Collidable.h"
#include "Component.h"
#include "ShaderHandler.h"

class GameObject
{
public:

	void init(Mesh *m,sf::Vector3f c);

	virtual void update(float dt)=0;
	void renderUpdate();
	SPC_Component findComponent(ComponentType::type);//!< Tries to find a component that the gameObject owns

	void setPosition(glm::vec3 _newPosition){myTransform=_newPosition;}
	void translate(glm::vec3 _newTransform){myTransform+=_newTransform;}
	void rotate(glm::vec3 _rot);
	void scale(glm::vec3 _newScale);
	void setVelocity(glm::vec3 _velocity){myVelocity=_velocity;}
	void modVelocity(glm::vec3 _velocity){myVelocity+=_velocity;}

	void setColour(sf::Vector3f);
	void giveMesh(Mesh *_newMesh);
	void setMyShader(GLuint _ShaderID){ myShaderID = _ShaderID;}

	virtual void inCollision();
	virtual void fighterCollision();
	virtual void blockCollision();
	virtual void hitboxCollision();

	Collidable* getCollidable(){return myCollidable;}

	Mesh *getMesh(){return myMesh;}
	GLuint getMyShader(){return myShaderID;}	
	glm::vec3 getTransform(){return myTransform;}
	glm::vec3 getRotation(){return myRotation;}
	glm::vec3 getScale(){return myScale;}
	glm::vec3 getVelocity(){return myVelocity;}
	sf::Vector3f getColour(){return myColour;}

	void setMaterials(glm::vec3 amb,glm::vec3 diff,glm::vec3 spec, float specEx)
	{setAmb(amb);setDiff(diff);setSpec(spec);_specEx = specEx;}

	void setAmb (glm::vec3 Ka){_Ka = Ka;}
	void setDiff(glm::vec3 Kd){_Kd = Kd;}
	void setSpec(glm::vec3 Ks){_Ks = Ks;}
	void setSpecEx(float specEx){_specEx = specEx;}

	glm::vec3 getAmb(){return _Ka;}
	glm::vec3 getDiff(){return _Kd;}
	glm::vec3 getSpec(){return _Ks;}
	float getSpecEx(){return _specEx;}
	std::string collisionString;

protected:

	SPC_Transform m_Transform;

	GLuint myShaderID;
	GLuint modelMatrixID;
	Mesh *myMesh;
	Collidable *myCollidable;

	glm::vec3 myTransform;
	glm::vec3 myRotation;
	glm::vec3 myScale;
	glm::vec3 myVelocity;
	sf::Vector3f myColour;

	glm::vec3 _Ka,_Kd,_Ks;
	float _specEx;
	
	float myYaw;
	float myPitch;
	float myRoll;

	
};
#endif
