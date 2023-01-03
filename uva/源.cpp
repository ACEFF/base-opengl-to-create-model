#include"objmodel.h"
#include"vertexdata.h"
#include<gl/glut.h>
#include"texture.h"
#include"camera.h"
#include"vector3f.h"
#include"mouse.h"
#include<iostream>
Camera camera;
int p1 = 0;
static float daox = 0.00;
static float daoy = daox * 7 / 4;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")

POINT originalPos;
bool bRotateView = false;
void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect;
	fAspect = (float)w / (float)h;
	gluPerspective(45.0, fAspect, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
//{
//	switch (button)
//	{
//	case GLUT_LEFT_BUTTON:
//		switch (action)
//		{
//		case GLUT_DOWN:originalPos.x = xMouse;
//			originalPos.y = yMouse;
//
//
//			ShowCursor(false);
//			bRotateView = true;
//			break;
//		case GLUT_UP:SetCursorPos(originalPos.x, originalPos.y);
//			ReleaseCapture();
//			ShowCursor(true);
//			bRotateView = false;
//			break;
//		}
//
//
//
//	}
//}
void mouse_button_callback(int button, int state, int x, int y) {
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
}




//void PassiveMouseMove(GLint xMouse, GLint yMouse)
//{
//
//	if (bRotateView)
//	{
//		POINT currentPos;
//		currentPos.x = xMouse;
//		currentPos.y = yMouse;
//
//		int deltaX = currentPos.x - originalPos.x;
//		int deltaY = currentPos.y - originalPos.y;
//		float angleRotatedByRight = (float)deltaY / 1000.0f;
//		float angleRotatedByUp = (float)deltaX / 1000.0f;
//		camera.Yaw(-angleRotatedByUp);
//		camera.Pitch(-angleRotatedByRight);
//		SetCursorPos(originalPos.x, originalPos.y);
//	}
//
//
//
//}
//void Key(unsigned char key, int x, int y)
//{
//
//	switch (key)
//	{
//	case 'A':
//		camera.mbMoveLeft = true;
//		break;
//	case'D':
//		camera.mbMoveRight = true;
//		break;
//	case'W':
//		camera.mbMoveForward = true;
//		break;
//	case'S':
//		camera.mbMoveBack = true;
//		break;
//	case'E':
//		camera.mbMoveLeft = false;
//		camera.mbMoveRight = false;
//		camera.mbMoveForward = false;
//		camera.mbMoveBack = false;
//	}
//
//}
void cursor_position_callback(int x, int y) {

	static int lastX = x, lastY = y;
	if (glutGet(GLUT_WINDOW_CURSOR) == GLUT_CURSOR_NONE) {
		int deltaX = x - lastX;
		int deltaY = y - lastY;
		camera.Yaw(-deltaX / 1000.0f);
		camera.Pitch(deltaY / 1000.0f);
		glutWarpPointer(lastX, lastY);
	}
	
		
	
}

void key_callback(unsigned char key, int x, int y) {
	static bool wireframe = false;
	wireframe = !wireframe;
	static bool TEXTURE = false;
	TEXTURE = !TEXTURE;
	/*static bool wireframe = false;
	wireframe = !wireframe;*/
	switch (key) {
	case 'a':
		camera.mbMoveLeft = true;
		break;
	case 'd':
		camera.mbMoveRight = true;
		break;
	case 'w':
		camera.mbMoveForward = true;
		break;
	case 's':
		camera.mbMoveBack = true;
		break;
	case 'i':
		

		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	
		break;
	case 'u':
		if (TEXTURE) {
			 glDisable(GL_TEXTURE_2D);
		}
		else {
			glEnable(GL_TEXTURE_2D);
		}
		
		
		break;
	
	case'g':
		if (TEXTURE) {
			
			glDisable(GL_LIGHTING);
		}
		else {
			glEnable(GL_LIGHTING);
		}
	case'k':if (daox >0.01)daox = daox - 0.01; /*std::cout << daox << "\n"; break;*/
	case'j':
		daox = daox + 0.01; /*std::cout << daox << "\n"; break;*/
	}
}

void key_up_callback(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		camera.mbMoveLeft = false;
		break;
	case 'd':
		camera.mbMoveRight = false;
		break;
	case 'w':
		camera.mbMoveForward = false;
		break;
	case 's':
		camera.mbMoveBack = false;
		break;


	}
}

Texture daoqiao;
Texture picture;
Texture picture2;
Texture picture3;
Texture phorse;
Texture pthorse;
ObjModel model;
ObjModel model1;
ObjModel model2;
ObjModel model3;
ObjModel horse;
ObjModel horse1;
ObjModel horsetail;

void Initial()
{
	daoqiao.Init("daoqiao.bmp");
	pthorse.Init("ming_horse_bumian_tail.bmp");
	phorse.Init("ming_horse_bumian.bmp");
	picture.Init("20220905140934.bmp");
	picture2.Init("vietnam_armor.bmp");
	picture3.Init("vietnam_hat.bmp");
	model.Init("xiuchundao.obj");
	model1.Init("xiuchundao_qiao.obj");
	model2.Init("vietnam_armor.obj");
	model3.Init("vietnam_helmet.obj");
	horse.Init("ming_horse_bumian.obj");
	horse1.Init("beifen_ming_horse_bumian.obj");
	horsetail.Init("ming_horse_bumian.1.obj");
	GLfloat light_postion[] = { 1,1,1,0 };
	GLfloat ambient[] = { 0.5,0.0,0.0,1 };
	GLfloat diffuse[] = { 1.0,0.5,0.0,1 };
	GLfloat specular[] = { 1.0,0.5,0.0,1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_postion);
	
	
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	/*GLfloat mat_ambient[] = { 0.0,0.3,0.4,0 };
	GLfloat mat_diffuse[] = { 0.6,0.4,0.4,0 };
	GLfloat mat_specular[] = { 0.2,0.2,0.5,0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_DEPTH_TEST);*/
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Display(void)
{
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;
	static float fElect1 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	
	
		
	
	glLoadIdentity();
	
	float currentTime =  timeGetTime() / 1000.0f;
	float timeElapse = currentTime - sTimeSinceStartUp;
	sTimeSinceStartUp = currentTime;
	

	camera.Update(timeElapse);
	
	fElect1 += 10.0f;
	if (fElect1 > 360.0f)
		fElect1 = 10.0f;
	
	
	
	glTranslatef(0, -2, 0);
	glPushMatrix();
	glTranslatef(2, 2, -2);
	glPushMatrix();
	/*glRotatef(fElect1, 0, 1.0f,0);*/
	daoy = daox * 7 / 4;
	glTranslatef(-daox, 0.0, -daoy);
	glBindTexture(GL_TEXTURE_2D, picture.mTextureID);
	model.Draw();
	glPopMatrix();
	glPushMatrix();
	
	
	glBindTexture(GL_TEXTURE_2D, daoqiao.mTextureID);
	model1.Draw();
	         
	glPopMatrix(); 
	glPopMatrix();
	//铠甲和头盔
	glPushMatrix();
	glTranslatef(0, 1, 0);
glPushMatrix();

	
	glBindTexture(GL_TEXTURE_2D, picture2.mTextureID);
	model2.Draw();

	glPopMatrix();
	glPushMatrix();

	
	
	glBindTexture(GL_TEXTURE_2D, picture3.mTextureID);
	model3.Draw();
	glPopMatrix();
	glPopMatrix();
	//马

	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, phorse.mTextureID);
	
	horse.Draw();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pthorse.mTextureID);
	horsetail.Draw();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, phorse.mTextureID);
	
	horse1.Draw();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pthorse.mTextureID);
	
	horsetail.Draw();
	glPopMatrix();
	glPopMatrix();



	glutSwapBuffers();
}
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}
void ProcessMenu(int value)
{
	switch (value)
	{
	case 1:glutPostRedisplay(); break;
	case 2: glutPostRedisplay(); break;
	case 3: glutPostRedisplay(); break;
	case 4: glutPostRedisplay(); break;

	default:break;

	}
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("分子动画示例");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
	glutMouseFunc(mouse_button_callback);
	glutMotionFunc(cursor_position_callback);
	glutKeyboardFunc(key_callback);
	glutKeyboardUpFunc(key_up_callback);
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("gong yu tian", 1);
	glutAddMenuEntry("peng zi si", 2);
	glutAddMenuEntry("wen bo fan", 3);
	glutAddMenuEntry("mi na", 4);
	glutAddMenuEntry("yang zhi han", 5);
	glutAddMenuEntry("li zhen", 6);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutTimerFunc(500, TimerFunc, 1);
	Initial();
	glutMainLoop();
	return 0;
}