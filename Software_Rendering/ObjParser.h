#pragma once
#include "math.h"
#include "Object.h"
#include <fstream>

class ObjParser
{
public:
    static Object LoadObject(std::string objectName);
};