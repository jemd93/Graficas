#include "Ogre\ExampleApplication.h"

float laserPos[4] = {0.0,0.0,0.0,0.0};


// Nodos para torretas.
Ogre::SceneNode* nodosTorreta[4];

// Nodos para pipes.
Ogre::SceneNode* nodosPipe[8];

// Nodos para formas curvas.
Ogre::SceneNode* nodosCurva[4];

// Nodos para canones.
Ogre::SceneNode* nodosCanon[4];

// Nodos para lasers.
Ogre::SceneNode* nodosLaser[4];

// Luz para las torretas
Ogre::Light* lucesTorr[4];
Ogre::SceneNode* nodosLuz[4];
Ogre::SceneNode* nodoEsfera1;

//Nodo para la nave
Ogre::SceneNode* nodoNave;

//Nodo para las alas (superiores e inferiores)
Ogre::SceneNode* nodosAlas[2];

//Nodos para los misiles de la nave
Ogre::SceneNode* nodosMisiles[4];

class FrameListenerProy : public Ogre::FrameListener {
private :
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;
	
	Ogre::Timer _timer[4];

public:
	FrameListenerProy(Ogre::Camera* cam, RenderWindow* win) {
		size_t windowHnd = 0;
		std::stringstream windowHndStr;
		win->getCustomAttribute("WINDOW",&windowHnd);
		windowHndStr << windowHnd;

		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"),windowHndStr.str()));

		// Eventos
		_man = OIS::InputManager::createInputSystem(pl);
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard,false));
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse,false));

		_cam = cam;

		for (int i = 0;i < 4;i++){
			_timer[i].reset();
		}

	}

	~FrameListenerProy() {
		_man->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
		_key->capture();
		_mouse->capture();

		float movSpeed = 10.0f;

		Ogre::Vector3 tmov(0,0,0);
		Ogre::Vector3 tcam(0,0,0);

		if (_key->isKeyDown(OIS::KC_ESCAPE) || _key->isKeyDown(OIS::KC_Q))
			return false;

		if (_key->isKeyDown(OIS::KC_W)){
			tcam+=Ogre::Vector3(0,0,-10);
		}
		if (_key->isKeyDown(OIS::KC_S)){
			tcam+=Ogre::Vector3(0,0,10);
		}
		if (_key->isKeyDown(OIS::KC_A)){
			tcam+=Ogre::Vector3(-10,0,0);
		}
		if (_key->isKeyDown(OIS::KC_D)){
			tcam+=Ogre::Vector3(10,0,0);
		}

		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame* -1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(tcam*movSpeed*evt.timeSinceLastFrame);

		for (int i = 0;i < 4;i++) {
			nodosLaser[i]->setPosition(0.0,laserPos[i],0.0);
			if (_timer[i].getMilliseconds() > 2000) {
				_timer[i].reset();
				laserPos[i] = 0.0;
			}
			else {
				laserPos[i] += 1;
			}
		}


		return true;
	}
};

class Example1 : public ExampleApplication
{

public:

	// Frame Listener
	Ogre::FrameListener* frameListener;

	Example1() {
		frameListener = NULL;
	}

	~Example1() {
		if (frameListener) {
			delete frameListener;
		}
	}

	void createFrameListener() {
		frameListener = new FrameListenerProy(mCamera,mWindow);
		mRoot->addFrameListener(frameListener);
	}

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,10,50);
		mCamera->lookAt(0,0,-50);
		mCamera->setNearClipDistance(5);

	}

	void modificarColor(Ogre::Entity* entidad,float r, float g, float b) {
		Ogre::MaterialPtr m_pMat = entidad->getSubEntity(0)->getMaterial();
		//m_pMat->getTechnique(0)->getPass(0)->setAmbient(r,g,b);
		//m_pMat->getTechnique(0)->getPass(0)->setDiffuse(1.0,1.0,1.0,1.0);
		//entidad->setMaterialName(m_pMat->getName());
	}

	void crearTorretas() {

		// TORRETA 1.
		Ogre::Entity* entTorreta01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[0] = mSceneMgr->createSceneNode("nodoTorreta1");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[0]);
		nodosTorreta[0]->attachObject(entTorreta01);
		nodosTorreta[0]->setPosition(-22,-5,-227);
		entTorreta01->setMaterialName("matTorretas01");

		// Pipes
		Ogre::Entity* entPipe01 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[0] = mSceneMgr->createSceneNode("nodoPipe1");
		nodosPipe[0]->attachObject(entPipe01);
		nodosTorreta[0]->addChild(nodosPipe[0]);
		nodosPipe[0]->setScale(0.65,0.65,0.65);
		nodosPipe[0]->setPosition(0.0,-2.0,0.0);
		entPipe01->setMaterialName("matTorretas01");

		Ogre::Entity* entPipe02 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[1] = mSceneMgr->createSceneNode("nodoPipe2");
		nodosPipe[1]->attachObject(entPipe02);
		nodosTorreta[0]->addChild(nodosPipe[1]);
		nodosPipe[1]->setScale(0.65,0.65,0.65);
		nodosPipe[1]->setPosition(0.0,3.0,0.0);
		entPipe02->setMaterialName("matTorretas01");

		// Forma curva.
		Ogre::Entity* entCurva01 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[0] = mSceneMgr->createSceneNode("nodoCurva1");
		nodosCurva[0]->attachObject(entCurva01);
		nodosTorreta[0]->addChild(nodosCurva[0]);
		nodosCurva[0]->setScale(0.65,0.65,0.65);
		nodosCurva[0]->setPosition(0.0,5.0,0.0);
		entCurva01->setMaterialName("matTorretas01");

		// Canon de la torreta
		Ogre::Entity* entCanon01 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[0] = mSceneMgr->createSceneNode("nodoCanon1");
		nodosCanon[0]->attachObject(entCanon01);
		nodosTorreta[0]->addChild(nodosCanon[0]);
		nodosCanon[0]->setScale(0.65,0.65,0.65);
		nodosCanon[0]->setPosition(1.0,7.0,2.0);
		nodosCanon[0]->yaw(Degree(25));
		nodosCanon[0]->pitch(Degree(60));
		entCanon01->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser01 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[0] = mSceneMgr->createSceneNode("nodoLaser1");
		nodosLaser[0]->attachObject(entLaser01);
		nodosCanon[0]->addChild(nodosLaser[0]);

		// Luz
		//lucesTorr[0] = mSceneMgr->createLight("Luz1");
		//lucesTorr[0]->setType(Ogre::Light::LT_POINT);
		//lucesTorr[0]->setDiffuseColour(1.0,1.0,1.0);
		//lucesTorr[0]->setPosition(0,0,0);
		//
		//nodosLuz[0] = mSceneMgr->createSceneNode("nodoLuz1");
		//nodosLuz[0]->attachObject(lucesTorr[0]);
		//nodosTorreta[0]->addChild(nodosLuz[0]);
		//nodosLuz[0]->setPosition(0,0,10);

		//Ogre::Entity* entEsferaPrueba = mSceneMgr->createEntity("EsferaLuz1",Ogre::SceneManager::PT_SPHERE);
		//nodoEsfera1 = mSceneMgr->createSceneNode("nodoEsferaLuz1");
		//mSceneMgr->getRootSceneNode()->addChild(nodoEsfera1);
		//nodoEsfera1->attachObject(entEsferaPrueba);
		//entEsferaPrueba->setCastShadows(false);
		//nodoEsfera1->addChild(nodosLuz[0]);
		//nodoEsfera1->setScale(0.03,0.03,0.03);
		//nodoEsfera1->setPosition(30,30,0);



		// TORRETA 2.
		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[1] = mSceneMgr->createSceneNode("nodoTorreta2");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[1]);
		nodosTorreta[1]->attachObject(entTorreta02);
		nodosTorreta[1]->setPosition(-22.5,-5,-638);
		entTorreta02->setMaterialName("matTorretas01");
		
		// Pipes
		Ogre::Entity* entPipe03 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[2] = mSceneMgr->createSceneNode("nodoPipe3");
		nodosPipe[2]->attachObject(entPipe03);
		nodosTorreta[1]->addChild(nodosPipe[2]);
		nodosPipe[2]->setScale(0.65,0.65,0.65);
		nodosPipe[2]->setPosition(0.0,-2.0,0.0);
		entPipe03->setMaterialName("matTorretas01");

		Ogre::Entity* entPipe04 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[3] = mSceneMgr->createSceneNode("nodoPipe4");
		nodosPipe[3]->attachObject(entPipe04);
		nodosTorreta[1]->addChild(nodosPipe[3]);
		nodosPipe[3]->setScale(0.65,0.65,0.65);
		nodosPipe[3]->setPosition(0.0,3.0,0.0);
		entPipe04->setMaterialName("matTorretas01");

		// Forma curva.
		Ogre::Entity* entCurva02 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[1] = mSceneMgr->createSceneNode("nodoCurva2");
		nodosCurva[1]->attachObject(entCurva02);
		nodosTorreta[1]->addChild(nodosCurva[1]);
		nodosCurva[1]->setScale(0.65,0.65,0.65);
		nodosCurva[1]->setPosition(0.0,5.0,0.0);
		entCurva02->setMaterialName("matTorretas01");

		// Canon de la torreta.
		Ogre::Entity* entCanon02 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[1] = mSceneMgr->createSceneNode("nodoCanon2");
		nodosCanon[1]->attachObject(entCanon02);
		nodosTorreta[1]->addChild(nodosCanon[1]);
		nodosCanon[1]->setScale(0.65,0.65,0.65);
		nodosCanon[1]->setPosition(1.0,7.0,2.0);
		nodosCanon[1]->yaw(Degree(25));
		nodosCanon[1]->pitch(Degree(60));
		entCanon02->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser02 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[1] = mSceneMgr->createSceneNode("nodoLaser2");
		nodosLaser[1]->attachObject(entLaser02);
		nodosCanon[1]->addChild(nodosLaser[1]);


		// TORRETA 3.
		Ogre::Entity* entTorreta03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[2] = mSceneMgr->createSceneNode("nodoTorreta3");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[2]);
		nodosTorreta[2]->attachObject(entTorreta03);
		nodosTorreta[2]->setPosition(22.5,-5,-407.5);
		entTorreta03->setMaterialName("matTorretas01");

		// Pipes
		Ogre::Entity* entPipe05 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[4] = mSceneMgr->createSceneNode("nodoPipe5");
		nodosPipe[4]->attachObject(entPipe05);
		nodosTorreta[2]->addChild(nodosPipe[4]);
		nodosPipe[4]->setScale(0.65,0.65,0.65);
		nodosPipe[4]->setPosition(0.0,-2.0,0.0);
		entPipe05->setMaterialName("matTorretas01");

		Ogre::Entity* entPipe06 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[5] = mSceneMgr->createSceneNode("nodoPipe6");
		nodosPipe[5]->attachObject(entPipe06);
		nodosTorreta[2]->addChild(nodosPipe[5]);
		nodosPipe[5]->setScale(0.65,0.65,0.65);
		nodosPipe[5]->setPosition(0.0,3.0,0.0);
		entPipe06->setMaterialName("matTorretas01");

		// Forma curva.
		Ogre::Entity* entCurva03 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[2] = mSceneMgr->createSceneNode("nodoCurva3");
		nodosCurva[2]->attachObject(entCurva03);
		nodosTorreta[2]->addChild(nodosCurva[2]);
		nodosCurva[2]->setScale(0.65,0.65,0.65);
		nodosCurva[2]->setPosition(0.0,5.0,0.0);
		entCurva03->setMaterialName("matTorretas01");

		// Canon de la torreta.
		Ogre::Entity* entCanon03 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[2] = mSceneMgr->createSceneNode("nodoCanon3");
		nodosCanon[2]->attachObject(entCanon03);
		nodosTorreta[2]->addChild(nodosCanon[2]);
		nodosCanon[2]->setScale(0.65,0.65,0.65);
		nodosCanon[2]->setPosition(-1.0,7.0,2.0);
		nodosCanon[2]->yaw(Degree(-25));
		nodosCanon[2]->pitch(Degree(60));
		entCanon03->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser03 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[2] = mSceneMgr->createSceneNode("nodoLaser3");
		nodosLaser[2]->attachObject(entLaser03);
		nodosCanon[2]->addChild(nodosLaser[2]);

		// TORRETA 4.
		Ogre::Entity* entTorreta04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[3] = mSceneMgr->createSceneNode("nodoTorreta4");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[3]);
		nodosTorreta[3]->attachObject(entTorreta04);
		nodosTorreta[3]->setPosition(22,-5,-883.5);
		entTorreta04->setMaterialName("matTorretas01");

		// Pipes
		Ogre::Entity* entPipe07 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[6] = mSceneMgr->createSceneNode("nodoPipe7");
		nodosPipe[6]->attachObject(entPipe07);
		nodosTorreta[3]->addChild(nodosPipe[6]);
		nodosPipe[6]->setScale(0.65,0.65,0.65);
		nodosPipe[6]->setPosition(0.0,-2.0,0.0);
		entPipe07->setMaterialName("matTorretas01");

		Ogre::Entity* entPipe08 = mSceneMgr->createEntity("usb_pipe.mesh");
		nodosPipe[7] = mSceneMgr->createSceneNode("nodoPipe8");
		nodosPipe[7]->attachObject(entPipe08);
		nodosTorreta[3]->addChild(nodosPipe[7]);
		nodosPipe[7]->setScale(0.65,0.65,0.65);
		nodosPipe[7]->setPosition(0.0,3.0,0.0);
		entPipe08->setMaterialName("matTorretas01");

		// Forma curva.
		Ogre::Entity* entCurva04 = mSceneMgr->createEntity("usb_formacurva.mesh");
		nodosCurva[3] = mSceneMgr->createSceneNode("nodoCurva4");
		nodosCurva[3]->attachObject(entCurva04);
		nodosTorreta[3]->addChild(nodosCurva[3]);
		nodosCurva[3]->setScale(0.65,0.65,0.65);
		nodosCurva[3]->setPosition(0.0,5.0,0.0);
		entCurva04->setMaterialName("matTorretas01");

		// Canon de la torreta.
		Ogre::Entity* entCanon04 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[3] = mSceneMgr->createSceneNode("nodoCanon4");
		nodosCanon[3]->attachObject(entCanon04);
		nodosTorreta[3]->addChild(nodosCanon[3]);
		nodosCanon[3]->setScale(0.65,0.65,0.65);
		nodosCanon[3]->setPosition(-1.0,7.0,2.0);
		nodosCanon[3]->yaw(Degree(-25));
		nodosCanon[3]->pitch(Degree(60));
		entCanon04->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser04 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[3] = mSceneMgr->createSceneNode("nodoLaser4");
		nodosLaser[3]->attachObject(entLaser04);
		nodosCanon[3]->addChild(nodosLaser[3]);

		modificarColor(entLaser01,1.0,0.0,0.0);
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
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(4, 0, -17.5);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(20, 0, -17.5);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(20, 0, -6.5);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(8, 0, -2.5);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(7.5, 0, -4);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(5, 0, -4);
			//alasSuperior->normal(0.0,1.0,0.0);
			alasSuperior->position(4.5, 0, -2.5);


			alasSuperior->triangle(0,7,1);
			alasSuperior->triangle(6,2,1);
			alasSuperior->quad(5,4,3,2);
			alasSuperior->triangle(6,5,2);
			alasSuperior->triangle(1,7,6);

			//Parte de abajo
			alasSuperior->position(4, -0.5, -2.5);
			alasSuperior->position(4, -0.5, -17.5);
			alasSuperior->position(20, -0.5, -17.5);
			alasSuperior->position(20, -0.5, -6.5);
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
			alasSuperior->position(-20, 0, -17.5);
			alasSuperior->position(-20, 0, -6.5);
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
			alasSuperior->position(-20, -0.5, -17.5);
			alasSuperior->position(-20, -0.5, -6.5);
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
			alasInferior->position(20, -0.5, -17.5);
			alasInferior->position(20, -0.5, -6.5);
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
			alasInferior->position(20, -1, -17.5);
			alasInferior->position(20, -1, -6.5);
			alasInferior->position(8, -1, -2.5);
			alasInferior->position(7.5, -1, -4);
			alasInferior->position(5, -1, -4);
			alasInferior->position(4.5, -1, -2.5);

			/*alasInferior->triangle(8,15,9);
			alasInferior->triangle(14,10,9);
			alasInferior->quad(13,12,11,10);
			alasInferior->triangle(14,13,10);
			alasInferior->triangle(9,15,14);*/
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

		//Ala izquierda
		alasInferior->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alasInferior->position(-4, -0.5, -2.5);
			alasInferior->position(-4, -0.5, -17.5);
			alasInferior->position(-20, -0.5, -17.5);
			alasInferior->position(-20, -0.5, -6.5);
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
			alasInferior->position(-20, -1, -17.5);
			alasInferior->position(-20, -1, -6.5);
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
		centroNave->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			centroNave->position(-3, 2.5, -13);
			centroNave->position(-2, 1.5, -33);
			centroNave->position(2, 1.5, -33);
			centroNave->position(3, 2.5, -13);
			
			centroNave->quad(3,2,1,0);

			//Parte de abajo
			centroNave->position(-3, -2.5, -13);
			centroNave->position(-2, -1.5, -33);
			centroNave->position(2, -1.5, -33);
			centroNave->position(3, -2.5, -13);

			centroNave->quad(4,5,6,7);

			//Punta superior de la nave
			centroNave->position(-2, 1.5, -33);
			centroNave->position(-0.5, 0.5, -35);
			centroNave->position(0.5, 0.5, -35);
			centroNave->position(2, 1.5, -33);

			centroNave->quad(11,10,9,8);

			//Punta inferior de la nave
			centroNave->position(-2, -1.5, -33);
			centroNave->position(-0.5, -0.5, -35);
			centroNave->position(0.5, -0.5, -35);
			centroNave->position(2, -1.5, -33);

			centroNave->quad(12,13,14,15);
			
			//Lateral izquierdo de la punta
			centroNave->quad(8,9,13,12);

			//Lateral derecho de la punta
			centroNave->quad(15,14,10,11);

			//Lateral izquierdo de la nave
			centroNave->position(-4, 0, -13); //Medio izquierdo atrás
			centroNave->position(-2, 0, -33); //Medio de la punta

			centroNave->quad(4,16,17,12);
			centroNave->quad(0,8,17,16);

			//Lateral derecho de la nave
			centroNave->position(4, 0, -13); //Medio derecho atrás
			centroNave->position(2, 0, -33); //Medio de la punta

			centroNave->quad(7,15,19,18);
			centroNave->quad(3,18,19,11);
		centroNave->end();


		nodoNave->attachObject(centroNave);
	}

	void agregarMisiles(int numMisil, float x, float y){
		nodosMisiles[numMisil] = mSceneMgr->createSceneNode("nodoMisil"+std::to_string(numMisil));

		Ogre::SceneNode* nodoCilindro;
		Ogre::Entity* entCilindro = mSceneMgr->createEntity("usb_cilindro.mesh");
		//entCilindro->setMaterialName("matTorretas01");
		nodoCilindro = mSceneMgr->createSceneNode("nodoCilindro"+std::to_string(numMisil));
		mSceneMgr->getRootSceneNode()->addChild(nodosMisiles[numMisil]);
		nodosMisiles[numMisil]->addChild(nodoCilindro);
		nodoCilindro->attachObject(entCilindro);
		nodoCilindro->setPosition(x,y,-6);
		nodoCilindro->setScale(0.2,0.5,0.2);
		nodoCilindro->roll(Degree(90));
		nodoCilindro->pitch(Degree(90));

		Ogre::SceneNode* nodoPipeMisil;
		Ogre::Entity* entPipe = mSceneMgr->createEntity("usb_pipe.mesh");
		//entPipe->setMaterialName("matBase01");
		nodoPipeMisil = mSceneMgr->createSceneNode("nodoPipeMisil"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoPipeMisil);
		nodoPipeMisil->attachObject(entPipe);
		nodoPipeMisil->setPosition(x,y,-9.2);
		nodoPipeMisil->setScale(0.10,0.10,0.10);
		nodoPipeMisil->pitch(Degree(90));

		Ogre::SceneNode* nodoCilindro2;
		Ogre::Entity* entCilindro2 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		entCilindro2->setMaterialName("Examples/RustySteel");
		nodoCilindro2 = mSceneMgr->createSceneNode("nodoCilindro2"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCilindro2);
		nodoCilindro2->attachObject(entCilindro2);
		nodoCilindro2->setPosition(x,y,-11);
		nodoCilindro2->setScale(0.025,0.5,0.025);
		nodoCilindro2->roll(Degree(90));
		nodoCilindro2->pitch(Degree(-90));

		Ogre::SceneNode* nodoCurvo;
		Ogre::Entity* entCurvo = mSceneMgr->createEntity("usb_formacurva.mesh");
		//entCurvo->setMaterialName("matTorretas01");
		nodoCurvo = mSceneMgr->createSceneNode("nodoCurvo"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo);
		nodoCurvo->attachObject(entCurvo);
		nodoCurvo->setPosition(x,y,-13);
		nodoCurvo->setScale(0.08,0.08,0.08);
		nodoCurvo->pitch(Degree(-90));
		
		Ogre::SceneNode* nodoCurvo2;
		Ogre::Entity* entCurvo2 = mSceneMgr->createEntity("usb_formacurva.mesh");
		//entCurvo2->setMaterialName("matTorretas01");
		nodoCurvo2 = mSceneMgr->createSceneNode("nodoCurvo2"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo2);
		nodoCurvo2->attachObject(entCurvo2);
		nodoCurvo2->setPosition(x,y,-13.3);
		nodoCurvo2->setScale(0.07,0.07,0.07);
		nodoCurvo2->pitch(Degree(-45));

		Ogre::SceneNode* nodoCurvo3;
		Ogre::Entity* entCurvo3 = mSceneMgr->createEntity("usb_formacurva.mesh");
		//entCurvo3->setMaterialName("matTorretas01");
		nodoCurvo3 = mSceneMgr->createSceneNode("nodoCurvo3"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo3);
		nodoCurvo3->attachObject(entCurvo3);
		nodoCurvo3->setPosition(x,y,-13.3);
		nodoCurvo3->setScale(0.07,0.07,0.07);
		nodoCurvo3->pitch(Degree(45));

	}

	void agregarTurbinas(int numTurbina, float x, float y){
		Ogre::SceneNode* nodoTurbina;
		Ogre::Entity* entTurbina = mSceneMgr->createEntity("usb_cilindro.mesh");
		entTurbina->setMaterialName("matTorretas01");
		nodoTurbina = mSceneMgr->createSceneNode("nodoTurbina"+std::to_string(numTurbina));
		mSceneMgr->getRootSceneNode()->addChild(nodoTurbina);
		nodoTurbina->attachObject(entTurbina);
		nodoTurbina->setPosition(x,y,-2);
		nodoTurbina->setScale(0.3,0.7,0.3);
		nodoTurbina->roll(Degree(90));
		nodoTurbina->pitch(Degree(90));

		Ogre::SceneNode* nodoTurbina2;
		Ogre::Entity* entTurbina2 = mSceneMgr->createEntity("usb_cilindro.mesh");
		entTurbina2->setMaterialName("matTorretas01");
		nodoTurbina2 = mSceneMgr->createSceneNode("nodoTurbina2"+std::to_string(numTurbina));
		mSceneMgr->getRootSceneNode()->addChild(nodoTurbina2);
		nodoTurbina2->attachObject(entTurbina2);
		nodoTurbina2->setPosition(x,y+1,-7);
		nodoTurbina2->setScale(0.5,0.3,0.5);
		nodoTurbina2->roll(Degree(90));
		nodoTurbina2->pitch(Degree(90));
	}

	void crearNave(){
		crearCentroNave();
		crearAlas();
		nodoNave->scale(0.5,0.5,0.5);
		nodosAlas[0]->scale(0.5,0.5,0.5);
		nodosAlas[1]->scale(0.5,0.5,0.5);
		for(int i = 0 ; i < 4; i++){
			agregarMisiles(i,((i==0 || i==1) ? 10 : -10),((i==1 || i==3) ? 0.6 : -1.1));
			//agregarTurbinas(i,((i==0 || i==1) ? 3 : -3),((i==1 || i==3) ? 0.6 : -1.1));
		}
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

		//mSceneMgr->setSkyBox(true, "skyBoxSW1",5000);
		mSceneMgr->setSkyBox(true, "skyBoxSW2",5000);
		//mSceneMgr->setSkyBox(true, "skyBoxSW3",5000);
	}
};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}