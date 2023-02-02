#pragma once
#include "EdgeEquation.h"
#include "math.h"

class BaryCenterCalculator
{
public:
    Vector3 u, v;
    Vector3 p1,p2,p3;
    BaryCenterCalculator(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);
    std::pair<float,float> Evaluate(float x, float y);
};