#include "../header_files/Rook.h"

Rook::Rook(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Rook::~Rook()
{
}

void Rook::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    std::vector<std::vector<std::string>> boardState = this->readBoardState();

    int i = 1;
    while ((column + i) < 8)
    {
        if (!boardState[row][column + i].empty())
        {
            std::stringstream ss(boardState[row][column + i]);

            std::string piece;
            int color;

            std::getline(ss, piece, ',');
            ss >> color;

            if (color == pieceColor)
            {
                break;
            }
            else
            {
                moveArray.push_back({row, column + i});
                break;
            }
        }

        moveArray.push_back({row, column + i});
        i++;
    }

    int j = 1;
    while ((column - j) >= 0)
    {
        if (!boardState[row][column - j].empty())
        {
            std::stringstream ss(boardState[row][column - j]);

            std::string piece;
            int color;

            std::getline(ss, piece, ',');
            ss >> color;

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

    int k = 1;
    while ((row + k) < 8)
    {
        if (!boardState[row + k][column].empty())
        {
            std::stringstream ss(boardState[row + k][column]);

            std::string piece;
            int color;

            std::getline(ss, piece, ',');
            ss >> color;

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

    int l = 1;
    while ((row - l) >= 0)
    {
        if (!boardState[row - l][column].empty())
        {
            std::stringstream ss(boardState[row - l][column]);

            std::string piece;
            int color;

            std::getline(ss, piece, ',');
            ss >> color;

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