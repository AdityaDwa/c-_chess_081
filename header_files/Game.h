#pragma once

#include "MainMenuState.h"

class Game
{
private:
    //INITIALIZING VARIABLES/POINTERS
    sf::RenderWindow *window;
    sf::Event e;
    sf::Clock dtClock;
    float deltaTime;
    std::stack<State*> states;      //LIFO DATA VARIABLE

    //METHOD FOR WINDOW AND STATE INITIALIZATION
    void initWindow();
    void initStates();
    
public:
    //CLASS CONSTRUCTOR AND DESTRUCTOR
    Game();
    virtual ~Game();
    
    void endApplication();

    //FULLSCREEN TOGGLE FUNCTION
    void toggleFullScreen();

    //GAME FLOW METHODS
    void updateDeltaTime();
    void updateWindow();
    void renderWindow();
    void run();
};
