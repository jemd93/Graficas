#include "Cilindro.h"


Cilindro::Cilindro(Ogre::SceneManager* mSceneMgr,float posX, float posZ,float angulo,float largo): id(newId++) {
	x = posX;
	y = 4;
	z = posZ;
	a = angulo;
	if (mSceneMgr != NULL) {
		nodoCilindro = mSceneMgr->createSceneNode("Cilindro"+std::to_string(id));
		mSceneMgr->getRootSceneNode()->addChild(nodoCilindro);
			
		entCilindro = mSceneMgr->createEntity("entCilindro"+std::to_string(id),"cilindro01.mesh");
		nodoCilindro->attachObject(entCilindro);
		//entCilindro->setMaterialName("Cilindro");
		nodoCilindro->setPosition(Ogre::Vector3(x,y,z));
		nodoCilindro->pitch(Degree(90));
		nodoCilindro->setScale(3.0,largo,3.0);
		nodoCilindro->roll(Degree(a));
	}
}


//Cilindro::~Cilindro(void)
//{
//}
