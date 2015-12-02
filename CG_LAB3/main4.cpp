//// glutEx1.cpp : 定义控制台应用程序的入口点。
////
//#include <Windows.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//#include <gl\glut.h>
//
//float fTranslate;
//float fRotate = 156.5f;
//float fScale = 1.0f;	// set inital scale value to 1.0f
//
//bool bPersp = true;
//bool bAnim = false;
//bool bWire = false;
//
//int wHeight = 0;
//int wWidth = 0;
//
//GLint dl = 0;
//
//void Draw_Leg();
//
//#define BUFSIZE 512
//GLuint selectBuf[BUFSIZE];
//
//int drawMode = 0;
//bool changecolor[BUFSIZE];
//
//GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//GLfloat mat_red[] = { 1.0, 0.0, 0.0, 1.0 };
//
//void Draw_Desk();
//
//void Draw_Scene() // This function draws a triangle with RGB colors
//{
//	int item_num = 1;
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, -1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, -1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, -1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, 1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, 1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, 1, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, 0, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, 0, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, 0, 5.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	//layer 2 rabbits
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, -1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, -1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, -1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, 1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, 1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, 1, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(-1, 0, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(0, 0, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	glPushMatrix();
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glTranslatef(1, 0, 7.5);
//	glLoadName(item_num++);
//	glutSolidSphere(1.0,20,20);
//	glPopMatrix();
//
//	if (changecolor[item_num]) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_red); else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
//	glLoadName(item_num++);
//	Draw_Desk();
//
//}
//
//void Draw_Desk()
//{
//	glPushMatrix();
//	glTranslatef(0, 0, 3.5);
//	glScalef(5, 4, 1);
//	glutSolidCube(1.0);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(1.5, 1, 1.5);
//	Draw_Leg();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-1.5, 1, 1.5);
//	Draw_Leg();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(1.5, -1, 1.5);
//	Draw_Leg();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-1.5, -1, 1.5);
//	Draw_Leg();
//	glPopMatrix();
//
//}
//
//void Draw_Leg()
//{
//	glScalef(1, 1, 3);
//	glutSolidCube(1.0);
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
//	if (bPersp) {
//		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
//	}
//	else {
//		glOrtho(-3, 3, -3, 3, -100, 100);
//	}
//
//	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
//}
//
//void reshape(int width, int height)
//{
//	if (height == 0)										// Prevent A Divide By Zero By
//	{
//		height = 1;										// Making Height Equal One
//	}
//
//	wHeight = height;
//	wWidth = width;
//
//	updateView(wHeight, wWidth);
//}
//
//void idle()
//{
//	glutPostRedisplay();
//}
//
//float center[] = { 0, -0.8, -6 };
//float eye[] = { 0, 1.2, 2 };
//
//void key(unsigned char k, int x, int y)
//{
//	switch (k)
//	{
//	case 27:
//	case 'q': {exit(0); break; }
//	case 'p': {bPersp = !bPersp; break; }
//
//	case ' ': {bAnim = !bAnim; break; }
//	case 'o': {bWire = !bWire; break; }
//	case '0': {drawMode++; drawMode %= 3; break; }
//
//	case 'a': {
//				  eye[0] += 0.2f;
//				  center[0] += 0.2f;
//				  break;
//	}
//	case 'd': {
//				  eye[0] -= 0.2f;
//				  center[0] -= 0.2f;
//				  break;
//	}
//	case 'w': {
//				  eye[1] -= 0.2f;
//				  center[1] -= 0.2f;
//				  break;
//	}
//	case 's': {
//				  eye[1] += 0.2f;
//				  center[1] += 0.2f;
//				  break;
//	}
//	case 'z': {
//				  eye[2] -= 0.2f;
//				  center[2] -= 0.2f;
//				  break;
//	}
//	case 'c': {
//				  eye[2] += 0.2f;
//				  center[2] += 0.2f;
//				  break;
//	}
//	}
//
//	updateView(wHeight, wWidth);
//}
//
//void getFPS()
//{
//	static int frame = 0, time, timebase = 0;
//	static char buffer[256];
//
//	char mode[64];
//	if (drawMode == 0)
//		strcpy(mode, "naive");
//	else if (drawMode == 1)
//		strcpy(mode, "vertex array");
//	else
//		strcpy(mode, "display list");
//
//	frame++;
//	time = glutGet(GLUT_ELAPSED_TIME);
//	if (time - timebase > 1000) {
//		sprintf(buffer, "FPS:%4.2f %s",
//			frame*1000.0 / (time - timebase), mode);
//		timebase = time;
//		frame = 0;
//	}
//
//	glutSetWindowTitle(buffer);
//}
//
//void redraw()
//{
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();									// Reset The Current Modelview Matrix
//
//	gluLookAt(eye[0], eye[1], eye[2],
//		center[0], center[1], center[2],
//		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
//
//	if (bWire) {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//	else {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	}
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_pos[] = { 5, 5, 5, 1 };
//
//	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
//	glEnable(GL_LIGHT0);
//
//	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
//	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
//	glRotatef(-90, 1, 0, 0);
//	glScalef(0.2, 0.2, 0.2);
//	Draw_Scene();						// Draw triangle
//
//	if (bAnim) fRotate += 0.5f;
//
//	getFPS();
//	glutSwapBuffers();
//}
//
//void processHits(GLint hits, GLuint buffer[])
//{
//	unsigned int i, j;
//	GLuint names, *ptr;
//
//	printf("hits = %d\n", hits);
//	ptr = (GLuint *)buffer;
//	for (i = 0; i < hits; i++) { /*  for each hit  */
//		names = *ptr;
//		printf(" number of names for hit = %d\n", names); ptr++;
//		printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
//		printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;
//		printf("   the name is ");
//		for (j = 0; j < names; j++) {     /*  for each name */
//			printf("%d ", *ptr); ptr++;
//		}
//		printf("\n");
//	}
//}
//
//void gl_select(int x, int y)
//{
//	GLuint buff[64] = { 0 };
//	GLint hits, view[4];
//
//	glSelectBuffer(64, buff);
//
//	//retrieve info about the viewport
//	glGetIntegerv(GL_VIEWPORT, view);
//	//switch select mode
//	glRenderMode(GL_SELECT);
//
//
//	glInitNames();
//	glPushName(0);
//
//	//modify the vieving volume, restricting selection area around the cursor
//	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
//	glLoadIdentity();
//
//	//restrict the draw to an area around the cursor
//	gluPickMatrix(x, y, 0.1, 0.1, view);
//	gluPerspective(45.0f, (GLfloat)wWidth / (GLfloat)wHeight, 0.1f, 100.0f);
//
//	//pretend to draw the objects onto the screen
//	glMatrixMode(GL_MODELVIEW);
//	glutSwapBuffers();
//	Draw_Scene();
//
//	//restore the view
//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();
//
//	//get number of objects drawed in that area and return to render mode
//	hits = glRenderMode(GL_RENDER);
//
//	processHits(hits, buff);
//	if (hits >= 1)
//	{
//		int choose = buff[3];
//		int depth = buff[1];
//
//		for (int i = 0; i < hits; i++)
//		{
//			if (buff[i * 4 + 1] < (GLuint)depth)	//obtain selected object with minimum depth
//			{
//				choose = buff[i * 4 + 3];
//				depth = buff[i * 4 + 1];
//			}
//		}
//		changecolor[choose] = !changecolor[choose];
//	}
//
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void mousedw(int x, int y, int but)
//{
//	//printf("Mouse button %d pressed at %d %d\n", but, x, y);
//	gl_select(x, wHeight - y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
//	{
//		mousedw(x, y, button);
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//	glutInitWindowSize(480, 480);
//	int windowHandle = glutCreateWindow("Simple GLUT App");
//
//	glutDisplayFunc(redraw);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(key);
//	glutMouseFunc(mouseClick);
//	glutIdleFunc(idle);
//
//	glSelectBuffer(BUFSIZE, selectBuf);
//	memset(changecolor, 0, sizeof(changecolor));
//
//	glutMainLoop();
//	return 0;
//}
//
//
