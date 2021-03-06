#include "Ogre\ExampleApplication.h"

//NOTA: La luz se encuentra pegada encima del centro de la nave 

float laserPos[4] = {0.0,-7.0,-7.0,-7.0};
float laserAlt[4] = {0.0,36.0,36.0,36.0};

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

int laserFinal = 2;

// Luz para las torretas y nave
Ogre::Light* luz;
Ogre::SceneNode* nodoLuz;

//Nodo para la nave
Ogre::SceneNode* nodoNave;

//Nodo para las alas (superiores e inferiores)
Ogre::SceneNode* nodosAlas[4];
float anguloAlas = 0.2;
bool abriendo = false;
bool cerrando = false;
bool abiertas = false;
bool cerradas = true;


//Nodos para los misiles de la nave
Ogre::SceneNode* nodosMisiles[4];

// Posicion de la nave.
float naveZ = 0.0;
float naveX = 0.0;
float anguloNave = 0.5;
float anguloMax = 28;
float anguloAct = 0.0;
float anguloNActual = 0.0;

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

	/* 
		M�todo para rotar la nave cuando se presionan las teclas A o D
	*/
	void rotarNave() {
		nodoNave->roll(Degree(anguloNave));
		for (int i = 0; i < 4;i++) {
			nodosAlas[i]->roll(Degree(anguloNave));
			nodosMisiles[i]->roll(Degree(anguloNave));
		}
	}

	/*
		M�todo que permite abrir y cerrar las alas seg�n la entrada de teclado.
	*/
	void rotarAlas() {
		if (abriendo) {
			if (anguloAct < anguloMax) {
				nodosAlas[0]->roll(Degree(-anguloAlas));
				nodosMisiles[3]->roll(Degree(-anguloAlas));

				nodosAlas[1]->roll(Degree(anguloAlas));
				nodosMisiles[2]->roll(Degree(anguloAlas));

				nodosAlas[2]->roll(Degree(-anguloAlas));
				nodosMisiles[0]->roll(Degree(-anguloAlas));

				nodosAlas[3]->roll(Degree(anguloAlas));
				nodosMisiles[1]->roll(Degree(anguloAlas));

				anguloAct += 0.5;
			}
			else {
				abriendo = false;
				abiertas = true;
			}
		}
		else if (cerrando) {
			if (anguloAct > 0.0) {
				nodosAlas[0]->roll(Degree(anguloAlas));
				nodosMisiles[3]->roll(Degree(anguloAlas));

				nodosAlas[1]->roll(Degree(-anguloAlas));
				nodosMisiles[2]->roll(Degree(-anguloAlas));

				nodosAlas[2]->roll(Degree(anguloAlas));
				nodosMisiles[0]->roll(Degree(anguloAlas));

				nodosAlas[3]->roll(Degree(-anguloAlas));
				nodosMisiles[1]->roll(Degree(-anguloAlas));

				anguloAct -= 0.5;
			}
			else {
				cerradas = true;
				cerrando = false;
			}
		}
	}

	/*
		M�todo para regresar la posici�n de las alas al estado inicial del juego.
	*/
	void reiniciarAlas(){
		float anguloR = 11;
		if (abiertas){
			nodosAlas[0]->roll(Degree(anguloR));
			nodosMisiles[3]->roll(Degree(anguloR));

			nodosAlas[1]->roll(Degree(-anguloR));
			nodosMisiles[2]->roll(Degree(-anguloR));

			nodosAlas[2]->roll(Degree(anguloR));
			nodosMisiles[0]->roll(Degree(anguloR));

			nodosAlas[3]->roll(Degree(-anguloR));
			nodosMisiles[1]->roll(Degree(-anguloR));
		}

		anguloAct = 0.0;
		abriendo = false;
		cerrando = false;
		abiertas = false;
		cerradas = true;
	}

	/*
		M�todo que permite regresar la nave a su estado inicial.
	*/
	void reiniciar(){
		laserFinal = 2;

		nodoNave->roll(Degree(anguloNActual));
		for (int i = 0; i < 4; i++){
			nodosAlas[i]->roll(Degree(anguloNActual));
			nodosMisiles[i]->roll(Degree(anguloNActual));
		}
		
		anguloNActual = 0.0;

		reiniciarAlas();

		naveZ = 0.0;
		naveX = 0.0;
		anguloNave = 0.5;

		for (int i = 0; i < 4; i++){
			if (i == 0){
				laserPos[i] = 0.0;
				laserAlt[i] = 0.0;
			}
			else {
				laserPos[i] = -7.0;
				laserAlt[i] = 36.0;
			}
			_timer[i].reset();
		}
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
		_key->capture();

		if (_key->isKeyDown(OIS::KC_ESCAPE) || _key->isKeyDown(OIS::KC_Q))
			return false;

		if (_key->isKeyDown(OIS::KC_W)){
			naveZ -= 1;
			if (naveZ <= -1280)
				reiniciar();
		}
		if (_key->isKeyDown(OIS::KC_A)){
			if (naveX - 0.5 > -24) { 
				anguloNActual -= 0.5;
				naveX -= 0.5;
				anguloNave = 0.5;
				rotarNave();
			}
		}
		if (_key->isKeyDown(OIS::KC_D)){
			if (naveX+0.5 < 24) {
				anguloNActual += 0.5;
				naveX += 0.5;
				anguloNave = -0.5;
				rotarNave();
			}
		}
		if (_key->isKeyDown(OIS::KC_E)) { // Abrir Alas
			if (!abriendo && !cerrando) {
				if (cerradas) {
					cerradas = false;
					abriendo = true;
				}
			}
		}
		if (_key->isKeyDown(OIS::KC_R)) { // Cerrar Alas
			if (!abriendo && !cerrando) {
				if (abiertas) {
					abiertas = false;
					cerrando = true;
				}
			}
		}

		if (naveZ <= -150) {
			if (laserPos[2] == -7.0) {
				laserPos[2] = 0.0;
				laserAlt[2] = 0.0;
				_timer[2].reset();
			}
		}
		if (naveZ <= -300) {
			if (laserPos[1] == -7.0) {
				laserPos[1] = 0.0;
				laserAlt[1] = 0.0;
				_timer[1].reset();
			}
		}
		if (naveZ <= -450) {
			if (laserPos[3] == -7.0) {
				laserPos[3] = 0.0;
				laserAlt[3] = 0.0;
				_timer[3].reset();
			}
		}

		for (int i = 0; i < 4;i++) {
			nodosLaser[i]->setPosition(0.0,laserPos[i],laserAlt[i]);
			if (_timer[i].getMilliseconds() > 3500) {
				_timer[i].reset();
				if (laserPos[i] != -7.0) {
					laserPos[i] = 0.0;
				}
			}
			else {
				if (laserPos[i] != -7.0) {
					laserPos[i] += 1;
				}
			}
		}

		// Aplicando las nuevas posiciones a la nave.
		nodoNave->setPosition(naveX,0,naveZ);
		_cam->setPosition(0,10,naveZ+40);
		nodoLuz->setPosition(0,5,naveZ);
		for (int i = 0; i < 4;i++) {
			nodosAlas[i]->setPosition(naveX,0,naveZ);
			nodosMisiles[i]->setPosition(naveX,0,naveZ);
		}

		rotarAlas();
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

	/*
		M�todo para crear las cuatro torretas del juego.
		Adem�s se incluyen las luces de cada una de ellas.
	*/
	void crearTorretas() {

		/*---------------- INICIO TORRETA 1 -------------------------*/
		Ogre::Entity* entTorreta01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[0] = mSceneMgr->createSceneNode("nodoTorreta1");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[0]);
		nodosTorreta[0]->attachObject(entTorreta01);
		nodosTorreta[0]->setPosition(-22,-5,-227);
		entTorreta01->setMaterialName("matTorretaSW1");

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

		// Ca��n de la torreta
		Ogre::Entity* entCanon01 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		nodosCanon[0] = mSceneMgr->createSceneNode("nodoCanon1");
		nodosCanon[0]->attachObject(entCanon01);
		nodosTorreta[0]->addChild(nodosCanon[0]);
		nodosCanon[0]->setScale(0.65,0.65,0.65);
		nodosCanon[0]->setPosition(0.5,3.5,5.0);
		nodosCanon[0]->yaw(Degree(5));
		nodosCanon[0]->pitch(Degree(90));
		entCanon01->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser01 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[0] = mSceneMgr->createSceneNode("nodoLaser1");
		nodosLaser[0]->attachObject(entLaser01);
		nodosCanon[0]->addChild(nodosLaser[0]);
		entLaser01->setMaterialName("matLaser01");
		/*------------------------ FIN TORRETA 1 ---------------------------*/


		/*---------------- INICIO TORRETA 2 -------------------------*/
		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[1] = mSceneMgr->createSceneNode("nodoTorreta2");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[1]);
		nodosTorreta[1]->attachObject(entTorreta02);
		nodosTorreta[1]->setPosition(-22.5,-5,-638);
		entTorreta02->setMaterialName("matTorretaSW1");
		
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
		nodosCanon[1]->setPosition(0.5,3.5,5.0);
		nodosCanon[1]->yaw(Degree(5));
		nodosCanon[1]->pitch(Degree(90));
		entCanon02->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser02 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[1] = mSceneMgr->createSceneNode("nodoLaser2");
		nodosLaser[1]->attachObject(entLaser02);
		nodosCanon[1]->addChild(nodosLaser[1]);
		entLaser02->setMaterialName("matLaser01");
		/*------------------------ FIN TORRETA 2 ---------------------------*/

		/*------------------------ INICIO TORRETA 3 ---------------------------*/
		Ogre::Entity* entTorreta03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[2] = mSceneMgr->createSceneNode("nodoTorreta3");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[2]);
		nodosTorreta[2]->attachObject(entTorreta03);
		nodosTorreta[2]->setPosition(22.5,-5,-407.5);
		entTorreta03->setMaterialName("matTorretaSW1");

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
		nodosCanon[2]->setPosition(-0.5,3.5,5.0);
		nodosCanon[2]->yaw(Degree(-5));
		nodosCanon[2]->pitch(Degree(90));
		entCanon03->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser03 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[2] = mSceneMgr->createSceneNode("nodoLaser3");
		nodosLaser[2]->attachObject(entLaser03);
		nodosCanon[2]->addChild(nodosLaser[2]);
		entLaser03->setMaterialName("matLaser01");
		/*------------------------ FIN TORRETA 3 ---------------------------*/

		/*------------------------ INICIO TORRETA 4 ---------------------------*/
		Ogre::Entity* entTorreta04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		nodosTorreta[3] = mSceneMgr->createSceneNode("nodoTorreta4");
		mSceneMgr->getRootSceneNode()->addChild(nodosTorreta[3]);
		nodosTorreta[3]->attachObject(entTorreta04);
		nodosTorreta[3]->setPosition(22,-5,-883.5);
		entTorreta04->setMaterialName("matTorretaSW1");

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
		nodosCanon[3]->setPosition(-0.5,3.5,5.0);
		nodosCanon[3]->yaw(Degree(-5));
		nodosCanon[3]->pitch(Degree(90));
		entCanon04->setMaterialName("matTorretas01");

		// Laser
		Ogre::Entity* entLaser04 = mSceneMgr->createEntity("usb_laser.mesh");
		nodosLaser[3] = mSceneMgr->createSceneNode("nodoLaser4");
		nodosLaser[3]->attachObject(entLaser04);
		nodosCanon[3]->addChild(nodosLaser[3]);
		entLaser04->setMaterialName("matLaser01");
		/*------------------------ FIN TORRETA 4 ---------------------------*/
	}

	/*
		M�todo para la creaci�n manual de las cuatro alas de la nave.
	*/
	void crearAlas(){
		ManualObject* alaSuperiorIzq = mSceneMgr->createManualObject("alaSuperiorIzq");
		ManualObject* alaInferiorIzq = mSceneMgr->createManualObject("alaInferiorIzq");
		ManualObject* alaSuperiorDer = mSceneMgr->createManualObject("alaSuperiorDer");
		ManualObject* alaInferiorDer = mSceneMgr->createManualObject("alaInferiorDer");

		nodosAlas[0] = mSceneMgr->createSceneNode("nodoAlaSuperiorIzq");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[0]);

		nodosAlas[1] = mSceneMgr->createSceneNode("nodoAlaInferiorIzq");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[1]);

		nodosAlas[2] = mSceneMgr->createSceneNode("nodoAlaSuperiorDer");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[2]);

		nodosAlas[3] = mSceneMgr->createSceneNode("nodoAlaInferiorDer");
		mSceneMgr->getRootSceneNode()->addChild(nodosAlas[3]);

		//Ala derecha
		alaSuperiorDer->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alaSuperiorDer->position(4, 0, -2.5); alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0,1);
			alaSuperiorDer->position(4, 0, -17.5);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0,0);
			alaSuperiorDer->position(20, 0, -17.5);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(1,0);
			alaSuperiorDer->position(20, 0, -6.5);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(1,0.6);
			alaSuperiorDer->position(8, 0, -2.5);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0.4,1);
			alaSuperiorDer->position(7.5, 0, -4);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0.3,1);
			alaSuperiorDer->position(5, 0, -4);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0.2,1);
			alaSuperiorDer->position(4.5, 0, -2.5);alaSuperiorDer->normal(0.0,1.0,0.0); alaSuperiorDer->textureCoord(0.1,1);


			alaSuperiorDer->triangle(0,7,1);
			alaSuperiorDer->triangle(6,2,1);
			alaSuperiorDer->quad(5,4,3,2);
			alaSuperiorDer->triangle(6,5,2);
			alaSuperiorDer->triangle(1,7,6);

			//Parte de abajo
			alaSuperiorDer->position(4, -0.5, -2.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0,1);
			alaSuperiorDer->position(4, -0.5, -17.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0,0);
			alaSuperiorDer->position(20, -0.5, -17.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(1,0);
			alaSuperiorDer->position(20, -0.5, -6.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(1,0.6);
			alaSuperiorDer->position(8, -0.5, -2.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0.4,1);
			alaSuperiorDer->position(7.5, -0.5, -4); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0.3,1);
			alaSuperiorDer->position(5, -0.5, -4); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0.2,1);
			alaSuperiorDer->position(4.5, -0.5, -2.5); alaSuperiorDer->normal(0.0,-1.0,0.0); alaSuperiorDer->textureCoord(0.1,1);
			
			alaSuperiorDer->triangle(8,15,9);
			alaSuperiorDer->triangle(14,10,9);
			alaSuperiorDer->quad(13,12,11,10);
			alaSuperiorDer->triangle(14,13,10);
			alaSuperiorDer->triangle(9,15,14);

			//Lateral izquierdo
			alaSuperiorDer->position(4, -0.5, -2.5); alaSuperiorDer->normal(-1.0,0.0,0.0); alaSuperiorDer->textureCoord(1,1); //Antiguo 8
			alaSuperiorDer->position(4, 0, -2.5); alaSuperiorDer->normal(-1.0,0.0,0.0); alaSuperiorDer->textureCoord(1,0); //Antiguo 0
			alaSuperiorDer->position(4, 0, -17.5);alaSuperiorDer->normal(-1.0,0.0,0.0); alaSuperiorDer->textureCoord(0,0); //Antiguo 1
			alaSuperiorDer->position(4, -0.5, -17.5); alaSuperiorDer->normal(-1.0,0.0,0.0); alaSuperiorDer->textureCoord(0,1); //Antiguo 9
			alaSuperiorDer->quad(16,17,18,19);

			//Lateral derecho
			alaSuperiorDer->position(20, 0, -6.5); alaSuperiorDer->normal(1.0,0.0,0.0); alaSuperiorDer->textureCoord(1,1); //Antiguo 3
			alaSuperiorDer->position(20, -0.5, -6.5); alaSuperiorDer->normal(1.0,0.0,0.0); alaSuperiorDer->textureCoord(1,0); //Antiguo 11
			alaSuperiorDer->position(20, -0.5, -17.5); alaSuperiorDer->normal(1.0,0.0,0.0); alaSuperiorDer->textureCoord(0,0); //Antiguo 10
			alaSuperiorDer->position(20, 0, -17.5); alaSuperiorDer->normal(1.0,0.0,0.0); alaSuperiorDer->textureCoord(0,1); //Antiguo 2
			alaSuperiorDer->quad(20,21,22,23);

			//Lateral trasero
			alaSuperiorDer->position(4, 0, -2.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0,0); //Antiguo 0
			alaSuperiorDer->position(20, 0, -6.5);alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(1,0); //Antiguo 3
			alaSuperiorDer->position(8, 0, -2.5);alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.4,0);//Antiguo 4
			alaSuperiorDer->position(7.5, 0, -4);alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.3,0);//Antiguo 5
			alaSuperiorDer->position(5, 0, -4);alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.2,0);//Antiguo 6
			alaSuperiorDer->position(4.5, 0, -2.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.1,0);//Antiguo 7
			alaSuperiorDer->position(4, -0.5, -2.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0,1); //Antiguo 8
			alaSuperiorDer->position(20, -0.5, -6.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(1,1);//Antiguo 11
			alaSuperiorDer->position(8, -0.5, -2.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.4,1);//Antiguo 12
			alaSuperiorDer->position(7.5, -0.5, -4); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.3,1);//Antiguo 13
			alaSuperiorDer->position(5, -0.5, -4); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.2,1);//Antiguo 14
			alaSuperiorDer->position(4.5, -0.5, -2.5); alaSuperiorDer->normal(0.0,0.0,1.0); alaSuperiorDer->textureCoord(0.1,1);//Antiguo 15
			alaSuperiorDer->quad(24,30,35,29);
			alaSuperiorDer->quad(29,35,34,28);
			alaSuperiorDer->quad(28,34,33,27);
			alaSuperiorDer->quad(27,33,32,26);
			alaSuperiorDer->quad(26,32,31,25);

		alaSuperiorDer->end();

		nodosAlas[2]->attachObject(alaSuperiorDer);

		//Ala izquierda
		alaSuperiorIzq->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alaSuperiorIzq->position(-4, 0, -2.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(1,1);
			alaSuperiorIzq->position(-4, 0, -17.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(1,0);
			alaSuperiorIzq->position(-20, 0, -17.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0,0);
			alaSuperiorIzq->position(-20, 0, -6.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0,0.6);
			alaSuperiorIzq->position(-8, 0, -2.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0.6,1);
			alaSuperiorIzq->position(-7.5, 0, -4); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0.7,1);
			alaSuperiorIzq->position(-5, 0, -4); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0.8,1);
			alaSuperiorIzq->position(-4.5, 0, -2.5); alaSuperiorIzq->normal(0.0,1.0,0.0); alaSuperiorIzq->textureCoord(0.9,1);

			alaSuperiorIzq->triangle(1,7,0);
			alaSuperiorIzq->triangle(1,2,6);
			alaSuperiorIzq->quad(2,3,4,5);
			alaSuperiorIzq->triangle(2,5,6);
			alaSuperiorIzq->triangle(6,7,1);
			
			//Parte de abajo
			alaSuperiorIzq->position(-4, -0.5, -2.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(1,1);
			alaSuperiorIzq->position(-4, -0.5, -17.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(1,0);
			alaSuperiorIzq->position(-20, -0.5, -17.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0,0);
			alaSuperiorIzq->position(-20, -0.5, -6.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0,0.6);
			alaSuperiorIzq->position(-8, -0.5, -2.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0.6,1);
			alaSuperiorIzq->position(-7.5, -0.5, -4); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0.7,1);
			alaSuperiorIzq->position(-5, -0.5, -4); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0.8,1);
			alaSuperiorIzq->position(-4.5, -0.5, -2.5); alaSuperiorIzq->normal(0.0,-1.0,0.0); alaSuperiorIzq->textureCoord(0.9,1);

			alaSuperiorIzq->triangle(8,15,9);
			alaSuperiorIzq->triangle(14,10,9);
			alaSuperiorIzq->quad(13,12,11,10);
			alaSuperiorIzq->triangle(14,13,10);
			alaSuperiorIzq->triangle(9,15,14);

			//Lateral derecho
			alaSuperiorIzq->position(-4, -0.5, -2.5); alaSuperiorIzq->normal(-1.0,0.0,0.0); alaSuperiorIzq->textureCoord(0,1);//Antiguo 8
			alaSuperiorIzq->position(-4, 0, -2.5); alaSuperiorIzq->normal(-1.0,0.0,0.0); alaSuperiorIzq->textureCoord(0,0);//Antiguo 0
			alaSuperiorIzq->position(-4, 0, -17.5);alaSuperiorIzq->normal(-1.0,0.0,0.0); alaSuperiorIzq->textureCoord(1,0);//Antiguo 1
			alaSuperiorIzq->position(-4, -0.5, -17.5); alaSuperiorIzq->normal(-1.0,0.0,0.0); alaSuperiorIzq->textureCoord(1,1); //Antiguo 9
			alaSuperiorIzq->quad(19,18,17,16);

			//Lateral izquierdo
			alaSuperiorIzq->position(-20, 0, -6.5); alaSuperiorIzq->normal(1.0,0.0,0.0); alaSuperiorIzq->textureCoord(1,1);//Antiguo 3
			alaSuperiorIzq->position(-20, -0.5, -6.5); alaSuperiorIzq->normal(1.0,0.0,0.0); alaSuperiorIzq->textureCoord(1,0);//Antiguo 11
			alaSuperiorIzq->position(-20, -0.5, -17.5); alaSuperiorIzq->normal(1.0,0.0,0.0); alaSuperiorIzq->textureCoord(0,0);//Antiguo 10
			alaSuperiorIzq->position(-20, 0, -17.5); alaSuperiorIzq->normal(1.0,0.0,0.0);alaSuperiorIzq->textureCoord(0,1);//Antiguo 2
			alaSuperiorIzq->quad(23,22,21,20);

			//Lateral trasero
			alaSuperiorIzq->position(-4, 0, -2.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0,0);//Antiguo 0
			alaSuperiorIzq->position(-20, 0, -6.5);alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(1,0);//Antiguo 3
			alaSuperiorIzq->position(-8, 0, -2.5);alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.4,0);//Antiguo 4
			alaSuperiorIzq->position(-7.5, 0, -4);alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.3,0);//Antiguo 5
			alaSuperiorIzq->position(-5, 0, -4);alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.2,0);//Antiguo 6
			alaSuperiorIzq->position(-4.5, 0, -2.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.1,0);//Antiguo 7
			alaSuperiorIzq->position(-4, -0.5, -2.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0,1);//Antiguo 8
			alaSuperiorIzq->position(-20, -0.5, -6.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(1,1);//Antiguo 11
			alaSuperiorIzq->position(-8, -0.5, -2.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.4,1);//Antiguo 12
			alaSuperiorIzq->position(-7.5, -0.5, -4); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.3,1);//Antiguo 13
			alaSuperiorIzq->position(-5, -0.5, -4); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.2,1);//Antiguo 14
			alaSuperiorIzq->position(-4.5, -0.5, -2.5); alaSuperiorIzq->normal(0.0,0.0,1.0); alaSuperiorIzq->textureCoord(0.1,1);//Antiguo 15
			alaSuperiorIzq->quad(29,35,30,24);
			alaSuperiorIzq->quad(28,34,35,29);
			alaSuperiorIzq->quad(27,33,34,28);
			alaSuperiorIzq->quad(26,32,33,27);
			alaSuperiorIzq->quad(25,31,32,26);
			
		alaSuperiorIzq->end();

		nodosAlas[0]->attachObject(alaSuperiorIzq);

		//Ala derecha
		alaInferiorDer->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alaInferiorDer->position(4, -0.5, -2.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0,1);
			alaInferiorDer->position(4, -0.5, -17.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0,0); 
			alaInferiorDer->position(20, -0.5, -17.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(1,0);
			alaInferiorDer->position(20, -0.5, -6.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(1,0.6);
			alaInferiorDer->position(8, -0.5, -2.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0.4,1);
			alaInferiorDer->position(7.5, -0.5, -4); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0.3,1);
			alaInferiorDer->position(5, -0.5, -4); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0.2,1);
			alaInferiorDer->position(4.5, -0.5, -2.5); alaInferiorDer->normal(0.0,1.0,0.0); alaInferiorDer->textureCoord(0.1,1);

			alaInferiorDer->triangle(0,7,1);
			alaInferiorDer->triangle(6,2,1);
			alaInferiorDer->quad(5,4,3,2);
			alaInferiorDer->triangle(6,5,2);
			alaInferiorDer->triangle(1,7,6);
			
			//Parte de abajo
			alaInferiorDer->position(4, -1, -2.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0,1);
			alaInferiorDer->position(4, -1, -17.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0,0); 
			alaInferiorDer->position(20, -1, -17.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(1,0);
			alaInferiorDer->position(20, -1, -6.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(1,0.6);
			alaInferiorDer->position(8, -1, -2.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0.4,1);
			alaInferiorDer->position(7.5, -1, -4); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0.3,1);
			alaInferiorDer->position(5, -1, -4); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0.2,1);
			alaInferiorDer->position(4.5, -1, -2.5); alaInferiorDer->normal(0.0,-1.0,0.0); alaInferiorDer->textureCoord(0.1,1);

			alaInferiorDer->triangle(9,15,8);
			alaInferiorDer->triangle(9,10,14);
			alaInferiorDer->quad(10,11,12,13);
			alaInferiorDer->triangle(10,13,14);
			alaInferiorDer->triangle(14,15,9);


			//Lateral izquierdo
			alaInferiorDer->position(4, -1, -2.5); alaInferiorDer->normal(-1.0,0.0,0.0); alaInferiorDer->textureCoord(1,1);//Antiguo 8
			alaInferiorDer->position(4, -0.5, -2.5); alaInferiorDer->normal(-1.0,0.0,0.0);alaInferiorDer->textureCoord(1,0); //Antiguo 0
			alaInferiorDer->position(4, -0.5, -17.5); alaInferiorDer->normal(-1.0,0.0,0.0); alaInferiorDer->textureCoord(0,0); //Antiguo 1
			alaInferiorDer->position(4, -1, -17.5); alaInferiorDer->normal(-1.0,0.0,0.0); alaInferiorDer->textureCoord(0,1);//Antiguo 9
			alaInferiorDer->quad(16,17,18,19);

			//Lateral derecho
			alaInferiorDer->position(20, -0.5, -6.5); alaInferiorDer->normal(1.0,0.0,0.0); alaInferiorDer->textureCoord(1,1); //Antiguo 3
			alaInferiorDer->position(20, -1, -6.5); alaInferiorDer->normal(1.0,0.0,0.0); alaInferiorDer->textureCoord(1,0);//Antiguo 11
			alaInferiorDer->position(20, -1, -17.5); alaInferiorDer->normal(1.0,0.0,0.0); alaInferiorDer->textureCoord(0,0);//Antiguo 10
			alaInferiorDer->position(20, -0.5, -17.5); alaInferiorDer->normal(1.0,0.0,0.0); alaInferiorDer->textureCoord(0,1);//Antiguo 2 
			alaInferiorDer->quad(20,21,22,23);

			//Lateral trasero
			alaInferiorDer->position(4, -0.5, -2.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0,0); //Antiguo 0
			alaInferiorDer->position(20, -0.5, -6.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(1,0); //Antiguo 3
			alaInferiorDer->position(8, -0.5, -2.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.4,0); //Antiguo 4
			alaInferiorDer->position(7.5, -0.5, -4); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.3,0);//Antiguo 5
			alaInferiorDer->position(5, -0.5, -4); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.2,0); //Antiguo 6
			alaInferiorDer->position(4.5, -0.5, -2.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.1,0);//Antiguo 7
			alaInferiorDer->position(4, -1, -2.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0,1);//Antiguo 8
			alaInferiorDer->position(20, -1, -6.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(1,1);//Antiguo 11
			alaInferiorDer->position(8, -1, -2.5); alaInferiorDer->normal(0.0,0.0,1.0);  alaInferiorDer->textureCoord(0.4,1);//Antiguo 12
			alaInferiorDer->position(7.5, -1, -4); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.3,1);//Antiguo 13
			alaInferiorDer->position(5, -1, -4); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.2,1);//Antiguo 14
			alaInferiorDer->position(4.5, -1, -2.5); alaInferiorDer->normal(0.0,0.0,1.0); alaInferiorDer->textureCoord(0.1,1);//Antiguo 15
			alaInferiorDer->quad(24,30,35,29);
			alaInferiorDer->quad(29,35,34,28);
			alaInferiorDer->quad(28,34,33,27);
			alaInferiorDer->quad(27,33,32,26);
			alaInferiorDer->quad(26,32,31,25);

		alaInferiorDer->end();

		nodosAlas[3]->attachObject(alaInferiorDer);

		//Ala izquierda
		alaInferiorIzq->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			alaInferiorIzq->position(-4, -0.5, -2.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(1,1); 
			alaInferiorIzq->position(-4, -0.5, -17.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(1,0); 
			alaInferiorIzq->position(-20, -0.5, -17.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0,0);
			alaInferiorIzq->position(-20, -0.5, -6.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0,0.6);
			alaInferiorIzq->position(-8, -0.5, -2.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0.6,1);
			alaInferiorIzq->position(-7.5, -0.5, -4); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0.7,1);
			alaInferiorIzq->position(-5, -0.5, -4); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0.8,1);
			alaInferiorIzq->position(-4.5, -0.5, -2.5); alaInferiorIzq->normal(0.0,1.0,0.0); alaInferiorIzq->textureCoord(0.9,1);

			alaInferiorIzq->triangle(1,7,0);
			alaInferiorIzq->triangle(1,2,6);
			alaInferiorIzq->quad(2,3,4,5);
			alaInferiorIzq->triangle(2,5,6);
			alaInferiorIzq->triangle(6,7,1);

			//Parte de abajo
			alaInferiorIzq->position(-4, -1, -2.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(1,1);
			alaInferiorIzq->position(-4, -1, -17.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(1,0);
			alaInferiorIzq->position(-20, -1, -17.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0,0);
			alaInferiorIzq->position(-20, -1, -6.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0,0.6);
			alaInferiorIzq->position(-8, -1, -2.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0.6,1);
			alaInferiorIzq->position(-7.5, -1, -4); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0.7,1);
			alaInferiorIzq->position(-5, -1, -4); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0.8,1);
			alaInferiorIzq->position(-4.5, -1, -2.5); alaInferiorIzq->normal(0.0,-1.0,0.0); alaInferiorIzq->textureCoord(0.9,1);

			alaInferiorIzq->triangle(15,9,8);
			alaInferiorIzq->triangle(14,10,9);
			alaInferiorIzq->quad(13,12,11,10);
			alaInferiorIzq->triangle(14,13,10);
			alaInferiorIzq->triangle(9,15,14);

			//Lateral derecho
			alaInferiorIzq->position(-4, -1, -2.5); alaInferiorIzq->normal(-1.0,0.0,0.0); alaInferiorIzq->textureCoord(0,1); //Antiguo 8
			alaInferiorIzq->position(-4, -0.5, -2.5); alaInferiorIzq->normal(-1.0,0.0,0.0); alaInferiorIzq->textureCoord(0,0);//Antiguo 0
			alaInferiorIzq->position(-4, -0.5, -17.5); alaInferiorIzq->normal(-1.0,0.0,0.0); alaInferiorIzq->textureCoord(1,0);//Antiguo 1
			alaInferiorIzq->position(-4, -1, -17.5); alaInferiorIzq->normal(-1.0,0.0,0.0); alaInferiorIzq->textureCoord(1,1);//Antiguo 9
			alaInferiorIzq->quad(16,17,18,19);

			//Lateral izquierdo
			alaInferiorIzq->position(-20, -0.5, -6.5); alaInferiorIzq->normal(1.0,0.0,0.0); alaInferiorIzq->textureCoord(1,1); //Antiguo 3
			alaInferiorIzq->position(-20, -1, -6.5); alaInferiorIzq->normal(1.0,0.0,0.0); alaInferiorIzq->textureCoord(1,0);//Antiguo 11
			alaInferiorIzq->position(-20, -1, -17.5); alaInferiorIzq->normal(1.0,0.0,0.0); alaInferiorIzq->textureCoord(0,0);//Antiguo 10
			alaInferiorIzq->position(-20, -0.5, -17.5); alaInferiorIzq->normal(1.0,0.0,0.0); alaInferiorIzq->textureCoord(0,1);//Antiguo 2 
			alaInferiorIzq->quad(23,22,21,20);

			//Lateral trasero
			alaInferiorIzq->position(-4, -0.5, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0,0); //Antiguo 0
			alaInferiorIzq->position(-20, -0.5, -6.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(1,0); //Antiguo 3
			alaInferiorIzq->position(-8, -0.5, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.4,0);//Antiguo 4
			alaInferiorIzq->position(-7.5, -0.5, -4); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.3,0); //Antiguo 5
			alaInferiorIzq->position(-5, -0.5, -4); alaInferiorIzq->normal(0.0,0.0,1.0);  alaInferiorIzq->textureCoord(0.2,0);//Antiguo 6
			alaInferiorIzq->position(-4.5, -0.5, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.1,0);//Antiguo 7
			alaInferiorIzq->position(-4, -1, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0,1);//Antiguo 8
			alaInferiorIzq->position(-20, -1, -6.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(1,1);//Antiguo 11
			alaInferiorIzq->position(-8, -1, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.4,1); //Antiguo 12
			alaInferiorIzq->position(-7.5, -1, -4); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.3,1);//Antiguo 13
			alaInferiorIzq->position(-5, -1, -4); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.2,1);//Antiguo 14
			alaInferiorIzq->position(-4.5, -1, -2.5); alaInferiorIzq->normal(0.0,0.0,1.0); alaInferiorIzq->textureCoord(0.1,1);//Antiguo 15
			alaInferiorIzq->quad(29,35,30,24);
			alaInferiorIzq->quad(28,34,35,29);
			alaInferiorIzq->quad(27,33,34,28);
			alaInferiorIzq->quad(26,32,33,27);
			alaInferiorIzq->quad(25,31,32,26);
			
		alaInferiorIzq->end();

		nodosAlas[1]->attachObject(alaInferiorIzq);
	}

	/*
		M�todo que permite crear con ManualObject la secci�n central de la nave.
	*/
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
		centroNave->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba del centro de la nave
			centroNave->position(-3, 2.5, 0); centroNave->normal(0.0,1.0,0.0);
			centroNave->position(-3, 2.5, -13); centroNave->normal(0.0,1.0,0.0);
			centroNave->position(3, 2.5, -13); centroNave->normal(0.0,1.0,0.0); 
			centroNave->position(3, 2.5, 0); centroNave->normal(0.0,1.0,0.0); 
			
			centroNave->quad(0,3,2,1);

			//Parte de abajo del centro de la nave
			centroNave->position(-3, -2.5, 0); centroNave->normal(0.0,-1.0,0.0); 
			centroNave->position(-3, -2.5, -13); centroNave->normal(0.0,-1.0,0.0);
			centroNave->position(3, -2.5, -13); centroNave->normal(0.0,-1.0,0.0); 
			centroNave->position(3, -2.5, 0); centroNave->normal(0.0,-1.0,0.0); 
			
			centroNave->quad(5,6,7,4);

			//Parte trasera del centro de la nave
			centroNave->position(-3, -2.5, 0); centroNave->normal(0.0,0.0,1.0);
			centroNave->position(-4, 0, 0); centroNave->normal(0.0,0.0,1.0);
			centroNave->position(-3, 2.5, 0); centroNave->normal(0.0,0.0,1.0);
			centroNave->position(3, 2.5, 0); centroNave->normal(0.0,0.0,1.0); 
			centroNave->position(4, 0, 0); centroNave->normal(0.0,0.0,1.0); 
			centroNave->position(3, -2.5, 0); centroNave->normal(0.0,0.0,1.0);
			
			centroNave->triangle(10,9,8);
			centroNave->quad(8,13,11,10);
			centroNave->triangle(13,12,11);

			//Parte frontal del centro de la nave
			centroNave->position(-3, -2.5, -13); centroNave->normal(0.0,0.0,-1.0);
			centroNave->position(-4, 0, -13); centroNave->normal(0.0,0.0,-1.0);
			centroNave->position(-3, 2.5, -13); centroNave->normal(0.0,0.0,-1.0);
			centroNave->position(3, 2.5, -13); centroNave->normal(0.0,0.0,-1.0);
			centroNave->position(4, 0, -13); centroNave->normal(0.0,0.0,-1.0);
			centroNave->position(3, -2.5, -13); centroNave->normal(0.0,0.0,-1.0);
			
			centroNave->triangle(16,15,14);
			centroNave->quad(14,19,17,16);
			centroNave->triangle(19,18,17);

			//Lateral izquierdo del centro de la nave
			centroNave->position(-3, -2.5, 0); centroNave->normal(-0.93,0.37,0.0); //Antiguo 8
			centroNave->position(-4, 0, 0); centroNave->normal(-0.93,0.37,0.0);  //Antiguo 9
			centroNave->position(-3, 2.5, 0); centroNave->normal(-0.93,0.37,0.0); //Antiguo 10
			centroNave->position(-3, -2.5, -13); centroNave->normal(-0.93,0.37,0.0); //Antiguo 14
			centroNave->position(-4, 0, -13); centroNave->normal(-0.93,0.37,0.0);  //Antiguo 15
			centroNave->position(-3, 2.5, -13); centroNave->normal(-0.93,0.37,0.0); //Antiguo 16
			centroNave->quad(20,21,24,23);
			centroNave->quad(21,22,25,24);

			//Lateral derecho del centro de la nave
			centroNave->position(3, 2.5, 0); centroNave->normal(0.93,0.37,0.0); //Antiguo 11
			centroNave->position(4, 0, 0); centroNave->normal(0.93,0.37,0.0); //Antiguo 12
			centroNave->position(3, -2.5, 0); centroNave->normal(0.93,0.37,0.0); // Antiguo 13
			centroNave->position(3, 2.5, -13); centroNave->normal(0.93,0.37,0.0);//Antiguo 17
			centroNave->position(4, 0, -13); centroNave->normal(0.93,0.37,0.0); //Antiguo 18
			centroNave->position(3, -2.5, -13); centroNave->normal(0.93,0.37,0.0); //Antiguo 19
			centroNave->quad(31,30,27,28);
			centroNave->quad(26,27,30,29);


		centroNave->end();


		//Secci�n frontal de la cabina
		/*    | |
		     |   |
			|     |
			-------
		*/
		centroNave->begin("matNaveSW3", RenderOperation::OT_TRIANGLE_LIST);
			//Parte de arriba
			centroNave->position(-3, 2.5, -13); centroNave->normal(0.0,-0.99,0.05);
			centroNave->position(-2, 1.5, -33); centroNave->normal(0.0,0.99,-0.05);
			centroNave->position(2, 1.5, -33); centroNave->normal(0.0,0.99,-0.05);
			centroNave->position(3, 2.5, -13); centroNave->normal(0.0,-0.99,0.05);
			
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
			centroNave->position(-4, 0, -13); //Medio izquierdo atr�s
			centroNave->position(-2, 0, -33); //Medio de la punta

			centroNave->quad(4,16,17,12);
			centroNave->quad(0,8,17,16);

			//Lateral derecho de la nave
			centroNave->position(4, 0, -13); //Medio derecho atr�s
			centroNave->position(2, 0, -33); //Medio de la punta

			centroNave->quad(7,15,19,18);
			centroNave->quad(3,18,19,11);
		centroNave->end();


		nodoNave->attachObject(centroNave);
	}

	/*
		M�todo para agregar los cuatro misiles que van en cada ala utilizando
		las primitivas dadas para el proyecto.
	*/
	void agregarMisiles(int numMisil, float x, float y){
		nodosMisiles[numMisil] = mSceneMgr->createSceneNode("nodoMisil"+std::to_string(numMisil));

		Ogre::SceneNode* nodoCilindro;
		Ogre::Entity* entCilindro = mSceneMgr->createEntity("usb_cilindro.mesh");
		entCilindro->setMaterialName("matNaveSW1");
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
		entPipe->setMaterialName("matNaveSW2");
		nodoPipeMisil = mSceneMgr->createSceneNode("nodoPipeMisil"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoPipeMisil);
		nodoPipeMisil->attachObject(entPipe);
		nodoPipeMisil->setPosition(x,y,-9.2);
		nodoPipeMisil->setScale(0.10,0.10,0.10);
		nodoPipeMisil->pitch(Degree(90));

		Ogre::SceneNode* nodoPipeMisil2;
		Ogre::Entity* entPipe2 = mSceneMgr->createEntity("usb_pipe.mesh");
		entPipe2->setMaterialName("matNaveSW2");
		nodoPipeMisil2 = mSceneMgr->createSceneNode("nodoPipeMisil2"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoPipeMisil2);
		nodoPipeMisil2->attachObject(entPipe2);
		nodoPipeMisil2->setPosition(x,y,-3);
		nodoPipeMisil2->setScale(0.10,0.10,0.10);
		nodoPipeMisil2->pitch(Degree(90));

		Ogre::SceneNode* nodoCilindro2;
		Ogre::Entity* entCilindro2 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		entCilindro2->setMaterialName("matNaveSW1");
		nodoCilindro2 = mSceneMgr->createSceneNode("nodoCilindro2"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCilindro2);
		nodoCilindro2->attachObject(entCilindro2);
		nodoCilindro2->setPosition(x,y,-11);
		nodoCilindro2->setScale(0.025,0.5,0.025);
		nodoCilindro2->roll(Degree(90));
		nodoCilindro2->pitch(Degree(-90));

		Ogre::SceneNode* nodoCurvo;
		Ogre::Entity* entCurvo = mSceneMgr->createEntity("usb_formacurva.mesh");
		entCurvo->setMaterialName("matNaveSW2");
		nodoCurvo = mSceneMgr->createSceneNode("nodoCurvo"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo);
		nodoCurvo->attachObject(entCurvo);
		nodoCurvo->setPosition(x,y,-13);
		nodoCurvo->setScale(0.08,0.08,0.08);
		nodoCurvo->pitch(Degree(-90));
		
		Ogre::SceneNode* nodoCurvo2;
		Ogre::Entity* entCurvo2 = mSceneMgr->createEntity("usb_formacurva.mesh");
		entCurvo2->setMaterialName("matNaveSW2");
		nodoCurvo2 = mSceneMgr->createSceneNode("nodoCurvo2"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo2);
		nodoCurvo2->attachObject(entCurvo2);
		nodoCurvo2->setPosition(x,y,-13.3);
		nodoCurvo2->setScale(0.07,0.07,0.07);
		nodoCurvo2->pitch(Degree(-45));

		Ogre::SceneNode* nodoCurvo3;
		Ogre::Entity* entCurvo3 = mSceneMgr->createEntity("usb_formacurva.mesh");
		entCurvo3->setMaterialName("matNaveSW2");
		nodoCurvo3 = mSceneMgr->createSceneNode("nodoCurvo3"+std::to_string(numMisil));
		nodosMisiles[numMisil]->addChild(nodoCurvo3);
		nodoCurvo3->attachObject(entCurvo3);
		nodoCurvo3->setPosition(x,y,-13.3);
		nodoCurvo3->setScale(0.07,0.07,0.07);
		nodoCurvo3->pitch(Degree(45));

	}

	/*
		M�todo para agregar las turbinas utilizando las primitivas dadas para el proyecto.
	*/
	void agregarTurbinas(int numTurbina, float x, float y){
		Ogre::SceneNode* nodoTurbina;
		Ogre::Entity* entTurbina = mSceneMgr->createEntity("usb_cilindro.mesh");
		entTurbina->setMaterialName("matNaveSW1");
		nodoTurbina = mSceneMgr->createSceneNode("nodoTurbina"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoTurbina);
		nodoTurbina->attachObject(entTurbina);
		nodoTurbina->setPosition(x,y,-1.5);
		nodoTurbina->setScale(0.25,0.4,0.25);
		nodoTurbina->roll(Degree(90));
		nodoTurbina->pitch(Degree(90));

		Ogre::SceneNode* nodoCurvo;
		Ogre::Entity* entCurvo = mSceneMgr->createEntity("usb_formacurva.mesh");
		entCurvo->setMaterialName("matNaveSW2");
		nodoCurvo = mSceneMgr->createSceneNode("nodoCurvoTurbina"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoCurvo);
		nodoCurvo->attachObject(entCurvo);
		nodoCurvo->setPosition(x,y,1.2);
		nodoCurvo->setScale(0.09,0.09,0.09);
		nodoCurvo->pitch(Degree(90));
		nodoCurvo->roll(Degree(180));

		Ogre::SceneNode* nodoTurbina2;
		Ogre::Entity* entTurbina2 = mSceneMgr->createEntity("usb_cilindro.mesh");
		entTurbina2->setMaterialName("matNaveSW1");
		nodoTurbina2 = mSceneMgr->createSceneNode("nodoTurbina2"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoTurbina2);
		nodoTurbina2->attachObject(entTurbina2);
		nodoTurbina2->setPosition(x,((numTurbina==1 || numTurbina==3) ? y+0.5 : y-0.6),-6.5);
		nodoTurbina2->setScale(0.4,0.4,0.4);
		nodoTurbina2->roll(Degree(90));
		nodoTurbina2->pitch(Degree(90));

		Ogre::SceneNode* nodoPipeTurbina;
		Ogre::Entity* entPipe = mSceneMgr->createEntity("usb_pipe.mesh");
		entPipe->setMaterialName("matNaveSW2");
		nodoPipeTurbina = mSceneMgr->createSceneNode("nodoPipeTurbina"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoPipeTurbina);
		nodoPipeTurbina->attachObject(entPipe);
		nodoPipeTurbina->setPosition(x,((numTurbina==1 || numTurbina==3) ? y+0.5 : y-0.6),-6.5);
		nodoPipeTurbina->setScale(0.2,0.2,0.2);
		nodoPipeTurbina->pitch(Degree(90));

		Ogre::SceneNode* nodoPipeTurbina2;
		Ogre::Entity* entPipe2 = mSceneMgr->createEntity("usb_pipe.mesh");
		entPipe2->setMaterialName("matNaveSW2");
		nodoPipeTurbina2 = mSceneMgr->createSceneNode("nodoPipeTurbina2"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoPipeTurbina2);
		nodoPipeTurbina2->attachObject(entPipe2);
		nodoPipeTurbina2->setPosition(x,((numTurbina==1 || numTurbina==3) ? y+0.5 : y-0.6),-9);
		nodoPipeTurbina2->setScale(0.2,0.2,0.2);
		nodoPipeTurbina2->pitch(Degree(90));

		Ogre::SceneNode* nodoCurvo2;
		Ogre::Entity* entCurvo2 = mSceneMgr->createEntity("usb_formacurva.mesh");
		entCurvo2->setMaterialName("matNaveSW2");
		nodoCurvo2 = mSceneMgr->createSceneNode("nodoCurvoTurbina2"+std::to_string(numTurbina));
		nodosMisiles[numTurbina]->addChild(nodoCurvo2);
		nodoCurvo2->attachObject(entCurvo2);
		nodoCurvo2->setPosition(x,((numTurbina==1 || numTurbina==3) ? y+0.5 : y-0.6),-4);
		nodoCurvo2->setScale(0.14,0.14,0.14);
		nodoCurvo2->pitch(Degree(90));
	}

	/*
		Creaci�n de la nave completa.
	*/
	void crearNave(){
		crearCentroNave();
		crearAlas();
		nodoNave->scale(0.5,0.5,0.5);
		for (int i = 0; i < 4; i++)
			nodosAlas[i]->scale(0.5,0.5,0.5);

		for(int i = 0 ; i < 4; i++){
			agregarMisiles(i,((i==0 || i==1) ? 10 : -10),((i==1 || i==3) ? 0.5 : -1.2));
			agregarTurbinas(i,((i==0 || i==1) ? 3 : -3),((i==1 || i==3) ? 0.85 : -1.29));
		}
	}

	void createScene() {

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

		luz = mSceneMgr->createLight("Luz1");
		luz->setType(Ogre::Light::LT_POINT);
		luz->setDiffuseColour(1.0,1.0,1.0);
		luz->setPosition(0,0,0);
		nodoLuz = mSceneMgr->createSceneNode("nodoLuz1");
		nodoLuz->attachObject(luz);
		nodoLuz->setPosition(0,5,0);
		mSceneMgr->getRootSceneNode()->addChild(nodoLuz);

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

		mSceneMgr->setSkyBox(true, "skyBoxSW2",5000);
	}
};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}