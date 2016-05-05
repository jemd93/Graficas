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
		glColor3f(rgb[0],rgb[1],rgb[2]);
		// CHEQUEAR CON IF EL HP A VER COMO SE DIBUJA. ESTE ES EL CASO BASICO
		glBegin(GL_LINE_LOOP);
			glVertex2f(x,y);
			glVertex2f(x+ancho,y);
			glVertex2f(x+ancho,y-alto);
			glVertex2f(x,y-alto);
		glEnd();
	glPopMatrix();
}

