#pragma once
#include "EdgeEquation.h"

class ParameterEquation
{
public:
    float a;
    float b;
    float c;

    ParameterEquation(float p1, float p2, float p3, const EdgeEquation &e1, const EdgeEquation &e2, const EdgeEquation &e3, float area);
    float Evaluate(float x, float y);
};