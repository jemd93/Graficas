#include "Pelota.h"


Pelota::Pelota(float cx,float cy,float r,float v,float a){
	x = cx;
	y = cy;
	radio = r;
	velocidad = v;
	angulo = a;
}

void Pelota::Dibujar() {
	float PI = 3.14159265358979323846;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		float delta_theta = 0.01;
		glBegin(GL_LINE_LOOP);
			for (float a = 0; a < 2*PI; a+= delta_theta){
				glVertex3f(radio*cos(a)+x,radio*sin(a)+y,0);
			}
		glEnd();
	glPopMatrix();
}

