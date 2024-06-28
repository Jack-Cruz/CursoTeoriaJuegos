#include "App.h"
#include "ScreenList.h"

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
}

void App::addScreen()
{
	menuScreen = std::make_unique<MenuScreen>(&window);
	gamePlayScreen = std::make_unique<GameplayScreen>(&window);
	screenList->addScreen(menuScreen.get());
	screenList->addScreen(gamePlayScreen.get());
	screenList->setCreen(menuScreen->getIndex());
}

void App::onExit()
{
}
