#include "../header_files/Queen.h"

Queen::Queen(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Queen::~Queen()
{
}

void Queen::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray){
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

    int m = 1;
    while (((row + m) < 8) && ((column + m) < 8))
    {
        if (!boardState[row + m][column + m].empty())
        {
            std::stringstream ss(boardState[row + m][column + m]);

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
                moveArray.push_back({row + m, column + m});
                break;
            }
        }

        moveArray.push_back({row + m, column + m});
        m++;
    }

    int n = 1;
    while (((row + n) < 8) && ((column - n) >= 0))
    {
        if (!boardState[row + n][column - n].empty())
        {
            std::stringstream ss(boardState[row + n][column - n]);

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
                moveArray.push_back({row + n, column - n});
                break;
            }
        }

        moveArray.push_back({row + n, column - n});
        n++;
    }

    int o = 1;
    while (((row - o) >= 0) && ((column + o) < 8))
    {
        if (!boardState[row - o][column + o].empty())
        {
            std::stringstream ss(boardState[row - o][column + o]);

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
                moveArray.push_back({row - o, column + o});
                break;
            }
        }

        moveArray.push_back({row - o, column + o});
        o++;
    }

    int p = 1;
    while (((row - p) >= 0) && ((column - p) >= 0))
    {
        if (!boardState[row - p][column - p].empty())
        {
            std::stringstream ss(boardState[row - p][column - p]);

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
                moveArray.push_back({row - p, column - p});
                break;
            }
        }

        moveArray.push_back({row - p, column - p});
        p++;
    }
}

void Queen::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
}