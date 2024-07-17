#pragma once

#include "Piece.h"

class Knight : public Piece
{
private:

public:
    Knight(bool pieceColor, int row, int column, float boardSquareSize, float boardDimension, sf::RenderTarget *target);
    virtual ~Knight();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
};

