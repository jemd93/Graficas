#include "Bloque.h"


Bloque::Bloque(float cx,float cy,float a,int t, bool b, GLfloat colors[3]){
	x = cx;
	y = cy;
	ancho = a;
	alto = 0.5;
	tipo = t;
	hp = t;
	bonus = b;
	for (int i = 0; i < 3; i++) {
		rgb[i] = colors[i];
	}
}

void Bloque::Dibujar() {
	glPushMatrix();
		//Caso bloque especial ya golpeado
		if (hp == 1 && tipo == 2){ 
			glColor3f(1.0,0.5,0.0);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x,y);
				glVertex2f(x+ancho/2,y);
				glVertex2f(x+ancho/2-0.25,y-0.15);
				glVertex2f(x+ancho/2+0.15,y-0.4);
				glVertex2f(x+ancho/2,y-alto);
				glVertex2f(x,y-alto);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex2f(x+ancho/2+0.1,y);
				glVertex2f(x+ancho,y);
				glVertex2f(x+ancho,y-alto);
				glVertex2f(x+ancho/2+0.15,y-alto);
				glVertex2f(x+ancho/2+0.25,y-0.4);
				glVertex2f(x+ancho/2-0.1,y-0.15);
			glEnd();
		} else {
			glColor3f(rgb[0],rgb[1],rgb[2]);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x,y);
				glVertex2f(x+ancho,y);
				glVertex2f(x+ancho,y-alto);
				glVertex2f(x,y-alto);
			glEnd();
		}
	glPopMatrix();
}

