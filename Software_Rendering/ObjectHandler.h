#pragma once
#include "Object.h"

class ObjectHandler
{
    private:
        std::vector<Object*> objects;
    public:
        void AddObject(Object* obj);
        void UpdateTransform(const Camera& camera);
        void Draw(BitmapBuffer& BitmapBuffer,const Camera& camera);
};