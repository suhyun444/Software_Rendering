#include "BaryCenterCalculator.h"
#include <iostream>
BaryCenterCalculator::BaryCenterCalculator(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
{
    p1 = v1;
    p2 = v2;
    p3 = v3;
    u = p2 - p1;
    v = p3 - p1;
}
std::pair<float,float> BaryCenterCalculator::Evaluate(float x, float y)
{
    Vector3 w = Vector3(x,y,0) - p1;
    float a = u.Dot(u), b = u.Dot(v), c = v.Dot(u),d = v.Dot(v), e = u.Dot(w), f = v.Dot(w);
    float s = ((d * e) - (b * f)) / ((a * d) - (b * c));
    float t = ((a * f) - (c * e)) / ((a * d) - (b * c));
    return {s,t};
}