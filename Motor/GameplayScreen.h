#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Level.h"
#include "Player.h"
#include "Human.h"
#include "Zombie.h"

enum class GameState2 {
    PLAY, EXIT
};

class GameplayScreen :
    public IGameScreen
{
private:
    GLS_Program program;
    Camera2D camera2D;
    Window* window = nullptr;
    SpriteBatch spriteBatch;
    GLTexture texture;
    InputManager inputManager;
    vector<Level*> levels;
    vector<Human*> humans;
    vector<Zombie*> zombies;
    Player* player;
    double alphaReduce;
    double alphaReduceTotal;
    int currentLevel;

public:
    GameplayScreen(Window* window);
    ~GameplayScreen();
    GameState2 gameState;
    virtual void build() override;
    virtual void destroy() override;
    virtual void onExit() override;
    virtual void onEntry() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void checkInput() override;
    virtual void initSystem() override;
    void updateElements();

    virtual int getNextScreen() const override;
    virtual int getPreviousScreen() const override;
};

