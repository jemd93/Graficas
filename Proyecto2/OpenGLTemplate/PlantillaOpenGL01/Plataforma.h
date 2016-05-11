#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Bono.h"


#pragma once
class Plataforma
{
public:
	float x,y; // Esquina superior izquierda
	float ancho; // Ancho de la plataforma
	float alto;
	float step;
	Plataforma(float cx = 0.0,float cy = 0.0,float a = 5.0);
	void Dibujar(void);
	int cheqColBonos(Bono bonos[6]);
};

