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
	float aRoll;
	float aPitch;
	float aYaw;
	bool adelante;

	Forma(Ogre::SceneManager* mSceneMgr=NULL,float posX=0.0,float posY=0.0,float posZ=0.0,float aR=0.0,float aP=0.0,float aY=0.0,float largo=1.0,float alto=1.0,float ancho=1.0,std::string forma="cilindro");
	void Forma::deslizar(bool horizontal,int min, int max,int vel);
	/*~Forma(void);*/
};

