#include "GameScene.h"
#include "FileUtils.h"
#include "BallFactory.h"
#include"ZombieFactory.h"
#include"BulletFactory.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	if (ball)
		delete ball;
	if (listBall)
		delete listBall;
	if (zombie)
		delete zombie;
	if (listBullet)
		delete listBullet;
}


void GameScene::gameInit()
{
	
	
	SpriteManager::createInstance()->init(this->SpriteHandle);
	TextureManager::createInstance(this->_d3ddv);
	FileUtils::getInstance()->loadFileCSV();
	
	
	listBall = BallFactory::getInstance()->createListBall();
	//pall = PallFactory::getInstance()->create();


	ball = BallFactory::getInstance()->createObj();

	zombie = ZombieFactory::createInstance()->create();

	listBullet = new std::vector<Bullet*>();

	isFile = true;

	
}

void GameScene::processInput()
{
	///*Input::createInstance()->ProcessKeyboard();

	//Input::createInstance()->Update();

	//int key_Down = Input::createInstance()->GetKeyDown();
	//int key_Up = Input::createInstance()->GetKeyUp();*/
}

void GameScene::gameUpdate(float dt)
{
	/*for (auto _ball : *listBall)
	{
		_ball->update(dt);
	}
*/
	currentTime += dt;

	Input::CreateInstance()->ProcessKeyboard();

	Input::CreateInstance()->Update();

	/*int key_Down = Input::createInstance()->GetKeyDown();
	int key_Up = Input::createInstance()->GetKeyUp();*/

	if (Input::CreateInstance()->IsKeyDown(DIK_Z) && currentTime >= 0.2)
	{
		Bullet* bullet = BulletFactory::createInstance()->create(zombie);
		listBullet->push_back(bullet);
		currentTime = 0;
	}
	

	ball->update(dt);

	//pall->update();

	zombie->update(dt);

	if (listBullet)
	{
		for (auto _bullet : *listBullet)
		{
			_bullet->update(dt);
		}
	}

}

void GameScene::gameDraw()
{
	/*for (auto _ball : *listBall)
	{
		_ball->draw();
	}*/
	ball->draw();
	//pall->draw();
	zombie->draw();
	if (listBullet)
	{
		for (auto _bullet : *listBullet)
		{
			_bullet->draw();
		}
	}

}

void GameScene::clearScreen()
{
	_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,NULL);
}

void GameScene::deleteMemoryGame()
{}