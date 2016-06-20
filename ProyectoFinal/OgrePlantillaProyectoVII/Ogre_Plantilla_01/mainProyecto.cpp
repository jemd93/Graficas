#include "Ogre\ExampleApplication.h"
#include <string>
#include "Vehiculo.h"
#include "Moneda.h"
#include "Forma.h"

Vehiculo carro;
Moneda monedas1[5];
Moneda monedas2[5];
Moneda monedas3[10];
Forma obstaculo1[7];

int Moneda::newId = 0;
int Forma::newId = 0;

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
				tcam += Ogre::Vector3(0,0,-20);
			}
			if (_key->isKeyDown(OIS::KC_S)) {
				tcam += Ogre::Vector3(0,0,20);
			}
			if (_key->isKeyDown(OIS::KC_A)) {
				tcam += Ogre::Vector3(-20,0,0);
			}
			if (_key->isKeyDown(OIS::KC_D)) {
				tcam += Ogre::Vector3(20,0,0);
			}
			if (_key->isKeyDown(OIS::KC_UP)) {
				carro.moverCarro(1);
			}
			if (_key->isKeyDown(OIS::KC_DOWN)) {
				carro.moverCarro(-1);
			}
			if (_key->isKeyDown(OIS::KC_LEFT)) {
				carro.rotarCarro(1);
			}
			if (_key->isKeyDown(OIS::KC_RIGHT)) {
				carro.rotarCarro(-1);
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

	void crearObstaculo1() {
		obstaculo1[0] = Forma(mSceneMgr,150,400,30,10,3.0,3.0,"cilindro");
		obstaculo1[1] = Forma(mSceneMgr,215,560,90,15,3.0,3.0,"cilindro");
		obstaculo1[2] = Forma(mSceneMgr,-30,900,90,10,3.0,3.0,"cilindro");
		obstaculo1[3] = Forma(mSceneMgr,65,700,0,10,3.0,3.0,"cilindro");
		obstaculo1[4] = Forma(mSceneMgr,65,700,90,8,3.0,3.0,"cilindro");
		obstaculo1[5] = Forma(mSceneMgr,-70,810,0,4.0,10.0,4.0,"cubo");
	}

	void crearMonedas() {
		for (int i = 0;i < 5;i++) {
			monedas1[i] = Moneda(mSceneMgr,0,250+(20*i));
		}

		for (int i = 0;i < 5;i++) {
			monedas2[i] = Moneda(mSceneMgr,-150,500+(60*i));
		}

		for (int i = 0; i < 10;i++) {
			if (i < 5)
				monedas3[i] = Moneda(mSceneMgr,-100+(60*i),650);
			else 
				monedas3[i] = Moneda(mSceneMgr,150,350+(i*60));
		}
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
		
		// Creando el carro
		carro = Vehiculo(mSceneMgr);

		// Creando monedas
		crearMonedas();

		// Creando obstaculos
		crearObstaculo1();

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