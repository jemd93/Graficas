#include "Forma.h"


Forma::Forma(Ogre::SceneManager* mSceneMgr,float posX,float posY, float posZ,float aR,float aP,float aY,float largo,float alto,float ancho,std::string forma, std::string mat): id(newId++) {
	x = posX;
	y = posY;
	z = posZ;
	aRoll = aR;
	aPitch = aP;
	aYaw = aY;
	adelante = true;
	if (mSceneMgr != NULL) {
		nodoForma = mSceneMgr->createSceneNode("nodo"+forma+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoForma);
			
		entForma = mSceneMgr->createEntity("ent"+forma+std::to_string(id),forma+".mesh");
		nodoForma->attachObject(entForma);
		entForma->setMaterialName(mat);
		nodoForma->setPosition(Ogre::Vector3(x,y,z));
		nodoForma->setScale(ancho,largo,alto);
		nodoForma->pitch(Degree(aPitch));
		nodoForma->roll(Degree(aRoll));
		nodoForma->yaw(Degree(aYaw));
	}
}

void Forma::deslizar(bool horizontal,int min, int max,int vel) {
	if (horizontal) {
		if ((x < max) && (adelante)){
			nodoForma->translate(vel,0,0);
			x += vel;
		}
		else if ((x == max) && (adelante)) {
			adelante = false;
		}
		else if ((x > min) && !(adelante)){
			nodoForma->translate(-vel,0,0);
			x -= vel;
		}
		else if ((x == min) && !(adelante)) {
			adelante = true;
		}
	}
	else {
		if ((z < max) && (adelante)){
			nodoForma->translate(0,0,vel);
			z += vel;
		}
		else if ((z == max) && (adelante)) {
			adelante = false;
		}
		else if ((z > min) && !(adelante)){
			nodoForma->translate(0,0,-vel);
			z -= vel;
		}
		else if ((z == min) && !(adelante)) {
			adelante = true;
		}
	}
}


//Forma::~Forma(void)
//{
//}
