#ifndef _OBJMODEL_H_
#define _OBJMODEL_H_
#include <Windows.h>
#include <stdio.h>
#include "glm.h"

class ObjModel
{
public:
	ObjModel(char * objFileName);
	void draw(int textureID);
	void draw();
	GLMmodel *getGLMmodel(){ return objModel; }
	~ObjModel();

private:
	GLMmodel *loadObj(char *file);
	GLMmodel *objModel;
};
#endif