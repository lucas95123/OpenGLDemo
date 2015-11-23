//#define GLUT_DISABLE_ATEXIT_HACK  
//#include <Windows.h>
//#include "gl/glut.h"  
//#include "glm.h"
//#include <stdio.h>
//#include <stdlib.h>
//#pragma comment(lib, "glut32.lib")  
//
//float eye[] = { 0, 0, 20 };
//float center[] = { 0, 0, 0 };
//
//float fTranslate;
//float fRotate = 0.0f;
//float fScale = 1.0f;	// set inital scale value to 1.0f
//
//bool bPersp = true;
//bool bAnim = false;
//bool bWire = false;
//
//int wHeight = 0;
//int wWidth = 0;
//
//unsigned int ID1 = -1;
//unsigned int ID2 = -1;
//unsigned int ID3 = -1;
//unsigned int ID4 = -1;
//unsigned int ID5 = -1;
//unsigned int ID6 = -1;
//unsigned int ID7 = -1;
//
//GLMmodel *g_model1 = glmReadOBJ("Ball_dABF.obj");
//GLMmodel *g_model2 = glmReadOBJ("Beetle_ABF.obj");
//GLMmodel *g_model3 = glmReadOBJ("Cow_dABF.obj");
//GLMmodel *g_model4 = glmReadOBJ("Gargoyle_ABF.obj");
//GLMmodel *g_model5 = glmReadOBJ("Isis_dABF.obj");
//GLMmodel *g_model6 = glmReadOBJ("Tails.obj");
//
//GLfloat lightPos[] = { 50.0f, 120.0f, 120.0f, 1.0f };  //光源位置  
//
//int previousX = 0;
//int previousY = 0;
//
//int loadBitmap(const char *file)
//{
//	int width, height;
//	byte *image, t;          //接受图像数据
//	FILE *fp;            //文件指针
//	BITMAPFILEHEADER FileHeader;    //接受位图文件头
//	BITMAPINFOHEADER InfoHeader;    //接受位图信息头
//	fp = fopen(file, "rb");
//	if (fp == NULL)
//	{
//		perror("LoadBitmap");        //打开文件失败
//		return -1;
//	}
//	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
//	if (FileHeader.bfType != 0x4D42)  //确保文件是一个位图文件，效验文件类型
//	{
//		printf("Error: This file is not a bmp file!");
//		fclose(fp);
//		return -1;
//	}
//	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
//	width = InfoHeader.biWidth;
//	height = InfoHeader.biHeight;
//	if (InfoHeader.biSizeImage == 0)          //确保图像数据的大小
//	{
//		InfoHeader.biSizeImage = width*height * 3;
//	}
//	fseek(fp, FileHeader.bfOffBits, SEEK_SET);  //将文件指针移动到实际图像数据处
//	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage); //申请空间
//	if (image == NULL)
//	{
//		free(image);
//		printf("Error: No enough space!");
//		return -1;
//	}
//	fread(image, 1, InfoHeader.biSizeImage, fp);
//	for (unsigned int i = 0; i < InfoHeader.biSizeImage; i += 3)
//	{
//		t = image[i];
//		image[i] = image[i + 2];
//		image[i + 2] = t;
//	}
//	fclose(fp);
//	unsigned int ID;
//	glGenTextures(1, &ID);
//	glBindTexture(GL_TEXTURE_2D, ID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width,
//		height, GL_RGB, GL_UNSIGNED_BYTE,
//		image);
//	glDisable(GL_TEXTURE_2D);
//	return ID;
//}
////显示 回调函数  
//void OnDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置  
//	gluLookAt(eye[0], eye[1], eye[2],
//		center[0], center[1], center[2],
//		0, 1, 0);
//
//	glColor3f(0.7f, 0.7f, 0.7f);
//	glutSolidSphere(50.0f, 50.0f, 50.0f); //绘制一个浅灰色的球体  
//
//	//glPushMatrix();
//	//glTranslatef(50, 50, 0);
//	//glScalef(10,10,10);
//	//glEnable(GL_TEXTURE_2D);
//	//glBindTexture(GL_TEXTURE_2D, ID3);
//	//glmDraw(g_model6, GLM_MATERIAL | GLM_TEXTURE);
//	//glDisable(GL_TEXTURE_2D);
//	//glPopMatrix();
//
//	glutSwapBuffers();
//
//}
////窗口尺寸变化后的回调函数  
//void OnReShape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式  
//	glLoadIdentity();
//
//	GLfloat aspect = (float)w / (float)h;
//
//	if (w <= h)
//	{
//		glOrtho(-100.0f, 100.0f, -100.0f / aspect, 100.0f / aspect, -100.0f, 100.0f);
//	}
//	else
//	{
//		glOrtho(-100.0f*aspect, 100.0f*aspect, -100.0f, 100.0f, -100.0f, 100.0f);
//	}
//}
////按键处理回调函数  
//void OnKey(GLubyte key, GLint x, GLint y)
//{
//	switch (key)
//	{
//	case 0x31:                    //打开红色射灯  
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT3);
//		glEnable(GL_LIGHT1);
//		break;
//
//	case 0x32:                    //打开绿色射灯  
//		glDisable(GL_LIGHT1);
//		glDisable(GL_LIGHT3);
//		glEnable(GL_LIGHT2);
//		break;
//
//	case 0x33:                    //打开蓝色射灯  
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT1);
//		glEnable(GL_LIGHT3);
//		break;
//
//	case 0x34:                    //打开红色主光源  
//		glDisable(GL_LIGHT0);
//		glEnable(GL_LIGHT4);
//		break;
//
//	case 'w':
//		eye[1]++;
//			break;
//	case 'a':
//		eye[1]--;
//		break;
//	case 's':
//		eye[0]++;
//		break;
//	case 'd':
//		eye[0]--;
//		break;
//
//	case 'i':
//		lightPos[1]+=2;
//		break;
//	case 'k':
//		lightPos[1]-=2;
//		break;
//	case 'j':
//		lightPos[0]+=2;
//		break;
//	case 'l':
//		lightPos[0]-=2;
//		break;
//
//	default:                    //关闭所有射灯并将主光源换成白色  
//		glDisable(GL_LIGHT1);
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT3);
//		glDisable(GL_LIGHT4);
//		glEnable(GL_LIGHT0);
//		break;
//
//	}
//	glutPostRedisplay();
//}
////设置渲染环境  
//void SetupRC()
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_SMOOTH);
//
//	ID1 = loadBitmap("Texture.bmp");
//	if (ID1 == -1)
//		exit(0);
//	ID2 = loadBitmap("Texture2.bmp");
//	if (ID2 == -1)
//		exit(0);
//	ID3 = loadBitmap("Tails.bmp");
//	if (ID3 == -1)
//		exit(0);
//	ID4 = loadBitmap("Shoes.bmp");
//	if (ID4 == -1)
//		exit(0);
//	ID5 = loadBitmap("Floor.bmp");
//	if (ID5 == -1)
//		exit(0);
//	ID6 = loadBitmap("WallBack.bmp");
//	if (ID6 == -1)
//		exit(0);
//	ID7 = loadBitmap("WallSide.bmp");
//	if (ID7 == -1)
//		exit(0);
//}
//
//void specialKey(int key, int x, int y)
//{
//	if (key == GLUT_KEY_RIGHT)
//		center[0]++;
//	if (key == GLUT_KEY_LEFT)
//		center[0]--;
//	if (key == GLUT_KEY_UP)
//		center[1]++;
//	if (key == GLUT_KEY_DOWN)
//		center[1]--;
//	glutPostRedisplay();
//}
////设置光照  
//void SetupLights()
//{
//	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//白色主光源环境光  
//	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//白色主光源漫反射  
//	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//白色主光源镜面光  
//
//	GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//红色主光源环境光  
//	GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//红色主光源漫反射  
//	GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//红色主光源镜面光  
//
//	GLfloat spotLightPos[] = { 0.0f, 0.0f, 200.0f, 1.0f }; //射灯位置  
//	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };            //射灯方向  
//
//	GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };       //红色光源  
//	GLfloat greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };     //绿色光源  
//	GLfloat blueLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };      //蓝色光源  
//
//
//	glEnable(GL_LIGHTING);                          //启用光照  
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //设置环境光源  
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //设置漫反射光源  
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //设置镜面光源  
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置  
//	glEnable(GL_LIGHT0);                            //打开白色主光源  
//
//	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
//	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
//	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
//	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);
//
//	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);      //红色射灯  
//	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);
//
//	glLightfv(GL_LIGHT2, GL_SPECULAR, greenLight);    //绿色射灯  
//	glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 85.0f);
//
//	glLightfv(GL_LIGHT3, GL_SPECULAR, blueLight);     //蓝色射灯  
//	glLightfv(GL_LIGHT3, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 85.0f);
//
//
//	glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪  
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面  
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应  
//	glMateriali(GL_FRONT, GL_SHININESS, 100);             //指定反射系数  
//}
//// main  
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(600, 480);
//	glutCreateWindow("OpenGL光源");
//
//	glutReshapeFunc(OnReShape);
//	glutDisplayFunc(OnDisplay);
//	glutKeyboardFunc(OnKey);
//	glutSpecialFunc(specialKey);
//
//	SetupRC();
//	SetupLights();
//
//	glutMainLoop();
//}