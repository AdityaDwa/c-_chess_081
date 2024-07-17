#include "../header_files/Board.h"

Board::Board()
{
    this->numSquares = 8;
    this->boardSquareSize = 120.f;
    this->boardColors[0] = sf::Color(235, 236, 220);
    this->boardColors[1] = sf::Color(139, 85, 19);
    this->boardDimension = numSquares * boardSquareSize;

    for (int i = 0; i < this->numSquares; ++i)
    {
        for (int j = 0; j < this->numSquares; ++j)
        {
            this->pieceInfo[i][j] = nullptr;
            this->boardPieces[i][j] = nullptr;
        }
    }

    this->pieceArrayGenerate();
}

Board::~Board()
{
    for (int i = 0; i < this->numSquares; ++i)
    {
        for (int j = 0; j < this->numSquares; ++j)
        {
            delete this->pieceInfo[i][j];
            delete this->boardPieces[i][j];
            this->pieceInfo[i][j] = nullptr;
            this->boardPieces[i][j] = nullptr;
        }
    }
}

void Board::render(bool *toRender, sf::RenderTarget *target)
{
    if (*toRender)
    {
        float startXPosition = (target->getSize().x - this->boardDimension) / 2;
        float startYPosition = (target->getSize().y - this->boardDimension) / 2;

        for (int i = 0; i < this->numSquares; i++)
        {
            for (int j = 0; j < this->numSquares; j++)
            {
                sf::RectangleShape square(sf::Vector2f(this->boardSquareSize, this->boardSquareSize));
                square.setPosition(startXPosition + (i * this->boardSquareSize), startYPosition + (j * this->boardSquareSize));

                square.setFillColor(this->boardColors[(i + j) % 2]);

                target->draw(square);

                delete this->boardPieces[i][j];
            }
        }

        for (int i = 0; i < this->numSquares; i++)
        {
            for (int j = 0; j < this->numSquares; j++)
            {
                if (this->pieceInfo[i][j] == nullptr)
                {
                    continue;
                }

                if (this->pieceInfo[i][j]->pieceType == "pawn")
                {
                    this->boardPieces[i][j] = new Pawn(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                    this->boardPieces[i][j]->render(target);
                }

                // else if (this->pieceInfo[i][j]->pieceType == "rook")
                // {
                //     this->boardPieces[i][j] = new Rook(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                //     this->boardPieces[i][j]->render(target);
                // }

                if (this->pieceInfo[i][j]->pieceType == "knight")
                {
                    this->boardPieces[i][j] = new Knight(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                    this->boardPieces[i][j]->render(target);
                }

                // else if (this->pieceInfo[i][j]->pieceType == "bishop")
                // {
                //     this->boardPieces[i][j] = new Bishop(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                //     this->boardPieces[i][j]->render(target);
                // }
                
                // else if (this->pieceInfo[i][j]->pieceType == "queen")
                // {
                //     this->boardPieces[i][j] = new Queen(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                //     this->boardPieces[i][j]->render(target);
                // }

                // else
                // {
                //     this->boardPieces[i][j] = new King(this->pieceInfo[i][j]->pieceColor, i, j, this->boardSquareSize, this->boardDimension, target);
                //     this->boardPieces[i][j]->render(target);
                // }
            }
        }

        *toRender = false;
    }
}

void Board::pieceArrayGenerate()
{
    this->pieceInfo[0][0] = new pieceIdentifier("rook", 0, 0, 1);
    this->pieceInfo[1][0] = new pieceIdentifier("knight", 1, 0, 1);
    this->pieceInfo[2][0] = new pieceIdentifier("bishop", 2, 0, 1);
    this->pieceInfo[3][0] = new pieceIdentifier("queen", 3, 0, 1);
    this->pieceInfo[4][0] = new pieceIdentifier("king", 4, 0, 1);
    this->pieceInfo[5][0] = new pieceIdentifier("bishop", 5, 0, 1);
    this->pieceInfo[6][0] = new pieceIdentifier("knight", 6, 0, 1);
    this->pieceInfo[7][0] = new pieceIdentifier("rook", 7, 0, 1);

    this->pieceInfo[0][1] = new pieceIdentifier("pawn", 0, 1, 1);
    this->pieceInfo[1][1] = new pieceIdentifier("pawn", 1, 1, 1);
    this->pieceInfo[2][1] = new pieceIdentifier("pawn", 2, 1, 1);
    this->pieceInfo[3][1] = new pieceIdentifier("pawn", 3, 1, 1);
    this->pieceInfo[4][1] = new pieceIdentifier("pawn", 4, 1, 1);
    this->pieceInfo[5][1] = new pieceIdentifier("pawn", 5, 1, 1);
    this->pieceInfo[6][1] = new pieceIdentifier("pawn", 6, 1, 1);
    this->pieceInfo[7][1] = new pieceIdentifier("pawn", 7, 1, 1);

    this->pieceInfo[0][6] = new pieceIdentifier("pawn", 0, 6, 0);
    this->pieceInfo[1][6] = new pieceIdentifier("pawn", 1, 6, 0);
    this->pieceInfo[2][6] = new pieceIdentifier("pawn", 2, 6, 0);
    this->pieceInfo[3][6] = new pieceIdentifier("pawn", 3, 6, 0);
    this->pieceInfo[4][6] = new pieceIdentifier("pawn", 4, 6, 0);
    this->pieceInfo[5][6] = new pieceIdentifier("pawn", 5, 6, 0);
    this->pieceInfo[6][6] = new pieceIdentifier("pawn", 6, 6, 0);
    this->pieceInfo[7][6] = new pieceIdentifier("pawn", 7, 6, 0);

    this->pieceInfo[0][7] = new pieceIdentifier("rook", 0, 7, 0);
    this->pieceInfo[1][7] = new pieceIdentifier("knight", 1, 7, 0);
    this->pieceInfo[2][7] = new pieceIdentifier("bishop", 2, 7, 0);
    this->pieceInfo[3][7] = new pieceIdentifier("queen", 3, 7, 0);
    this->pieceInfo[4][7] = new pieceIdentifier("king", 4, 7, 0);
    this->pieceInfo[5][7] = new pieceIdentifier("bishop", 5, 7, 0);
    this->pieceInfo[6][7] = new pieceIdentifier("knight", 6, 7, 0);
    this->pieceInfo[7][7] = new pieceIdentifier("rook", 7, 7, 0);
}

void Board::populateBoard(sf::RenderTarget *target)
{
}