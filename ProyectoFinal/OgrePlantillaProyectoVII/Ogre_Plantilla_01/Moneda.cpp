#include "Moneda.h"


Moneda::Moneda(Ogre::SceneManager* mSceneMgr,float posX, float posZ): id(newId++) {
	if (mSceneMgr != NULL) {
		//Chasis
		nodoMoneda = mSceneMgr->createSceneNode("Moneda"+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoMoneda);
			
		entMoneda = mSceneMgr->createEntity("entMoneda"+std::to_string(id),"sphere.mesh");
		nodoMoneda->attachObject(entMoneda);
		entMoneda->setMaterialName("moneda");
		nodoMoneda->setPosition(Ogre::Vector3(posX,4,posZ));
		nodoMoneda->setScale(0.04,0.04,0.04);
	}
}


//Moneda::~Moneda(void)
//{
//}
