#pragma once
//#include <gl/glew.h>

//#include <glut.h>
#include "./shared/gltools.h"	// OpenGL toolkit
#include "./shared/math3d.h"
#include "./shared/glframe.h"

#include <math.h>



class CSphereWorldShadow
{
public:
	CSphereWorldShadow();
	~CSphereWorldShadow();

	static void SetupRC();
	static void DrawGround(void);
	static void DrawInhabitants(GLint nShadow);
	static void RenderScene(void);
	static void SpecialKeys(int key, int x, int y);
	static void TimerFunction(int value);
	static void ChangeSize(int w, int h);
};

