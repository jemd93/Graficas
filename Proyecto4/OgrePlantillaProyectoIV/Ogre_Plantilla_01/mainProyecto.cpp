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
		ManualObject* alas = mSceneMgr->createManualObject("alas");
		//Ala derecha
		alas->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			alas->position(4, 0, -2.5);
			alas->position(4, 0, -17.5);
			alas->position(32, 0, -17.5);
			alas->position(32, 0, -3.5);
			alas->position(8, 0, -2.5);
			alas->position(7.5, 0, -4);
			alas->position(5, 0, -4);
			alas->position(4.5, 0, -2.5);
			
			alas->index(0);
			alas->index(1);
			alas->index(2);
			alas->index(3);
			alas->index(4);
			alas->index(5);
			alas->index(6);
			alas->index(7);
			alas->index(0);
		alas->end();

		//Ala izquierda
		alas->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			alas->position(-4, 0, -2.5);
			alas->position(-4, 0, -17.5);
			alas->position(-32, 0, -17.5);
			alas->position(-32, 0, -3.5);
			alas->position(-8, 0, -2.5);
			alas->position(-7.5, 0, -4);
			alas->position(-5, 0, -4);
			alas->position(-4.5, 0, -2.5);
			
			alas->index(0);
			alas->index(1);
			alas->index(2);
			alas->index(3);
			alas->index(4);
			alas->index(5);
			alas->index(6);
			alas->index(7);
			alas->index(0);
		alas->end();

		mSceneMgr->getRootSceneNode()->attachObject(alas);
	}

	void crearCentroNave(){
		ManualObject* centroNave = mSceneMgr->createManualObject("centroNave");

		//Parte de arriba del centro de la nave
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, 2.5, 0);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(3, 2.5, -13);
			centroNave->position(3, 2.5, 0);
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
			centroNave->index(0);
		centroNave->end();

		//Parte de abajo del centro de la nave
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, -2.5, 0);
			centroNave->position(-3, -2.5, -13);
			centroNave->position(3, -2.5, -13);
			centroNave->position(3, -2.5, 0);
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
			centroNave->index(0);
		centroNave->end();

		//Parte trasera del centro de la nave
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, -2.5, 0);
			centroNave->position(-4, 0, 0);
			centroNave->position(-3, 2.5, 0);
			centroNave->position(3, 2.5, 0);
			centroNave->position(4, 0, 0);
			centroNave->position(3, -2.5, 0);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
			centroNave->index(4);
			centroNave->index(5);
			centroNave->index(0);
		centroNave->end();

		//Parte frontal del centro de la nave
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, -2.5, -13);
			centroNave->position(-4, 0, -13);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(3, 2.5, -13);
			centroNave->position(4, 0, -13);
			centroNave->position(3, -2.5, -13);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
			centroNave->index(4);
			centroNave->index(5);
			centroNave->index(0);
		centroNave->end();

		//Sección frontal de la cabina
		centroNave->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
			centroNave->position(-3, -2.5, -13);
			centroNave->position(-4, 0, -13);
			centroNave->position(-3, 2.5, -13);
			centroNave->position(3, 2.5, -13);
			centroNave->position(4, 0, -13);
			centroNave->position(3, -2.5, -13);
			
			centroNave->index(0);
			centroNave->index(1);
			centroNave->index(2);
			centroNave->index(3);
			centroNave->index(4);
			centroNave->index(5);
			centroNave->index(0);
		centroNave->end();

		mSceneMgr->getRootSceneNode()->attachObject(centroNave);
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