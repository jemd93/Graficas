#include "Vehiculo.h"


Vehiculo::Vehiculo(Ogre::SceneManager* mSceneMgr)
{
	anguloGiroRuedas = 4.0;
	anguloRoteRuedas = 2.0;
	anguloActRote = 0.0;
	velocidad = 0.0;
	maxVel = 7.0;
	if (mSceneMgr != NULL) {
		//Chasis
		nodoChasis01 = mSceneMgr->createSceneNode("Chasis01");
		mSceneMgr->getRootSceneNode()->addChild(nodoChasis01);
			
		entChasis01 = mSceneMgr->createEntity("entChasis01", "chasisCarro.mesh");
		entChasis01->setMaterialName("shCarro01");
		nodoChasis01->attachObject(entChasis01);

		// Esfera SOLO PARA PRUEBAS. BORRAR ANTES DE ENTREGAR
		//nodoEsfera01 = mSceneMgr->createSceneNode("Esfera01");
		//nodoChasis01->addChild(nodoEsfera01);
		//	
		//entEsfera01 = mSceneMgr->createEntity("entEsfera01", "sphere.mesh");
		//nodoEsfera01->attachObject(entEsfera01);
		//nodoEsfera01->setScale(0.15,0.15,0.15);

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
	//printf("%f,%f,%f\n",nodoChasis01->getPosition().x,nodoChasis01->getPosition().y,nodoChasis01->getPosition().z);
	if (velocidad < maxVel) 
		velocidad += 0.07;
	nodoChasis01->translate(0, 0, frente*velocidad, Ogre::Node::TS_LOCAL);
	for (int i = 0; i < 4;i++) {
		nodosRuedas[i]->pitch(frente*Degree(anguloGiroRuedas));
	}
}

void Vehiculo::rotarCarro(int izq) {
	anguloActRote =  anguloActRote + izq;
	if (izq == 1){
		if (anguloActRote < 15) {
			for (int i = 0; i < 2;i++) {
				nodosYaw[i]->yaw(izq*Degree(anguloRoteRuedas));
			}
		}
	}
	else {
		if (anguloActRote > -15) {
			for (int i = 0; i < 2;i++) {
				nodosYaw[i]->yaw(izq*Degree(anguloRoteRuedas));
			}
		}
	}

	nodoChasis01->yaw(izq*Degree(anguloRoteRuedas));
}

//Vehiculo::~Vehiculo(void)
//{
//}
