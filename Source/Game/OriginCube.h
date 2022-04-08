/*+===================================================================
  File:      ORIGINCUBE.H

  Summary:   Origin cube header file contains declarations of OriginCube
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: OriginCube

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once
#include "Cube/BaseCube.h"
class OriginCube : public BaseCube
{
public:
    OriginCube();
    virtual void Update(_In_ FLOAT deltaTime) override;
    ~OriginCube();
};