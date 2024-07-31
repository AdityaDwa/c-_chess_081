#pragma once

#include "Piece.h"

class King : public Piece
{
private:
    bool kingFlag, rightRookFlag, leftRookFlag;
    
public:
    King(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target);
    virtual ~King();

    void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray);
    void filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray, const std::vector<std::vector<std::string>>& boardState);
    void isCastlingPossible();
};

