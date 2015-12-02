#include "ObjModel.h"

ObjModel::ObjModel(char *objFileName)
{
	objModel=loadObj(objFileName);
	glmFacetNormals(objModel);
	glmVertexNormals(objModel,90);
}

ObjModel::~ObjModel()
{
	delete objModel;
}

void ObjModel::draw(int textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glmDraw(objModel, GLM_SMOOTH|GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
}

void ObjModel::draw()
{
	glmDraw(objModel, GLM_SMOOTH);
}

GLMmodel *ObjModel::loadObj(char *file)
{
	return glmReadOBJ(file);
}