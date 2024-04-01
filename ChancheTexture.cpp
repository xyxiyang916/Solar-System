#include "ChancheTexture.h"


CChancheTexture::CChancheTexture()
{
}


CChancheTexture::~CChancheTexture()
{
}

C3DSModel  CChancheTexture::draw3ds[5];  //有多少个模型，数组就定义多大


float CChancheTexture::eyex = 0, CChancheTexture::eyey = 0, CChancheTexture::eyez = 100, CChancheTexture::atx = 0, CChancheTexture::aty = 0, CChancheTexture::atz = 0;
float CChancheTexture::rotatex, CChancheTexture::rotatey;
char* CChancheTexture::pTitle = "3D - chanche texture";



void CChancheTexture::init()
{


	// 调入模型文件   一般设置init()中，例如
	//draw3ds[0].Load("chanche.3ds");
	glClearColor(1, 1, 1, 0);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);//启用第0个光源
	glDisable(GL_FOG);//启用雾效果模拟
	
	glEnable(GL_DEPTH_TEST); // 启用深度测试

}

void CChancheTexture::load()
{
	// 调入模型文件   一般设置init()中，例如
	draw3ds[0].Load("chanche.3ds");

}

void CChancheTexture::Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);

	//glRotatef(rotatex, 1, 0, 0);
	glRotatef(rotatey, 0, 1, 0);

	glScalef(0.4, 0.4, 0.4);
	draw3DSModel();  //绘制玩物	

	glutSwapBuffers();
}

void CChancheTexture::draw3DSModel()
{

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	draw3ds[0].Render();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}



void CChancheTexture::specialkeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		eyey += 5;  aty += 5;
	}
	if (key == GLUT_KEY_DOWN)
	{
		eyey -= 5;  aty -= 5;
	}
	glutPostRedisplay();

}

void CChancheTexture::Keyboard(unsigned char key, int x, int y)
{


	switch (key)
	{
	case 'w':
		eyez -= 5;
		atz -= 5;
		break;
	case 's':
		eyez += 5;
		atz += 5;
		break;
	case 'a':
		//eyex-=5;
		eyex -= 5;
		atx -= 5;
		break;
	case 'd':
		//eyex+=5;
		eyex += 5;
		atx += 5;

		break;

	}

	glutPostRedisplay();
}
void CChancheTexture::Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, w / h, 2, 2500);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CChancheTexture::myidle()
{

	Sleep(100);

	rotatex+=2;
	rotatey += 2;


	glutPostRedisplay();


}
