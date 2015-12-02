
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl\glut.h>
#include "TextureLib.h"
#include "ObjModel.h"
#include "Vec3.h"
#include <vector>
#define Pi 3.1415926
#define delta 0.4
#define deltaRoam 0.1
#define BUFSIZE 64
bool selected[BUFSIZE];

float eye[] = { -20, -3, 8 };
float center[] = { 0, -3, 8 };
float headup[] = { 0, 0, 1 };
float face[] = { 20, 0, 0 };
int eye_fi = 0, eye_theta = 450;
int Rotate_angle = 0;
int RotateSpeed = 3;

float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;
bool bSelection = false;
bool bDrag = false;
bool bRoam = false;
bool bLight = false;
int increX = 0;
int increY = 0;
int increZ = 0;

int wHeight = 0;
int wWidth = 0;

int lastx = -1;
int lasty = -1;

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//白色主光源环境光  
GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//白色主光源镜面光  
GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };//白色主光源漫反射  

GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//红色主光源环境光  
GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//红色主光源漫反射  
GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//红色主光源镜面光  

GLfloat lightPos[] = { 0.0f, 0.0f, 60.0f, 1.0f };  //光源位置  
GLfloat spotLightPos[] = { 0.0f, 60.0f, 60.0f, 1.0f }; //射灯位置  
GLfloat spotDir[] = { 0.0f, -1.0f, -1.0f };            //射灯方向  

GLfloat redLight[] = { 3.0f, 0.0f, 0.0f, 1.0f };       //红色光源  
GLfloat greenLight[] = { 0.0f, 3.0f, 0.0f, 1.0f };     //绿色光源  
GLfloat blueLight[] = { 0.0f, 0.0f, 3.0f, 1.0f };      //蓝色光源  


ObjModel* obj1;
ObjModel* obj2;
ObjModel* obj3;
ObjModel* obj4;
ObjModel* obj5;
ObjModel* obj6;
ObjModel* obj7;
ObjModel* obj8;
TextureLib* textureLib;


//todo
//hint: some additional parameters may needed here when you operate the teapot
void SetupLights();

void Init()
{
	glEnable(GL_LIGHTING);                          //启用光照  
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//指定深度比较中使用的数值
	glShadeModel(GL_SMOOTH);
	SetupLights();
	//载入贴图
	textureLib = new TextureLib();
	textureLib->addTexture("Texture.bmp");
	textureLib->addTexture("Texture2.bmp");
	textureLib->addTexture("Cow_text.bmp");
	textureLib->addTexture("Tails.bmp");
	textureLib->addTexture("Shoes.bmp");
	textureLib->addTexture("Floor.bmp");
	textureLib->addTexture("WallBack.bmp");
	textureLib->addTexture("WallSide.bmp");
	textureLib->addTexture("Steel1.bmp");
	textureLib->addTexture("grass.bmp");
	//载入OBJ
	obj1 = new ObjModel("Ball_dABF.obj");
	obj2 = new ObjModel("Beetle_ABF.obj");
	obj3 = new ObjModel("Cow_dABF.obj");
	obj4 = new ObjModel("Gargoyle_ABF.obj");
	obj5 = new ObjModel("Isis_dABF.obj");
	obj6 = new ObjModel("Tails.obj");
	obj7 = new ObjModel("mini_obj.obj");
	//obj8 = new ObjModel("batman.obj");
	//初始化selection buffer
	memset(selected, 0, sizeof(selected));
}

void SetupLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //设置环境光源  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //设置漫反射光源  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //设置镜面光源  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置  
	glEnable(GL_LIGHT0);                            //打开白色主光源  
	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);      //红色射灯  
	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);

	glLightfv(GL_LIGHT2, GL_SPECULAR, greenLight);    //绿色射灯  
	glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);

	glLightfv(GL_LIGHT3, GL_SPECULAR, blueLight);     //蓝色射灯  
	glLightfv(GL_LIGHT3, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0f);
}

void Draw_indicator(GLfloat height,int Scale)
{
	glPushMatrix();
	glTranslatef(0, 0, height);
	glScalef(0.05*Scale, 0.05*Scale, 0.8*Scale);
	glutSolidCone(1.0, 0.4, 40, 40);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, height);
	glScalef(0.05*Scale, 0.05*Scale, 0.8*Scale);
	glutSolidCone(1.0, 0.4, 40, 40);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, height);
	glScalef(0.05*Scale, 0.05*Scale, 0.8*Scale);
	glutSolidCone(1.0, 0.4, 40, 40);
	glPopMatrix();
}

void Draw_Scene()
{
	glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪  
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面  
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应  
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);             //指定反射系数  

	int itemNum = 0; //每个物体的ID

	glPushMatrix();
	glTranslatef(-51, 0, 55);
	glScalef(4, 4, 4);
	glLoadName(++itemNum);
	if (!selected[1])
		obj1->draw(textureLib->getTextureID("Texture.bmp"));
	else
		obj1->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, 0, 4 + 3);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glLoadName(++itemNum);
	if (!selected[2])
		obj2->draw(textureLib->getTextureID("Texture2.bmp"));
	else
		obj2->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-21, -20, 15);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glLoadName(++itemNum);
	if (!selected[3])
		obj3->draw(textureLib->getTextureID("Cow_text.bmp"));
	else
		obj3->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, 4 + 6);
	glScalef(5, 5, 5);
	glLoadName(++itemNum);
	if (!selected[4])
		obj4->draw(textureLib->getTextureID("Texture.bmp"));
	else
		obj4->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 0, 45);
	glScalef(5, 5, 5);
	glLoadName(++itemNum);
	if (!selected[5])
	{
		obj5->draw(textureLib->getTextureID("Texture.bmp"));
	}
	else
	{
		obj5->draw(textureLib->getTextureID("Texture.bmp"));
		Draw_indicator(0.8,1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30+increX, 0+increY, 4 + 1+increZ);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glLoadName(++itemNum);
	if (!selected[6])
		obj6->draw(textureLib->getTextureID("Tails.bmp"));
	else
	{
		obj6->draw(textureLib->getTextureID("Tails.bmp"));
		glRotatef(-90, 1, 0, 0);
		Draw_indicator(7,3);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-158, 0, 4 + 6);
	glRotatef(90, 1, 0, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	glLoadName(++itemNum);
	if (!selected[7])
		obj7->draw(textureLib->getTextureID("Texture.bmp"));
	else
		obj7->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("Floor.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -40, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, -40, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 40, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 40, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 0, 50 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallSide.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -40, -50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, -40, 50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 40, 50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 40, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 0, 50 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallSide.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -40, -50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, -40, 50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 40, 50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 40, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 100 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("Floor.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -40, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, -40, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 40, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 40, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("grass.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000, -400, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1000, -400, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1000, 400, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000, 400, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 40, 50 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallBack.bmp"));
	glLoadName(++itemNum);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 0, -50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0, -50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0, 50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 0, 50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 60);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("Steel1.bmp"));
	glLoadName(++itemNum);
	glutSolidTeapot(6.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	wWidth = width;
	wHeight = height;
	//todo when 'p' operation, hint: use FUNCTION gluPerspective
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void idle()
{
	glutPostRedisplay();
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr;

	printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) { /*  for each hit  */
		names = *ptr;
		printf(" number of names for hit = %d\n", names); ptr++;
		printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
		printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;
		printf("   the name is ");
		for (j = 0; j < names; j++) {     /*  for each name */
			printf("%d ", *ptr); ptr++;
		}
		printf("\n");
	}
}

void gl_select(int x, int y)
{
	GLuint buff[64] = { 0 };
	GLint hits, view[4];

	glSelectBuffer(64, buff);

	//retrieve info about the viewport
	glGetIntegerv(GL_VIEWPORT, view);
	//switch select mode
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	//modify the vieving volume, restricting selection area around the cursor
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//restrict the draw to an area around the cursor
	gluPickMatrix(x, y, 0.1, 0.1, view);
	gluPerspective(45.0f, (GLfloat)wWidth / (GLfloat)wHeight, 0.1f, 100.0f);

	//pretend to draw the objects onto the screen
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
	Draw_Scene();

	//restore the view
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//get number of objects drawed in that area and return to render mode
	hits = glRenderMode(GL_RENDER);

	processHits(hits, buff);

	if (hits >= 1)
	{
		int choose = buff[3];
		int depth = buff[1];

		for (int i = 0; i < hits; i++)
		{
			if (buff[i * 4 + 1] < (GLuint)depth)	//obtain selected object with minimum depth
			{
				choose = buff[i * 4 + 3];
				depth = buff[i * 4 + 1];
			}
		}
		selected[choose] = !selected[choose];
		bSelection = !bSelection;
	}

	glMatrixMode(GL_MODELVIEW);
}

void mousedw(int x, int y, int but)
{
	//printf("Mouse button %d pressed at %d %d\n", but, x, y);
	gl_select(x, wHeight - y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{
		lastx = lasty = -1;
	}

	if (bSelection)
	{
		if (button == 3)
		{
			increY++;
		}
		if (button == 4)
		{
			increY--;
		}
	}

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		mousedw(x, y, button);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{

	}
	glutPostRedisplay();
}

void cross(float *a, float *b, float *p)
{
	p[0] = a[1] * b[2] - a[2] * b[1];
	p[1] = a[2] * b[0] - a[0] * b[2];
	p[2] = a[0] * b[1] - a[1] * b[0];
	return;
}

void calcface()
{
	face[0] = center[0] - eye[0];
	face[1] = center[1] - eye[1];
	face[2] = center[2] - eye[2];
}

void key(unsigned char k, int x, int y)
{
	float d;
	float *dp = (float *)malloc(sizeof(float)* 3);
	calcface();
	switch (k)
	{
	case 27:
	case 'f': {exit(0); break; }
	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }
	case 'a': {
				  cross(face, headup, dp);
				  eye[0] += -delta*(dp[0]);
				  center[0] += -delta*(dp[0]);
				  eye[1] += -delta*dp[1];
				  center[1] += -delta*dp[1];
				  eye[2] += -delta*dp[2];
				  center[2] += -delta*dp[2];
				  break;
	}
	case 'd': {
				  cross(face, headup, dp);
				  eye[0] += delta*(dp[0]);
				  center[0] += delta*(dp[0]);
				  eye[1] += delta*dp[1];
				  center[1] += delta*dp[1];
				  eye[2] += delta*dp[2];
				  center[2] += delta*dp[2];
				  break;
	}
	case 's': {
				  d = (center[2] - eye[2])*delta;
				  eye[2] += -d;
				  center[2] += -d;
				  d = (center[1] - eye[1])*delta;
				  eye[1] += -d;
				  center[1] += -d;
				  d = (center[0] - eye[0])*delta;
				  eye[0] += -d;
				  center[0] += -d;
				  break;
	}
	case 'w': {
				  d = (center[2] - eye[2])*delta;
				  eye[2] += d;
				  center[2] += d;
				  d = (center[1] - eye[1])*delta;
				  eye[1] += d;
				  center[1] += d;
				  d = (center[0] - eye[0])*delta;
				  eye[0] += d;
				  center[0] += d;
				  break;
	}
	case 'q': {
				  Rotate_angle += RotateSpeed;
				  break;
	}
	case 'e': {
				  Rotate_angle -= RotateSpeed;
				  break;
	}
	case '_': {
				  for (int i = 0; i < 3; i++)
				  {
					  ambientLight[i] -= 0.1;
				  }
				  break;
	}
	case '+': {
				  for (int i = 0; i < 3; i++)
				  {
					  ambientLight[i] += 0.1;
				  }
				  break;
	}
	case 'r': {
				  bRoam = !bRoam;
				  break;
	}
	case 'i':
		bLight = !bLight;
		if (bLight)
			glDisable(GL_LIGHTING);
		else
			glEnable(GL_LIGHTING);
		break;
	case 0x31:                    //打开红色射灯  
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT1);
		break;

	case 0x32:                    //打开绿色射灯  
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT2);
		break;

	case 0x33:                    //打开蓝色射灯  
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT3);
		break;

	case 0x34:                    //打开红色主光源  
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT4);
		break;

	default:                    //关闭所有射灯并将主光源换成白色  
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glEnable(GL_LIGHT0);
		break;
	}
}

void MotionFunc()
{
	if (lastx == -1 && lasty == -1)
	{
		SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
		POINT mousePos;
		GetCursorPos(&mousePos);
		lastx = mousePos.x;
		lasty = mousePos.y;
	}
	else
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		int deltax = mousePos.x - lastx;
		int deltay = mousePos.y - lasty;
		eye_fi += -deltax;
		eye_theta += deltay;
		//printf("fi_theta:%d %d\n", eye_fi, eye_theta);
		if (eye_theta <= 0) eye_theta = 1;
		if (eye_theta >= 180 * 5) eye_theta = 180 * 5 - 1;
		float vector_x = cos(eye_fi * 2 * Pi / 1800.0);
		float vector_y = sin(eye_fi * 2 * Pi / 1800.0);
		float vector_z = cos(eye_theta * 2 * Pi / 1800.0);
		center[0] = eye[0] + vector_x;
		center[1] = eye[1] + vector_y;
		center[2] = eye[2] + vector_z;

		calcface();
		SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
		float dp[3];
		//printf("motionfuc\n");
	}
}

void specialKey(int key, int x, int y)
{
	if (bSelection)
		switch (key)
		{
			case GLUT_KEY_UP:{
							 if (bSelection)
								 increZ++;
							 break;
			}
			case GLUT_KEY_DOWN:{
							   if (bSelection)
								   increZ--;
							   break;
			}
			case GLUT_KEY_LEFT:{
							   if (bSelection)
								   increX--;
							   break;
			}
			case GLUT_KEY_RIGHT:{
								if (bSelection)
									increX++;
								break;
			}
		default:
			break;
		}
}

void redraw()
{
	MotionFunc();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	if (bRoam)
	{
		float d;
		float *dp = (float *)malloc(sizeof(float)* 3);
		calcface();
		d = (center[2] - eye[2])*deltaRoam;
		eye[2] += d;
		center[2] += d;
		d = (center[1] - eye[1])*deltaRoam;
		eye[1] += d;
		center[1] += d;
		d = (center[0] - eye[0])*deltaRoam;
		eye[0] += d;
		center[0] += d;
	}

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		headup[0], headup[1], headup[2]);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //
	spotLightPos[0] = eye[0]; //射灯位置 
	spotLightPos[1] = eye[1];
	spotLightPos[2] = eye[2];
	spotDir[0] = face[0];            //射灯方向  
	spotDir[1] = face[1];
	spotDir[2] = face[2];
	SetupLights();

	glTranslatef(face[0], face[1], face[2]);
	glRotatef(Rotate_angle, face[0], face[1], face[2]);
	glTranslatef(-face[0], -face[1], -face[2]);
	//glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	//glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	int windowHandle = glutCreateWindow("Ex 3");
	Init();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutSpecialFunc(specialKey);
	//glutPassiveMotionFunc(motion);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}