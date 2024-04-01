#pragma once

#include <math.h>
#include "3ds.h"
#include <glut.h>

class CChancheTexture
{
public:
	CChancheTexture();
	~CChancheTexture();


	static C3DSModel  draw3ds[5];  //�ж��ٸ�ģ�ͣ�����Ͷ�����


	static float eyex , eyey, eyez, atx, aty, atz;
	static float rotatex, rotatey;
	static char* pTitle;


	static void init(void);
	static void Display(void);
	static void Keyboard(unsigned char key, int x, int y);
	static void specialkeyboard(int key, int x, int y);
	static void draw3DSModel();
	static void Reshape(GLsizei w, GLsizei h);
	static void myidle();
	static void load();


};

