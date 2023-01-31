#include "EdgeEquation.h"

EdgeEquation::EdgeEquation(const Vector3& v1, const Vector3& v2)
{
    a = v1.y - v2.y;
    b = v2.x - v1.x;
    c = -(a * (v1.x + v2.x) + b * (v1.y + v2.y)) / 2;
    tie = a != 0 ? a > 0 : b > 0;
}
float EdgeEquation::Evaluate(float x, float y)
{
    return a * x + b * y + c;
}

bool EdgeEquation::CheckInside(float x, float y)
{
    return CheckInside(Evaluate(x, y));
}

bool EdgeEquation::CheckInside(float v)
{
    return (v > 0 || v == 0 && tie);
}