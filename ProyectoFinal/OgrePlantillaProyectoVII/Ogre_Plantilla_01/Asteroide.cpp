#include "Asteroide.h"

Asteroide::Asteroide(Ogre::SceneManager* mSceneMgr){
	
	if (mSceneMgr != NULL){
		cinturon1 = mSceneMgr->createSceneNode("Cinturon1_1");
		cinturon2 = mSceneMgr->createSceneNode("Cinturon2_2");
		cinturon3 = mSceneMgr->createSceneNode("Cinturon3_3");
		mSceneMgr->getRootSceneNode()->addChild(cinturon1);
		mSceneMgr->getRootSceneNode()->addChild(cinturon2);
		mSceneMgr->getRootSceneNode()->addChild(cinturon3);

		int x = 300;
		int y = 150;
		int z = 6770;
		for (int i = 0; i < 5; i++){
			switch (i)
			{
			case 1:
				x = 200;
				y = 80;
				z = 6690;
				break;
			case 2:
				x = 100;
				y = 65;
				z = 6700;
				break;
			case 3:
				x = 50;
				y = 41;
				z = 6720;
				break;
			case 4:
				x = 0;
				y = 15;
				z = 6770;
				break;
			default:
				break;
			}

			nodoCinturon1[i] = cinturon1->createChildSceneNode("NodoCinturon1"+std::to_string(i));
			entAsteroides1[i] = mSceneMgr->createEntity("EntCinturon1"+std::to_string(i),"roca01.mesh");
			entAsteroides1[i]->setMaterialName("rocaMat");
			nodoCinturon1[i]->attachObject(entAsteroides1[i]);
			nodoCinturon1[i]->setPosition(x,y,z);
			nodoCinturon1[i]->setScale(0.7,0.7,0.7);
			
		}
		x = -300;
		y = 150;
		z = 7800;
		for (int i = 0; i < 8; i++){
			nodoCinturon2[i] = cinturon2->createChildSceneNode("NodoCinturon2"+std::to_string(i));
			switch (i)
			{
			case 1:
				x = -250;
				y = 90;
				z = 7820;
				break;
			case 2:
				x = -190;
				y = 100;
				z = 7800;
				break;
			case 3:
				x = -150;
				y = 75;
				z = 7810;
				break;
			case 4:
				x = -100;
				y = 50;
				z = 7806;
				break;
			case 5:
				x = -80;
				y = 30;
				z = 7820;
				break;
			case 6:
				x = -50;
				y = 55;
				z = 7800;
				break;
			case 7:
				x = 0;
				y = 25;
				z = 7800;
				break;
			default:
				break;
			}
			entAsteroides2[i] = mSceneMgr->createEntity("EntCinturon2"+std::to_string(i),"roca02.mesh");
			entAsteroides2[i]->setMaterialName("rocaMat");
			nodoCinturon2[i]->attachObject(entAsteroides2[i]);
			nodoCinturon2[i]->setPosition(x,y,z);
			nodoCinturon2[i]->setScale(0.7,0.7,0.7);
		}
		x = 200;
		y = 45;
		z = 9500;
		for (int i = 0; i < 11; i++){
			nodoCinturon3[i] = cinturon3->createChildSceneNode("NodoCinturon3"+std::to_string(i));
			switch (i)
			{
			case 1:
				x = 150;
				y = 30;
				z = 9400;
				break;
			case 2:
				x = 80;
				y = 24;
				z = 9380;
				break;
			case 3:
				x = 45;
				y = 51;
				z = 9370;
				break;
			case 4:
				x = 20;
				y = 10;
				z = 9350;
				break;
			case 5:
				x = 0;
				y = 14;
				z = 9290;
				break;
			case 6:
				x = 75;
				y = 10;
				z = 9200;
				break;
			case 7:
				x = 110;
				y = 27;
				z = 9280;
				break;
			case 8:
				x = 180;
				y = 22;
				z = 9290;
				break;
			case 9:
				x = 205;
				y = 16;
				z = 9350;
				break;
			case 10:
				x = 300;
				y = 10;
				z = 9500;
				break;
			default:
				break;
			}
			entAsteroides3[i] = mSceneMgr->createEntity("EntCinturon3"+std::to_string(i),"roca03.mesh");
			entAsteroides3[i]->setMaterialName("rocaMat");
			nodoCinturon3[i]->attachObject(entAsteroides3[i]);
			nodoCinturon3[i]->setPosition(x,y,z);
			nodoCinturon3[i]->setScale(0.7,0.7,0.7);
		}
	}
}

void Asteroide::animar(){

}