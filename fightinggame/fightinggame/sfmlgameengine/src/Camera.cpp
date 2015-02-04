#include "Camera.h"

void Camera::init()
{
	myPosition = glm::vec3(0.0f,0.0f,2.5f);
	myTarget = glm::vec3(0.0f,0.0f,0.0f);
	myUp = glm::vec3(0.0f,1.0f,0.0f);

	mView = glm::lookAt(myPosition,myPosition-myTarget,myUp);
	mProj = glm::perspective(glm::radians(90.f), 1.0f, 0.0001f,100.0f);

	//viewMatrixID = glGetUniformLocation(baseShaderID, "mView");
	//projectionMatrixID = glGetUniformLocation(baseShaderID, "mProjection");

	//glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &mProj[0][0]);
}
void Camera::setPostion(glm::vec3 _newPos)
{
	myPosition = _newPos;
}
void Camera::setTarget(glm::vec3 _newTarg)
{
	myTarget = _newTarg;
}
void Camera::pan(glm::vec3 _pan)
{
	float speedX = 5.f, speedY = 5.f;

	glm::vec3 forward = myTarget - myPosition;
	glm::vec3 relRight = glm::cross(forward,glm::vec3(0,1,0));
	glm::vec3 relUp = glm::cross(forward,relRight);

	myTarget += relRight * _pan.x * speedX;
	myPosition += relRight * _pan.x * speedX;
	myPosition += relUp * _pan.y * speedY;
	myTarget += relUp * _pan.y* speedY;
}

void Camera::zoom(float _zoomAmount)
{
	float zoomSpeed = 5.f;
	glm::vec3 forward = myTarget - myPosition;
	myPosition -= forward * -_zoomAmount * zoomSpeed;
	myTarget -= forward * -_zoomAmount * zoomSpeed;
}
void Camera::rotate(float _angleX,float _angleY, float _angleZ)
{
	myPitch += _angleY;
	myYaw += _angleX;
	myRoll += _angleZ;

	if ((myPitch>360) || (myPitch<-360)) myPitch=0;
	if ((myYaw>360) || (myYaw<-360)) myYaw=0;
	if ((myRoll>360) || (myRoll<-360)) myRoll=0;

	myPosition = myPosition - myTarget;

	myPosition = glm::rotate(myPosition,_angleX,glm::vec3(1.f,0.f,0.f));
	myPosition = glm::rotate(myPosition,_angleY,glm::vec3(0.f,1.f,0.f));
	myPosition = glm::rotate(myPosition,_angleZ,glm::vec3(0.f,0.f,1.f));

	myPosition = myPosition + myTarget;
}
void Camera::update()
{
	myForward = myTarget - myPosition;

	myRight = glm::cross(myUp,myForward);
	glm::vec3 up = glm::normalize(glm::cross(myForward,myRight));		
	mView= glm::lookAt(myPosition,myTarget,myUp);

	//glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &mView[0][0]);
}
