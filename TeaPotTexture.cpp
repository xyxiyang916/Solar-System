#include "TeaPotTexture.h"
#define stripeImageWidth 32

CTeaPotTexture::CTeaPotTexture()
{
}


CTeaPotTexture::~CTeaPotTexture()
{
}


materialStruct1 CTeaPotTexture::redPlasticMaterials = {
	{ 0.1, 0.1, 0.1, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	32.0
};

lightingStruct1 CTeaPotTexture::whiteLighting = {
	{ 0.1, 0.1, 0.1, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};

materialStruct1 *CTeaPotTexture::currentMaterials;
lightingStruct1 *CTeaPotTexture::currentLighting;


GLubyte stripeImage[4 * stripeImageWidth];

void makeStripeImage(void)
{
	int j;
	for (j = 0; j < stripeImageWidth; j++) {
		stripeImage[4 * j] = (GLubyte)((j <= 4) ? 255 : 0);
		stripeImage[4 * j + 1] = (GLubyte)((j>4) ? 255 : 0);
		stripeImage[4 * j + 2] = (GLubyte)0;
		stripeImage[4 * j + 3] = (GLubyte)255;
	}
}

static GLfloat xequalzero[] = { 1.0, 0.0, 0.0, 0.0 };
static GLfloat slanted[] = { 1.0, 1.0, 1.0, 0.0 };
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;


void CTeaPotTexture::Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	makeStripeImage();//构造纹理图像
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_TEXTURE_1D);//启用1D纹理映射
	glEnable(GL_TEXTURE_GEN_S);//启用纹理坐标S的自动生成功能

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);//载入图像到一个一维纹理

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);//纹理卷绕模式

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理放大或缩小时候滤波模式
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//纹理颜色与几何对象颜色的融合模式

	currentCoeff = xequalzero;
	currentGenMode = GL_OBJECT_LINEAR;
	currentPlane = GL_OBJECT_PLANE;
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
	glTexGenfv(GL_S, currentPlane, currentCoeff);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	currentLighting = &whiteLighting;
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//setting color of ambient light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//setting color of diffuse light
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//setting color of specular light

	currentMaterials = &redPlasticMaterials;
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);//setting ambient reflection attributes of 3D object
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);//setting diffuse reflection attributes of 3D object
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);//setting specular reflection attributions of 3D object
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);//setting shininess coefficeint of specular reflection

	//glMaterialf(GL_FRONT, GL_SHININESS, 164.0);

	glutSolidTeapot(2.0);

	glDisable(GL_TEXTURE_1D);//启用1D纹理映射
	glDisable(GL_TEXTURE_GEN_S);//启用纹理坐标S的自动生成功能
	glPopMatrix();
	glutSwapBuffers();

}



void CTeaPotTexture::init()
{

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);//启用第0个光源
	glDisable(GL_FOG);//启用雾效果模拟
}

