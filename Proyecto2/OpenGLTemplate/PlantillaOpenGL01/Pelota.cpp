#include "Pelota.h"


Pelota::Pelota(float cx,float cy,float r,float v,float a){
	x = cx;
	y = cy;
	radio = r;
	velocidad = v;
	angulo = a; 
}

void Pelota::Dibujar(clock_t t) {
	float PI = 3.14159265358979323846;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		float delta_theta = 0.01;
		if (velocidad > 0.0) {
			x = x+velocidad*cos(angulo);
			y = y+velocidad*sin(angulo);
		}
		/*printf("----Inicio------\n");
		printf("Angulo : %f",angulo);
		printf("x: %f | y: %f | compX: %f | compY: %f",x,y,cos(angulo),sin(angulo));
		printf("nuevaX: %f",x+velocidad*cos(angulo));
		printf("nuevaY: %f",y+velocidad*sin(angulo));
		printf("----Fin---------\n");*/
		glTranslatef(x,y,0.0);
		glBegin(GL_LINE_LOOP);
			for (float a = 0; a < 2*PI; a+= delta_theta){
				glVertex3f(radio*cos(a),radio*sin(a),0);
			}
		glEnd();
	glPopMatrix();
}

