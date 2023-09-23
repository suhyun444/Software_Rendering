#pragma once
#include "VertexShader.h"

class FragmentShdaer
{
protected:
    Output input;
public:
    virtual void BindInput(Output output){this->input = output;}
    virtual Vector3 Calculate(std::pair<float,float> uv) = 0;
};