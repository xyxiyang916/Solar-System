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
	glutAddMenuEntry("1 茶壶雾化", TEAPOTFROG);
	glutAddMenuEntry("2 世界阴影", WORLDSHADOW);
	glutAddMenuEntry("3 茶壶纹理", TEAPOTTEXTURE);
	glutAddMenuEntry("4 铲车纹理", CHANCHETEXTURE);
	glutAddMenuEntry("5 太阳系", SOLARSYSTEM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);  //指定菜单事件由鼠标右键单击产生
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

	glutInit(&argc, argv);    //初始化GLUT库；
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateMenu(OnMenu);
	glutCreateWindow("纹理雾化阴影");  //创建窗口”；
	glutReshapeFunc(pReshape);
	glutDisplayFunc(onDisplay);  //用于绘制当前窗口；
	CChancheTexture::load();
	Sphere::load();
	
	glEnable(GL_DEPTH_TEST); // 启用深度测试
	
	makeMenu();					//实际生成菜单
	//glutTimerFunc(33, CSphereWorldShadow::TimerFunction, 1);
	glutMainLoop();   //表示开始运行程序，用于程序的结尾；

	return 0;
}
