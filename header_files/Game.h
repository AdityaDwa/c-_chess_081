#pragma once

#include "MainMenuState.h"
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
    // CONSTRUCTOR AND DESTRUCTOR
    Game();
    virtual ~Game();

    //WINDOW UPDATE AND RENDER METHODS
    void updateDeltaTime();
    void updateWindow();
    void renderWindow();

    // GAME LOOPING METHOD
    void run();

};