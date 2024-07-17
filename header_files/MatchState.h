#pragma once

#include "State.h"
#include "Board.h"

class MatchState : public State
{
private:
    Board gameBoard;
    
public:
    MatchState(bool *toRender, sf::RenderWindow *window);
    virtual ~MatchState();

    void updateMousePositions();

    void updateInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(bool *toRender, sf::RenderTarget *target = nullptr);
    void endState();
};
