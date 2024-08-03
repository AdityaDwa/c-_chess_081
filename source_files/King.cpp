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

    // MOVES ARE PUSHED TO MOVE ARRAY AFTER CHECKING IF THERE IS POSSIBLE SPACE IN THE BOARD
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
    // EACH MOVE GENERATED IS ITERATED TO CHECK IF IT IS VALID OR NOT
    std::vector<std::vector<int>> validMoves;
    for (const auto &move : moveArray)
    {
        int newRow = move[0];
        int newColumn = move[1];

        // CHECKING IF THE CURRENT BOARD POSITION IS EMPTY OR NOT
        if (!boardState[newRow][newColumn].empty())
        {
            std::stringstream boardInfoString(boardState[newRow][newColumn]);

            std::string piece;
            int color;

            std::getline(boardInfoString, piece, ',');
            boardInfoString >> color;

            // CHECKING IF THE PIECE ON THE POSITION IS OF SAME COLOR AS KING OR NOT
            if (color == pieceColor)
            {
                continue;
            }
        }
        validMoves.push_back(move);
    }
    moveArray = validMoves;

    this->isCastlingPossible();

    // CHECKING IF KING AND RIGHT ROOK MOVE FLAG IS ON OR NOT
    if (this->kingFlag && this->rightRookFlag)
    {
        // CHECKING IF THERE IS SPACE FOR KING TO DO CASTLING OR NOT
        if ((row + 2) < 8)
        {
            // CHECKING IF THERE IS ANY PIECE IN BETWEEN KING AND THE ROOK
            if (boardState[row + 1][column].empty() && boardState[row + 2][column].empty())
            {
                moveArray.push_back({row + 2, column});
            }
        }
    }

    // CHECKING IF KING AND LEFT ROOK MOVE FLAG IS ON OR NOT
    if (this->kingFlag && this->leftRookFlag)
    {
        // CHECKING IF THERE IS SPACE FOR KING TO DO CASTLING OR NOT
        if ((row - 3) >= 0)
        {
            // CHECKING IF THERE IS ANY PIECE IN BETWEEN KING AND THE ROOK
            if (boardState[row - 1][column].empty() && boardState[row - 2][column].empty() && boardState[row - 3][column].empty())
            {
                moveArray.push_back({row - 2, column});
            }
        }
    }
}

void King::isCastlingPossible()
{
    // CURRENT PLAYER TURN IS RETRIEVED
    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    if (playerTurn)
    {
        // IF WHITE PLAYER'S TURN THEN WHITE KING MOVE FLAG IS CHECKED
        bool whiteKingMoved;
        std::ifstream whiteKingCastleFile("../templates/white_king_castle.txt");
        whiteKingCastleFile >> whiteKingMoved;
        whiteKingCastleFile.close();
        this->kingFlag = !whiteKingMoved;

        // IF KING HAS NOT MOVED THEN ROOKS' MOVE FLAGS ARE CHECKED
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
        // IF BLACK PLAYER'S TURN THEN BLACK KING MOVE FLAG IS CHECKED
        bool blackKingMoved;
        std::ifstream blackKingCastleFile("../templates/black_king_castle.txt");
        blackKingCastleFile >> blackKingMoved;
        blackKingCastleFile.close();
        this->kingFlag = !blackKingMoved;

        // IF KING HAS NOT MOVED THEN ROOKS' MOVE FLAGS ARE CHECKED
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