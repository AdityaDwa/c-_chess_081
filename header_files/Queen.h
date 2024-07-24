#pragma once

#include "Piece.h"

class Queen : public Piece
{
private:

public:
    Queen(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target);
    virtual ~Queen();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
    void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray);
};

