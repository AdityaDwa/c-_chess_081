#pragma once

#include "State.h"

class GameState : public State {
private:
    Entity player;

public:
    GameState(sf::RenderWindow *window);
    ~GameState();
    void endState();
    void updateInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = NULL);
};
