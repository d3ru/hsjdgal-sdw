#ifndef __GAMESCENE__H__
#define __GAMESCENE__H__

#include "Game.h"
#include"SpriteManager.h"
#include"TextureManager.h"
#include"Ball.h"
#include"Zombie.h"
#include"Bullet.h"

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

	std::vector<Ball*>* listBall;

	Ball* ball;


	Zombie* zombie;

	std::vector<Bullet*>* listBullet;

	bool isFile;

	float currentTime;
};

#endif