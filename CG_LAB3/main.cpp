//
//#include <Windows.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <gl\glut.h>
//#include <gl\GL.h>
//#include <gl\GLU.h>
//#include "TextureLib.h"
//#include "ObjModel.h"
//
//float eye[] = { 0, 20, 20 };
//float center[] = { 0, 0, 0 };
//
//float fTranslate;
//float fRotate = 0.0f;
//float fScale = 1.0f;	// set inital scale value to 1.0f
//
//bool bPersp = true;
//bool bAnim = false;
//bool bWire = false;
//bool bSelection = false;
//
//int wHeight = 0;
//int wWidth = 0;
//
//int previousX = 0;
//int previousY = 0;
//
//GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//��ɫ����Դ������  
//GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��ɫ����Դ������  
//
//ObjModel* obj1;
//ObjModel* obj2;
//ObjModel* obj3;
//ObjModel* obj4;
//ObjModel* obj5;
//ObjModel* obj6;
//ObjModel* obj7;
//TextureLib* textureLib;
////todo
////hint: some additional parameters may needed here when you operate the teapot
//void SetupLights();
//
//void Init()
//{
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);//ָ����ȱȽ���ʹ�õ���ֵ
//	glShadeModel(GL_SMOOTH);
//	SetupLights();
//	//������ͼ
//	textureLib = new TextureLib();
//	textureLib->addTexture("Texture.bmp");
//	textureLib->addTexture("Texture2.bmp");
//	textureLib->addTexture("Cow_text.bmp");
//	textureLib->addTexture("Tails.bmp");
//	textureLib->addTexture("Shoes.bmp");
//	textureLib->addTexture("Floor.bmp");
//	textureLib->addTexture("WallBack.bmp");
//	textureLib->addTexture("WallSide.bmp");
//	//����OBJ
//	obj1 = new ObjModel("Ball_dABF.obj");
//	obj2 = new ObjModel("Beetle_ABF.obj");
//	obj3 = new ObjModel("Cow_dABF.obj");
//	obj4 = new ObjModel("Gargoyle_ABF.obj");
//	obj5 = new ObjModel("Isis_dABF.obj");
//	obj6 = new ObjModel("Tails.obj");
//}
//
//void SetupLights()
//{
//	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//��ɫ����Դ������  
//	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��ɫ����Դ������  
//	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//��ɫ����Դ�����  
//
//	GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������  
//	GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������  
//	GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ�����  
//
//	GLfloat lightPos[] = { 0.0f, 0.0f, 60.0f, 1.0f };  //��Դλ��  
//	GLfloat spotLightPos[] = { 0.0f, 60.0f, 60.0f, 1.0f }; //���λ��  
//	GLfloat spotDir[] = { 0.0f, -1.0f, -1.0f };            //��Ʒ���  
//
//	GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };       //��ɫ��Դ  
//	GLfloat greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };     //��ɫ��Դ  
//	GLfloat blueLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };      //��ɫ��Դ  
//
//
//	glEnable(GL_LIGHTING);                          //���ù���  
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //�����������Դ  
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //���þ����Դ  
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //���õƹ�λ��  
//	glEnable(GL_LIGHT0);                            //�򿪰�ɫ����Դ  
//
//	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
//	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
//	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
//	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);
//
//	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);      //��ɫ���  
//	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);
//
//	glLightfv(GL_LIGHT2, GL_SPECULAR, greenLight);    //��ɫ���  
//	glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 85.0f);
//
//	glLightfv(GL_LIGHT3, GL_SPECULAR, blueLight);     //��ɫ���  
//	glLightfv(GL_LIGHT3, GL_POSITION, spotLightPos);
//	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);
//	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 85.0f);
//
//}
//
//void Draw_Scene()
//{
//	glPushMatrix();
//	glTranslatef(-40, 0, 6);
//	glScalef(10, 10, 10);
//	obj1->draw(textureLib->getTextureID("Texture.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-7, 0, 4 + 3);
//	glRotatef(90, 1, 0, 0);
//	glScalef(5, 5, 5);
//	obj2->draw(textureLib->getTextureID("Texture2.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-21, 0, 15);
//	glRotatef(90, 1, 0, 0);
//	glScalef(15, 15, 15);
//	obj3->draw(textureLib->getTextureID("Cow_text.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-28, 0, 4 + 6);
//	glScalef(5, 5, 5);
//	obj4->draw(textureLib->getTextureID("Texture.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(14, 0, 4 + 5);
//	glRotatef(90, 1, 0, 0);
//	glScalef(5, 5, 5);
//	obj5->draw(textureLib->getTextureID("Texture.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(30, 0, 4 + 1);
//	glRotatef(90, 1, 0, 0);
//	glScalef(5, 5, 5);
//	obj6->draw(textureLib->getTextureID("Tails.bmp"));
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0, 3.5);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("Floor.bmp"));
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -40, 0);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, -40, 0);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 40, 0);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 40, 0);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-100, 0, 50 + 3.5);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallSide.bmp"));
//	glBegin(GL_QUADS);
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -40, -50);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, -40, 50);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 40, 50);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 40, -50);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(100, 0, 50 + 3.5);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallSide.bmp"));
//	glBegin(GL_QUADS);
//	glNormal3f(1.0f, 0.0f, 0.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -40, -50);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, -40, 50);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 40, 50);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 40, -50);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0, 100 + 3.5);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("Floor.bmp"));
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -40, 0);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, -40, 0);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 40, 0);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 40, 0);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glTranslatef(0, 40, 50 + 3.5);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureLib->getTextureID("WallBack.bmp"));
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 0, -50);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0, -50);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0, 50);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 0, 50);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0, 60);
//	glRotatef(90, 1, 0, 0);
//	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	glEnable(GL_COLOR_MATERIAL);                        //���ò��ʵ���ɫ����  
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //ָ��������ɫ����  
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //ָ�����϶Ծ����ķ�Ӧ  
//	glMateriali(GL_FRONT, GL_SHININESS, 128);             //ָ������ϵ��  
//	glutSolidTeapot(2.0);
//	glPopMatrix();
//}
//
//void updateView(int width, int height)
//{
//	glViewport(0, 0, width, height);						// Reset The Current Viewport
//
//	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//	glLoadIdentity();									// Reset The Projection Matrix
//
//	float whRatio = (GLfloat)width / (GLfloat)height;
//
//	if (bPersp){
//		//todo when 'p' operation, hint: use FUNCTION gluPerspective
//		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
//	}
//	else
//	if (width <= height)
//		glOrtho(-10, 10, -10 * (GLfloat)height / (GLfloat)width, 10 * (GLfloat)height / (GLfloat)width, -100, 100);
//	else
//		glOrtho(-10 * (GLfloat)width / (GLfloat)height, 10 * (GLfloat)width / (GLfloat)height, -10, 10, -100, 100);
//}
//
//void reshape(int width, int height)
//{
//	if (height == 0)										// Prevent A Divide By Zero By
//	{
//		height = 1;										// Making Height Equal One
//	}
//	wHeight = height;
//	wWidth = width;
//	updateView(wWidth, wHeight);
//}
//
//void idle()
//{
//	glutPostRedisplay();
//}
//
//void mouse(int button, int state, int x, int y)
//{
//	if (button == 3)
//		eye[2]--;
//	if (button == 4)
//		eye[2]++;
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		bSelection = false;
//		previousX = x;
//		previousY = y;
//	}
//	else if (button == GLUT_RIGHT_BUTTON)
//	{
//		bSelection=true;
//	}
//}
//
//void key(unsigned char k, int x, int y)
//{
//	switch (k)
//	{
//	case 27:
//	case 'q': {exit(0); break; }
//	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }
//
//	case ' ': {bAnim = !bAnim; break; }
//	case 'o': {bWire = !bWire; break; }
//
//	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
//				  center[0]--;
//				  break;
//	}
//	case 'd': {//todo
//				  center[0]++;
//				  break;
//	}
//	case 'w': {//todo
//				  center[1]++;
//				  break;
//	}
//	case 's': {//todo
//				  center[1]--;
//				  break;
//	}
//	case 'j': {//todo, hint: eye[] and center[] are the keys to solve the problems
//				  for (int i = 0; i < 3; i++)
//				  {
//					  ambientLight[i] -= 0.1;
//					  if (ambientLight[i] < 0)
//						  ambientLight[i] = 0;
//				  }
//				 break;
//	}
//	case 'k': {//todo, hint: eye[] and center[] are the keys to solve the problems
//				  for (int i = 0; i < 3; i++)
//				  {
//					  ambientLight[i] += 0.1;
//					  if (ambientLight[i] < 0)
//						  ambientLight[i] = 0;
//				  }
//				  break;
//	}
//	case 'l':
//		glDisable(GL_LIGHTING);
//		break;
//	case 'm':
//		glEnable(GL_LIGHTING);
//		break;
//	case 0x31:                    //�򿪺�ɫ���  
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT3);
//		glEnable(GL_LIGHT1);
//		break;
//
//	case 0x32:                    //����ɫ���  
//		glDisable(GL_LIGHT1);
//		glDisable(GL_LIGHT3);
//		glEnable(GL_LIGHT2);
//		break;
//
//	case 0x33:                    //����ɫ���  
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT1);
//		glEnable(GL_LIGHT3);
//		break;
//
//	case 0x34:                    //�򿪺�ɫ����Դ  
//		glDisable(GL_LIGHT0);
//		glEnable(GL_LIGHT4);
//		break;
//
//	default:                    //�ر�������Ʋ�������Դ���ɰ�ɫ  
//		glDisable(GL_LIGHT1);
//		glDisable(GL_LIGHT2);
//		glDisable(GL_LIGHT3);
//		glDisable(GL_LIGHT4);
//		glEnable(GL_LIGHT0);
//		break;
//	}
//}
//
//void motion(int x, int y)
//{
//	if (!bSelection)
//	if (previousX == 0 && previousY == 0)
//	{
//		previousX = x;
//		previousY = y;
//	}
//	else
//	{
//		eye[0] -= 0.05*(x - previousX);
//		eye[1] += 0.05*(y - previousY);
//		previousX = x;
//		previousY = y;
//	}
//}
//
//void specialKey(int key, int x, int y)
//{
//	if (key == GLUT_KEY_RIGHT)
//		eye[0]++;
//	if (key == GLUT_KEY_LEFT)
//		eye[0]--;
//	if (key == GLUT_KEY_UP)
//		eye[1]++;
//	if (key == GLUT_KEY_DOWN)
//		eye[1]--;
//}
//
//void redraw()
//{
//	glClearColor(0.4, 0.4, 0.4, 0.6);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();									// Reset The Current Modelview Matrix
//
//	gluLookAt(eye[0], eye[1], eye[2],
//		center[0], center[1], center[2],
//		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������
//
//	if (bWire) {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//	else {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	}
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
//	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
//	glRotatef(-90, 1, 0, 0);
//	glScalef(0.2, 0.2, 0.2);
//	Draw_Scene();						// Draw Scene
//
//	if (bAnim) fRotate += 0.5f;
//	glutSwapBuffers();
//}
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//	glutInitWindowSize(900, 900);
//	int windowHandle = glutCreateWindow("Ex 3");
//	Init();
//	glutDisplayFunc(redraw);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(key);
//	glutMouseFunc(mouse);
//	glutSpecialFunc(specialKey);
//	glutMotionFunc(motion);
//	glutIdleFunc(idle);
//
//	glutMainLoop();
//	return 0;
//}