#pragma once

#include "Piece.h"

class Pawn : public Piece
{
private:

public:
    Pawn(bool pieceColor, int row, int column, float boardSquareSize, float boardDimension, sf::RenderTarget *target);
    virtual ~Pawn();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
};

