#include "GameScene.h"
#include "FileUtils.h"
#include"ZombieFactory.h"
#include"BulletFactory.h"
#include"HideObjectFactory.h"
#include"BackGround.h"
#include"config.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{

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
	
	
	
	
	RECT _rect;
	_rect.left = 0;
	_rect.right = 6656 - Screen_Height / 2;
	_rect.top = 440;
	_rect.bottom = 0;

	SpriteManager::createInstance()->camera->setBound(_rect);

	
	//screen = SpriteManager::createInstance()->camera->getScreen();

	listHideObject = HideObjectFactory::createInstance()->create();

	zombie = ZombieFactory::createInstance()->create();

	listBullet = new std::vector<Bullet*>();

	isFile = true;


	bg = new BackGround();
	bg->readData("..\\Resource\\map\\TileMap01.txt");
	//bg = BackGround::createInstance()->readData("..\\Resource\\map\\TileMap01.txt");
	
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

	//
	screen = SpriteManager::createInstance()->camera->getViewPortScreen();
	bg->checkTileInBound(screen);
	

	

	zombie->update(dt);
	zombie->collision(dt, listHideObject);

	SpriteManager::createInstance()->updateCamera(Zombie::getInstance()->getPositionX(), dt);

	
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
	
	zombie->drawBoundingBox(_d3ddv, zombie->getBox());

	bg->drawBackGround();

	zombie->draw();
	if (listBullet)
	{
		for (auto _bullet : *listBullet)
		{
			_bullet->draw();
		}
	}

	for (auto hideObject : listHideObject)
	{
		hideObject->drawBoundingBox(_d3ddv,hideObject->getBox());
	}

	}

void GameScene::clearScreen()
{
	_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,NULL);
}

void GameScene::deleteMemoryGame()
{}