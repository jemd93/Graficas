#include <GL\glew.h>
#include <GL\freeglut.h>
#include <math.h> 

#pragma once
static GLfloat defaultColor[]={1.0,0.0,0.0};
class Bloque
{
public:
	float x,y;
	float ancho;
	float alto;
	int tipo; // 1 o 2 segun el tipo del bloque.
	int hp; // 1 o 2 segun los golpes que toma romper el bloque.
	bool bonus; // True si el bloque tiene bonus.
	bool exploto;
	GLfloat rgb [3];
	Bloque(float cx = 0.0,float cy = 0.0,float a = 2.0,int t = 1, bool b = false,GLfloat colors[3] = defaultColor);
	void Dibujar();
};

