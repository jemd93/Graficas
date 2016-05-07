#include <iostream>
#include <stdio.h>   
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Plataforma.h"
#include "Bloque.h"
#include "Pelota.h"

using namespace std;

#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	10.0f
#define DEF_floorGridZSteps	10.0f

// Arreglos RGB para colores.
static GLfloat naranja[]={1.0,0.4,0.0};
static GLfloat amarillo[]={1.0,1.0,0.0};
static GLfloat rojo[]={1.0,0.0,0.0};
static GLfloat azul[]={0.0,0.0,1.0};
static GLfloat blanco[]={1.0,1.0,1.0};
static GLfloat verde[]={0.0,1.0,0.0};

Plataforma plat;
Pelota pelota;
Bloque bloques[7][5];
int estadoJuego = 1;
int stepAngulo = 5;

// Función para verificar si un bloque es especial.
int esEspecial(int id,int especiales[5]){
	for (int i = 0 ;i < 5;i++){
		if (especiales[i] == id) {
			return 2;
		}
	}
	return 1;
}

// Función para verificar si un bloque es bonus.
bool esBonus(int id,int bonuses[6]){
	for (int i = 0 ;i < 6;i++){
		if (bonuses[i] == id) {
			return true;
		}
	}
	return false;
}

// Función de inicialización
void inicializar() {
	plat = Plataforma(-2.0,-8.0,4.0);

	pelota = Pelota(0.0,-7.7,0.3,0.0,0.0);

	int id = 0;
	int especiales[5];
	int bonuses[6];

	for (int i = 0; i < 5;i++){
		especiales[i] = rand() % 35; 
		bonuses[i] = rand() % 35; 
	}
	bonuses[5] = rand() % 35;

	float x = -10.0;
	float y = 8.0;
	// Inicializar bloques
	for (int i = 0;i < 7;i++){

		for (int j = 0;j < 5;j++) {
			bloques[i][j] = Bloque(x+2.0,y+bloques[i][j].alto,2.0,esEspecial(id,especiales),esBonus(id,bonuses),
								   (esEspecial(id,especiales) == 2 ? amarillo : rojo));
			x = x+2+1.5;
			id++;
		}
		x = -10.0;
		y = y-bloques[i][0].alto-0.75;
		id++;
	}
}

void changeViewport(int w, int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectratio;
	aspectratio = (float) w / (float) h;

	if (w <= h) 
		glOrtho(-10,10,-10/aspectratio,10/aspectratio, 1.0,-1.0);
	else
		glOrtho(-10*aspectratio,10*aspectratio,-10,10,1.0,-1.0);
}

// Función para dibujar el marco verde del juego.
void dibujarMarco() {
	glPushMatrix();
		glLineWidth(1.0);
		glColor3f(0.0,1.0,0.0);
		// Barra de arriba
		glBegin(GL_LINE_LOOP);
			glVertex2f(-9.0,9.5);
			glVertex2f(9.0,9.5);
			glVertex2f(9.0,9.0);
			glVertex2f(-9.0,9.0);
		glEnd();
		// Barra de la derecha
		glBegin(GL_LINE_LOOP);
			glVertex2f(9.0,9.5);
			glVertex2f(9.5,9.5);
			glVertex2f(9.5,-9.0);
			glVertex2f(9.0,-9.0);
		glEnd();
		// Barra de la izquierda
		glBegin(GL_LINE_LOOP);
			glVertex2f(-9.0,9.5);
			glVertex2f(-9.5,9.5);
			glVertex2f(-9.5,-9.0);
			glVertex2f(-9.0,-9.0);
		glEnd();

	glPopMatrix();
}

//Función para dibujar los bloques activos del juego
void dibujarBloques() {
	for (int i = 0; i < 7; i++){
		for (int j = 0;j < 5;j++){
			if (bloques[i][j].hp != 0) //Solo dibuja los bloques activos
				bloques[i][j].Dibujar();
		}
	}
}

void dibujarDireccion(){
	glLineWidth(2.0);
	glColor3f(0.5,0.0,1.0);
	glPushMatrix();
		//Roto respecto al centro de la pelota
		glTranslatef(pelota.x,pelota.y,0);
		glRotatef(pelota.angulo,0.0,0.0,1);
		glTranslatef(-pelota.x,-pelota.y,0);

		glBegin(GL_LINES);
			glVertex2f(pelota.x,pelota.y+pelota.radio);
			glVertex2f(pelota.x,pelota.y+pelota.radio+2);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2f(pelota.x-0.3,pelota.y+pelota.radio+1.5);
			glVertex2f(pelota.x,pelota.y+pelota.radio+2);
			glVertex2f(pelota.x+0.3,pelota.y+pelota.radio+1.5);
		glEnd();
	glPopMatrix();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;
	
	/* Render Grid */
	/*glPushMatrix();
    glColor3f( 0.0f, 0.7f, 0.7f );
    glBegin( GL_LINES );
    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
	xLocal = DEF_floorGridScale * loopX;
	glVertex3f( xLocal, -zExtent, 0.0f );
	glVertex3f( xLocal, zExtent,  0.0f );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
	zLocal = DEF_floorGridScale * loopZ;
	glVertex3f( -xExtent, zLocal, 0.0f );
	glVertex3f(  xExtent, zLocal, 0.0f );
	}
    glEnd();
    glPopMatrix();*/
	
	// Dibujar el marco verde.
	dibujarMarco();

	// Dibujar plataforma.
	plat.Dibujar();

	// Dibujar la pelota.
	pelota.Dibujar();

	// Dibujar los bloques.
	dibujarBloques();

	//Dibuja la barra inicial para el ángulo de lanzamiento
	if (estadoJuego == 1){
		dibujarDireccion();
	}

	glutSwapBuffers();

}

void teclado(unsigned char key, int x, int y) {
	if (key == 'a' || key == 'A') {
		if (estadoJuego == 1){
			if (pelota.angulo + stepAngulo <= 45)
				pelota.angulo = pelota.angulo + stepAngulo;
		} else {
			if (plat.x != -9.0)
				plat.x = plat.x-plat.step;
		}
	}
	if (key == 'd' || key == 'D') {
		if (estadoJuego == 1){
			if (pelota.angulo - stepAngulo >= -45)
				pelota.angulo = pelota.angulo - stepAngulo;
		} else {
			if (plat.x+plat.ancho != 9.0)
				plat.x = plat.x+plat.step;
		}
		
	}
	if ((key == ' ') && (estadoJuego == 1)){ //Caso de barra espaciadora
		//Aquí va lo de lanzar la pelota
		printf("%s","HOLA");
	}
}

void flechas(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT:
		if (estadoJuego == 1){
			if (pelota.angulo + stepAngulo <= 45)
				pelota.angulo = pelota.angulo + stepAngulo;
		} else {
			if (plat.x != -9.0)
				plat.x = plat.x-plat.step;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (estadoJuego == 1){
			if(pelota.angulo - stepAngulo >= -45)
				pelota.angulo = pelota.angulo - stepAngulo;
		} else{
			if (plat.x+plat.ancho != 9.0)
				plat.x = plat.x+plat.step;
		}
		
		break;
	default:
		break;
	}
}

void actualizar() {
	glutPostRedisplay();
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Opengl");

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(flechas);
	glutIdleFunc(actualizar);

	// Inicializa los datos.
	inicializar();
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	

	glutMainLoop();
	return 0;

}