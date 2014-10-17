#pragma once

#include<d3d9.h>
#include<d3dx9.h>
#include"Input.h"

class Game
{
protected:

	HWND		_hWnd;
	LPDIRECT3D9	_d3d;
	LPDIRECT3DDEVICE9 _d3ddv;
	LPDIRECT3DSURFACE9 _BackBuffer;
	LPD3DXSPRITE SpriteHandle;

	Input* _Input;

	int _FrameRate;
	DWORD _DeltaTime;

	bool Init_Window(HINSTANCE);
	bool Init_Direct3D();
	virtual void gameUpdate(float DeltaTime);
	virtual void gameDraw();
	virtual void gameInit();
	virtual void clearScreen();
	virtual void processInput();
	virtual void deleteMemoryGame();
	void Render();

	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

public:
	Game();

	HWND getWindowHandle();
	LPDIRECT3DDEVICE9 getD3DDEVICE();

	bool Init(HINSTANCE);
	void GameRun();
	void GameEnd();

	~Game();
};

