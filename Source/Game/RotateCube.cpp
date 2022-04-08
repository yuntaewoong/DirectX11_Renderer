#include "RotateCube.h"

RotateCube::RotateCube()
{
	m_rotatingAmount = 0;
}
void RotateCube::Update(_In_ FLOAT deltaTime)
{
	m_rotatingAmount += deltaTime;
    XMMATRIX mOrbit = XMMatrixRotationY(-2.0f * m_rotatingAmount);
    XMMATRIX mSpin = XMMatrixRotationZ(-1.0f * m_rotatingAmount);
    XMMATRIX mTranslate = XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
    XMMATRIX mScale = XMMatrixScaling(0.3f, 0.3f, 0.3f);
    m_world = mScale * mSpin * mTranslate * mOrbit;
}
RotateCube::~RotateCube()
{}