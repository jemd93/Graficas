#pragma once

#include "Ogre\ExampleApplication.h"
#include "stdafx.h"

class Asteroide
{
public:
	SceneNode* cinturon1;
	SceneNode* cinturon2;
	SceneNode* cinturon3;


	SceneNode* nodoCinturon1[5];
	SceneNode* nodoCinturon2[8];
	SceneNode* nodoCinturon3[11];

	Entity* entAsteroides1[5];
	Entity* entAsteroides2[8];
	Entity* entAsteroides3[11];

	int x,y,z;

	Asteroide(Ogre::SceneManager* mSceneMgr = NULL);

};

