#pragma once

#include "Piece.h"

class Queen : public Piece
{
private:

public:
    // CONSTRUCTOR AND DESTRUCTOR
    Queen(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target);
    virtual ~Queen();

    // MOVE GENERATING METHODS
    void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray);
    void filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray, const std::vector<std::vector<std::string>>& boardState);
};

