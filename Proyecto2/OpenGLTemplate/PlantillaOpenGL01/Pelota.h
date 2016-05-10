#include <iostream>
#include <stdio.h>   
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <ctime>
#include <math.h>
#include "Plataforma.h"
#include "Bloque.h"

#pragma once
class Pelota
{
public:
	float x,y;
	float radio;
	float velocidad;
	float angulo;
	int flagx;
	int flagy;
	Pelota(float cx = 0.0,float cy = 0.0,float r = 0.3,float v = 0.0,float a = 0.0);
	void Dibujar();
	void cheqColPared(float xmin = -50.0,float xmax = 50.0,float ymax = 50.0);
	void cheqColPlat(Plataforma plat = Plataforma());
	void cheqColBloques(Bloque bloques[7][5]);
};

