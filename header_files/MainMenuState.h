#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State {
private:
    sf::RectangleShape background;
    sf::Font font;
    
    std::map<std::string, Button*> btns; 

    void initFonts();
    void initBtns();

public:
    MainMenuState(sf::RenderWindow *window);
    ~MainMenuState();
    void endState();
    void updateInput(const float& deltaTime);
    void updateBtns();
    void update(const float& deltaTime);
    void renderBtns(sf::RenderTarget *target = NULL);
    void render(sf::RenderTarget *target = NULL);
};