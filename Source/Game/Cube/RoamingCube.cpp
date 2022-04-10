#include "Cube/RoamingCube.h"
RoamingCube::RoamingCube() : 
	m_bRoamingRight(true),
	m_roamingAmount(0.0f),
	m_roamingLimit(5.0f)
{}
void RoamingCube::Update(_In_ FLOAT deltaTime)
{
	m_roamingAmount += deltaTime;
	if (m_roamingAmount >= m_roamingLimit)
	{
		m_roamingAmount = 0.0f;
		m_bRoamingRight = !m_bRoamingRight;
	}
	if (m_bRoamingRight)
	{
		Translate(DirectX::XMVectorSet(deltaTime, 0, 0, 0));
	}
	else
	{
		Translate(DirectX::XMVectorSet(-deltaTime, 0, 0, 0));
	}
}
RoamingCube::~RoamingCube()
{

}