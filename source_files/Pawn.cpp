#include "../header_files/Pawn.h"

Pawn::Pawn(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Pawn::~Pawn()
{
}

void Pawn::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    std::vector<std::vector<std::string>> boardState = this->readBoardState();
    if (pieceColor)
    {
        bool up = (column + 1) < 8;
        bool right = (row + 1) < 8;
        bool left = (row - 1) >= 0;
        bool intialPos = (column == 1);

        if (up && boardState[row][column + 1].empty())
        {
            moveArray.push_back({row, column + 1});
        }

        if (up && right)
        {
            if (!boardState[row + 1][column + 1].empty())
            {
                std::stringstream boardInfoString(boardState[row + 1][column + 1]);

                std::string piece;
                int color;

                std::getline(boardInfoString, piece, ',');
                boardInfoString >> color;

                if (color != pieceColor)
                {
                    moveArray.push_back({row + 1, column + 1});
                }
            }
        }

        if (up && left)
        {
            if (!boardState[row - 1][column + 1].empty())
            {
                std::stringstream boardInfoString(boardState[row - 1][column + 1]);

                std::string piece;
                int color;

                std::getline(boardInfoString, piece, ',');
                boardInfoString >> color;

                if (color != pieceColor)
                {
                    moveArray.push_back({row - 1, column + 1});
                }
            }
        }

        if (intialPos && boardState[row][column + 1].empty() && boardState[row][column + 2].empty())
        {
            moveArray.push_back({row, column + 2});
        }
    }
    else
    {
        bool down = (column - 1) >= 0;
        bool right = (row + 1) < 8;
        bool left = (row - 1) >= 0;
        bool intialPos = (column == 6);

        if (down && boardState[row][column - 1].empty())
        {
            moveArray.push_back({row, column - 1});
        }

        if (down && right)
        {
            if (!boardState[row + 1][column - 1].empty())
            {
                std::stringstream boardInfoString(boardState[row + 1][column - 1]);

                std::string piece;
                int color;

                std::getline(boardInfoString, piece, ',');
                boardInfoString >> color;

                if (color != pieceColor)
                {
                    moveArray.push_back({row + 1, column - 1});
                }
            }
        }

        if (down && left)
        {
            if (!boardState[row - 1][column - 1].empty())
            {
                std::stringstream boardInfoString(boardState[row - 1][column - 1]);

                std::string piece;
                int color;

                std::getline(boardInfoString, piece, ',');
                boardInfoString >> color;

                if (color != pieceColor)
                {
                    moveArray.push_back({row - 1, column - 1});
                }
            }
        }

        if (intialPos && boardState[row][column - 1].empty() && boardState[row][column - 2].empty())
        {
            moveArray.push_back({row, column - 2});
        }
    }
}

void Pawn::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
}