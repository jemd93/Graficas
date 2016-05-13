#include "Plataforma.h"


Plataforma::Plataforma(float cx,float cy,float a){
	x = cx;
	y = cy;
	ancho = a;
	alto = 0.5;
	step = 1;
}

void Plataforma::Dibujar(void) {
	glPushMatrix();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x,y);
			glVertex2f(x+ancho,y);
			glVertex2f(x+ancho,y-alto);
			glVertex2f(x,y-alto);
		glEnd();
	glPopMatrix();
}

int Plataforma::cheqColBonos(Bono bonos[6]){
	for (int i = 0; i < 6;i++){
		if (bonos[i].dibujar) {
			if ((bonos[i].x >= x) && (bonos[i].x <= x+ancho) 
				&& (bonos[i].y-bonos[i].radio <= y) && (bonos[i].y+bonos[i].radio >= y - alto) ) {
				bonos[i].dibujar = false;
				return bonos[i].tipo;
			}
		}
	}
	return 0;
}