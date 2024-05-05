#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include "Window.h"

using namespace std;

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	int width;
	int height;
	float time;
	Window* window;
	Sprite sprite;
	GLS_Program program;
	void init();
	void processInput();
	void initShaders();
	int cnt;
public:
	GameState gameState;
	MainGame();
	~MainGame();
	void run();
	void draw();
	void update();
};

