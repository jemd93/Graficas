#pragma once
#include "stdafx.h"
#include <string>
#include "Ogre\ExampleApplication.h"

class Vehiculo
{
public:
// Variables de las ruedas
	Ogre::SceneNode* nodosRuedas[4];
	Ogre::SceneNode* nodosYaw[4];
	Ogre::Entity* entRuedas[4];
	float anguloGiroRuedas;
	float anguloRoteRuedas;
	float anguloActRote;
	

	// Variables del chasis
	Ogre::SceneNode* nodoChasis01;
	Ogre::Entity* entChasis01;
	int pos[3]; //x,y,z

	//Variables de las alas
	Ogre::SceneNode* nodoAlas;
	bool estaVolando;
	ManualObject* alaIzquierda;
	ManualObject* alaDerecha;
	int activarAnimacion; // 0 no se ha activado, 1 ya se activ� y sigue volando  

	Vehiculo(Ogre::SceneManager* mSceneMgr = NULL);
	//~Vehiculo(void);
	void Vehiculo::moverCarro(int frente);
	void Vehiculo::rotarCarro(int izq);
	void Vehiculo::dibujarAlas(Ogre::SceneManager* mSceneMgr);
	void Vehiculo::animarVuelo(int frente);
};

