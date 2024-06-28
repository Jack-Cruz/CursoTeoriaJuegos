#include <SDL/SDL.h>
#include "MainGame.h"
#include "App.h"

int main(int argc, char** argv) {
	MainGame mainGame;
	mainGame.run();
	//App app;
	//app.run();
	system("pause");
	return 0;
}
