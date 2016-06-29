#pragma once

#include "Ogre\ExampleApplication.h"
#include "stdafx.h"

class Moneda
{
private:
	static int newId;
public:
	int id;
	Ogre::SceneManager* scnMgr;
	Ogre::SceneNode* nodoMoneda;
	Ogre::Entity* entMoneda;
	float x;
	float y;
	float z;
	float radio;
	bool mostrar;

	Moneda(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0,float posY=0.0, float posZ=0.0);
	/*~Moneda(void);*/
};

