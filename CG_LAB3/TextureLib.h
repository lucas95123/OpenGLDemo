#pragma once
#include <Windows.h>
#include <map>
#include <stdio.h>
#include <gl/glut.h>
class TextureLib
{
public:
	TextureLib();
	~TextureLib();
	int addTexture(std::string textureName);
	int textureNum(){ return textureMap.size(); }
	int getTextureID(std::string textureName);
private:
	std::map<std::string, int> textureMap;
};

