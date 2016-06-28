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

		// QUITAR ANTES DE ENTREGAR, SOLO EL SHOW.
		nodoChasis01->showBoundingBox(true);

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

			estaVolando = false;
			activarAnimacion = 0; //No ha empezado a volar
			escalaAlas = 0.1;
			
		}
	}
}

int Vehiculo::cheqColMon(Moneda mon) {
	if (nodoChasis01->_getWorldAABB().intersects(mon.nodoMoneda->_getWorldAABB())) {
		mon.scnMgr->destroyEntity(mon.entMoneda);
		return 1;
	}
	return 0;
}

void Vehiculo::cheqColObs(Forma form) {
	AxisAlignedBox aab = nodoChasis01->_getWorldAABB().intersection(form.nodoForma->_getWorldAABB());
	if(!aab.isNull())
	{
		velocidad = 1;
		Vector3 diff = nodoChasis01->getPosition();
		Vector3 dir = diff.normalisedCopy();
		Vector3 p = aab.getMaximum() - aab.getMinimum();
		Vector3 trans = dir * Math::Abs(p.normalisedCopy().dotProduct(dir)) * p.length() * 0.5;
		
		if (nodoChasis01->_getWorldAABB().getMinimum().z < form.nodoForma->_getWorldAABB().getMinimum().z)
			nodoChasis01->translate(0,0,-trans.z);
		else 
			nodoChasis01->translate(0,0,trans.z);

		//if (nodoChasis01->_getWorldAABB().getMinimum().x < form.nodoForma->_getWorldAABB().getMinimum().x)
		//	nodoChasis01->translate(-trans.x,0,0);
		//else 
		//	nodoChasis01->translate(trans.x,0,0);
	}
}

void Vehiculo::cheqColAst(SceneNode* ast) {
	AxisAlignedBox aab = nodoChasis01->_getWorldAABB().intersection(ast->_getWorldAABB());
	if(!aab.isNull())
	{
		velocidad = 1;
		Vector3 diff = nodoChasis01->getPosition();
		Vector3 dir = diff.normalisedCopy();
		Vector3 p = aab.getMaximum() - aab.getMinimum();
		Vector3 trans = dir * Math::Abs(p.normalisedCopy().dotProduct(dir)) * p.length() * 0.5;
		
		if (nodoChasis01->_getWorldAABB().getMinimum().z < ast->_getWorldAABB().getMinimum().z)
			nodoChasis01->translate(0,0,-trans.z);
		else 
			nodoChasis01->translate(0,0,trans.z);

		//if (nodoChasis01->_getWorldAABB().getMinimum().x < ast->_getWorldAABB().getMinimum().x)
		//	nodoChasis01->translate(-trans.x,0,0);
		//else 
		//	nodoChasis01->translate(trans.x,0,0);
	}
}
void Vehiculo::moverCarro(int frente) {
	//printf("%f,%f,%f\n",nodoChasis01->getPosition().x,nodoChasis01->getPosition().y,nodoChasis01->getPosition().z);
	if (velocidad < maxVel) 
		velocidad += 0.07;
	nodoChasis01->translate(0, 0, frente*velocidad, Ogre::Node::TS_LOCAL);
	nodoAlas->translate(0, 0, frente*velocidad, Ogre::Node::TS_LOCAL);
	for (int i = 0; i < 4;i++) {
		nodosRuedas[i]->pitch(frente*Degree(anguloGiroRuedas));
	}
	if (nodoChasis01->getPosition().z >= 6530){
		estaVolando = true;
	} else
		estaVolando = false;
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
	nodoAlas->yaw(izq*Degree(anguloRoteRuedas));
}

void Vehiculo::dibujarAlas(Ogre::SceneManager* mSceneMgr){
	alaIzquierda = mSceneMgr->createManualObject("alaIzquierda");
	alaDerecha = mSceneMgr->createManualObject("alaDerecha");
	nodoAlas = mSceneMgr->createSceneNode("nodoAlas");
	mSceneMgr->getRootSceneNode()->addChild(nodoAlas);

	nodoAlas->setVisible(false);
	alaIzquierda->setVisible(false);
	alaDerecha->setVisible(false);

	alaIzquierda->begin("shCarro01", RenderOperation::OT_TRIANGLE_LIST);
		/* Parte de arriba */
		alaIzquierda->position(5,9.5,-1); alaIzquierda->normal(0.0,1.0,0.0); //0
		alaIzquierda->position(8,9.5,-1); alaIzquierda->normal(0.0,1.0,0.0); //1
		alaIzquierda->position(23,9.5,-11); alaIzquierda->normal(0.0,1.0,0.0); //2
		alaIzquierda->position(18.5,9.5,-9.5); alaIzquierda->normal(0.0,1.0,0.0); //3
		alaIzquierda->position(14,9.5,-11); alaIzquierda->normal(0.0,1.0,0.0); //4
		alaIzquierda->position(9.5,9.5,-9.5); alaIzquierda->normal(0.0,1.0,0.0); //5
		alaIzquierda->position(5,9.5,-11); alaIzquierda->normal(0.0,1.0,0.0); //6

		alaIzquierda->triangle(0,1,2);
		alaIzquierda->triangle(0,2,3);
		alaIzquierda->triangle(0,3,4);
		alaIzquierda->triangle(0,4,5);
		alaIzquierda->triangle(0,5,6);

		/* Parte de abajo */
		alaIzquierda->position(5,8.5,-1); alaIzquierda->normal(0.0,-1.0,0.0); //7
		alaIzquierda->position(8,8.5,-1); alaIzquierda->normal(0.0,-1.0,0.0); //8
		alaIzquierda->position(23,8.5,-11); alaIzquierda->normal(0.0,-1.0,0.0); //9
		alaIzquierda->position(18.5,8.5,-9.5); alaIzquierda->normal(0.0,-1.0,0.0); //10
		alaIzquierda->position(14,8.5,-11); alaIzquierda->normal(0.0,-1.0,0.0); //11
		alaIzquierda->position(9.5,8.5,-9.5); alaIzquierda->normal(0.0,-1.0,0.0); //12
		alaIzquierda->position(5,8.5,-11); alaIzquierda->normal(0.0,-1.0,0.0); //13

		alaIzquierda->triangle(9,8,7);
		alaIzquierda->triangle(10,9,7);
		alaIzquierda->triangle(11,10,7);
		alaIzquierda->triangle(12,11,7);
		alaIzquierda->triangle(13,12,7);

		/* Parte trasera */
		alaIzquierda->position(23,9.5,-11); alaIzquierda->normal(0.0,0.0,1.0); //2-14
		alaIzquierda->position(18.5,9.5,-9.5); alaIzquierda->normal(0.0,0.0,1.0); //3-15
		alaIzquierda->position(14,9.5,-11); alaIzquierda->normal(0.0,0.0,1.0); //4-16
		alaIzquierda->position(9.5,9.5,-9.5); alaIzquierda->normal(0.0,0.0,1.0); //5-17
		alaIzquierda->position(5,9.5,-11); alaIzquierda->normal(0.0,0.0,1.0); //6-18
		alaIzquierda->position(23,8.5,-11); alaIzquierda->normal(0.0,0.0,1.0);//9-19
		alaIzquierda->position(18.5,8.5,-9.5); alaIzquierda->normal(0.0,0.0,1.0);//10-20
		alaIzquierda->position(14,8.5,-11); alaIzquierda->normal(0.0,0.0,1.0);//11-21
		alaIzquierda->position(9.5,8.5,-9.5); alaIzquierda->normal(0.0,0.0,1.0);//12-22
		alaIzquierda->position(5,8.5,-11); alaIzquierda->normal(0.0,0.0,1.0);//13-23

		alaIzquierda->quad(19,20,15,14);
		alaIzquierda->quad(20,21,16,15);
		alaIzquierda->quad(21,22,17,16);
		alaIzquierda->quad(22,23,18,17);

		/* Lateral izquierdo */
		alaIzquierda->position(8,9.5,-1); //alaIzquierda->normal(0.0,1.0,0.0); //1-24
		alaIzquierda->position(23,9.5,-11); //alaIzquierda->normal(0.0,1.0,0.0); //2-25
		alaIzquierda->position(8,8.5,-1); //alaIzquierda->normal(0.0,-1.0,0.0); //8-26
		alaIzquierda->position(23,8.5,-11); //alaIzquierda->normal(0.0,-1.0,0.0); //9-27

		alaIzquierda->quad(26,27,25,24);
	alaIzquierda->end();
	nodoAlas->attachObject(alaIzquierda);
	alaDerecha->begin("shCarro01", RenderOperation::OT_TRIANGLE_LIST);
		/* Parte de arriba */
		alaDerecha->position(-5,9.5,-1); alaDerecha->normal(0.0,1.0,0.0); //0
		alaDerecha->position(-8,9.5,-1); alaDerecha->normal(0.0,1.0,0.0); //1
		alaDerecha->position(-23,9.5,-11); alaDerecha->normal(0.0,1.0,0.0); //2
		alaDerecha->position(-18.5,9.5,-9.5); alaDerecha->normal(0.0,1.0,0.0); //3
		alaDerecha->position(-14,9.5,-11); alaDerecha->normal(0.0,1.0,0.0); //4
		alaDerecha->position(-9.5,9.5,-9.5); alaDerecha->normal(0.0,1.0,0.0); //5
		alaDerecha->position(-5,9.5,-11); alaDerecha->normal(0.0,1.0,0.0); //6

		alaDerecha->triangle(2,1,0);
		alaDerecha->triangle(3,2,0);
		alaDerecha->triangle(4,3,0);
		alaDerecha->triangle(5,4,0);
		alaDerecha->triangle(6,5,0);

		/* Parte de abajo */
		alaDerecha->position(-5,8.5,-1); alaDerecha->normal(0.0,-1.0,0.0); //7
		alaDerecha->position(-8,8.5,-1); alaDerecha->normal(0.0,-1.0,0.0); //8
		alaDerecha->position(-23,8.5,-11); alaDerecha->normal(0.0,-1.0,0.0); //9
		alaDerecha->position(-18.5,8.5,-9.5); alaDerecha->normal(0.0,-1.0,0.0); //10
		alaDerecha->position(-14,8.5,-11); alaDerecha->normal(0.0,-1.0,0.0); //11
		alaDerecha->position(-9.5,8.5,-9.5); alaDerecha->normal(0.0,-1.0,0.0); //12
		alaDerecha->position(-5,8.5,-11); alaDerecha->normal(0.0,-1.0,0.0); //13

		alaDerecha->triangle(7,8,9);
		alaDerecha->triangle(7,9,10);
		alaDerecha->triangle(7,10,11);
		alaDerecha->triangle(7,11,12);
		alaDerecha->triangle(7,12,13);

		alaDerecha->position(-23,9.5,-11); alaDerecha->normal(0.0,0.0,1.0); //2-14
		alaDerecha->position(-18.5,9.5,-9.5); alaDerecha->normal(0.0,0.0,1.0); //3-15
		alaDerecha->position(-14,9.5,-11); alaDerecha->normal(0.0,0.0,1.0); //4-16
		alaDerecha->position(-9.5,9.5,-9.5); alaDerecha->normal(0.0,0.0,1.0); //5-17
		alaDerecha->position(-5,9.5,-11); alaDerecha->normal(0.0,0.0,1.0); //6-18
		alaDerecha->position(-23,8.5,-11); alaDerecha->normal(0.0,0.0,1.0);//9-19
		alaDerecha->position(-18.5,8.5,-9.5); alaDerecha->normal(0.0,0.0,1.0);//10-20
		alaDerecha->position(-14,8.5,-11); alaDerecha->normal(0.0,0.0,1.0);//11-21
		alaDerecha->position(-9.5,8.5,-9.5); alaDerecha->normal(0.0,0.0,1.0);//12-22
		alaDerecha->position(-5,8.5,-11); alaDerecha->normal(0.0,0.0,1.0);//13-23

		alaDerecha->quad(14,15,20,19);
		alaDerecha->quad(15,16,21,20);
		alaDerecha->quad(16,17,22,21);
		alaDerecha->quad(17,18,23,22);

		/* Lateral derecho */
		alaDerecha->position(-8,9.5,-1); //alaDerecha->normal(0.0,1.0,0.0); //1-24
		alaDerecha->position(-23,9.5,-11); //alaDerecha->normal(0.0,1.0,0.0); //2-25
		alaDerecha->position(-8,8.5,-1); //alaDerecha->normal(0.0,-1.0,0.0); //8-26
		alaDerecha->position(-23,8.5,-11); //alaDerecha->normal(0.0,-1.0,0.0); //9-27

		alaDerecha->quad(24,25,27,26);
	alaDerecha->end();
	nodoAlas->attachObject(alaDerecha);

}

void Vehiculo::animarVuelo(int frente){
	if (frente == 1){
		nodoAlas->setVisible(true);
		alaIzquierda->setVisible(true);
		alaDerecha->setVisible(true);
		nodoAlas->setScale(escalaAlas,escalaAlas,escalaAlas);
		escalaAlas += 0.05;
		for (int i = 0; i < 4; i++){
			nodosYaw[i]->roll(Degree(5));
		}
		if (escalaAlas > 1){
			activarAnimacion = 1;
			escalaAlas = 1.0;
		}
	} else{
		nodoAlas->setScale(escalaAlas,escalaAlas,escalaAlas);
		escalaAlas -= 0.05;
		for (int i = 0; i < 4; i++){
			nodosYaw[i]->roll(Degree(-5));
		}
		if (escalaAlas < 0){
			nodoAlas->setVisible(false);
			alaIzquierda->setVisible(false);
			alaDerecha->setVisible(false);
			activarAnimacion = 0;
			escalaAlas = 0.1;
		}
		
	}
}

//Vehiculo::~Vehiculo(void)
//{
//}
