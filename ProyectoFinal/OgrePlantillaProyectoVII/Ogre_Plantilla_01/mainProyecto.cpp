#include "Ogre\ExampleApplication.h"
#include <string>
#include "Vehiculo.h"
#include "Moneda.h"
#include "Forma.h"
#include "Asteroide.h"

Vehiculo carro;
Moneda monedas1[5];
Moneda monedas2[5];
Moneda monedas3[10];
Moneda monedas4[11];
Moneda monedas5[10];
Moneda monedas6[25];

Forma obstaculo1[7];
Forma obstaculo2[6];
Forma obstaculo3[13];

Asteroide cinturon;

int Moneda::newId = 0;
int Forma::newId = 0;

AnimationState* alasAnimState;
AnimationState* asteroidAnimState;

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

			// Animar obstaculo 2 :
			obstaculo2[0].deslizar(true,-150,30,2);
			obstaculo2[1].deslizar(true,30,150,2);
			obstaculo2[2].deslizar(false,1650,1900,2);
			obstaculo2[3].deslizar(false,1800,2100,2);
			obstaculo2[4].deslizar(true,-150,30,2);
			obstaculo2[5].deslizar(true,30,150,2);

			if (carro.estaVolando && carro.activarAnimacion==0){
					carro.animarVuelo(1);
			}
			else if (!carro.estaVolando && carro.activarAnimacion==1){
					carro.animarVuelo(-1);
			}

			cinturon.animar();
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
		obstaculo1[0] = Forma(mSceneMgr,150,4,400,30,90,0.0,10,3.0,3.0,"cilindro01");
		obstaculo1[1] = Forma(mSceneMgr,215,4,560,90,90,0.0,15,3.0,3.0,"cilindro01");
		obstaculo1[2] = Forma(mSceneMgr,-30,4,900,90,90,0.0,10,3.0,3.0,"cilindro01");
		obstaculo1[3] = Forma(mSceneMgr,65,4,700,0,90,0.0,10,3.0,3.0,"cilindro01");
		obstaculo1[4] = Forma(mSceneMgr,65,4,700,90,90,0.0,8,3.0,3.0,"cilindro01");
		obstaculo1[5] = Forma(mSceneMgr,-70,40,810,0,90,0.0,4.0,10.0,4.0,"cubo01");
	}

	void crearObstaculo2() {
		obstaculo2[0] = Forma(mSceneMgr,-150,20,1400,0,90,90,4.0,12.0,4.0,"cubo01");
		obstaculo2[1] = Forma(mSceneMgr,150,20,1500,0,90,90,4.0,12.0,4.0,"cubo01");
		obstaculo2[2] = Forma(mSceneMgr,100,20,1650,0,0,0,4.0,12.0,4.0,"cubo01");
		obstaculo2[3] = Forma(mSceneMgr,-100,20,1800,0,0,0,4.0,12.0,4.0,"cubo01");
		obstaculo2[4] = Forma(mSceneMgr,-150,20,2200,0,90,90,4.0,12.0,4.0,"cubo01");
		obstaculo2[5] = Forma(mSceneMgr,150,20,2300,0,90,90,4.0,12.0,4.0,"cubo01");
	}

	void crearObstaculo3() {
		obstaculo3[0] = Forma(mSceneMgr,0,10,5600,0,0,0,2.0,2.0,2.0,"roca02");
		obstaculo3[1] = Forma(mSceneMgr,-100,10,5650,0,0,0,2.0,2.0,2.0,"roca04");
		obstaculo3[2] = Forma(mSceneMgr,200,15,5850,0,0,0,1.5,1.5,1.5,"roca01");
		obstaculo3[3] = Forma(mSceneMgr,50,5,6200,0,0,0,2.0,2.0,2.0,"roca01");
		obstaculo3[4] = Forma(mSceneMgr,-150,0,5975,0,0,0,1.0,1.0,1.0,"roca03");
		obstaculo3[5] = Forma(mSceneMgr,-175,0,5950,0,0,0,1.0,1.0,1.0,"roca02");
		obstaculo3[6] = Forma(mSceneMgr,-200,0,6000,0,0,0,1.0,1.0,1.0,"roca01");
		obstaculo3[7] = Forma(mSceneMgr,25,0,5900,0,90,0,3.0,3.0,3.0,"roca04");
		obstaculo3[8] = Forma(mSceneMgr,50,0,6100,0,0,0,1.5,1.5,1.5,"roca03");
		obstaculo3[9] = Forma(mSceneMgr,65,0,6140,0,30,0,2.0,2.0,2.0,"roca02");
		obstaculo3[10] = Forma(mSceneMgr,65,5,6020,0,45,90,1.7,1.7,1.7,"roca04");
		obstaculo3[11] = Forma(mSceneMgr,-100,5,6300,50,0,0,2.0,2.0,2.0,"roca02");
		obstaculo3[12] = Forma(mSceneMgr,-50,0,6350,0,0,90,2.0,2.0,2.0,"roca03");
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

		for (int i = 0;i < 11;i++) {
			monedas4[i] = Moneda(mSceneMgr,150-(30*i),930+(i*30));
		}

		for (int i = 0; i < 10;i++) {
			if (i < 3) 
				monedas5[i] = Moneda(mSceneMgr,-150,1400 + (i*60));
			else if ((i >= 3) && (i < 7)) 
				monedas5[i] = Moneda(mSceneMgr,0,1500 + (i*60));
			else 
				monedas5[i] = Moneda(mSceneMgr,150,1800 + (i*60));
		}

		for (int i = 0;i < 25;i++) {
			if (i < 5)
				monedas6[i] = Moneda(mSceneMgr,125,5500 + (i*60));
			else if ((i >= 5) && (i < 8))
				monedas6[i] = Moneda(mSceneMgr,-175,5500 + ((i-3)*60));
			else if ((i >= 8) && (i < 13)) 
				monedas6[i] = Moneda(mSceneMgr,-100,5500 + ((i-2)*60));
			else if ((i >= 13) && (i < 17))
				monedas6[i] = Moneda(mSceneMgr,150,5500 + ((i-1)*60));
			else if ((i >= 17) && (i < 21))
				monedas6[i] = Moneda(mSceneMgr,-200,5500 + ((i-3)*60));
			else if ((i >= 21) && (i < 25))
				monedas6[i] = Moneda(mSceneMgr,-160 + ((i-18)*30),5985 + ((i-5)*15));
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
		LuzPuntual02->setDirection(Ogre::Vector3( -1, -1, 1 ));
		
		// Creando el carro
		carro = Vehiculo(mSceneMgr);
		carro.dibujarAlas(mSceneMgr);

		// Creando monedas
		crearMonedas();

		// Creando obstaculos
		crearObstaculo1();
		crearObstaculo2();
		crearObstaculo3();

		cinturon = Asteroide(mSceneMgr);

		//BordePista
		Ogre::SceneNode* _nodeBPista = mSceneMgr->createSceneNode("BordePista");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBPista);
				
		Ogre::Entity* _entBPista = mSceneMgr->createEntity("BordePista01", "bordePista.mesh");
		_entBPista->setMaterialName("shParedes01");
		_nodeBPista->attachObject(_entBPista);


		//PisoObstaculo
		Ogre::SceneNode* _nodePObstaculo = mSceneMgr->createSceneNode("PistaObstaculo");
		mSceneMgr->getRootSceneNode()->addChild(_nodePObstaculo);
				
		Ogre::Entity* _entPObstaculo = mSceneMgr->createEntity("PistaObstaculo", "pisoObstaculo01.mesh");
		_nodePObstaculo->attachObject(_entPObstaculo);
		_entPObstaculo->setMaterialName("shObstaculo01");

		//PisoNOObstaculo
		Ogre::SceneNode* _nodePNObstaculo = mSceneMgr->createSceneNode("PistaNoObstaculo");
		mSceneMgr->getRootSceneNode()->addChild(_nodePNObstaculo);
				
		Ogre::Entity* _entPNOObstaculo = mSceneMgr->createEntity("PistaNoObstaculo", "pisoNoObstaculo01.mesh");
		_nodePNObstaculo->attachObject(_entPNOObstaculo);
		_entPNOObstaculo->setMaterialName("shAreaNoObtaculo01");


		//PosterInicioFinal
		Ogre::SceneNode* _nodePoster = mSceneMgr->createSceneNode("PosterInicioFinal");
		mSceneMgr->getRootSceneNode()->addChild(_nodePoster);
			
		Ogre::Entity* _entPoster = mSceneMgr->createEntity("PosterInicioFinal", "posterInicioFinal.mesh");
		_entPoster->setMaterialName("posterInicioFinal");
		_nodePoster->attachObject(_entPoster);

				
		//BanderaInicial
		Ogre::SceneNode* _nodeBInicial = mSceneMgr->createSceneNode("BanderaInicial");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBInicial);
				
		Ogre::Entity* _entBanderaI = mSceneMgr->createEntity("BanderaInicial", "banderaInicial.mesh");				
		_entBanderaI->setMaterialName("banderaInicial");				
		_nodeBInicial->attachObject(_entBanderaI);
		_nodeBInicial->yaw(Degree(180));
		_nodeBInicial->translate(-11,0,125);


		//BanderaFinal
		Ogre::SceneNode* _nodeBFinal = mSceneMgr->createSceneNode("BanderaFinal");
		mSceneMgr->getRootSceneNode()->addChild(_nodeBFinal);
		
		Ogre::Entity* _entBanderaF = mSceneMgr->createEntity("BanderaFinal", "banderaFinal.mesh");
		_entBanderaF->setMaterialName("lambert1");
		_nodeBFinal->attachObject(_entBanderaF);

		mSceneMgr->setSkyBox(true, "skyBoxM2",5000);

	}

};

int main (void)
{

	Example1 app;
	app.go();
	return 0;
}