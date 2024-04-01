#pragma once

#include <math.h>
#include "3ds.h"
#include <glut.h>

class Sphere
{
public:
	Sphere();
	~Sphere();




	static double eyex, eyey, eyez, atx, aty, atz;
	static double rotatex, rotatey;
	static char* pTitle;

	static void init();
	static void Display(void);
	static void motion(int x, int y);
	static void mouseButton(int btn, int state, int x, int y);
	static void keyboard(unsigned char key, int x, int y);
	static void specialkeyboard(int key, int x, int y);
	static void draw3DSModel(int i);
	static void drawControl();
	static void Reshape(GLsizei w, GLsizei h);
	static void myidle();
	static void load();


};

