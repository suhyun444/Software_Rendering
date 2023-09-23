#include "ObjParser.h"
#include <iostream>
#include <sstream>
#include <string>

Index FaceValueToVertexIndex(std::string input1,std::string input2,std::string input3)
{
    std::string x, y, z;
    std::stringstream ss1(input1);
    std::getline(ss1, x, '/');
    std::stringstream ss2(input2);
    std::getline(ss2, y, '/');
    std::stringstream ss3(input3);
    std::getline(ss3, z, '/');
    int xInt = std::stoi(x);
    int yInt = std::stoi(y);
    int zInt = std::stoi(z);
    return Index(xInt - 1,yInt - 1,zInt - 1);
}
Index FaceValueToTextureIndex(std::string input1, std::string input2, std::string input3)
{
    std::string x, y, z;
    std::stringstream ss1(input1);
    std::getline(ss1, x, '/');
    std::getline(ss1, x, '/');
    std::stringstream ss2(input2);
    std::getline(ss2, y, '/');
    std::getline(ss2, y, '/');
    std::stringstream ss3(input3);
    std::getline(ss3, z, '/');
    std::getline(ss3, z, '/');
    int xInt = std::stoi(x);
    int yInt = std::stoi(y);
    int zInt = std::stoi(z);
    return Index(xInt - 1, yInt - 1, zInt - 1);
}
Object ObjParser::LoadObject(std::string objectName, std::string textureName)
{
    std::ifstream fin("D:\\Winapi\\Software_Rendering\\Software_Rendering\\Objects\\" + objectName);
    std::string s;
    Object result;
    if(!fin)
    {
        std::cout << "not Found\n";
        return result;
    }
    while(fin >> s)
    {
        if(s == "v")
        {
            float x, y, z;
            fin >> x >> y >> z;
            Vector3 v = Vector3(x, y, z);
            result.vertices.push_back(v);
        }
        else if(s == "vt")
        {
            float x,y;
            fin >> x >> y;
            Vector2 v = Vector2(x,y);
            result.textureVertices.push_back(v);
        }
        else if(s == "f")
        {
            std::string input1, input2, input3;
            fin >> input1 >> input2 >> input3;
            Index vertexIndex = FaceValueToVertexIndex(input1, input2, input3);
            Index textureIndex = FaceValueToTextureIndex(input1,input2,input3);
            result.indices.push_back(vertexIndex);
            result.textureIndices.push_back(textureIndex);
        }
    }
    result.InitVertexVector();
    result.SetTexture(textureName);
    return result;
}