#include "MenuScreen.h"
#include "ScreenIndices.h"

MenuScreen::MenuScreen(Window* window) : window(window)
{
    this->screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::build()
{
    background = new Background("Images/fondo/background_zombies.png");
    background->setResolution(800, 500);
	spriteBatch.init();
}

void MenuScreen::destroy()
{
	background = nullptr;
}

void MenuScreen::onExit()
{
}

void MenuScreen::onEntry()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
	spriteBatch.init();
	camera2D.init(window->getScreenWidth(), window->getScreenHeight());
	//program.linkShader();
}

void MenuScreen::update()
{
	draw();
	camera2D.update();
	inputManager.update();
	checkInput();
}

void MenuScreen::draw()
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
	background->draw(spriteBatch);
	spriteBatch.end();
	spriteBatch.renderBatch();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	program.unuse();
	window->swapWindow();
}

void MenuScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				inputManager.pressKey(event.button.button);
				this->currentState = ScreenState::CHANGE_NEXT;
			break;
			case SDL_MOUSEBUTTONUP:
				inputManager.releaseKey(event.button.button);
			break;
		}
		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			this->currentState = ScreenState::CHANGE_NEXT;
		}
	}
}

void MenuScreen::initSystem()
{
	//window->create("Einal", 800, 600, 0);
}

int MenuScreen::getNextScreen() const
{
    return 0;
}

int MenuScreen::getPreviousScreen() const
{
    return 0;
}

MenuScreen::~MenuScreen()
{
}
