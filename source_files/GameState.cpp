#include "../header_files/GameState.h"

GameState::GameState(sf::RenderWindow *window) : State(window) {
}

GameState::~GameState(){  
}

void GameState::endState(){
    std::cout<<"end State";
}

void GameState::updateInput(const float& deltaTime){
    this->checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->player.move(deltaTime, 0.f, -1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->player.move(deltaTime, -1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->player.move(deltaTime, 0.f, 1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->player.move(deltaTime, 1.f, 0.f);
    }
}

void GameState::update(const float& deltaTime){
    this->updateMousePositions();
    this->updateInput(deltaTime);

    this->player.update(deltaTime);
}

void GameState::render(sf::RenderTarget *target){
    if (!target)
    {
        target = this->window;
    }
    
    this->player.render(target);
    
}