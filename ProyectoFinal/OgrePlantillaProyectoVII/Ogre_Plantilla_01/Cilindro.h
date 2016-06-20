#pragma once
#include "Ogre\ExampleApplication.h"
#include "stdafx.h"
class Cilindro
{
private:
	static int newId;
public:
	int id;
	Ogre::SceneNode* nodoCilindro;
	Ogre::Entity* entCilindro;
	float x;
	float y;
	float z;
	float a;

	Cilindro(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0, float posZ=0.0,float angulo=0.0,float largo=1.0);
	/*~Cilindro(void);*/
};

