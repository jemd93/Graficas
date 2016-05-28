#include "Ogre\ExampleApplication.h"

class Example1 : public ExampleApplication
{

public:
	Ogre::SceneNode* nodoTorreta1;
	Ogre::SceneNode* nodoTorreta2;
	Ogre::SceneNode* nodoTorreta3;
	Ogre::SceneNode* nodoTorreta4;

	Ogre::SceneNode* nodoPipe1;
	Ogre::SceneNode* nodoPipe2;

	Ogre::SceneNode* nodoCurva1;

	Ogre::SceneNode* nodoCanon1;

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
		Ogre::Entity* entTorreta01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodoTorreta1 = mSceneMgr->createSceneNode("nodoTorreta1");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta1);
		nodoTorreta1->attachObject(entTorreta01);
		nodoTorreta1->setPosition(-22,-5,-227);

		Ogre::Entity* entPipe01 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodoPipe1 = mSceneMgr->createSceneNode("nodoPipe1");
		nodoPipe1->attachObject(entPipe01);
		nodoTorreta1->addChild(nodoPipe1);
		nodoPipe1->setScale(0.65,0.65,0.65);
		nodoPipe1->setPosition(0.0,-2.0,0.0);

		Ogre::Entity* entPipe02 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodoPipe2 = mSceneMgr->createSceneNode("nodoPipe2");
		nodoPipe2->attachObject(entPipe02);
		nodoTorreta1->addChild(nodoPipe2);
		nodoPipe2->setScale(0.65,0.65,0.65);
		nodoPipe2->setPosition(0.0,3.0,0.0);

		Ogre::Entity* entCurva01 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodoCurva1 = mSceneMgr->createSceneNode("nodoCurva1");
		nodoCurva1->attachObject(entCurva01);
		nodoTorreta1->addChild(nodoCurva1);
		nodoCurva1->setScale(0.65,0.65,0.65);
		nodoCurva1->setPosition(0.0,5.0,0.0);

		// Canon de la torreta
		//Ogre::Entity* entCanon01 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		//nodoCanon1 = mSceneMgr->createSceneNode("nodoCanon1");
		//nodoCanon1->attachObject(entCanon01);
		//nodoTorreta1->addChild(nodoCanon1);
		//nodoCanon1->setScale(0.65,0.65,0.65);
		//nodoCanon1->setPosition(0.0,10.0,0.0);
		//nodoCanon1->pitch(Degree(45));
		//nodoCanon1->roll(Degree(45));



		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodoTorreta2 = mSceneMgr->createSceneNode("nodoTorreta2");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta2);
		nodoTorreta2->attachObject(entTorreta02);
		nodoTorreta2->setPosition(-22.5,-5,-638);
		
		Ogre::Entity* entTorreta03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodoTorreta3 = mSceneMgr->createSceneNode("nodoTorreta3");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta3);
		nodoTorreta3->attachObject(entTorreta03);
		nodoTorreta3->setPosition(22.5,-5,-407.5);

		Ogre::Entity* entTorreta04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodoTorreta4 = mSceneMgr->createSceneNode("nodoTorreta4");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta4);
		nodoTorreta4->attachObject(entTorreta04);
		nodoTorreta4->setPosition(22,-5,-883.5);

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