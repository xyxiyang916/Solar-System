// win32Test.cpp : Defines the entry point for the application.
//

#include "SphereWorldShadow.h"
#include "ChancheTexture.h"
#include "TeapotFrog.h"
#include "TeaPotTexture.h"
#include "Sphere.h"

#define SOLARSYSTEM 5
#define TEAPOTFROG         1
#define TEAPOTTEXTURE  2
#define CHANCHETEXTURE         3
#define WORLDSHADOW  4


void(*pReshape)(int, int) = CTeapotFrog::Reshape;
//void(*pReshape)(int, int) = CSphereWorldShadow::ChangeSize;
void(*pInit)() = CTeapotFrog::init;
void(*Display)() = CTeapotFrog::Display;
void(*pMyidle)() = CChancheTexture::myidle;

GLint nSelected = SOLARSYSTEM;

void OnMenu(int value)
{
	
	switch (value)
	{
	case CHANCHETEXTURE :
		nSelected = CHANCHETEXTURE;
		break;
	case TEAPOTFROG :
		nSelected = TEAPOTFROG;
		break;
	case TEAPOTTEXTURE:
		nSelected = TEAPOTTEXTURE;
		break;

	case WORLDSHADOW:
		nSelected = WORLDSHADOW;
		break;
	case  SOLARSYSTEM:
		nSelected = SOLARSYSTEM;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}
void makeMenu()
{
	glutAddMenuEntry("1 �����", TEAPOTFROG);
	glutAddMenuEntry("2 ������Ӱ", WORLDSHADOW);
	glutAddMenuEntry("3 �������", TEAPOTTEXTURE);
	glutAddMenuEntry("4 ��������", CHANCHETEXTURE);
	glutAddMenuEntry("5 ̫��ϵ", SOLARSYSTEM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);  //ָ���˵��¼�������Ҽ���������
}




void onDisplay()
{
	switch (nSelected)
	{
	case CHANCHETEXTURE:

	
		CChancheTexture::init();
		CChancheTexture::Display();
		glutIdleFunc(CChancheTexture::myidle);
		break;
	case WORLDSHADOW:
		CSphereWorldShadow::SetupRC();
		CSphereWorldShadow::RenderScene();
		break;
	case TEAPOTFROG:
		CTeapotFrog::init();
		CTeapotFrog::Display();
		break;
	case TEAPOTTEXTURE:
		CTeaPotTexture::init();
		CTeaPotTexture::Display();
		break;
	case  SOLARSYSTEM:
		
		Sphere::init();
		Sphere::Display();
		glutIdleFunc(Sphere::myidle);
		glutKeyboardFunc(Sphere::keyboard);
		break;
	default:
		break;
	}

}


int main(int argc, char * argv[])
{

	glutInit(&argc, argv);    //��ʼ��GLUT�⣻
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //������ʾģʽ�������壬��ɫ���ͣ�
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateMenu(OnMenu);
	glutCreateWindow("��������Ӱ");  //�������ڡ���
	glutReshapeFunc(pReshape);
	glutDisplayFunc(onDisplay);  //���ڻ��Ƶ�ǰ���ڣ�
	CChancheTexture::load();
	Sphere::load();
	
	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	
	makeMenu();					//ʵ�����ɲ˵�
	//glutTimerFunc(33, CSphereWorldShadow::TimerFunction, 1);
	glutMainLoop();   //��ʾ��ʼ���г������ڳ���Ľ�β��

	return 0;
}
