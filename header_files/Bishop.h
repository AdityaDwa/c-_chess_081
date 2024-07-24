#pragma once

#include "Piece.h"

class Bishop : public Piece
{
private:

public:
    Bishop(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target);
    virtual ~Bishop();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
    void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray);
};

