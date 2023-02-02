#include "BaryCenterCalculator.h"

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
    float s = (((w.Dot(v)) * (u.Dot(v))) - ((w.Dot(u))) * ((v.Dot(v)))) / (((u.Dot(v)) * (u.Dot(v))) - ((v.Dot(v)) * (u.Dot(u))));
    float t = (((w.Dot(u)) * (u.Dot(v))) - ((w.Dot(v))) * ((u.Dot(u)))) / (((u.Dot(v)) * (u.Dot(v))) - ((v.Dot(v)) * (u.Dot(u))));
    return {s,t};
}