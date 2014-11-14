#ifndef __SPRITEMANAGER__H__
#define __SPRITEMANAGER__H__

#pragma once


#include"SpriteManager.h"
#include"Texture.h"
#include"Sprite.h"
#include"ObjectGame.h"
#include"Camera.h"

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	Sprite* sprite;

	Camera* camera;

	static SpriteManager* createInstance();
	void init(LPD3DXSPRITE spriteHandle);
	void draw(Texture* texture, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF);
	void drawObj(ObjectGame*, D3DCOLOR transcolor = 0xFFFFFFFF);
	void updateCamera(float posRambo, float dt);
	void drawLine(LPDIRECT3DDEVICE9 _d3ddv, Point startPosition, Point endPostion);
};

#endif