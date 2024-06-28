#include "GameplayScreen.h"
#include <random>
#include <ctime>

using namespace std;

GameplayScreen::GameplayScreen(Window* window) : window(window)
{
	gameState = GameState2::PLAY;
}

GameplayScreen::~GameplayScreen()
{
}

void GameplayScreen::build()
{
	levels.push_back(new Level("Level/level1.txt"));
	levels.push_back(new Level("Level/level2.txt"));
	currentLevel = 1;
	spriteBatch.init();
	// Player
	player = new Player();
	player->init(3.5f, levels[currentLevel]->getPlayerPosition(),
		&inputManager);

	// Humans
	std::mt19937 randomEngie(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, levels[currentLevel]->getWidth() - 2
	);
	std::uniform_int_distribution<int>randPosY(
		1, levels[currentLevel]->getHeight() - 2
	);
	for (int i = 0; i < levels[currentLevel]->getNumHumans(); i++)
	{
		humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngie) * TILE_WIDTH,
			randPosY(randomEngie) * TILE_WIDTH);
		humans.back()->init(1.5f, pos);
	}
	// Zombies
	for (glm::vec2 pos : levels[currentLevel]->getZombiesPosition())
	{
		zombies.push_back(new Zombie());
		zombies.back()->init(1.5f, pos);
	}
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onExit()
{
}

void GameplayScreen::onEntry()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
	camera2D.init(window->getScreenWidth(), window->getScreenHeight());
}

void GameplayScreen::updateElements() {

	camera2D.update();
	camera2D.setPosition(player->getPosition());
}


void GameplayScreen::update()
{
	while (gameState != GameState2::EXIT) {
		draw();
		checkInput();
		updateElements();
		inputManager.update();
		player->update(levels[currentLevel]->getLevelData(), humans, zombies);
		for (size_t i = 0; i < humans.size(); i++)
		{
			humans[i]->update(levels[currentLevel]->getLevelData(),
				humans, zombies);
		}
		for (size_t i = 0; i < zombies.size(); i++)
		{
			zombies[i]->update(levels[currentLevel]->getLevelData(),
				humans, zombies);
			for (size_t j = 0; j < humans.size(); j++)
			{
				if (zombies[i]->collideWithAgent(humans[j])) {
					zombies.push_back(new Zombie());
					zombies.back()->init(1.3f, humans[j]->getPosition());
					delete humans[j];
					humans[j] = humans.back();
					humans.pop_back();
				}
			}
		}

	}
}

void GameplayScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 cameraMatrix = camera2D.getCameraMatrix();
	GLuint pCameraLocation = program.getUniformLocation("pCamera");
	glUniformMatrix4fv(pCameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	spriteBatch.begin();
	levels[currentLevel]->draw();
	player->draw(spriteBatch);
	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i]->draw(spriteBatch);
	}
	for (size_t i = 0; i < zombies.size(); i++)
	{
		zombies[i]->draw(spriteBatch);
	}
	spriteBatch.end();
	spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	program.unuse();
	window->swapWindow();
}

void GameplayScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState2::EXIT;
			break;
		case SDL_MOUSEMOTION:
			/*cout << "Posicion del mousec " << event.motion.x << " " << event.motion.y << endl;
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			glm::vec2 mouseCoords = camera2D.convertToScreenWorld(inputManager.getMouseCoords());
			//cout << "Nueva posicion de acuerdo a camara " <<  mouseCoords.x
				//	<< " " << mouseCoords.y << endl;*/
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(event.button.button);
			break;
		}
	}
}

void GameplayScreen::initSystem()
{
}

int GameplayScreen::getNextScreen() const
{
    return 0;
}

int GameplayScreen::getPreviousScreen() const
{
    return 0;
}
