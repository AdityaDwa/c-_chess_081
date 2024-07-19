#pragma once

#include "Piece.h"

class King : public Piece
{
private:

public:
    King(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target);
    virtual ~King();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
};

