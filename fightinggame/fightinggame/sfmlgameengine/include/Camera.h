#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include <glew\GL\glew.h>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#define GLM_FORCE_RADIANS
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

class Camera
{
public:
	void init();
	void update();

	void setPostion(glm::vec3 _newPos);
	void setTarget(glm::vec3 _newTarg);

	void pan(glm::vec3 _pan);
	void zoom(float _zoomAmount);
	void rotate(float _angleX, float _angleY, float _angleZ);

	glm::vec3 getRotation(){return glm::vec3(myYaw,myPitch,myRoll);}
	glm::vec3 getPosition(){return myPosition;}
	glm::vec3 getTarget(){return myTarget;}

	glm::mat4 mProj;
	glm::mat4 mView;

	GLuint baseShaderID;

	std::vector<GLuint *>* lstOfShaderIDs;

private:

	GLuint viewMatrixID,projectionMatrixID;

	float myYaw;
	float myPitch;
	float myRoll;

	glm::vec3 myPosition;
	glm::vec3 myTarget;
	glm::vec3 myUp;
	glm::vec3 myRight;
	glm::vec3 myForward;

};
#endif