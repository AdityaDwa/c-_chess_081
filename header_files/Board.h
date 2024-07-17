#pragma once

#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"

struct pieceIdentifier {
    std::string pieceType;
    int row;
    int column;
    bool pieceColor;

    pieceIdentifier(const std::string& type, int r, int c, bool color) : pieceType(type), row(r), column(c), pieceColor(color) {}
};

class Board
{
private:
    int numSquares;
    float boardSquareSize;
    sf::Color boardColors[2];
    float boardDimension;

    pieceIdentifier* pieceInfo[8][8] = {nullptr};
    Piece* boardPieces[8][8];
    
public:
    Board();
    virtual ~Board();

    void render(bool *toRender, sf::RenderTarget *target);
    void pieceArrayGenerate();
    void populateBoard(sf::RenderTarget *target);
};
