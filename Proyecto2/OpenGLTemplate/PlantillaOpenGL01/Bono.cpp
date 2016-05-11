#include "Bono.h"


Bono::Bono(int t,bool d,float cx,float cy,int bi, int bj,float r,float v){
	tipo = t;
	dibujar = d;
	x = cx;
	y = cy;
	radio = r;
	velocidad = v;
	i = bi;
	j = bj;
}

void Bono::Dibujar(Bloque bloques[7][5]) {
	if (bloques[i][j].hp == 0)  {
		bloques[i][j].hp = -1;
		dibujar = true;
	}
	if (dibujar) {
		float PI = 3.14159265358979323846;
		glColor3f(1.0,0.4,0.0);
		// Circulo.
		glPushMatrix();
			float delta_theta = 0.01;
			y = y - velocidad;
			glTranslatef(x,y,0.0);
			glBegin(GL_LINE_LOOP);
				for (float a = 0; a < 2*PI; a+= delta_theta){
					glVertex3f(0.4*cos(a),0.4*sin(a),0);
				}
			glEnd();
		glPopMatrix();
		// Velocidad
		if (tipo == 1){
			glBegin(GL_TRIANGLES);
				glVertex2f(x-0.25,y+0.25);
				glVertex2f(x,y);
				glVertex2f(x-0.25,y-0.25);
			glEnd();
			glBegin(GL_TRIANGLES);
				glVertex2f(x+0.05,y+0.25);
				glVertex2f(x+0.3,y);
				glVertex2f(x+0.05,y-0.25);
			glEnd();
		}
		// Tamano de la plataforma
		else if (tipo == 2) {
			glBegin(GL_TRIANGLES);
				glVertex2f(x-0.30,y+0.15);
				glVertex2f(x-0.15,y);
				glVertex2f(x-0.30,y-0.15);
			glEnd();
			glBegin(GL_TRIANGLES);
				glVertex2f(x+0.30,y+0.15);
				glVertex2f(x+0.15,y);
				glVertex2f(x+0.30,y-0.15);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(x-0.14,y);
				glVertex2f(x+0.15,y);
			glEnd();
		}
	}
}
