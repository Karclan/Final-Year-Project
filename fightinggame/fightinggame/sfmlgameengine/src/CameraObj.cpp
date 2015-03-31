#include "CameraObj.h"

CameraObj::CameraObj()
{
	m_Camera = nullptr;
	m_Transform = nullptr;
}
CameraObj::CameraObj(SPC_Camera c, SPC_Transform t)
{
	m_Camera = c;
	m_Transform = t;

	m_components.push_back(c);
	m_components.push_back(m_Transform);
	m_Camera->init(m_Transform);
}
void CameraObj::update(float dt)
{

}
void CameraObj::renderUpdate()
{

}