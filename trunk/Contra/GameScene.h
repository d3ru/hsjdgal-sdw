#ifndef __GAMESCENE__H__
#define __GAMESCENE__H__

#include "Game.h"
#include"SpriteManager.h"
#include"TextureManager.h"
#include"Zombie.h"
#include"Bullet.h"
#include"BackGround.h"
#include"HideObject.h"

#pragma once
class GameScene : public Game
{
public:
	GameScene();
	~GameScene();

	virtual void gameUpdate(float DeltaTime) override;
	virtual void gameDraw() override;
	virtual void gameInit() override;
	virtual void clearScreen() override;
	virtual void processInput() override;
	virtual void deleteMemoryGame() override; 

private:

	
	RECT screen;

	Zombie* zombie;

	std::vector<Bullet*>* listBullet;

	bool isFile;

	float currentTime;

	BackGround* bg;

	std::vector<HideObject*> listHideObject;
};

#endif