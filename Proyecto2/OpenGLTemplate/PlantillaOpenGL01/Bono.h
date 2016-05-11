#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdio.h>   
#include <stdlib.h>
#include <math.h>
#include "Bloque.h"

#pragma once
class Bono
{
public:
	int tipo;
	float x,y;
	float radio;
	float velocidad;
	bool dibujar;
	int i,j;
	Bono(int t = 1,bool d = false,float cx = 0.0,float cy = 0.0,int bi = 0,int bj = 0,float r = 0.4,float v = 0.008);
	void Dibujar(Bloque bloques[7][5]);
};

