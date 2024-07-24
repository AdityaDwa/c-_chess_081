#pragma once

#include "State.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Button.h"

class MatchState : public State
{
private:
    Piece* boardPieces[8][8];
    Button* btns[30];
    
public:
    MatchState(sf::RenderWindow *window);
    virtual ~MatchState();

    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = nullptr);
    void endState();

    void renderBoard(sf::RenderTarget *target);
    void renderPieces(sf::RenderTarget *target);
};
