#include "Moneda.h"


Moneda::Moneda(Ogre::SceneManager* mSceneMgr,float posX, float posZ): id(newId++) {
	x = posX;
	y = 4;
	z = posZ;
	if (mSceneMgr != NULL) {
		nodoMoneda = mSceneMgr->createSceneNode("Moneda"+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoMoneda);
			
		entMoneda = mSceneMgr->createEntity("entMoneda"+std::to_string(id),"sphere.mesh");
		nodoMoneda->attachObject(entMoneda);
		entMoneda->setMaterialName("moneda");
		nodoMoneda->setPosition(Ogre::Vector3(x,y,z));
		nodoMoneda->setScale(0.04,0.04,0.04);
	}
}


//Moneda::~Moneda(void)
//{
//}