#pragma once
#include "stdafx.h"
#include <string>
#include "Ogre\ExampleApplication.h"
#include "Moneda.h"
#include "Forma.h"
#include "Asteroide.h"

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
	float velocidad;
	float maxVel;

	// Variables del chasis
	Ogre::SceneNode* nodoChasis01;
	Ogre::Entity* entChasis01;

	//Variables de las alas
	Ogre::SceneNode* nodoAlas;
	bool estaVolando;
	ManualObject* alaIzquierda;
	ManualObject* alaDerecha;
	int activarAnimacion; // 0 no se ha activado, 1 ya se activ� y sigue volando  
	float escalaAlas;

	Vehiculo(Ogre::SceneManager* mSceneMgr = NULL);
	
	int Vehiculo::cheqColMon(Moneda mon);
	void Vehiculo::cheqColObs(Forma form);
	void Vehiculo::cheqColAst(SceneNode* ast);
	void Vehiculo::moverCarro(int frente);
	void Vehiculo::volar(int pos);
	void Vehiculo::rotarCarro(int izq);
	void Vehiculo::dibujarAlas(Ogre::SceneManager* mSceneMgr);
	void Vehiculo::animarVuelo(int frente);
};

