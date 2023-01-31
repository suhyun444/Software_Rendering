#pragma once
#include "math.h"

class EdgeEquation
{
private:
    bool CheckInside(float x, float y);
    bool CheckInside(float v);
    float Evaluate(float x, float y);
public:
    float a,b,c;
    bool tie;
    EdgeEquation(const Vector3& v1, const Vector3& v2);
};