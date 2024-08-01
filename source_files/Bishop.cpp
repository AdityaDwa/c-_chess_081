#include "../header_files/Bishop.h"

Bishop::Bishop(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Bishop::~Bishop()
{
}

void Bishop::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    std::vector<std::vector<std::string>> boardState = this->readBoardState();

    int i = 1;
    while (((row + i) < 8) && ((column + i) < 8))
    {
        if (!boardState[row + i][column + i].empty())
        {
            std::stringstream boardInfoString(boardState[row + i][column + i]);

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
                moveArray.push_back({row + i, column + i});
                break;
            }
        }

        moveArray.push_back({row + i, column + i});
        i++;
    }

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