#include "../header_files/Knight.h"

Knight::Knight(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, imagePath, target)
{
}

Knight::~Knight()
{
}

void Knight::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray)
{
    bool up = (column + 2) < 8;
    bool down = (column - 2) >= 0;
    bool right = (row + 2) < 8;
    bool left = (row - 2) >= 0;

    if (((row + 1) < 8) && up)
    {
        moveArray.push_back({row + 1, column + 2});
    }

    if (((row - 1) >= 0) && up)
    {
        moveArray.push_back({row - 1, column + 2});
    }

    if (right && ((column + 1) < 8))
    {
        moveArray.push_back({row + 2, column + 1});
    }

    if (right && ((column - 1) >= 0))
    {
        moveArray.push_back({row + 2, column - 1});
    }

    if (((row + 1) < 8) && down)
    {
        moveArray.push_back({row + 1, column - 2});
    }

    if (((row - 1) >= 0) && down)
    {
        moveArray.push_back({row - 1, column - 2});
    }

    if (left && ((column + 1) < 8))
    {
        moveArray.push_back({row - 2, column + 1});
    }

    if (left && ((column - 1) >= 0))
    {
        moveArray.push_back({row - 2, column - 1});
    }

    std::vector<std::vector<std::string>> boardState = this->readBoardState();
    this->filterValidMoves(row, column, pieceColor, moveArray, boardState);
}

void Knight::filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>> &moveArray, const std::vector<std::vector<std::string>> &boardState)
{
    std::vector<std::vector<int>> validMoves;
    for (const auto &move : moveArray)
    {
        int newRow = move[0];
        int newColumn = move[1];
        if (!boardState[newRow][newColumn].empty())
        {
            std::stringstream boardInfoString(boardState[newRow][newColumn]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;
            
            if (color == pieceColor)
            {
                continue;
            }
        }
        validMoves.push_back(move);
    }
    moveArray = validMoves;
}