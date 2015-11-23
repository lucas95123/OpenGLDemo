
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glm.h"

float eye[] = { 0, 20, 20 };
float center[] = { 0, 0, 0 };

float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool bSelection = false;

int wHeight = 0;
int wWidth = 0;

unsigned int ID1 = -1;
unsigned int ID2 = -1;
unsigned int ID3 = -1;
unsigned int ID4 = -1;
unsigned int ID5 = -1;
unsigned int ID6 = -1;
unsigned int ID7 = -1;

GLMmodel *g_model1 = glmReadOBJ("mini_obj.obj");
GLMmodel *g_model2 = glmReadOBJ("Beetle_ABF.obj");
GLMmodel *g_model3 = glmReadOBJ("ak47.obj");
GLMmodel *g_model4 = glmReadOBJ("Gargoyle_ABF.obj");
GLMmodel *g_model5 = glmReadOBJ("Isis_dABF.obj");
GLMmodel *g_model6 = glmReadOBJ("Tails.obj");

int previousX = 0;
int previousY = 0;

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//��ɫ����Դ������  
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��ɫ����Դ������  
//todo
//hint: some additional parameters may needed here when you operate the teapot

int loadBitmap(const char *file)
{
	int width, height;
	byte *image, t;          //����ͼ������
	FILE *fp;            //�ļ�ָ��
	BITMAPFILEHEADER FileHeader;    //����λͼ�ļ�ͷ
	BITMAPINFOHEADER InfoHeader;    //����λͼ��Ϣͷ
	fp = fopen(file, "rb");
	if (fp == NULL)
	{
		perror("LoadBitmap");        //���ļ�ʧ��
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if (FileHeader.bfType != 0x4D42)  //ȷ���ļ���һ��λͼ�ļ���Ч���ļ�����
	{
		printf("Error: This file is not a bmp file!");
		fclose(fp);
		return -1;
	}
	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = InfoHeader.biWidth;
	height = InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0)          //ȷ��ͼ�����ݵĴ�С
	{
		InfoHeader.biSizeImage = width*height * 3;
	}
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);  //���ļ�ָ���ƶ���ʵ��ͼ�����ݴ�
	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage); //����ռ�
	if (image == NULL)
	{
		free(image);
		printf("Error: No enough space!");
		return -1;
	}
	fread(image, 1, InfoHeader.biSizeImage, fp);
	for (unsigned int i = 0; i < InfoHeader.biSizeImage; i += 3)
	{
		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	fclose(fp);
	unsigned int ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width,
		height, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	return ID;
}
void SetupLights()
{
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//��ɫ����Դ������  
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��ɫ����Դ������  
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//��ɫ����Դ�����  

	GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������  
	GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������  
	GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ�����  

	GLfloat lightPos[] = { 0.0f, 0.0f, 60.0f, 1.0f };  //��Դλ��  
	GLfloat spotLightPos[] = { 0.0f, 60.0f, 60.0f, 1.0f }; //���λ��  
	GLfloat spotDir[] = { 0.0f, -1.0f, -1.0f };            //��Ʒ���  

	GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };       //��ɫ��Դ  
	GLfloat greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };     //��ɫ��Դ  
	GLfloat blueLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };      //��ɫ��Դ  


	glEnable(GL_LIGHTING);                          //���ù���  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //�����������Դ  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //���þ����Դ  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //���õƹ�λ��  
	glEnable(GL_LIGHT0);                            //�򿪰�ɫ����Դ  

	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);      //��ɫ���  
	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);

	glLightfv(GL_LIGHT2, GL_SPECULAR, greenLight);    //��ɫ���  
	glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 85.0f);

	glLightfv(GL_LIGHT3, GL_SPECULAR, blueLight);     //��ɫ���  
	glLightfv(GL_LIGHT3, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 85.0f);

}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//ָ����ȱȽ���ʹ�õ���ֵ
	glShadeModel(GL_SMOOTH);
	SetupLights();

	ID1 = loadBitmap("Texture.bmp");
	if (ID1 == -1)
		exit(0);
	ID2 = loadBitmap("Texture2.bmp");
	if (ID2 == -1)
		exit(0);
	ID3 = loadBitmap("Tails.bmp");
	if (ID3 == -1)
		exit(0);
	ID4 = loadBitmap("Shoes.bmp");
	if (ID4 == -1)
		exit(0);
	ID5 = loadBitmap("Floor.bmp");
	if (ID5 == -1)
		exit(0);
	ID6 = loadBitmap("WallBack.bmp");
	if (ID6 == -1)
		exit(0);
	ID7 = loadBitmap("WallSide.bmp");
	if (ID7 == -1)
		exit(0);
}

void Draw_Scene()
{
	glPushMatrix();
	glTranslatef(-40, 0, 6);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID1);
	glmDraw(g_model1, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, 0, 4 + 3);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID1);
	glmDraw(g_model2, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-21, 0, 15);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID1);
	glmDraw(g_model3, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, 4 + 6);
	glScalef(5, 5, 5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID1);
	glmDraw(g_model4, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 0, 4 + 5);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID1);
	glmDraw(g_model5, GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, 5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID3);
	glmDraw(g_model6, GLM_MATERIAL | GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID5);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
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
	glBindTexture(GL_TEXTURE_2D, ID7);
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
	glTranslatef(100, 0, 50 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID7);
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
	glTranslatef(0, 0, 100 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID5);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -40, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, -40, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 40, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 40, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 40, 50 + 3.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID6);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
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
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_COLOR_MATERIAL);                        //���ò��ʵ���ɫ����  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //ָ��������ɫ����  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //ָ�����϶Ծ����ķ�Ӧ  
	glMateriali(GL_FRONT, GL_SHININESS, 128);             //ָ������ϵ��  
	glutSolidTeapot(2.0);
	glPopMatrix();
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
	}
	else
	if (width <= height)
		glOrtho(-10, 10, -10 * (GLfloat)height / (GLfloat)width, 10 * (GLfloat)height / (GLfloat)width, -100, 100);
	else
		glOrtho(-10 * (GLfloat)width / (GLfloat)height, 10 * (GLfloat)width / (GLfloat)height, -10, 10, -100, 100);
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	wHeight = height;
	wWidth = width;
	updateView(wWidth, wHeight);
}

void idle()
{
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == 3)
		eye[2]--;
	if (button == 4)
		eye[2]++;
	if (button == GLUT_LEFT_BUTTON)
	{
		bSelection = false;
		previousX = x;
		previousY = y;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		bSelection=true;
	}
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
				  center[0]--;
				  break;
	}
	case 'd': {//todo
				  center[0]++;
				  break;
	}
	case 'w': {//todo
				  center[1]++;
				  break;
	}
	case 's': {//todo
				  center[1]--;
				  break;
	}
	case 'j': {//todo, hint: eye[] and center[] are the keys to solve the problems
				  for (int i = 0; i < 3;i++)
				  ambientLight[i]-=0.1;
				  break;
	}
	case 'k': {//todo, hint: eye[] and center[] are the keys to solve the problems
				  for (int i = 0; i < 3; i++)
				  ambientLight[i]+=0.1;
				  break;
	}
	case 'l':
		glDisable(GL_LIGHTING);
		break;
	case 'm':
		glEnable(GL_LIGHTING);
		break;
	case 0x31:                    //�򿪺�ɫ���  
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT1);
		break;

	case 0x32:                    //����ɫ���  
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT2);
		break;

	case 0x33:                    //����ɫ���  
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT3);
		break;

	case 0x34:                    //�򿪺�ɫ����Դ  
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT4);
		break;

	default:                    //�ر�������Ʋ�������Դ���ɰ�ɫ  
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glEnable(GL_LIGHT0);
		break;
	}
}

void motion(int x, int y)
{
	if (!bSelection)
	if (previousX == 0 && previousY == 0)
	{
		previousX = x;
		previousY = y;
	}
	else
	{
		eye[0] -= 0.05*(x - previousX);
		eye[1] += 0.05*(y - previousY);
		previousX = x;
		previousY = y;
	}
}

void specialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
		eye[0]++;
	if (key == GLUT_KEY_LEFT)
		eye[0]--;
	if (key == GLUT_KEY_UP)
		eye[1]++;
	if (key == GLUT_KEY_DOWN)
		eye[1]--;
}

void redraw()
{
	glClearColor(0.4, 0.4, 0.4, 0.6);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	int windowHandle = glutCreateWindow("Ex 3");
	Init();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutSpecialFunc(specialKey);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}