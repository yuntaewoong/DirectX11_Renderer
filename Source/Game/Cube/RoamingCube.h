#pragma once
/*+===================================================================
  File:      ROAMINGCUBE.H

  Summary:   Rotate cube header file contains declarations of RotateCube
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: RoamCube

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once
#include "Cube/BaseCube.h"
class RoamingCube : public BaseCube
{
public:
    RoamingCube();
    virtual void Update(_In_ FLOAT deltaTime) override;
    ~RoamingCube();
private:
    BOOL m_bRoamingRight;
    FLOAT m_roamingAmount;
    FLOAT m_roamingLimit;
};