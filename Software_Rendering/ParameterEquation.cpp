#include "ParameterEquation.h"

ParameterEquation::ParameterEquation(float p1, float p2, float p3, const EdgeEquation &e1, const EdgeEquation &e2, const EdgeEquation &e3, float area)
{
    float factor = 1.0f / (2.0f * area);

    a = factor * (p1 * e1.a + p2 * e2.a + p3 * e3.a);
    b = factor * (p1 * e1.b + p2 * e2.b + p3 * e3.b);
    c = factor * (p1 * e1.c + p2 * e2.c + p3 * e3.c);
}
float ParameterEquation::Evaluate(float x, float y)
{
    return a * x + b * y + c;
}