#pragma once

#include "State.h"

class MainMenuState : public State
{
private:
   
public:
    MainMenuState(sf::RenderWindow *window);
    virtual ~MainMenuState();

    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = nullptr);
    void endState();

    void renderBtns(sf::RenderTarget *target);
};