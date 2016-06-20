#pragma once

#include "Ogre\ExampleApplication.h"
#include "stdafx.h"

class Moneda
{
private:
	static int newId;
public:
	int id;
	Ogre::SceneNode* nodoMoneda;
	Ogre::Entity* entMoneda;

	Moneda(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0, float posZ=0.0);
	/*~Moneda(void);*/
};

