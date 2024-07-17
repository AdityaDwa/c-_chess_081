#pragma once

#include "State.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"

class MatchState : public State
{
private:
    Piece* boardPieces[32];
    
public:
    MatchState(sf::RenderWindow *window);
    virtual ~MatchState();

    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = nullptr);
    void endState();

    void renderBoard(sf::RenderTarget *target);
    void renderPieces(sf::RenderTarget *target);
};
