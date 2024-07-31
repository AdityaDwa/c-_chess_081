#pragma once

#include "MatchState.h"

class Game
{
private:
    sf::RenderWindow *window;
    sf::Event e;
    sf::Clock dtClock;
    std::stack<State*> stateStack; 
    float deltaTime;

    void initWindow();
    void initStates();
    void initApplication();
    
public:
    Game();
    virtual ~Game();

    void updateDeltaTime();
    void updateWindow();
    void renderWindow();
    void run();

};