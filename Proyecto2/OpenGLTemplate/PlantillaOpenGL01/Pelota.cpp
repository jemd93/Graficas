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
	if (x + radio >= xmax) {
		flagx = -flagx;
		x = xmax - radio;
	}
	if (x - radio <= xmin) {
		flagx = -flagx;
		x = xmin + radio;
	}
	if (y + radio >= ymax) {
		flagy = -flagy;
		y = ymax - radio;
	}
	x = x + flagx*velocidad*cos(angulo);
	y = y + flagy*velocidad*sin(angulo);
}

void Pelota::cheqColPlat(Plataforma plat) {

	/* Colision con la parte de arriba de la plataforma */

	if ((x >= plat.x) && (x <= plat.x + plat.ancho) && (y - radio <= plat.y) &&  (y - radio >= plat.y - plat.alto)) {
		printf("Estoy arriba");
		flagy = -flagy;
		y = plat.y + radio;
	}
	/* Colision con la parte izquierda de la plataforma */
	else if ((x + radio >= plat.x) && (x+radio < plat.x + plat.ancho) && (y <= plat.y) && (y >= plat.y-plat.alto)) {
		printf("Estoy del lado izquierdo");
		flagx = -flagx;
		x = plat.x - radio;
	}
	/* Colision con la parte derecha de la plataforma */
	else if ((x - radio <= plat.x + plat.ancho) && (x - radio > plat.x)&& (y <= plat.y) && (y >= plat.y-plat.alto)) {
		printf("Estoy del lado derecho");
		flagx = -flagx;
		x = plat.x + plat.ancho + radio;
	}
	/* Colision con la esquina superior izquierda */
	else if (pow((plat.x-x),2) + pow(plat.y-y,2) <= pow(radio,2)){
		printf("Estoy en la esquina izquierda");
		flagy = -flagy;
		y = y + radio;
	} 
	/* Colision con la esquina superior derecha */
	else if (pow((plat.x+plat.ancho-x),2) + pow(plat.y-y,2) <= pow(radio,2)){ 
		printf("Estoy en la esquina derecha");
		flagy = -flagy;
		y = y + radio;
	}
	/* Colision con la esquina inferior derecha */
	else if (pow((plat.x+plat.ancho-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)){ 
		flagx = -flagx;
		x = x+radio;
	}
	/* Colision con la esquina inferior izquierda */
	else if (pow((plat.x-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)){ 
		flagx = -flagx;
		x = x+radio;
	}
	/*if((pow((plat.x-x),2) + pow(plat.y-plat.alto-y,2) <= pow(radio,2)) &&
		(pow((plat.x-x),2) + pow(plat.y-y,2) <= pow(radio,2))){
			printf("Estoy dentro del circulo");
	}*/
	x = x + flagx*velocidad*cos(angulo);
	y = y + flagy*velocidad*sin(angulo);
}

void Pelota::cheqColBloques(Bloque bloques [7][5]) {
	Bloque bloqueAct;
	for (int i = 0 ; i < 7; i++) {
		for (int j = 0 ; j < 5; j++){
			bloqueAct = bloques[i][j];
			if (bloqueAct.hp != 0) {
				// Abajo
				if ((x >= bloqueAct.x) && (x <= bloqueAct.x + bloqueAct.ancho) && 
					(y + radio >= bloqueAct.y - bloqueAct.alto) &&  (y + radio <= bloqueAct.y)) {
					flagy = -flagy;
					bloques[i][j].hp--;
					y = bloqueAct.y - bloqueAct.alto - radio;
				} 
				// Arriba
				else if ((x >= bloqueAct.x) && (x <= bloqueAct.x + bloqueAct.ancho) && 
					(y - radio <= bloqueAct.y) &&  (y - radio >= bloqueAct.y - bloqueAct.alto)) {
					flagy = -flagy;
					bloques[i][j].hp--;
					y = bloqueAct.y + radio;
				}
				// Izquierdo
				else if ((x + radio >= bloqueAct.x) && (x+radio < bloqueAct.x + bloqueAct.ancho) 
					&& (y <= bloqueAct.y) && (y >= bloqueAct.y-bloqueAct.alto)) {
					flagx = -flagx;
					bloques[i][j].hp--;
					x = bloqueAct.x - radio;
				}
				// Derecho
				else if ((x - radio <= bloqueAct.x + bloqueAct.ancho) 
					&& (x - radio > bloqueAct.x)&& (y <= bloqueAct.y) 
					&& (y >= bloqueAct.y-bloqueAct.alto)) {
					flagx = -flagx;
					bloques[i][j].hp--;
					x = bloqueAct.x + bloqueAct.ancho + radio;
				}
				/* Colision con la esquina superior izquierda */
				else if (pow((bloqueAct.x-x),2) + pow(bloqueAct.y-y,2) <= pow(radio,2)){
					flagy = -flagy;
					bloques[i][j].hp--;
					y = y + radio;
				} 
				/* Colision con la esquina superior derecha */
				else if (pow((bloqueAct.x+bloqueAct.ancho-x),2) + pow(bloqueAct.y-y,2) <= pow(radio,2)){ 
					flagy = -flagy;
					bloques[i][j].hp--;
					y = y + radio;
				}
				// Esquina inferior derecha
				else if (pow((bloqueAct.x+bloqueAct.ancho-x),2) + pow(bloqueAct.y-bloqueAct.alto-y,2) <= pow(radio,2)){ 
					flagx = -flagx;
					bloques[i][j].hp--;
					x = x+radio;
				}
				/* Colision con la esquina inferior izquierda */
				else if (pow((bloqueAct.x-x),2) + pow(bloqueAct.y-bloqueAct.alto-y,2) <= pow(radio,2)){ 
					flagx = -flagx;
					bloques[i][j].hp--;
					x = x+radio;
				}
			}
		}
	}
	x = x + flagx*velocidad*cos(angulo);
	y = y + flagy*velocidad*sin(angulo);
}

