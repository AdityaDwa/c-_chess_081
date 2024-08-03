#include "../header_files/Bishop.h"

Bishop::Bishop(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Bishop::~Bishop()
{
}

void Bishop::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    // INVOKING FUNCTION TO READ THE CURRENT STATE OF THE BOARD
    std::vector<std::vector<std::string>> boardState = this->readBoardState();

    // ADDING POSSIBLE MOVES IN ARRAY IN RIGHT TOP DIAGONAL
    int i = 1;
    while (((row + i) < 8) && ((column + i) < 8))
    {
        // CHECKS IF THE CURRENT ITERATION OF THE COORDINATE IN THE BOARD IS EMPTY OR NOT
        if (!boardState[row + i][column + i].empty())
        {
            std::stringstream boardInfoString(boardState[row + i][column + i]);

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
                moveArray.push_back({row + i, column + i});
                break;
            }
        }

        moveArray.push_back({row + i, column + i});
        i++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN RIGHT BOTTOM DIAGONAL
    int j = 1;
    while (((row + j) < 8) && ((column - j) >= 0))
    {
        if (!boardState[row + j][column - j].empty())
        {
            std::stringstream boardInfoString(boardState[row + j][column - j]);

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
                moveArray.push_back({row + j, column - j});
                break;
            }
        }

        moveArray.push_back({row + j, column - j});
        j++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN LEFT TOP DIAGONAL
    int k = 1;
    while (((row - k) >= 0) && ((column + k) < 8))
    {
        if (!boardState[row - k][column + k].empty())
        {
            std::stringstream boardInfoString(boardState[row - k][column + k]);

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
                moveArray.push_back({row - k, column + k});
                break;
            }
        }

        moveArray.push_back({row - k, column + k});
        k++;
    }

    // ADDING POSSIBLE MOVES IN ARRAY IN LEFT BOTTOM DIAGONAL
    int l = 1;
    while (((row - l) >= 0) && ((column - l) >= 0))
    {
        if (!boardState[row - l][column - l].empty())
        {
            std::stringstream boardInfoString(boardState[row - l][column - l]);

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
                moveArray.push_back({row - l, column - l});
                break;
            }
        }

        moveArray.push_back({row - l, column - l});
        l++;
    }
}

void Bishop::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
}