#include "Forma.h"


Forma::Forma(Ogre::SceneManager* mSceneMgr,float posX,float posY, float posZ,float aR,float aP,float aY,float largo,float alto,float ancho,std::string forma): id(newId++) {
	x = posX;
	y = posY;
	z = posZ;
	aRoll = aR;
	aPitch = aP;
	aYaw = aY;
	if (mSceneMgr != NULL) {
		nodoForma = mSceneMgr->createSceneNode("nodo"+forma+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoForma);
			
		entForma = mSceneMgr->createEntity("ent"+forma+std::to_string(id),forma+"01.mesh");
		nodoForma->attachObject(entForma);
		//entForma->setMaterialName("Forma");
		nodoForma->setPosition(Ogre::Vector3(x,y,z));
		nodoForma->setScale(ancho,largo,alto);
		nodoForma->pitch(Degree(aPitch));
		nodoForma->roll(Degree(aRoll));
		nodoForma->yaw(Degree(aYaw));
	}
}


//Forma::~Forma(void)
//{
//}
