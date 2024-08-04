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
        // IF THE PAWN IS WHITE THEN THE MOVES IN THE UP DIRECTION ARE GENERATED
        bool up = (column + 1) < 8;
        bool right = (row + 1) < 8;
        bool left = (row - 1) >= 0;
        bool intialPos = (column == 1);

        // IF THE ONE COORDINATE ABOVE PAWN IS EMPTY
        if (up && boardState[row][column + 1].empty())
        {
            moveArray.push_back({row, column + 1});
        }

        // IF THE UP RIGHT POSITION OF WHITE IS OCCUPIED BY BLACK PAWN THEN ONLY THIS MOVE IS GENERATED
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

        // IF THE UP LEFT POSITION OF WHITE IS OCCUPIED BY BLACK PAWN THEN ONLY THIS MOVE IS GENERATED
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

        // IF BOTH TWO POSITIONS ABOVE THE PAWN IS EMPTY THEN THIS MOVE IS GENERATED
        if (intialPos && boardState[row][column + 1].empty() && boardState[row][column + 2].empty())
        {
            moveArray.push_back({row, column + 2});
        }
    }
    else
    {
        // IF THE PAWN IS BLACK THEN THE MOVES IN THE DOWN DIRECTION ARE GENERATED
        bool down = (column - 1) >= 0;
        bool right = (row + 1) < 8;
        bool left = (row - 1) >= 0;
        bool intialPos = (column == 6);

        // IF THE ONE COORDINATE BELOW PAWN IS EMPTY
        if (down && boardState[row][column - 1].empty())
        {
            moveArray.push_back({row, column - 1});
        }

        // IF THE DOWN RIGHT POSITION OF WHITE IS OCCUPIED BY BLACK PAWN THEN ONLY THIS MOVE IS GENERATED
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

        // IF THE DOWN AND LEFT POSITION OF WHITE IS OCCUPIED BY BLACK PAWN THEN ONLY THIS MOVE IS GENERATED
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

        // IF BOTH TWO POSITIONS BELOW THE PAWN IS EMPTY THEN THIS MOVE IS GENERATED
        if (intialPos && boardState[row][column - 1].empty() && boardState[row][column - 2].empty())
        {
            moveArray.push_back({row, column - 2});
        }
    }
}

void Pawn::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
}