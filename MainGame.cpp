#include "MainGame.h"


MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	cnt = 0;
}

MainGame::~MainGame()
{
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Left 4 Dead 2", width, height, 0);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	initShaders();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cnt++;
	if (cnt >= 100) {
		program.use();
		sprite.draw();
		program.unuse();
	}
	if (cnt == 200) cnt = 0;
	window->swapWindow();
}



void MainGame::run()
{
	init();
	sprite.init(-1, -1, 2, 2, "img/Left4Dead2.png");
	update();
}



void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << "Posicion en X: " << event.motion.x <<
				// " Y: " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shader/colorShaderVert.txt",
		"Shader/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}
