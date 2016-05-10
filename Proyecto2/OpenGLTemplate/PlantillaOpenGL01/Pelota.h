#include <iostream>
#include <stdio.h>   
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <ctime>

#pragma once
class Pelota
{
public:
	float x,y;
	float radio;
	float velocidad;
	float angulo;
	Pelota(float cx = 0.0,float cy = 0.0,float r = 0.3,float v = 0.0,float a = 0.0);
	void Dibujar(clock_t t = 0.0);
};

