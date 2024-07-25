#include "../header_files/King.h"

King::King(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

King::~King()
{
}

void King::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    bool up = (column + 1) < 8;
    bool down = (column - 1) >= 0;
    bool right = (row + 1) < 8;
    bool left = (row - 1) >= 0;

    if (up)
    {
        moveArray.push_back({row, column + 1});
    }

    if (up && right)
    {
        moveArray.push_back({row + 1, column + 1});
    }

    if (up && left)
    {
        moveArray.push_back({row - 1, column + 1});
    }

    if (down)
    {
        moveArray.push_back({row, column - 1});
    }

    if (down && right)
    {
        moveArray.push_back({row + 1, column - 1});
    }

    if (down && left)
    {
        moveArray.push_back({row - 1, column - 1});
    }

    if (right)
    {
        moveArray.push_back({row + 1, column});
    }
    
    if (left)
    {
        moveArray.push_back({row - 1, column});
    }

    std::vector<std::vector<std::string>> boardState = this->readBoardState();
    this->filterValidMoves(row, column, pieceColor, moveArray, boardState);
}

void King::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
    std::vector<std::vector<int>> validMoves;
    for (const auto &move : moveArray)
    {
        int newRow = move[0];
        int newColumn = move[1];
        if (!boardState[newRow][newColumn].empty())
        {
            std::stringstream ss(boardState[newRow][newColumn]);

            std::string piece;
            int color;

            std::getline(ss, piece, ',');
            ss >> color;
            
            if (color == pieceColor)
            {
                continue;
            }
        }
        validMoves.push_back(move);
    }
    moveArray = validMoves;
}