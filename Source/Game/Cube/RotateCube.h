#pragma once
/*+===================================================================
  File:      ROTATECUBE.H

  Summary:   Rotate cube header file contains declarations of RotateCube
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: RotateCube

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once
#include "Cube/BaseCube.h"
class RotateCube : public BaseCube
{
public:
    RotateCube();
    virtual void Update(_In_ FLOAT deltaTime) override;
    ~RotateCube();
private:
    FLOAT m_rotatingAmount;
};