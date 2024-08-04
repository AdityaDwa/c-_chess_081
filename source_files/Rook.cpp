#include "../header_files/Rook.h"

Rook::Rook(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Rook::~Rook()
{
}

void Rook::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    // INVOKING FUNCTION TO READ THE CURRENT STATE OF THE BOARD
    std::vector<std::vector<std::string>> boardState = this->readBoardState();

    // ADDING POSSIBLE MOVES IN ARRAY IN UP DIRECTION
    int i = 1;
    while ((column + i) < 8)
    {
        // CHECKS IF THE CURRENT ITERATION OF THE COORDINATE IN THE BOARD IS EMPTY OR NOT
        if (!boardState[row][column + i].empty())
        {
            std::stringstream boardInfoString(boardState[row][column + i]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;

            if (color == pieceColor)
            {
                // IF THE PIECE IN THE POSITION IS OF SAME COLOR AS THE MOVING PIECE THEN THE WHOLE LOOP IS SKIPPED
                break;
            }
            else
            {
                // IF THE PIECE IS OF DIFFERENT COLOR THEN THIS MOVE IS ADDED AND THE WHOLE LOOP IS SKIPPED
                moveArray.push_back({row, column + i});
                break;
            }
        }

        moveArray.push_back({row, column + i});
        i++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN DOWN DIRECTION
    int j = 1;
    while ((column - j) >= 0)
    {
        if (!boardState[row][column - j].empty())
        {
            std::stringstream boardInfoString(boardState[row][column - j]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;

            if (color == pieceColor)
            {
                break;
            }
            else
            {
                moveArray.push_back({row, column - j});
                break;
            }
        }

        moveArray.push_back({row, column - j});
        j++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN RIGHT DIRECTION
    int k = 1;
    while ((row + k) < 8)
    {
        if (!boardState[row + k][column].empty())
        {
            std::stringstream boardInfoString(boardState[row + k][column]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;

            if (color == pieceColor)
            {
                break;
            }
            else
            {
                moveArray.push_back({row + k, column});
                break;
            }
        }

        moveArray.push_back({row + k, column});
        k++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN LEFT DIRECTION
    int l = 1;
    while ((row - l) >= 0)
    {
        if (!boardState[row - l][column].empty())
        {
            std::stringstream boardInfoString(boardState[row - l][column]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;

            if (color == pieceColor)
            {
                break;
            }
            else
            {
                moveArray.push_back({row - l, column});
                break;
            }
        }

        moveArray.push_back({row - l, column});
        l++;
    }
}

void Rook::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
}