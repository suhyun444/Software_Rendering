#pragma once
#include "math.h"

class EdgeEquation
{
public:
    float a,b,c;
    bool tie;
    Vector3 v1,v2;
    EdgeEquation(const Vector3& v1, const Vector3& v2);
    bool CheckInside(float x, float y);
    bool CheckInside(float v);
    float Evaluate(float x, float y);
};