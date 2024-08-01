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

    this->isCastlingPossible();

    if (this->kingFlag && this->rightRookFlag)
    {
        if ((row + 2) < 8)
        {
            if (boardState[row + 1][column].empty() && boardState[row + 2][column].empty())
            {
                moveArray.push_back({row + 2, column});
            }
        }
    }

    if (this->kingFlag && this->leftRookFlag)
    {
        if ((row - 3) >= 0)
        {
            if (boardState[row - 1][column].empty() && boardState[row - 2][column].empty() && boardState[row - 3][column].empty())
            {
                moveArray.push_back({row - 2, column});
            }
        }
    }
}

void King::isCastlingPossible()
{
    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    if (playerTurn)
    {
        bool whiteKingMoved;
        std::ifstream whiteKingCastleFile("../templates/white_king_castle.txt");
        whiteKingCastleFile >> whiteKingMoved;
        whiteKingCastleFile.close();
        this->kingFlag = !whiteKingMoved;

        if (!whiteKingMoved)
        {
            bool whiteRightRookMoved;
            std::ifstream whiteRightRookCastleFile("../templates/white_right_rook_castle.txt");
            whiteRightRookCastleFile >> whiteRightRookMoved;
            whiteRightRookCastleFile.close();
            this->rightRookFlag = !whiteRightRookMoved;

            bool whiteLeftRookMoved;
            std::ifstream whiteLeftRookCastleFile("../templates/white_left_rook_castle.txt");
            whiteLeftRookCastleFile >> whiteLeftRookMoved;
            whiteLeftRookCastleFile.close();
            this->leftRookFlag = !whiteLeftRookMoved;
        }
    }
    else
    {
        bool blackKingMoved;
        std::ifstream blackKingCastleFile("../templates/black_king_castle.txt");
        blackKingCastleFile >> blackKingMoved;
        blackKingCastleFile.close();
        this->kingFlag = !blackKingMoved;

        if (!blackKingMoved)
        {
            bool blackRightRookMoved;
            std::ifstream blackRightRookCastleFile("../templates/black_right_rook_castle.txt");
            blackRightRookCastleFile >> blackRightRookMoved;
            blackRightRookCastleFile.close();
            this->rightRookFlag = !blackRightRookMoved;

            bool blackLeftRookMoved;
            std::ifstream blackLeftRookCastleFile("../templates/black_left_rook_castle.txt");
            blackLeftRookCastleFile >> blackLeftRookMoved;
            blackLeftRookCastleFile.close();
            this->leftRookFlag = !blackLeftRookMoved;
        }
    }
}