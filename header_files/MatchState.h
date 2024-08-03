#pragma once

#include "State.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Button.h"

class MatchState : public State
{
private:
    Piece* boardPieces[8][8];
    Piece* virtualBoardPieces[8][8];
    Button* btns[30];

    sf::Font labelFont;
    sf::Text xtileLabel;
    sf::Text ytileLabel;

    sf::Font playerFont;
    sf::Text playerName;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape icon;

    bool playerTurn, whiteKingCheckFlag, blackKingCheckFlag;
    bool checkmate = false;

public:
    // CONSTRUCTOR AND DESTRUCTOR
    MatchState(sf::RenderWindow *window);
    virtual ~MatchState();

    // STATE UPDATING AND RENDERING METHODS
    void update(const float& deltaTime);
    void render(sf::RenderTarget *target = nullptr);
    void endState();

    // COMPONENTS RENDERING METHODS
    void renderBoard(sf::RenderTarget *target);
    void renderPieces(sf::RenderTarget *target);
    void renderPawnPromoDialog(sf::RenderTarget *target);
    void renderCheckDialog(sf::RenderTarget *target);
    void renderResignDialog(sf::RenderTarget *target);
    void renderResignConfirmDialog(sf::RenderTarget *target);
    void renderStalemateDialog(sf::RenderTarget *target);

    // SPECIAL MOVES CHECKING METHODS
    void checkForPawnPromotion();
    void castle(int initialRow, int initialColumn, int finalRow, int finalColumn);
    void isCheck(sf::RenderTarget *target);
    void isCheckmate(bool shade, std::vector<std::vector<int>>& oppMoveArray);
};
