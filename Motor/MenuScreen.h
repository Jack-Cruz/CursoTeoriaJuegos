#pragma once
#include "IGameScreen.h"
#include "Window.h"
#include "SpriteBatch.h"
#include "Background.h"
#include "GLS_Program.h"
#include "Camera2D.h"
#include "InputManager.h"

class MenuScreen :
    public IGameScreen
{
private:
    Window* window = nullptr;
    SpriteBatch spriteBatch;
    Background* background;
    GLS_Program program;
    Camera2D camera2D;
    InputManager inputManager;
public:
    MenuScreen(Window* window);
    virtual void checkInput() override;
    virtual void initSystem() override;
    virtual void build() override;
    virtual void destroy() override;
    virtual void onExit() override;
    virtual void onEntry() override;
    virtual void draw() override;
    virtual void update() override;
    virtual int getNextScreen() const override;
    virtual int getPreviousScreen() const override;
    ~MenuScreen();
};

