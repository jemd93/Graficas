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
	float velocidad;
	float maxVel;

	// Variables del chasis
	Ogre::SceneNode* nodoChasis01;
	Ogre::Entity* entChasis01;

	// Variables esfera prueba SOLO PARA PRUEBAS. BORRAR ANTES DE ENTREGAR
	//Ogre::SceneNode* nodoEsfera01;
	//Ogre::Entity* entEsfera01;

	Vehiculo(Ogre::SceneManager* mSceneMgr = NULL);
	//~Vehiculo(void);
	void Vehiculo::moverCarro(int frente);
	void Vehiculo::rotarCarro(int izq);
};

