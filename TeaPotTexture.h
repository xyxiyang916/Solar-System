#pragma once

#include <glut.h>


typedef struct materialStruct1 {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct1;

typedef struct lightingStruct1 {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct1;



class CTeaPotTexture
{
public:
	CTeaPotTexture();
	~CTeaPotTexture();

	static void init(void);
	static void Display(void);

	static materialStruct1 redPlasticMaterials;

	static lightingStruct1 whiteLighting;


	static materialStruct1 *currentMaterials;
	static lightingStruct1 *currentLighting;

};

