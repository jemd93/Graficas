#include "Vehiculo.h"


Vehiculo::Vehiculo(Ogre::SceneManager* mSceneMgr)
{
	anguloGiroRuedas = 4.0;
	anguloRoteRuedas = 2.0;
	anguloActRote = 0.0;
	if (mSceneMgr != NULL) {
		//Chasis
		nodoChasis01 = mSceneMgr->createSceneNode("Chasis01");
		mSceneMgr->getRootSceneNode()->addChild(nodoChasis01);
			
		entChasis01 = mSceneMgr->createEntity("entChasis01", "chasisCarro.mesh");
		entChasis01->setMaterialName("shCarro01");
		nodoChasis01->attachObject(entChasis01);

		//Ruedas
		for (int i = 0; i < 4; i++) {
			nodosYaw[i] = mSceneMgr->createSceneNode("ruedaYaw0"+std::to_string(i+1));
			
			nodoChasis01->addChild(nodosYaw[i]);

			nodosRuedas[i] = mSceneMgr->createSceneNode("Rueda0"+std::to_string(i+1));
			nodosYaw[i]->addChild(nodosRuedas[i]);

			entRuedas[i] = mSceneMgr->createEntity("entRueda0"+std::to_string(i+1), "ruedaDetallada.mesh");
			if (i == 0)
				nodosYaw[i]->translate(8,3.517,9.5);  // Rueda delantera izquierda
			else if (i == 1)
				nodosYaw[i]->translate(-5.77,3.517,9.5); // Rueda delantera derecha
			else if (i == 2)
				nodosYaw[i]->translate(8,3.517,-9.462);  // Rueda trasera izquierda
			else if (i == 3)
				nodosYaw[i]->translate(-5.77,3.517,-9.462); // Rueda trasera derecha

			entRuedas[i]->setMaterialName("shRueda02");
			nodosRuedas[i]->attachObject(entRuedas[i]);
		}
	}
}

void Vehiculo::moverCarro(int frente) {
	nodoChasis01->translate(0, 0, frente*2, Ogre::Node::TS_LOCAL);
	for (int i = 0; i < 4;i++) {
		nodosRuedas[i]->pitch(frente*Degree(anguloGiroRuedas));
	}
}

void Vehiculo::rotarCarro(int izq) {
	anguloActRote =  anguloActRote + izq;
	for (int i = 0; i < 2;i++) {
		nodosYaw[i]->yaw(izq*Degree(anguloRoteRuedas));
	}

	nodoChasis01->yaw(izq*Degree(anguloRoteRuedas));
}
//Vehiculo::~Vehiculo(void)
//{
//}
