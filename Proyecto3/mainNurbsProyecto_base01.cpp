#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0


GLUnurbsObj *theNurb;
float static PI = 3.141592653589;
GLfloat ctlpoints[21][21][3];
GLfloat knots[25];

GLfloat L1, L2, A1, A2, S1, S2, D1[2], D2[2];

int olaActual;
int val; // Para controlar la animación
float tiempo;

void ejesCoordenada() {
	
	glLineWidth(2.5);
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(0,10);
		glVertex2f(0,-10);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(10,0);
		glVertex2f(-10,0);
	glEnd();

	glLineWidth(1.5);
	int i;
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		for(i = -10; i <=10; i++){
			if (i!=0) {		
				if ((i%2)==0){	
					glVertex2f(i,0.4);
					glVertex2f(i,-0.4);

					glVertex2f(0.4,i);
					glVertex2f(-0.4,i);
				}else{
					glVertex2f(i,0.2);
					glVertex2f(i,-0.2);

					glVertex2f(0.2,i);
					glVertex2f(-0.2,i);

				}
			}
		}
		
	glEnd();

	glLineWidth(1.0);
}

void changeViewport(int w, int h) {
	
	float aspectratio;

	if (h==0)
		h=1;

	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode (GL_MODELVIEW);

}

float H(int x,int z,float t) {
	/* Normalización del vector D de la ola 1 */
	float D1xNorm = D1[0]/sqrt(D1[0]*D1[0]+D1[1]*D1[1]);
	float D1yNorm = D1[1]/sqrt(D1[0]*D1[0]+D1[1]*D1[1]);
	/* Normalización del vector D de la ola 2 */
	float D2xNorm = D2[0]/sqrt(D2[0]*D2[0]+D2[1]*D2[1]);
	float D2yNorm = D2[1]/sqrt(D2[0]*D2[0]+D2[1]*D2[1]);

	float w1 = 2*PI/L1;
	float ola1 = A1*sin((D1xNorm*x + D1yNorm*z)*w1 + t*w1*S1);
	float w2 = 2*PI/L2;
	float ola2 = A2*sin((D2xNorm*x+D2yNorm*z)*w2 + t*w2*S2);

	return ola1 + ola2;
}

void generarOleaje(){
	for (int i=0; i < 21; i++){
		for (int j=0; j < 21; j++){
			ctlpoints[i][j][1] = H(ctlpoints[i][j][0], ctlpoints[i][j][2],tiempo);
		}
	}
}

void animacion(int value) {
	
	if (val == 1){
		generarOleaje();
		tiempo += 0.1;
		glutTimerFunc(10,animacion,1);
		glutPostRedisplay();
	}
	
}

void init_surface() {
	/* Inicialización de los puntos de control */
	int x = 10;
	int z = 10;
	for (int i = 0; i <21; i++) {
		x = 10;
		for (int j = 0; j < 21; j++) {
			
			ctlpoints[i][j][0] = x;
			ctlpoints[i][j][1] = 0;
			ctlpoints[i][j][2] = z;
			x--;
		}
		z--;
	}
	
	/* Inicialización de los knots */
	float p = 1.0/21.0;
	for (int i = 0; i < 25;i++) {
		if (i < 4){
			knots[i] = 0.0;
		} 
		else if (i > 20){
			knots[i] = 1.0;	
		}
		else {
			knots[i] =  p;
			p += 1.0/21.0;
		}
	}	
}

void init(){

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);

   init_surface();

   theNurb = gluNewNurbsRenderer();
   gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 15.0);
   gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

   // Inicializacion de variabes de las olas
	olaActual = 1;
	printf("Ingrese los siguientes valores para la ola 1\n");
	printf("L = distancia entre cada ola\n");
	cin >> L1;
	printf("A = altura de la ola\n");
	cin >> A1;
	printf("S = velocidad de la ola\n");
	cin >> S1;
	printf("D = coordenadas X,Y de la direccion de la ola\n");
	cin >> D1[0];
	cin >> D1[1];

	printf("Ingrese los siguientes valores para la ola 2\n");
	printf("L = distancia entre cada ola\n");
	cin >> L2;
	printf("A = altura de la ola\n");
	cin >> A2;
	printf("S = velocidad de la ola\n");
	cin >> S2;
	printf("D = coordenadas X,Y de la direccion de la ola\n");
	cin >> D2[0];
	cin >> D2[1];

	printf("L1 %f, A1 %f, S1 %f, Dx1 %f, Dy1 %f\n",L1,A1,S1,D1[0],D1[1]);
	printf("L2 %f, A2 %f, S2 %f, Dx2 %f, Dy2 %f\n",L2,A2,S2,D2[0],D2[1]);

	tiempo = 0.0;
}

void Keyboard(unsigned char key, int x, int y)
{
  if (key == '1') {
	  olaActual = 1;
  }
  else if (key == '2') {
	  olaActual = 2;
  }
  else if (key == 'a' || key == 'A') {
	  if (olaActual == 1) {
		  L1 = L1-0.1;
		  printf("L1 %f \n",L1);
	  }
	  else { 
		  L2 = L2-0.1;
		  printf("L2 %f \n",L2);
	  }
  }
  else if (key == 'z' || key == 'Z') {
	  if (olaActual == 1) {
		  L1 = L1+0.1;
	      printf("L1 %f \n",L1);
	  }
	  else {
		  L2 = L2+0.1;
		  printf("L2 %f \n",L2);
	  }
  }
  else if (key == 's' || key == 'S') {
	  if (olaActual == 1) {
		  A1 = A1-0.1;
		  printf("A1 %f \n",A1);
	  }
	  else {
		  A2 = A2-0.1;
		  printf("A2 %f \n",A2);
	  }
  }
  else if (key == 'x' || key == 'X') {
	  if (olaActual == 1) {
		  A1 = A1+0.1;
	      printf("A1 %f \n",A1);
	  }
	  else {
		  A2 = A2+0.1;
	      printf("A2 %f \n",A2);
	  }
  }
  else if (key == 'd' || key == 'D') {
	  if (olaActual == 1) {
		  S1 = S1-0.1;
	      printf("S1 %f \n",S1);
	  }
	  else {
		  S2 = S2-0.1;
		  printf("S2 %f \n",S2);
	  }
  }
  else if (key == 'c' || key == 'C') {
	  if (olaActual == 1) {
		  S1 = S1+0.1;
	      printf("S1 %f \n",S1);
	  }
	  else {
		  S2 = S2+0.1;
	      printf("S2 %f \n",S2);
	  }
  }
  else if (key == 'f' || key == 'F') {
	  if (olaActual == 1) {
		  D1[0] = D1[0]-0.1;
		  printf("D1x %f \n",D1[0]);
	  }
	  else {
		  D2[0] = D2[0]-0.1;
		  printf("D2x %f \n",D2[0]);
	  }
  }
  else if (key == 'v' || key == 'V') {
	  if (olaActual == 1) {
		  D1[0] = D1[0]+0.1;
	      printf("D1x %f \n",D1[0]);
	  }
	  else {
		  D2[0] = D2[0]+0.1;
		  printf("D2x %f \n",D2[0]);
	  }
  }
  else if (key == 'g' || key == 'G') {
	  if (olaActual == 1) {
		  D1[1] = D1[1]-0.1;
	      printf("D1y %f \n",D1[1]);
	  }
	  else {
		  D2[1] = D2[1]-0.1;
		  printf("D2y %f \n",D2[1]);
	  }
  }
  else if (key == 'b' || key == 'B') {
	  if (olaActual == 1) { 
		  D1[1] = D1[1]+0.1;
	      printf("D1y %f \n",D1[1]);
	  }
	  else {
		  D2[1] = D2[1]+0.1;
	      printf("D2y %f \n",D2[1]);
	  }
  } 
  else if (key == 'p' || key == 'P'){
	  val = 0;
  }
  else if (key == 'r' || key == 'R'){
	  val = 1;
	  animacion(1);
  }
  switch (key)
  {
	case 27:             
		exit (0);

		break;
	
  }
}

void render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

	glLoadIdentity ();                       
	gluLookAt (25.0, 12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

	// Luz y material

	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.9, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 60.0 };
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	

    GLfloat light_ambient[] = { 0.0, 0.0, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_position[] = { -10.0, 5.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);   


	
	// Render Grid 
	/*glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	glPushMatrix();
	glRotatef(90,1.0,0.0,0.0);
    glColor3f( 0.0, 0.7, 0.7 );
    glBegin( GL_LINES );
    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
		xLocal = DEF_floorGridScale * loopX;
		glVertex3f( xLocal, -zExtent, 0.0 );
		glVertex3f( xLocal, zExtent,  0.0 );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
		zLocal = DEF_floorGridScale * loopZ;
		glVertex3f( -xExtent, zLocal, 0.0 );
		glVertex3f(  xExtent, zLocal, 0.0 );
	}
    glEnd();
	ejesCoordenada();
    glPopMatrix();
	glEnable(GL_LIGHTING);*/
	// Fin Grid
	


	//Suaviza las lineas
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );	

	
	glPushMatrix();

	gluBeginSurface(theNurb);

	gluNurbsSurface(theNurb, 
                   25, knots, 25, knots,
                   21 * 3, 3, &ctlpoints[0][0][0], 
                   4, 4, GL_MAP2_VERTEX_3);
	/*
		No cambien los numeros de la funcion, solo deben de poner los nombres de las variables correspondiente.
		
	*/


	gluEndSurface(theNurb);
	
	glPopMatrix();
	
	/* ctlpoints debe ser una matriz de 3 dimensiones con x,y y z de cada punto.
	   los puntos deben estar desde el -10,-10 hasta el 10,10 y supongo que el z
	   siempre es el mismo */
	
	/* Muestra los puntos de control */
	
		/*int i,j;
		glPointSize(5.0);
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i <21; i++) {
			for (j = 0; j < 21; j++) {
	            glVertex3f(ctlpoints[i][j][0], 	ctlpoints[i][j][1], ctlpoints[i][j][2]);
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);*/
	
		

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glutSwapBuffers();
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(960,540);

	glutCreateWindow("Nurbs Proyecto - Ola | María V. Jorge y Jorge Marcano");

	init ();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc (Keyboard);
		
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	

	glutMainLoop();
	return 0;

}