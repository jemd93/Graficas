#include "Forma.h"


Forma::Forma(Ogre::SceneManager* mSceneMgr,float posX, float posZ,float angulo,float largo,float alto,float ancho,std::string forma): id(newId++) {
	x = posX;
	y = 4;
	z = posZ;
	a = angulo;
	if (mSceneMgr != NULL) {
		nodoForma = mSceneMgr->createSceneNode("nodo"+forma+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoForma);
			
		entForma = mSceneMgr->createEntity("ent"+forma+std::to_string(id),forma+"01.mesh");
		nodoForma->attachObject(entForma);
		//entForma->setMaterialName("Forma");
		nodoForma->setPosition(Ogre::Vector3(x,y,z));
		nodoForma->pitch(Degree(90));
		nodoForma->setScale(ancho,largo,alto);
		nodoForma->roll(Degree(a));
	}
}


//Forma::~Forma(void)
//{
//}
