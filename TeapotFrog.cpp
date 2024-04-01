#include "TeapotFrog.h"


typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

static GLfloat light0_pos[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat atmoColor[4] = { 0.8, 0.8, 1.0, 1.0 };//雾的色彩
static GLfloat theta = 0.0;

static materialStruct *currentMaterials;
static lightingStruct *currentLighting;




CTeapotFrog::CTeapotFrog()
{
}


CTeapotFrog::~CTeapotFrog()
{
}




materialStruct redPlasticMaterials = {
	{ 0.3, 0.0, 0.0, 1.0 },
	{ 0.6, 0.0, 0.0, 1.0 },
	{ 0.8, 0.6, 0.6, 1.0 },
	32.0
};

lightingStruct whiteLighting = {
	{ 0.1, 0.1, 0.1, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};



void CTeapotFrog::Display(void)
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);//setting position of light source
	//此时，光源位置是在观察坐标系中定义，观察坐标系的(0.0,0.0,0.0)正好是世界坐标系的(4.0,4.0,4.0)
	//而(4.0,4.0,4.0)也是观察点的位置
	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//glRotatef(theta, 0.0, 1.0, 0.0);

	glutSolidTeapot(2.0);//glut object,自动计算每个顶点的法向量
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -4);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -8.0);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -13.0);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	
	glBegin(GL_POLYGON);//绘制一个背景
	glVertex3f(-160.0, -18.0, 160.0);
	glVertex3f(-160.0, -18.0, -160.0);
	glVertex3f(160.0, -18.0, -160.0);
	glVertex3f(160.0, -18.0, 160.0);
	glEnd();
	
	glutSwapBuffers();
}

//void mouseMotion(int x, int y)
//{
//	theta += 0.1;
//	if (theta >= 360.0)
//		theta = 0.0;
//	glutPostRedisplay();
//}

void CTeapotFrog::Reshape(int w, int h)
{
	/*glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -10.0, 100.0);
	else
		glOrtho(-4.0 * (GLfloat)w / (GLfloat)h, 4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -10.0, 100.0);*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w / h, 2, 1000);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void CTeapotFrog::init()
{
	//启用光照计算将意味着对象的色彩将由光源和材质属性来决定，而非glColor*函数
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//启用第0个光源
	//glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);

	glClearColor(1, 1, 1, 0);
	currentLighting = &whiteLighting;
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//setting color of ambient light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//setting color of diffuse light
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//setting color of specular light

	currentMaterials = &redPlasticMaterials;
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);//setting ambient reflection attributes of 3D object
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);//setting diffuse reflection attributes of 3D object
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);//setting specular reflection attributions of 3D object
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);//setting shininess coefficeint of specular reflection

	glEnable(GL_FOG);//启用雾效果模拟
	glFogfv(GL_FOG_COLOR, atmoColor);//设定雾的色彩
	glFogi(GL_FOG_MODE, GL_EXP);//设定雾衰减模型
	glFogf(GL_FOG_DENSITY, 0.05);//试着使用不同的雾的密度，值越大，生成的雾越浓

	

}
