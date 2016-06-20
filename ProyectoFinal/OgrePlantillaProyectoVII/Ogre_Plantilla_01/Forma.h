#pragma once
#include "Ogre\ExampleApplication.h"
#include "stdafx.h"
class Forma
{
private:
	static int newId;
public:
	int id;
	Ogre::SceneNode* nodoForma;
	Ogre::Entity* entForma;
	float x;
	float y;
	float z;
	float a;

	Forma(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0, float posZ=0.0,float angulo=0.0,float largo=1.0,float alto=1.0,float ancho=1.0,std::string forma="cilindro");
	/*~Forma(void);*/
};

