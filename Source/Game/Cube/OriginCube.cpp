#include "Cube/OriginCube.h"


OriginCube::OriginCube()
{
}
void OriginCube::Update(_In_ FLOAT deltaTime)
{
	RotateY(deltaTime);
}
OriginCube::~OriginCube()
{}