#include "ObjectHandler.h"

void ObjectHandler::AddObject(Object *obj)
{
    objects.push_back(obj);
}
void ObjectHandler::UpdateTransform(const Camera &camera)
{
    for(int i=0;i<objects.size();++i)
    {
        objects[i]->UpdateTransform(camera);
    }
}
void ObjectHandler::Draw(BitmapBuffer &bitmapBuffer, const Camera &camera)
{
    for (int i = 0; i < objects.size(); ++i)
    {
        objects[i]->Draw(bitmapBuffer,camera);
    }
}
