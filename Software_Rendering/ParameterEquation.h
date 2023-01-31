#pragma once
#include "EdgeEquation.h"

class ParameterEquation
{
public:
    float a;
    float b;
    float c;

    ParameterEquation(float p0, float p1, float p2, const EdgeEquation &e0, const EdgeEquation &e1, const EdgeEquation &e2, float area);
    float Evaluate(float x, float y);
};