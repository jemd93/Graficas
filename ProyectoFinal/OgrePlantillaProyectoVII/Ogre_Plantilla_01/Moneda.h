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
	float x;
	float y;
	float z;

	Moneda(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0, float posZ=0.0);
	/*~Moneda(void);*/
};
