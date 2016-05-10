#include "Pelota.h"

Pelota::Pelota(float cx,float cy,float r,float v,float a){
	x = cx;
	y = cy;
	radio = r;
	angulo = a; 
	velocidad = v;
	flagx = 1;
	flagy = 1;
}

void Pelota::Dibujar() {
	float PI = 3.14159265358979323846;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		float delta_theta = 0.01;
		if (velocidad > 0.0) {
			x = x+flagx*velocidad*cos(angulo);
			y = y+flagy*velocidad*sin(angulo);
		}
		glTranslatef(x,y,0.0);
		glBegin(GL_LINE_LOOP);
			for (float a = 0; a < 2*PI; a+= delta_theta){
				glVertex3f(radio*cos(a),radio*sin(a),0);
			}
		glEnd();
	glPopMatrix();
}

void Pelota::cheqColPared(float xmin,float xmax,float ymax) {
	if ((x + radio >= xmax) || (x - radio <= xmin)) {
		flagx = -flagx;
	}
	if (y + radio >= ymax) {
		flagy = -flagy;
	}
	x = x + flagx*velocidad*cos(angulo);
	y = y + flagy*velocidad*sin(angulo);
}

void Pelota::cheqColPlat(Plataforma plat) {

	/* Colision con la parte de arriba de la plataforma */

	if ((x >= plat.x) && (x <= plat.x + plat.ancho) && (y - radio <= plat.y)) {
		printf("Estoy arriba");
		flagy = -flagy;
	}
	/* Colision con la parte izquierda de la plataforma */
	else if ((x + radio >= plat.x) && (y <= plat.y) && (y >= plat.y-plat.alto)) {
		printf("Estoy del lado izquierdo");
		flagx = -flagx;
	}
	/* Colision con la parte derecha de la plataforma */
	else if ((x - radio <= plat.x + plat.ancho) && (y <= plat.y) && (y >= plat.y-plat.alto)) {
		printf("Estoy del lado derecho");
		flagx = -flagx;
	}
	/* Colision con la esquina superior izquierda */
	else if (pow((plat.x-x),2) + pow(plat.y-y,2) <= pow(radio,2)){
		printf("Estoy en la esquina izquierda");
		flagy = -flagy;
	} 
	/* Colision con la esquina superior derecha */
	else if (pow((plat.x+plat.ancho-x),2) + pow(plat.y-y,2) <= pow(radio,2)){ 
		printf("Estoy en la esquina derecha");
		flagy = -flagy;
	}
	/* Colision con la esquina inferior derecha */
	else if (pow((plat.x+plat.ancho-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)){ 
		flagx = -flagx;
	}
	/* Colision con la esquina inferior izquierda */
	else if (pow((plat.x-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)){ 
		flagx = -flagx;
	}

	if((pow((plat.x-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)) &&
		(pow((plat.x-x),2) + pow(plat.y-y,2) <= pow(radio,2))){
			printf("Estoy dentro del circulo");
	}
	x = x + flagx*velocidad*cos(angulo);
	y = y + flagy*velocidad*sin(angulo);
}

void Pelota::cheqColBloques(Bloque bloques [7][5]) {
	for (int i = 0 ; i < 7; i++) {
		for (int j = 0 ; j < 5; j++){
			if (bloques[i][j].hp != 0) {
				if ((x + radio >= bloques[i][j].x) && (x + radio <= bloques[i][j].x + bloques[i][j].ancho)) {
					if  ((y + radio >= bloques[i][j].y - bloques[i][j].alto) || (y - radio >= bloques[i][j].y)){
						flagy = -flagy;
						bloques[i][j].hp--;
					}
				}
			}
			/*if (pow((bloques[i][j].x-x),2) + pow(bloques[i][j].y-y,2) <= pow(radio,2))*/
		}
	}
}

