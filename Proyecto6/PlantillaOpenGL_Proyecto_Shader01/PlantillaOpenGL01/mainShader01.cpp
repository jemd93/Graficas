#include <stdlib.h>
#include <conio.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "glsl.h"
#include "glm.h"

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// the global Assimp scene object
const aiScene* scene = NULL;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


using namespace std;

cwc::glShaderManager SM;
cwc::glShader *shader01;
cwc::glShader *shader02;

//Variables para el Spirograph Curves
float R = 10.0;
float hoff = 0.0;
float freq = 1.0;
float calctype = 1.0;
float f = 1.0;

//Variables para el Mandelbrot Fractal
float xc = 0.5;
float yc = 0.5;
float sz = 4;
float huefreq = 1;
float escape = 256;
float maxiter = 20;

void ejesCoordenada() {
	
	glDisable(GL_LIGHTING);	
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

	glEnable(GL_LIGHTING);

	glLineWidth(1.0);
}

void changeViewport(int w, int h) {
	
	float aspectratio;

	if (h==0)
		h=1;

	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 300.0);
   glMatrixMode (GL_MODELVIEW);

}

void init(){
	
   
   shader01 = SM.loadfromFile("mandel.vert","mandel.frag"); // load (and compile, link) from file
  		  if (shader01==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";

   shader02 = SM.loadfromFile("spirofield.vert","spirofield.frag"); // load (and compile, link) from file
  		  if (shader02==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";

}

void cargar_shader(int idx) {


	// Plano Derecho Mandel
	if (idx == 0){	
			if (shader01) shader01->begin();
			shader01->setUniform1f("_xc",xc);
		    shader01->setUniform1f("_yc",yc);
		    shader01->setUniform1f("_sz",sz);
		    shader01->setUniform1f("_huefreq",huefreq);
		    shader01->setUniform1f("_escape",escape);
			shader01->setUniform1f("_maxiter",maxiter);
			//Colocar aqui los parametros Uniform

	}

	// Plano Izquierdo SpiroField
	if (idx == 1){		
		   if (shader02) shader02->begin();
		   shader02->setUniform1f("_R",R);
		   shader02->setUniform1f("_hoff",hoff);
		   shader02->setUniform1f("_freq",freq);
		   shader02->setUniform1f("_calctype",calctype);
		   shader02->setUniform1f("_f",f);
		   //Colocar aqui los parametros Uniform
	}


}

void fin_shader(int idx) {


	// Material Piso
	if (idx == 0){	
			if (shader01) shader01->end();
	}

	// Material Columna
	if (idx == 1){		
		   if (shader02) shader02->end();
	}


}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q'){
		calctype = 0;
	}
	else if (key == 'a' || key == 'A'){
		calctype = 1;
	}
	else if (key == 'z' || key == 'Z'){
		calctype = 2;
	}
	else if (key == 'w' || key == 'W'){
		R += 1;
	}
	else if (key == 'e' || key == 'E'){
		R -=1;
		if (R <= 0)
			R = 1;
	}
	else if (key == 's' || key == 'S'){
		freq += 0.05;
	}
	else if (key == 'd' || key == 'D'){
		freq -= 0.05;
		if (freq <= 0)
			freq = 0.05;
	}
	else if (key == 'x' || key == 'X'){
		hoff += 0.1;
	}
	else if (key == 'c' || key == 'C'){
		hoff -= 0.1;
		if (hoff <= 0)
			hoff = 0.05;
	}
	else if (key == 'r' || key == 'R'){
		f += 0.05;
	}
	else if (key == 't' || key == 'T'){
		f -= 0.05;
		if (f <= 0)
			f = 0.05;
	} 
	else if (key == '1'){
		R = 6.5;
		hoff = 1.9;
		freq = 0.75;
		calctype = 1;
		f = 1;
		xc = 0.5;
		yc = 0.5;
		huefreq = 1;
		sz = 4;
		escape = 256;
		maxiter = 20;
	}
	else if (key == '2'){
		R = 13;
		hoff = 1.05;
		freq = 0.8;
		calctype = 1;
		f = 0.5;
		xc = 0.5;
		yc = 0.5;
		huefreq = 1;
		sz = 4;
		escape = 256;
		maxiter = 20;
	}
	else if (key == '3'){
		R = 2;
		hoff = 0;
		freq = 0.25;
		calctype = 0;
		f = 1;
		xc = 0.5;
		yc = 0.5;
		huefreq = 1;
		sz = 4;
		escape = 256;
		maxiter = 20;
	}
	else if (key == '4'){
		R = 11;
		hoff = 0.8;
		freq = 0.55;
		calctype = 2;
		f = 1;
		xc = 0.5;
		yc = 0.5;
		huefreq = 1;
		sz = 4;
		escape = 256;
		maxiter = 20;
	}
	else if (key == '5'){
		R = 11;
		hoff = 0.8;
		freq = 0.55;
		calctype = 2;
		f = 1;
		xc = 0.39;
		yc = 0.25;
		huefreq = 0.36;
		sz = 0.05;
		escape = 512;
		maxiter = 120;
	}
	else if (key == '6'){
		R = 11;
		hoff = 0.8;
		freq = 0.55;
		calctype = 2;
		f = 1;
		xc = 0.39;
		yc = 0.27;
		huefreq = 2.4;
		sz = 0.01;
		escape = 512;
		maxiter = 256;
	}
	// Mandelbrot Fractal
	if (key == 'y' || key == 'Y') {
		xc += 0.05;
	}
	if (key == 'u' || key == 'U') {
		xc -= 0.05;
		if (xc <= 0) {
			xc = 0.05;
		}
	}
	if (key == 'h' || key == 'H') {
		yc += 0.05;
	}
	if (key == 'j' || key == 'J') {
		yc -= 0.05;
		if (yc <= 0) {
			yc = 0.05;
		}
	}
	if (key == 'n' || key == 'N') {
		sz += 0.001;
	}
	if (key == 'm' || key == 'M') {
		sz -= 0.001;
		if (sz <= 0) {
			sz = 0.001;
		}
	}
	if (key == 'i' || key == 'I') {
		huefreq += 0.05;
	}
	if (key == 'o' || key == 'O') {
		huefreq -= 0.05;
		if (huefreq <= 0) {
			huefreq = 0.05;
		}
	}
	if (key == 'f' || key == 'F') {
		escape += 12;
	}
	if (key == 'g' || key == 'G') {
		escape -= 12;
		if (escape <= 0) {
			escape = 12;
		}
	}
	if (key == 'v' || key == 'V') {
		maxiter += 12;
	}
	if (key == 'b' || key == 'B') {
		maxiter -= 12;
		if (maxiter <= 0) {
			maxiter = 12;
		}
	}

	scene_list = 0;
	glutPostRedisplay();
}

void recursive_render (const aiScene *sc, const aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				
				if(mesh->mNormals != NULL) 
					glNormal3fv(&mesh->mNormals[index].x);
				
				if (mesh->HasTextureCoords(0)) 
					glTexCoord2f(mesh->mTextureCoords[0][index].x, 1-mesh->mTextureCoords[0][index].y);
				
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		cargar_shader(n);
		recursive_render(sc, nd->mChildren[n]);
		fin_shader(n);
	}

	glPopMatrix();
}

void render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

	glLoadIdentity ();                       
	gluLookAt (0.0, 0.0, 70.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );	

			
	glPushMatrix();


	// Codigo para el mesh	
	glEnable(GL_NORMALIZE);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}
	glCallList(scene_list);
	
	glPopMatrix();
	
	system("cls");
	printf("Spirofield Parametros\n");
	printf("==========================\n");
	printf("_R: %f\n",R);
	printf("_hoff: %f\n",hoff);
	printf("_freq: %f\n",freq);
	printf("_calctype: %f\n",calctype);
	printf("_f: %f\n",f);
	printf("--------------------------\n\n");
	printf("Mandel Parametros\n");
	printf("==========================\n");
	printf("_xc: %f\n",xc);
	printf("_yc: %f\n",yc);
	printf("_huefreq: %f\n",huefreq);
	printf("_sz: %f\n",sz);
	printf("_escape: %f\n",escape);
	printf("_maxiter: %f\n",maxiter);
	printf("--------------------------\n\n");

	
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glutSwapBuffers();
}

void animacion(int value) {
	
	glutTimerFunc(10,animacion,1);
    glutPostRedisplay();
	
}

void get_bounding_box_for_node (const aiNode* nd, 	aiVector3D* min, 	aiVector3D* max, 	aiMatrix4x4* trafo){
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

void get_bounding_box (aiVector3D* min, aiVector3D* max){
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	
	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
}

int loadasset (const char* path){
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.
	scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene) {
		get_bounding_box(&scene_min,&scene_max);
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
		return 0;
	}
	return 1;
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(960,540);

	glutCreateWindow("Test Opengl");


	// Codigo para cargar la geometria usando ASSIMP

	aiLogStream stream;
	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It remains active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	// ... same procedure, but this stream now writes the
	// log messages to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);

	// the model name can be specified on the command line. If none
	// is specified, we try to locate one of the more expressive test 
	// models from the repository (/models-nonbsd may be missing in 
	// some distributions so we need a fallback from /models!).
	
	
	loadasset( "planos.obj");



	init ();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc(Keyboard);
	
	glutMainLoop();
	return 0;

}
