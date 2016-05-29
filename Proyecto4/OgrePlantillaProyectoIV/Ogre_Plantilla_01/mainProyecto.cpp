#include "Ogre\ExampleApplication.h"

class Example1 : public ExampleApplication
{

public:
	// Nodos para torretas.
	Ogre::SceneNode* nodosTorreta[4];

	// Nodos para pipes.
	Ogre::SceneNode* nodosPipe[8];

	// Nodos para formas curvas.
	Ogre::SceneNode* nodosCurva[4];

	// Nodos para canones.
	Ogre::SceneNode* nodosCanon[4];

	//Nodo para la nave
	Ogre::SceneNode* nodoNave;

	//Nodo para las alas (superiores e inferiores)
	Ogre::SceneNode* nodosAlas[2];

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,10,50);
		mCamera->lookAt(0,0,-50);
		mCamera->setNearClipDistance(5);

	}

	void modificarColor(Ogre::Entity* entidad,float r, float g, float b) {
		Ogre::MaterialPtr m_pMat = entidad->getSubEntity(0)->getMaterial();
		m_pMat->getTechnique(0)->getPass(0)->setAmbient(r,g,b);
		m_pMat->getTechnique(0)->getPass(0)->setDiffuse(0.0,0.0,0.0,0.0);
		entidad->setMaterialName(m_pMat->getName());
	}

	void crearTorretas() {

		// TORRETA 1.
		Ogre::Entity* entTorreta01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[0] = mSceneMgr->createSceneNode("nodoTorreta1");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[0]);
		nodosTorreta[0]->attachObject(entTorreta01);
		nodosTorreta[0]->setPosition(-22,-5,-227);

		// Pipes
		Ogre::Entity* entPipe01 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[0] = mSceneMgr->createSceneNode("nodoPipe1");
		nodosPipe[0]->attachObject(entPipe01);
		nodosTorreta[0]->addChild(nodosPipe[0]);
		nodosPipe[0]->setScale(0.65,0.65,0.65);
		nodosPipe[0]->setPosition(0.0,-2.0,0.0);

		Ogre::Entity* entPipe02 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[1] = mSceneMgr->createSceneNode("nodoPipe2");
		nodosPipe[1]->attachObject(entPipe02);
		nodosTorreta[0]->addChild(nodosPipe[1]);
		nodosPipe[1]->setScale(0.65,0.65,0.65);
		nodosPipe[1]->setPosition(0.0,3.0,0.0);

		// Forma curva.
		Ogre::Entity* entCurva01 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[0] = mSceneMgr->createSceneNode("nodoCurva1");
		nodosCurva[0]->attachObject(entCurva01);
		nodosTorreta[0]->addChild(nodosCurva[0]);
		nodosCurva[0]->setScale(0.65,0.65,0.65);
		nodosCurva[0]->setPosition(0.0,5.0,0.0);

		// Canon de la torreta
		Ogre::Entity* entCanon01 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[0] = mSceneMgr->createSceneNode("nodoCanon1");
		nodosCanon[0]->attachObject(entCanon01);
		nodosTorreta[0]->addChild(nodosCanon[0]);
		nodosCanon[0]->setScale(0.65,0.65,0.65);
		nodosCanon[0]->setPosition(1.0,7.0,2.0);
		nodosCanon[0]->yaw(Degree(25));
		nodosCanon[0]->pitch(Degree(60));


		// TORRETA 2.
		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[1] = mSceneMgr->createSceneNode("nodoTorreta2");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[1]);
		nodosTorreta[1]->attachObject(entTorreta02);
		nodosTorreta[1]->setPosition(-22.5,-5,-638);
		
		// Pipes
		Ogre::Entity* entPipe03 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[2] = mSceneMgr->createSceneNode("nodoPipe3");
		nodosPipe[2]->attachObject(entPipe03);
		nodosTorreta[1]->addChild(nodosPipe[2]);
		nodosPipe[2]->setScale(0.65,0.65,0.65);
		nodosPipe[2]->setPosition(0.0,-2.0,0.0);

		Ogre::Entity* entPipe04 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[3] = mSceneMgr->createSceneNode("nodoPipe4");
		nodosPipe[3]->attachObject(entPipe04);
		nodosTorreta[1]->addChild(nodosPipe[3]);
		nodosPipe[3]->setScale(0.65,0.65,0.65);
		nodosPipe[3]->setPosition(0.0,3.0,0.0);

		// Forma curva.
		Ogre::Entity* entCurva02 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[1] = mSceneMgr->createSceneNode("nodoCurva2");
		nodosCurva[1]->attachObject(entCurva02);
		nodosTorreta[1]->addChild(nodosCurva[1]);
		nodosCurva[1]->setScale(0.65,0.65,0.65);
		nodosCurva[1]->setPosition(0.0,5.0,0.0);

		// Canon de la torreta.
		Ogre::Entity* entCanon02 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[1] = mSceneMgr->createSceneNode("nodoCanon2");
		nodosCanon[1]->attachObject(entCanon02);
		nodosTorreta[1]->addChild(nodosCanon[1]);
		nodosCanon[1]->setScale(0.65,0.65,0.65);
		nodosCanon[1]->setPosition(1.0,7.0,2.0);
		nodosCanon[1]->yaw(Degree(25));
		nodosCanon[1]->pitch(Degree(60));


		// TORRETA 3.
		Ogre::Entity* entTorreta03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[2] = mSceneMgr->createSceneNode("nodoTorreta3");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[2]);
		nodosTorreta[2]->attachObject(entTorreta03);
		nodosTorreta[2]->setPosition(22.5,-5,-407.5);

		// Pipes
		Ogre::Entity* entPipe05 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[4] = mSceneMgr->createSceneNode("nodoPipe5");
		nodosPipe[4]->attachObject(entPipe05);
		nodosTorreta[2]->addChild(nodosPipe[4]);
		nodosPipe[4]->setScale(0.65,0.65,0.65);
		nodosPipe[4]->setPosition(0.0,-2.0,0.0);

		Ogre::Entity* entPipe06 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[5] = mSceneMgr->createSceneNode("nodoPipe6");
		nodosPipe[5]->attachObject(entPipe06);
		nodosTorreta[2]->addChild(nodosPipe[5]);
		nodosPipe[5]->setScale(0.65,0.65,0.65);
		nodosPipe[5]->setPosition(0.0,3.0,0.0);

		// Forma curva.
		Ogre::Entity* entCurva03 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[2] = mSceneMgr->createSceneNode("nodoCurva3");
		nodosCurva[2]->attachObject(entCurva03);
		nodosTorreta[2]->addChild(nodosCurva[2]);
		nodosCurva[2]->setScale(0.65,0.65,0.65);
		nodosCurva[2]->setPosition(0.0,5.0,0.0);

		// Canon de la torreta.
		Ogre::Entity* entCanon03 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[2] = mSceneMgr->createSceneNode("nodoCanon3");
		nodosCanon[2]->attachObject(entCanon03);
		nodosTorreta[2]->addChild(nodosCanon[2]);
		nodosCanon[2]->setScale(0.65,0.65,0.65);
		nodosCanon[2]->setPosition(-1.0,7.0,2.0);
		nodosCanon[2]->yaw(Degree(-25));
		nodosCanon[2]->pitch(Degree(60));


		// TORRETA 4.
		Ogre::Entity* entTorreta04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[3] = mSceneMgr->createSceneNode("nodoTorreta4");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[3]);
		nodosTorreta[3]->attachObject(entTorreta04);
		nodosTorreta[3]->setPosition(22,-5,-883.5);

				// Pipes
		Ogre::Entity* entPipe07 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[6] = mSceneMgr->createSceneNode("nodoPipe7");
		nodosPipe[6]->attachObject(entPipe07);
		nodosTorreta[3]->addChild(nodosPipe[6]);
		nodosPipe[6]->setScale(0.65,0.65,0.65);
		nodosPipe[6]->setPosition(0.0,-2.0,0.0);

		Ogre::Entity* entPipe08 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[7] = mSceneMgr->createSceneNode("nodoPipe8");
		nodosPipe[7]->attachObject(entPipe08);
		nodosTorreta[3]->addChild(nodosPipe[7]);
		nodosPipe[7]->setScale(0.65,0.65,0.65);
		nodosPipe[7]->setPosition(0.0,3.0,0.0);

		// Forma curva.
		Ogre::Entity* entCurva04 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[3] = mSceneMgr->createSceneNode("nodoCurva4");
		nodosCurva[3]->attachObject(entCurva04);
		nodosTorreta[3]->addChild(nodosCurva[3]);
		nodosCurva[3]->setScale(0.65,0.65,0.65);
		nodosCurva[3]->setPosition(0.0,5.0,0.0);

		// Canon de la torreta.
		Ogre::Entity* entCanon04 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[3] = mSceneMgr->createSceneNode("nodoCanon4");
		nodosCanon[3]->attachObject(entCanon04);
		nodosTorreta[3]->addChild(nodosCanon[3]);
		nodosCanon[3]->setScale(0.65,0.65,0.65);
		nodosCanon[3]->setPosition(-1.0,7.0,2.0);
		nodosCanon[3]->yaw(Degree(-25));
		nodosCanon[3]->pitch(Degree(60));

		modificarColor(entTorreta01,0.411,0.411,0.411);
	}

	void crearAlas(){
		ManualObject* alasSuperior = mSceneMgr->createManualObject("alasSuperior");
		ManualObject* alasInferior = mSceneMgr->createManualObject("alasInferior");

		nodosAlas[0] = mSceneMgr->createSceneNode("nodoAlasSuperior");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[0]);

		nodosAlas[1] = mSceneMgr->createSceneNode("nodoAlasInferior");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[1]);

		//Ala derecha
		alasSuperior->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alasSuperior->position(4, 0, -2.5);
			alasSuperior->position(4, 0, -17.5);
			alasSuperior->position(32, 0, -17.5);
			alasSuperior->position(32, 0, -6.5);
			alasSuperior->position(8, 0, -2.5);
			alasSuperior->position(7.5, 0, -4);
			alasSuperior->position(5, 0, -4);
			alasSuperior->position(4.5, 0, -2.5);

			alasSuperior->triangle(0,7,1);
			alasSuperior->triangle(6,2,1);
			alasSuperior->quad(5,4,3,2);
			alasSuperior->triangle(6,5,2);
			alasSuperior->triangle(1,7,6);

			//Parte de abajo
			alasSuperior->position(4, -0.5, -2.5);
			alasSuperior->position(4, -0.5, -17.5);
			alasSuperior->position(32, -0.5, -17.5);
			alasSuperior->position(32, -0.5, -6.5);
			alasSuperior->position(8, -0.5, -2.5);
			alasSuperior->position(7.5, -0.5, -4);
			alasSuperior->position(5, -0.5, -4);
			alasSuperior->position(4.5, -0.5, -2.5);
			
			alasSuperior->triangle(8,15,9);
			alasSuperior->triangle(14,10,9);
			alasSuperior->quad(13,12,11,10);
			alasSuperior->triangle(14,13,10);
			alasSuperior->triangle(9,15,14);

			//Lateral izquierdo
			alasSuperior->quad(8,0,1,9);

			//Lateral derecho
			alasSuperior->quad(3,11,10,2);

			//Lateral frontal
			alasSuperior->quad(2,10,9,1);

			//Lateral trasero
			alasSuperior->quad(0,8,15,7);
			alasSuperior->quad(7,15,14,6);
			alasSuperior->quad(6,14,13,5);
			alasSuperior->quad(5,13,12,4);
			alasSuperior->quad(4,12,11,3);

		alasSuperior->end();

		//Ala izquierda
		alasSuperior->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alasSuperior->position(-4, 0, -2.5);
			alasSuperior->position(-4, 0, -17.5);
			alasSuperior->position(-32, 0, -17.5);
			alasSuperior->position(-32, 0, -6.5);
			alasSuperior->position(-8, 0, -2.5);
			alasSuperior->position(-7.5, 0, -4);
			alasSuperior->position(-5, 0, -4);
			alasSuperior->position(-4.5, 0, -2.5);

			alasSuperior->triangle(1,7,0);
			alasSuperior->triangle(1,2,6);
			alasSuperior->quad(2,3,4,5);
			alasSuperior->triangle(2,5,6);
			alasSuperior->triangle(6,7,1);
			
			//Parte de abajo
			alasSuperior->position(-4, -0.5, -2.5);
			alasSuperior->position(-4, -0.5, -17.5);
			alasSuperior->position(-32, -0.5, -17.5);
			alasSuperior->position(-32, -0.5, -6.5);
			alasSuperior->position(-8, -0.5, -2.5);
			alasSuperior->position(-7.5, -0.5, -4);
			alasSuperior->position(-5, -0.5, -4);
			alasSuperior->position(-4.5, -0.5, -2.5);

			alasSuperior->triangle(9,15,8);
			alasSuperior->triangle(9,10,14);
			alasSuperior->quad(10,11,12,13);
			alasSuperior->triangle(10,13,14);
			alasSuperior->triangle(14,15,9);

			//Lateral izquierdo
			alasSuperior->quad(8,0,1,9);

			//Lateral derecho
			alasSuperior->quad(3,11,10,2);

			//Lateral frontal
			alasSuperior->quad(2,10,9,1);

			//Lateral trasero
			alasSuperior->quad(0,8,15,7);
			alasSuperior->quad(7,15,14,6);
			alasSuperior->quad(6,14,13,5);
			alasSuperior->quad(5,13,12,4);
			alasSuperior->quad(4,12,11,3);
			
		alasSuperior->end();

		nodosAlas[0]->attachObject(alasSuperior);

		//Ala derecha
		alasInferior->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			alasInferior->position(4, -0.5, -2.5);
			alasInferior->position(4, -0.5, -17.5);
			alasInferior->position(32, -0.5, -17.5);
			alasInferior->position(32, -0.5, -6.5);
			alasInferior->position(8, -0.5, -2.5);
			alasInferior->position(7.5, -0.5, -4);
			alasInferior->position(5, -0.5, -4);
			alasInferior->position(4.5, -0.5, -2.5);

			alasInferior->triangle(0,7,1);
			alasInferior->triangle(6,2,1);
			alasInferior->quad(5,4,3,2);
			alasInferior->triangle(6,5,2);
			alasInferior->triangle(1,7,6);
			
			//Parte de abajo
			alasInferior->position(4, -1, -2.5);
			alasInferior->position(4, -1, -17.5);
			alasInferior->position(32, -1, -17.5);
			alasInferior->position(32, -1, -6.5);
			alasInferior->position(8, -1, -2.5);
			alasInferior->position(7.5, -1, -4);
			alasInferior->position(5, -1, -4);
			alasInferior->position(4.5, -1, -2.5);

			alasInferior->triangle(8,15,9);
			alasInferior->triangle(14,10,9);
			alasInferior->quad(13,12,11,10);
			alasInferior->triangle(14,13,10);
			alasInferior->triangle(9,15,14);

			//Lateral izquierdo
			alasInferior->quad(8,0,1,9);

			//Lateral derecho
			alasInferior->quad(3,11,10,2);

			//Lateral frontal
			alasInferior->quad(2,10,9,1);

			//Lateral trasero
			alasInferior->quad(0,8,15,7);
			alasInferior->quad(7,15,14,6);
			alasInferior->quad(6,14,13,5);
			alasInferior->quad(5,13,12,4);
			alasInferior->quad(4,12,11,3);

		alasInferior->end();

		//Ala izquierda
		alasInferior->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alasInferior->position(-4, -0.5, -2.5);
			alasInferior->position(-4, -0.5, -17.5);
			alasInferior->position(-32, -0.5, -17.5);
			alasInferior->position(-32, -0.5, -6.5);
			alasInferior->position(-8, -0.5, -2.5);
			alasInferior->position(-7.5, -0.5, -4);
			alasInferior->position(-5, -0.5, -4);
			alasInferior->position(-4.5, -0.5, -2.5);

			alasInferior->triangle(1,7,0);
			alasInferior->triangle(1,2,6);
			alasInferior->quad(2,3,4,5);
			alasInferior->triangle(2,5,6);
			alasInferior->triangle(6,7,1);

			//Parte de abajo
			alasInferior->position(-4, -1, -2.5);
			alasInferior->position(-4, -1, -17.5);
			alasInferior->position(-32, -1, -17.5);
			alasInferior->position(-32, -1, -6.5);
			alasInferior->position(-8, -1, -2.5);
			alasInferior->position(-7.5, -1, -4);
			alasInferior->position(-5, -1, -4);
			alasInferior->position(-4.5, -1, -2.5);

			alasInferior->triangle(9,15,8);
			alasInferior->triangle(9,10,14);
			alasInferior->quad(10,11,12,13);
			alasInferior->triangle(10,13,14);
			alasInferior->triangle(14,15,9);

			//Lateral izquierdo
			alasInferior->quad(8,0,1,9);

			//Lateral derecho
			alasInferior->quad(3,11,10,2);

			//Lateral frontal
			alasInferior->quad(2,10,9,1);

			//Lateral trasero
			alasInferior->quad(0,8,15,7);
			alasInferior->quad(7,15,14,6);
			alasInferior->quad(6,14,13,5);
			alasInferior->quad(5,13,12,4);
			alasInferior->quad(4,12,11,3);
			
		alasInferior->end();

		nodosAlas[1]->attachObject(alasInferior);
	}

	void crearCentroNave(){
		ManualObject* centroNave = mSceneMgr->createManualObject("centroNave");
		nodoNave = mSceneMgr->createSceneNode("nodoNave");
		mSceneMgr->getRootSceneNode()->addChild(nodoNave);


		/*
			|		|
			|		|
		 ---|		|---
			---------
		*/
		centroNave->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba del centro de la nave
			centroNave->position(-3, 2.5, 0);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(3, 2.5, -13);
			centroNave->position(3, 2.5, 0);
			
			centroNave->quad(0,3,2,1);

			//Parte de abajo del centro de la nave
			centroNave->position(-3, -2.5, 0);
			centroNave->position(-3, -2.5, -13);
			centroNave->position(3, -2.5, -13);
			centroNave->position(3, -2.5, 0);
			
			centroNave->quad(5,6,7,4);

			//Parte trasera del centro de la nave
			centroNave->position(-3, -2.5, 0);
			centroNave->position(-4, 0, 0);
			centroNave->position(-3, 2.5, 0);
			centroNave->position(3, 2.5, 0);
			centroNave->position(4, 0, 0);
			centroNave->position(3, -2.5, 0);
			
			centroNave->triangle(10,9,8);
			centroNave->quad(8,13,11,10);
			centroNave->triangle(13,12,11);

			//Parte frontal del centro de la nave
			centroNave->position(-3, -2.5, -13);
			centroNave->position(-4, 0, -13);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(3, 2.5, -13);
			centroNave->position(4, 0, -13);
			centroNave->position(3, -2.5, -13);
			
			centroNave->triangle(16,15,14);
			centroNave->quad(14,19,17,16);
			centroNave->triangle(19,18,17);

			//Lateral izquierdo del centro de la nave
			centroNave->quad(8,9,15,14);
			centroNave->quad(9,10,16,15);

			//Lateral derecho del centro de la nave
			centroNave->quad(19,18,12,13);
			centroNave->quad(11,12,18,17);


		centroNave->end();


		//Sección frontal de la cabina
		/*    | |
		     |   |
			|     |
			-------
		*/
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(-2, 1.5, -33);
			centroNave->position(2, 1.5, -33);
			centroNave->position(3, 2.5, -13);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
		centroNave->end();

		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, -2.5, -13);
			centroNave->position(-2, -1.5, -33);
			centroNave->position(2, -1.5, -33);
			centroNave->position(3, -2.5, -13);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
		centroNave->end();

		//Punta de la nave superior
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-2, 1.5, -33);
			centroNave->position(-0.5, 1, -35);
			centroNave->position(0.5, 1, -35);
			centroNave->position(2, 1.5, -33);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
		centroNave->end();

		//Punta de la nave inferior
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-2, -1.5, -33);
			centroNave->position(-0.5, -1, -35);
			centroNave->position(0.5, -1, -35);
			centroNave->position(2, -1.5, -33);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
		centroNave->end();


		nodoNave->attachObject(centroNave);
	}

	void crearNave(){
		crearCentroNave();
		crearAlas();
	}

	void createScene() {

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		

		/*Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");*/
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		/*node01->attachObject(ent01);*/
		

		Ogre::Entity* entEscena01 = mSceneMgr->createEntity("ogre_base01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena01);

		Ogre::Entity* entEscena02 = mSceneMgr->createEntity("ogre_fondo01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena02);

		Ogre::Entity* entEscena03 = mSceneMgr->createEntity("ogre_pared01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena03);

		Ogre::Entity* entEscena04 = mSceneMgr->createEntity("ogre_pared02.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena04);

		Ogre::Entity* entEscena05 = mSceneMgr->createEntity("ogre_pared03.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena05);

		Ogre::Entity* entEscena06 = mSceneMgr->createEntity("ogre_torretas01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena06);
		
		crearTorretas();
		crearNave();
	}
};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}