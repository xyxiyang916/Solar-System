#include "Sphere.h"
#define PI 3.1415926
#define N 360
#define num 10

Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

static C3DSModel  draw3ds[num+1];  //有多少个模型，数组就定义多大


double Sphere::eyex = 200, Sphere::eyey = 50, Sphere::eyez = 0, Sphere::atx = 0, Sphere::aty = 0, Sphere::atz = 0;
double Sphere::rotatex, Sphere::rotatey;
char* Sphere::pTitle = "3D - Solar System";
static bool isLeftMouseDown, isRightMouseDown;

double axis = -1, xrot = 0, yrot = 0, zrot = 0;
double last_x = 0, last_y = 0;
//星球数据
//大小缩放
vector<double> scale = { 1, 0.2, 0.2, 0.3, 0.1, 0.25, 0.8, 0.6, 0.4, 0.4 };
//公转角度记录
vector<double> angle1 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//公转角度变化
vector<double> angle1Add = { 0, 1, 0.9, 0.8, 2, 0.6, 0.5, 0.4, 0.3, 0.2 };
//公转半径长度
vector<double> radius = { 0, 20, 30, 45, 5, 60, 80, 110, 140, 160 };
//自转角度记录
vector<double> angle2 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//自转角度变化
vector<double> angle2Add = { 0.5, 1, 0.5, 2, 2.5, 3, 3.5, 4, 4.5, 5 };


void Sphere::init()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_FOG);
	glClearColor(1, 1, 1, 0);

}


void Sphere::load()
{
	// 调入模型文件   一般设置init()中，例如
	draw3ds[0].Load("Sun.3ds");
	draw3ds[1].Load("Mercury.3ds");
	draw3ds[2].Load("Venus.3ds");
	draw3ds[3].Load("Earth.3ds");
	draw3ds[4].Load("Moon.3ds");
	draw3ds[5].Load("Mars.3ds");
	draw3ds[6].Load("Jupiter.3ds");
	draw3ds[7].Load("Saturn.3ds");
	draw3ds[8].Load("Uranus.3ds");
	draw3ds[9].Load("Neptune.3ds");
	draw3ds[10].Load("tip.3ds");

}

void Sphere::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);
	//glScalef(0.1, 0.1, 0.1);
	//draw3ds[6].Render();
	glPushMatrix();
	glTranslatef(eyex - 100, eyey + 10, eyez + 10);
	
	glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(0.1, 0.1, 0.1);
	draw3ds[10].Render();
	glPopMatrix();

	glColor3f(0.8, 0.8, 1); // 蓝色
	glBegin(GL_POLYGON);//绘制一个背景
	glVertex3f(-160.0, -30.0, 160.0);
	glVertex3f(-160.0, -30.0, -160.0);
	glVertex3f(160.0, -30.0, -160.0);
	glVertex3f(160.0, -30.0, 160.0);
	glEnd();

	glColor3f(1,0.5, 0.5);
	glBegin(GL_POLYGON);//绘制一个长方形
	glVertex3f(-160.0, -29.0, 16.0);
	glVertex3f(-160.0, -29.0, -16.0);
	glVertex3f(40.0, -29.0, -16.0);
	glVertex3f(40.0, -29.0, 16.0);
	glEnd();

	// 绘制箭头的箭头部分
	glBegin(GL_TRIANGLES);
	glVertex3f(80.0, -29.0, 0.0);
	glVertex3f(40.0, -29.0, -80.0);
	glVertex3f(40.0, -29.0, 80.0);
	glEnd();
	drawControl();
	axis = -1;
	glutSwapBuffers();
}

void Sphere::draw3DSModel(int i)
{
	
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	//draw3ds[i].Render();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void Sphere::drawControl()
{
	//绘制公转
	//保存矩阵
	//自转
	for (int i = 0; i < num; i++)
	{
		glPushMatrix();
		glTranslated(radius[i] * sin(rotatex + angle1[i] * 2 * PI / N), 0, 1.05*radius[i] * cos(rotatex + angle1[i] * 2 * PI / N) + sqrt(radius[i] * radius[i] * 0.1025));
		if (i == 3)
		{
			i++;
			glPushMatrix();
			glTranslated(radius[i] * sin(angle1[i] * 2 * PI / N), 0, 1.1*radius[i] * cos(angle1[i] * 2 * PI / N) + sqrt(radius[i] * radius[i] * 0.1025));
			glRotatef(angle2[i] + rotatex * 10, 0, 1, 0);
			glScalef(scale[i], scale[i], scale[i]);
			draw3ds[i].Render();
			glPopMatrix();
			i--;
		}
		glRotatef(angle2[i]+rotatex*10, 0, 1, 0);
		glScalef(scale[i], scale[i], scale[i]);
		draw3ds[i].Render();
		if (i == 3)
		{
			i++;
		}
		glPopMatrix();
	}
}


void Sphere::motion(int x, int y)
{
	if (isLeftMouseDown)
	{
		aty += 10.0f;
		glutPostRedisplay();
	}
	else if (isRightMouseDown)
	{
		aty -= 10.0f;
		glutPostRedisplay();
	}
}

void Sphere::mouseButton(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			isLeftMouseDown = true;
		}
		else if (state == GLUT_UP)
		{
			isLeftMouseDown = false;
		}
	}
	else if (btn == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			isRightMouseDown = true;
		}
		else if (state == GLUT_UP)
		{
			isRightMouseDown = false;
		}
	}
}

void Sphere::keyboard(unsigned char key, int x, int y)
{


	switch (key)
	{
	case 'd':
		eyez -= 10;
		atz -= 10;
		break;
	case 'a':
		eyez += 10;
		atz += 10;
		break;
	case 'w':
		//eyex-=5;
		eyex -= 10;
		atx -= 10;
		break;
	case 's':
		//eyex+=5;
		eyex += 10;
		atx += 10;
		break;
	case'q':
		eyey += 10;
		aty += 10;
		break;
	case'e':
		eyey -= 10;
		aty -= 10;
		break;
	}

	glutPostRedisplay();
}
void Sphere::Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, w / h, 2, 10000);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Sphere::myidle()
{

	//Sleep(100);
	//角度计算
	for (int i = 0; i < num; i++)
	{
		angle1[i] = angle1[i] + angle1Add[i];
		angle2[i] = angle2[i] + angle2Add[i];
	}
	glutPostRedisplay();
}
