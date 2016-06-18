#include "Ogre\ExampleApplication.h"
#include <string>

// Variables de las ruedas
Ogre::SceneNode* nodosRuedas[4];
Ogre::SceneNode* nodosYaw[4];
Ogre::Entity* entRuedas[4];
float anguloGiroRuedas = 4.0;
float anguloRoteRuedas = 2.0;
float anguloActRote = 0.0;

// Variables del chasis
Ogre::SceneNode* nodoChasis01;
Ogre::Entity* entChasis01;
float carroZ = 0.0;

class FrameListenerProy : public Ogre::FrameListener {
private :
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;
	
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

	}

	~FrameListenerProy() {
		_man->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

	void moverCarro(int frente) {
		nodoChasis01->translate(0, 0, frente*2, Ogre::Node::TS_LOCAL);
		for (int i = 0; i < 4;i++) {
			nodosRuedas[i]->pitch(frente*Degree(anguloGiroRuedas));
		}
	}

	void rotarCarro(int izq) {
		anguloActRote =  anguloActRote + izq;
		for (int i = 0; i < 2;i++) {
			nodosYaw[i]->yaw(izq*Degree(anguloRoteRuedas));
		}

		nodoChasis01->yaw(izq*Degree(anguloRoteRuedas));
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
			_key->capture();
			_mouse->capture();

			float movSpeed = 10.0f;

			Ogre::Vector3 tmov(0,0,0);
			Ogre::Vector3 tcam(0,0,0);

			if (_key->isKeyDown(OIS::KC_ESCAPE) || _key->isKeyDown(OIS::KC_Q)) {
				return false;
			}
			// Mover camara.
			if (_key->isKeyDown(OIS::KC_W)) {
				tcam += Ogre::Vector3(0,0,-10);
			}
			if (_key->isKeyDown(OIS::KC_S)) {
				tcam += Ogre::Vector3(0,0,10);
			}
			if (_key->isKeyDown(OIS::KC_A)) {
				tcam += Ogre::Vector3(-10,0,0);
			}
			if (_key->isKeyDown(OIS::KC_D)) {
				tcam += Ogre::Vector3(10,0,0);
			}
			if (_key->isKeyDown(OIS::KC_UP)) {
				moverCarro(1);
			}
			if (_key->isKeyDown(OIS::KC_DOWN)) {
				moverCarro(-1);
			}
			if (_key->isKeyDown(OIS::KC_LEFT)) {
				if (anguloActRote < 15)
					rotarCarro(1);
			}
			if (_key->isKeyDown(OIS::KC_RIGHT)) {
				if (anguloActRote > -15)
					rotarCarro(-1);
			}

			// Rotar camara
			float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
			float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
			_cam->yaw(Ogre::Radian(rotX));
			_cam->pitch(Ogre::Radian(rotY));
			_cam->moveRelative(tcam*movSpeed*evt.timeSinceLastFrame);

			return true;
		}
	};

class Example1 : public ExampleApplication
{

public:

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
		mCamera->setPosition(0,100,-200);
		mCamera->lookAt(0,0,100);
		mCamera->setNearClipDistance(1);

	}

	void createScene()
	{

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		
		Ogre::Light* LuzPuntual01 = mSceneMgr->createLight("Luz01");
		LuzPuntual01->setType(Ogre::Light::LT_DIRECTIONAL);
		LuzPuntual01->setDiffuseColour(1.0,1.0,1.0);
		LuzPuntual01->setDirection(Ogre::Vector3( 1, -1, -1 ));
		
		Ogre::Light* LuzPuntual02 = mSceneMgr->createLight("Luz02");
		LuzPuntual02->setType(Ogre::Light::LT_DIRECTIONAL);
		LuzPuntual02->setDiffuseColour(1.0,1.0,1.0);
		LuzPuntual02->setDirection(Ogre::Vector3( -1, -1, -1 ));
		
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

		// Codigo inicial de las ruedas por si a caso.
		/*Ogre::SceneNode* _nodeRueda01 = mSceneMgr->createSceneNode("Rueda01");
		mSceneMgr->getRootSceneNode()->addChild(_nodeRueda01);	
		Ogre::Entity* _entRueda01 = mSceneMgr->createEntity("entRueda01", "ruedaDetallada.mesh");
		_nodeRueda01->translate(5.77,3.517,-9.462);
		_entRueda01->setMaterialName("shRueda02");
		_nodeRueda01->attachObject(_entRueda01);*/

		//BordePista
		Ogre::SceneNode* _nodeBPista = mSceneMgr->createSceneNode("BordePista");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBPista);
				
		Ogre::Entity* _entBPista = mSceneMgr->createEntity("BordePista01", "bordePista.mesh");
		_nodeBPista->attachObject(_entBPista);


		//PisoObstaculo
		Ogre::SceneNode* _nodePObstaculo = mSceneMgr->createSceneNode("PistaObstaculo");
		mSceneMgr->getRootSceneNode()->addChild(_nodePObstaculo);
				
		Ogre::Entity* _entPObstaculo = mSceneMgr->createEntity("PistaObstaculo", "pisoObstaculo01.mesh");
		_nodePObstaculo->attachObject(_entPObstaculo);

		//PisoNOObstaculo
		Ogre::SceneNode* _nodePNObstaculo = mSceneMgr->createSceneNode("PistaNoObstaculo");
		mSceneMgr->getRootSceneNode()->addChild(_nodePNObstaculo);
				
		Ogre::Entity* _entPNOObstaculo = mSceneMgr->createEntity("PistaNoObstaculo", "pisoNoObstaculo01.mesh");
		_nodePNObstaculo->attachObject(_entPNOObstaculo);


		//PosterInicioFinal
		Ogre::SceneNode* _nodePoster = mSceneMgr->createSceneNode("PosterInicioFinal");
		mSceneMgr->getRootSceneNode()->addChild(_nodePoster);
			
		Ogre::Entity* _entPoster = mSceneMgr->createEntity("PosterInicioFinal", "posterInicioFinal.mesh");
		_nodePoster->attachObject(_entPoster);

				
		//BanderaInicial
		Ogre::SceneNode* _nodeBInicial = mSceneMgr->createSceneNode("BanderaInicial");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBInicial);
				
		Ogre::Entity* _entBanderaI = mSceneMgr->createEntity("BanderaInicial", "banderaInicial.mesh");				
		_entBanderaI->setMaterialName("lambert1");				
		_nodeBInicial->attachObject(_entBanderaI);


		//BanderaFinal
		Ogre::SceneNode* _nodeBFinal = mSceneMgr->createSceneNode("BanderaFinal");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBFinal);
		
		Ogre::Entity* _entBanderaF = mSceneMgr->createEntity("BanderaFinal", "banderaFinal.mesh");
		_entBanderaF->setMaterialName("lambert1");
		_nodeBFinal->attachObject(_entBanderaF);




	}

};

int main (void)
{

	Example1 app;
	app.go();
	return 0;
}