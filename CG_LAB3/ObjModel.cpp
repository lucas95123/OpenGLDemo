#include "ObjModel.h"

ObjModel::ObjModel(char *objFileName)
{
	objModel=loadObj(objFileName);
}

ObjModel::~ObjModel()
{
	delete objModel;
}

void ObjModel::draw(int textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glmDraw(objModel, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
}

GLMmodel *ObjModel::loadObj(char *file)
{
	return glmReadOBJ(file);
}