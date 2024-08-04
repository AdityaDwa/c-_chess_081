#pragma once

#include "State.h"

class MainMenuState : public State
{
private:
   
public:
    // CONSTRUCTOR AND DESTRUCTOR
    MainMenuState(sf::RenderWindow *window);
    virtual ~MainMenuState();

    // STATE UPDATING AND RENDERING METHODS
    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = nullptr);
    void endState();

    // COMPONENTS RENDERING METHOD
    void renderBtns(sf::RenderTarget *target);
};