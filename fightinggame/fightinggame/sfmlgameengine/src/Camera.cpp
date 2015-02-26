#include "Camera.h"

Camera::Camera()
{
	m_Transform = nullptr;
	std::cout << "Camera Created!\n";
}
Camera::Camera(SPC_Transform t)
{
	m_Transform = t;
	std::cout << "Camera Created!\n";
}
Camera::~Camera()
{
	m_Transform = nullptr;
	std::cout << "Camera Destroyed\n";
}
ComponentType::type Camera::getType()
{
	return ComponentType::CAMERA;
}
void Camera::tearDown()
{

}
void Camera::init(SPC_Transform t)
{
	m_Transform = t;
	m_Transform->setPosition(glm::vec3(0.0f,0.0f,2.5f));
	m_Target = glm::vec3(0.0f,0.0f,0.0f);
	m_Up = glm::vec3(0.0f,1.0f,0.0f);

	m_mView = glm::lookAt(m_Transform->getPosition(),m_Transform->getPosition()-m_Target,m_Up);
	m_mProj = glm::perspectiveFov(glm::radians(90.f), (float)GS::SCREENWIDTH, (float)GS::SCREENHEIGHT, 0.0001f, 100.0f);

}
void Camera::setPostion(glm::vec3 _newPos)
{
	m_Transform->setPosition(_newPos);
}
void Camera::setTarget(glm::vec3 _newTarg)
{
	m_Target = _newTarg;
}
void Camera::pan(glm::vec3 _pan)
{
	float speedX = 5.f, speedY = 5.f;

	glm::vec3 forward = m_Target - m_Transform->getPosition();
	glm::vec3 relRight = glm::cross(forward,glm::vec3(0,1,0));
	glm::vec3 relUp = glm::cross(forward,relRight);

	m_Target += relRight * _pan.x * speedX;
	m_Transform->translate(relRight * _pan.x * speedX);
	m_Transform->translate(relUp * _pan.y * speedY);
	m_Target += relUp * _pan.y* speedY;
}
void Camera::zoom(float _zoomAmount)
{
	float zoomSpeed = 5.f;
	glm::vec3 forward = m_Target - m_Transform->getPosition();
	m_Transform->translate(forward * -_zoomAmount * zoomSpeed);
	m_Target -= forward * -_zoomAmount * zoomSpeed;
}
void Camera::rotate(glm::vec3 rot)
{
	m_Target = m_Target - m_Transform->getPosition();

	m_Target = glm::rotate(m_Target, rot.x, glm::vec3(1.f, 0.f, 0.f));
	m_Target = glm::rotate(m_Target, rot.y, glm::vec3(0.f, 1.f, 0.f));
	m_Target = glm::rotate(m_Target, rot.z, glm::vec3(0.f, 0.f, 1.f));

	m_Target = m_Target + m_Transform->getPosition();
}
void Camera::orbit(glm::vec3 rot)
{
		m_Transform->setPosition(m_Transform->getPosition() - m_Target);
	
		m_Transform->setPosition(glm::rotate(m_Transform->getPosition(),rot.x,glm::vec3(1.f,0.f,0.f)));
		m_Transform->setPosition(glm::rotate(m_Transform->getPosition(),rot.y,glm::vec3(0.f,1.f,0.f)));
		m_Transform->setPosition(glm::rotate(m_Transform->getPosition(),rot.z, glm::vec3(0.f, 0.f, 1.f)));
	
		m_Transform->setPosition(m_Transform->getPosition() + m_Target);
}
void Camera::update()
{
	m_Forward = m_Target - m_Transform->getPosition();

	m_Right = glm::cross(m_Up,m_Forward);
	glm::vec3 up = glm::normalize(glm::cross(m_Forward,m_Right));		
	m_mView= glm::lookAt(m_Transform->getPosition(),m_Target,m_Up);

}
