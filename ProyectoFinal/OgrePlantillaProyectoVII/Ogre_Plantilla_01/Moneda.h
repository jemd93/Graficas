#pragma once

#include "Ogre\ExampleApplication.h"
#include "stdafx.h"

class Moneda
{
public:
	Ogre::SceneNode* nodoMoneda;
	Ogre::Entity* entMoneda;

	Moneda(Ogre::SceneManager* mSceneMgr=NULL);
	/*~Moneda(void);*/
};

