#include "../header_files/MatchState.h"

MatchState::MatchState(sf::RenderWindow *window) : State(window)
{
    // STATE BACKGROUND AND SIZE ARE INITIALIZED
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(54, 58, 55));

    // BOARD PIECES AND VIRTUAL BOARD PIECES ARRAYS ARE NULL POINTED
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->boardPieces[i][j] = nullptr;
            this->virtualBoardPieces[i][j] = nullptr;
        }
    }

    // MOVE BUTTONS ARRAY IS NULL POINTED
    for (int i = 0; i < 30; i++)
    {
        this->btns[i] = nullptr;
    }
}

MatchState::~MatchState()
{
    // EACH PIECE OBJECT IN BOARD PIECES AND VIRTUAL BOARD PIECES IS DELETED AND NULL POINTED
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; j++)
        {
            delete this->boardPieces[i][j];
            this->boardPieces[i][j] = nullptr;

            delete this->virtualBoardPieces[i][j];
            this->virtualBoardPieces[i][j] = nullptr;
        }
    }

    // EACH MOVE BUTTON IN BTNS ARRAY IS DELETED AND NULL POINTED
    for (int i = 0; i < 30; i++)
    {
        delete this->btns[i];
        this->btns[i] = nullptr;
    }
}

void MatchState::update(const float &deltaTime)
{
    // METHOD TO UPDATE MOUSE POSITIONS IN THE WINDOW IS INVOKED
    this->updateMousePositions();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->boardPieces[i][j] != nullptr)
            {
                // UPDATE METHOD OF EACH PIECE OBJECT IN BOARD PIECES ARRAY IS INVOKED IF THE CURRENT ARRAY ELEMENT IS NOT NULLPTR
                this->boardPieces[i][j]->update();
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        if (this->btns[i] != nullptr)
        {
            // UPDATE METHOD OF EACH BUTTON OBJECT IN BTNS ARRAY IS INVOKED IF THE CURRENT ARRAY ELEMENT IS NOT NULLPTR
            this->btns[i]->update();
        }
    }
}

void MatchState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

    // BACKGROUND AND GAME COMPONENTS ARE RENDERED
    target->draw(this->stateBackground);
    this->renderBoard(target);
    this->renderPieces(target);

    // DIALOG BOX TO INDICATE VARIOUS GAME PROGRESS ARE RENDERED
    this->renderPawnPromoDialog(target);
    this->renderCheckDialog(target);
    this->renderResignDialog(target);
    this->renderResignConfirmDialog(target);
    this->renderStalemateDialog(target);
}

void MatchState::endState()
{
    // DESTRUCTOR OF MATCHSTATE OBJECT IS INVOKED
    this->~MatchState();
}

void MatchState::renderBoard(sf::RenderTarget *target)
{
    // SQUARES ON THE CHESS BOARD ARE RENDERED
    int numSquares = 8;
    float boardSquareSize = 120.f;
    sf::Color boardColors[2] = {sf::Color(235, 236, 220), sf::Color(139, 85, 19)};
    float boardDimension = numSquares * boardSquareSize;

    float startXPosition = (target->getSize().x - boardDimension) / 2;
    float startYPosition = (target->getSize().y - boardDimension) / 2;

    for (int i = 0; i < numSquares; i++)
    {
        for (int j = 0; j < numSquares; j++)
        {
            sf::RectangleShape square(sf::Vector2f(boardSquareSize, boardSquareSize));
            square.setPosition(startXPosition + (i * boardSquareSize), startYPosition + (j * boardSquareSize));

            // SQUARE COLOR IS RENDERED ALTERNATIVELY
            square.setFillColor(boardColors[(i + j) % 2]);

            target->draw(square);
        }
    }

    this->labelFont.loadFromFile("../fonts/inter_regular.ttf");

    this->xtileLabel.setFont(this->labelFont);
    this->ytileLabel.setFont(this->labelFont);

    // COLUMN AND ROW LABELS ARE RENDERED IN ORDER ACCORDING TO THE PLAYER TURN
    char colLabels[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char rowLabels[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    // CURRENT PLAYER TURN IS RETRIEVED
    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    for (int i = 0; i < 8; i++)
    {
        // CHANGE ORIENTATION OF LABELS ACCORDING TO PLAYER TURN
        int num = playerTurn ? i : std::abs(i - 7);

        this->xtileLabel.setString(colLabels[num]);
        this->ytileLabel.setString(rowLabels[num]);

        this->xtileLabel.setCharacterSize(24);
        this->ytileLabel.setCharacterSize(24);

        this->xtileLabel.setFillColor(sf::Color(196, 205, 194));
        this->ytileLabel.setFillColor(sf::Color(196, 205, 194));

        float colXCoord = startXPosition + (i * 120.f) + 60.f;
        float colYCoord = startYPosition + (8 * 120.f);

        float rowXCoord = startXPosition - 30.f;
        float rowYCoord = startYPosition + (i * 120.f) + 50.f;

        this->xtileLabel.setPosition(colXCoord, colYCoord);
        this->ytileLabel.setPosition(rowXCoord, rowYCoord);

        target->draw(this->xtileLabel);
        target->draw(this->ytileLabel);
    }

    // ACTIVE PLAYER INDICATOR RENDERED ACCORDING TO PLAYER TURN
    float whitePlayerIconPosition = playerTurn ? 730.f : 130.f;
    float blackPlayerIconPosition = playerTurn ? 130.f : 730.f;

    this->icon.setPosition(sf::Vector2f(100.f, whitePlayerIconPosition));
    this->icon.setSize(sf::Vector2f(70.f, 70.f));
    this->icon.setFillColor(sf::Color(169, 169, 169));

    this->texture.loadFromFile("../src/white_player_icon.png");
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 70.f / this->sprite.getLocalBounds().width;
    float scaleY = 70.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(100.f, whitePlayerIconPosition);

    target->draw(this->icon);
    target->draw(this->sprite);

    this->texture.loadFromFile("../src/black_player_icon.png");
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    this->icon.setPosition(sf::Vector2f(100.f, blackPlayerIconPosition));
    this->sprite.setPosition(100.f, blackPlayerIconPosition);

    target->draw(this->icon);
    target->draw(this->sprite);

    this->playerFont.loadFromFile("../fonts/inter_bold.ttf");
    this->playerName.setFont(this->playerFont);

    this->playerName.setString("White");
    this->playerName.setCharacterSize(30);
    this->playerName.setFillColor(sf::Color::White);

    float whitePlayerNamePosition = playerTurn ? 765.f : 165.f;
    float blackPlayerNamePosition = playerTurn ? 165.f : 765.f;

    this->playerName.setPosition(180.f, whitePlayerNamePosition);
    target->draw(this->playerName);

    this->playerName.setString("Black");
    this->playerName.setFillColor(sf::Color::Black);
    this->playerName.setPosition(180.f, blackPlayerNamePosition);
    target->draw(this->playerName);

    // RECTANGLE SHAPE OBJECT TO RENDER RESIGN BUTTON
    sf::RectangleShape exitBtn;

    sf::Font exitBtnFont;
    sf::Text exitBtnText;

    float btnXPosition = target->getSize().x - 205.f;
    float btnYPosition = 60.f;

    exitBtn.setPosition(sf::Vector2f(btnXPosition, btnYPosition));
    exitBtn.setSize(sf::Vector2f(185.f, 75.f));
    exitBtn.setFillColor(sf::Color(169, 169, 169));

    target->draw(exitBtn);

    exitBtnFont.loadFromFile("../fonts/inter_bold.ttf");
    exitBtnText.setFont(exitBtnFont);

    exitBtnText.setString("Resign");
    exitBtnText.setCharacterSize(30);
    exitBtnText.setFillColor(sf::Color::White);

    exitBtnText.setPosition(sf::Vector2f(btnXPosition + 45.f, btnYPosition + 20.f));
    target->draw(exitBtnText);

    bool clicked;
    char del1, del2;
    float mouseX, mouseY;

    std::ifstream mousePositionFile("../templates/mouse_position.txt");
    mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
    mousePositionFile.close();

    // CURRENT MOUSE POSITION AND CLICKED FLAG IS RETRIEVED
    sf::Vector2f clickPosition(mouseX, mouseY);

    if (clicked)
    {
        if (exitBtn.getGlobalBounds().contains(clickPosition))
        {
            // IF THE BUTTON IS CLICKED AND THE BUTTON CONTAINS THE MOUSE POSITION

            // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
            std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
            mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
            mousePositionFile_1.close();

            // RESIGN FLAG IS TURNED ON
            std::ofstream resignPopupFile("../templates/resign_popup.txt");
            resignPopupFile << 1;
            resignPopupFile.close();
        }
    }
}

void MatchState::renderPieces(sf::RenderTarget *target)
{
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    std::ifstream activeTileInfoFile("../templates/active_tile_info.txt");
    std::string activeLineInfo;

    // CURRENT PIECE POSITIONS AND ACTIVE TILE INFO ARE RETRIEVED
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::getline(currentPositionFile, infoLine);
            std::istringstream infoString(infoLine);

            std::getline(activeTileInfoFile, activeLineInfo);
            std::istringstream activeInfoString(activeLineInfo);

            int row, col;
            std::string pieceType;
            bool pieceColor;
            std::string pieceIdentifier;

            int num1, num2, num3;
            char delimiter1, delimiter2;

            infoString >> row;
            infoString.ignore(1, ',');

            infoString >> col;
            infoString.ignore(1, ',');

            std::getline(infoString, pieceType, ',');
            if (infoString.fail())
                continue;

            infoString >> pieceColor;
            if (infoString.fail())
                continue;
            infoString.ignore(1, ',');

            std::getline(infoString, pieceIdentifier);
            if (infoString.fail())
                continue;

            pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
            pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

            activeInfoString >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3;

            sf::Color btnColor = num3 ? sf::Color(169, 169, 169) : sf::Color(0, 0, 0, 0);
            if (num3)
            {
                // POSSIBLE MOVE OF PIECE IN COORDINATE OF TILE WHICH IS ACTIVE IS RETRIEVED
                std::vector<std::vector<int>> moveArray = {};
                this->boardPieces[row][col]->possibleMoves(row, col, pieceColor, moveArray);

                // MOVE BUTTONS TO INDICATE POSSIBLE MOVE IN UI ARE RENDERED
                int i = 0;
                for (const auto &pair : moveArray)
                {
                    delete this->btns[i];
                    int x = pair[0];
                    int y = pair[1];
                    this->btns[i] = new Button(x, y, row, col, pieceColor, target);
                    this->btns[i]->render(target);
                    i++;
                }
            }

            std::string imageColor = pieceColor ? "white" : "black";

            // PIECE OBJECT OF PREVIOUS RENDER ITERATION IS DELETED TO FREE UP MEMORY
            delete this->boardPieces[row][col];

            // PIECE IS RENDERED IN THE SPECIFIC COORDINATE ACCORDING TO ITS TYPE
            if (pieceType == "pawn")
            {
                std::string imagePath = "../src/" + imageColor + "_pawn.png";
                this->boardPieces[row][col] = new Pawn(pieceColor, row, col, btnColor, imagePath, target);
            }
            else if (pieceType == "bishop")
            {
                std::string imagePath = "../src/" + imageColor + "_bishop.png";
                this->boardPieces[row][col] = new Bishop(pieceColor, row, col, btnColor, imagePath, target);
            }
            else if (pieceType == "knight")
            {
                std::string imagePath = "../src/" + imageColor + "_knight.png";
                this->boardPieces[row][col] = new Knight(pieceColor, row, col, btnColor, imagePath, target);
            }
            else if (pieceType == "rook")
            {
                std::string imagePath = "../src/" + imageColor + "_rook.png";
                this->boardPieces[row][col] = new Rook(pieceColor, row, col, btnColor, imagePath, target);
            }
            else if (pieceType == "queen")
            {
                std::string imagePath = "../src/" + imageColor + "_queen.png";
                this->boardPieces[row][col] = new Queen(pieceColor, row, col, btnColor, imagePath, target);
            }
            else if (pieceType == "king")
            {
                std::string imagePath = "../src/" + imageColor + "_king.png";
                this->boardPieces[row][col] = new King(pieceColor, row, col, btnColor, imagePath, target);
            }

            this->boardPieces[row][col]->render(target);
        }
    }

    currentPositionFile.close();
    activeTileInfoFile.close();

    std::ifstream isButtonClickedFile("../templates/is_button_clicked.txt");
    std::string coordInfoLine;

    // FUNCTIONS TO RUN AFTER THE MOVE BUTTON IS CLICKED ARE CALLED
    while (std::getline(isButtonClickedFile, coordInfoLine))
    {
        std::istringstream coordInfoString(coordInfoLine);

        int initialRow, initialColumn, finalRow, finalColumn, moveFlag;
        char delimiter1, delimiter2, delimiter3, delimiter4;

        coordInfoString >> initialRow >> delimiter1 >> initialColumn >> delimiter2 >> finalRow >> delimiter3 >> finalColumn >> delimiter4 >> moveFlag;
        if (moveFlag)
        {
            // PIECE IS MOVED IF MOVEFLAG IS ON

            // IF THE MOVED PIECES WERE KING OR ROOKS THEN THEIR MOVE FLAG IS TURNED ON TO PREVENT CASTLING FROM NOW ON
            if (this->boardPieces[initialRow][initialColumn] != nullptr)
            {
                std::ifstream currentPositionFile_5("../templates/current_piece_position.txt");
                std::string infoLine_5;

                while (std::getline(currentPositionFile_5, infoLine_5))
                {
                    std::istringstream infoString_5(infoLine_5);
                    int _x, _y;
                    std::string _pisType;
                    bool _pisColor;
                    std::string _pisIdentifier;

                    infoString_5 >> _x;
                    infoString_5.ignore(1, ',');

                    infoString_5 >> _y;
                    infoString_5.ignore(1, ',');

                    std::getline(infoString_5, _pisType, ',');
                    if (infoString_5.fail())
                        continue;

                    infoString_5 >> _pisColor;
                    if (infoString_5.fail())
                        continue;
                    infoString_5.ignore(1, ',');

                    std::getline(infoString_5, _pisIdentifier);
                    if (infoString_5.fail())
                        continue;

                    if (_x == initialRow && _y == initialColumn)
                    {
                        if (_pisColor)
                        {
                            bool whiteKingMoved;
                            std::ifstream whiteKingCastleFile("../templates/white_king_castle.txt");
                            whiteKingCastleFile >> whiteKingMoved;
                            whiteKingCastleFile.close();

                            bool whiteRightRookMoved;
                            std::ifstream whiteRightRookCastleFile("../templates/white_right_rook_castle.txt");
                            whiteRightRookCastleFile >> whiteRightRookMoved;
                            whiteRightRookCastleFile.close();

                            bool whiteLeftRookMoved;
                            std::ifstream whiteLeftRookCastleFile("../templates/white_left_rook_castle.txt");
                            whiteLeftRookCastleFile >> whiteLeftRookMoved;
                            whiteLeftRookCastleFile.close();

                            if (_pisType == "king" && !whiteKingMoved)
                            {
                                std::ofstream whiteKingCastleFile_1("../templates/white_king_castle.txt");
                                whiteKingCastleFile_1 << 1;
                                whiteKingCastleFile_1.close();
                            }
                            else if (_pisType == "rook" && _pisIdentifier == "rook2" && !whiteRightRookMoved)
                            {
                                std::ofstream whiteRightRookCastleFile_1("../templates/white_right_rook_castle.txt");
                                whiteRightRookCastleFile_1 << 1;
                                whiteRightRookCastleFile_1.close();
                            }
                            else if (_pisType == "rook" && _pisIdentifier == "rook1" && !whiteLeftRookMoved)
                            {
                                std::ofstream whiteLeftRookCastleFile_1("../templates/white_left_rook_castle.txt");
                                whiteLeftRookCastleFile_1 << 1;
                                whiteLeftRookCastleFile_1.close();
                            }
                        }
                        else
                        {
                            bool blackKingMoved;
                            std::ifstream blackKingCastleFile("../templates/black_king_castle.txt");
                            blackKingCastleFile >> blackKingMoved;
                            blackKingCastleFile.close();

                            bool blackRightRookMoved;
                            std::ifstream blackRightRookCastleFile("../templates/black_right_rook_castle.txt");
                            blackRightRookCastleFile >> blackRightRookMoved;
                            blackRightRookCastleFile.close();

                            bool blackLeftRookMoved;
                            std::ifstream blackLeftRookCastleFile("../templates/black_left_rook_castle.txt");
                            blackLeftRookCastleFile >> blackLeftRookMoved;
                            blackLeftRookCastleFile.close();

                            if (_pisType == "king" && !blackKingMoved)
                            {
                                std::ofstream blackKingCastleFile_1("../templates/black_king_castle.txt");
                                blackKingCastleFile_1 << 1;
                                blackKingCastleFile_1.close();
                            }
                            else if (_pisType == "rook" && _pisIdentifier == "rook2" && !blackRightRookMoved)
                            {
                                std::ofstream blackRightRookCastleFile_1("../templates/black_right_rook_castle.txt");
                                blackRightRookCastleFile_1 << 1;
                                blackRightRookCastleFile_1.close();
                            }
                            else if (_pisType == "rook" && _pisIdentifier == "rook1" && !blackLeftRookMoved)
                            {
                                std::ofstream blackLeftRookCastleFile_1("../templates/black_left_rook_castle.txt");
                                blackLeftRookCastleFile_1 << 1;
                                blackLeftRookCastleFile_1.close();
                            }
                        }
                    }
                }
                currentPositionFile_5.close();

                // CASTLING IS DONE IF THE KING OF ACTIVE PLAYER IS NOT IN CHECK
                if ((this->playerTurn && !this->whiteKingCheckFlag) || (!this->playerTurn && !this->blackKingCheckFlag))
                {
                    this->castle(initialRow, initialColumn, finalRow, finalColumn);
                }

                // THE PIECE IS MOVED USING MOVEPIECE FUNCTION
                this->boardPieces[initialRow][initialColumn]->movePiece(initialRow, initialColumn, finalRow, finalColumn);

                // FUNCTIONS FOR PAWN PROMOTION AND CHECK ARE INVOKED
                this->checkForPawnPromotion();
                this->isCheck(target);

                // PIECE IN THE INITIAL POSITION IS DELETED TO FREE UP MEMORY
                delete this->boardPieces[initialRow][initialColumn];
                this->boardPieces[initialRow][initialColumn] = nullptr;

                // ALL THE MOVE BUTTONS ARE DELETED
                for (int i = 0; i < 30; i++)
                {
                    delete this->btns[i];
                    this->btns[i] = nullptr;
                }

                // PLAYER TURN IS INVERSED FOR TURN MANAGEMENT
                bool turnNum, inverseTurn;
                std::ifstream playerTurnFile_2("../templates/player_turn.txt");
                std::ofstream inversePlayerTurnFile_2("../templates/inverse_player_turn.txt");

                playerTurnFile_2 >> turnNum;
                inverseTurn = !turnNum;
                inversePlayerTurnFile_2 << inverseTurn;

                playerTurnFile_2.close();
                inversePlayerTurnFile_2.close();
                std::filesystem::remove("../templates/player_turn.txt");
                std::filesystem::rename("../templates/inverse_player_turn.txt", "../templates/player_turn.txt");
            }
        }
    }
    isButtonClickedFile.close();

    // IS BUTTON CLICKED FLAG IS TURNED OFF AS THE PIECE WAS SUCCESSFULLY MOVED NOW ITS ANOTHER PLAYER'S TURN
    std::ofstream isButtonClickedFile_1("../templates/is_button_clicked.txt");
    isButtonClickedFile_1.close();
}

void MatchState::renderPawnPromoDialog(sf::RenderTarget *target)
{
    int pawnX, pawnY;
    bool pawnColor, pawnPromoFlag;
    char deli1, deli2, deli3;

    std::ifstream pawnPromotionInfoFile("../templates/pawn_promotion_info.txt");
    pawnPromotionInfoFile >> pawnX >> deli1 >> pawnY >> deli2 >> pawnColor >> deli3 >> pawnPromoFlag;
    pawnPromotionInfoFile.close();

    if (pawnPromoFlag)
    {
        // IF PAWN PROMO FLAG IS ON, THEN THE DIALOG BOX IS RENDERED

        // RECTANGLE OBJECT TO RENDER DIALOG BOX
        sf::RectangleShape pawnPromoDialogBox;

        sf::Font titleFont;
        sf::Text titleText;

        sf::Texture textures[4];
        sf::Sprite sprites[4];

        float startXPosition = (target->getSize().x - 350.f) / 2;
        float startYPosition = (target->getSize().y - 400.f) / 2;

        pawnPromoDialogBox.setPosition(sf::Vector2f(startXPosition, startYPosition));
        pawnPromoDialogBox.setSize(sf::Vector2f(350.f, 400.f));
        pawnPromoDialogBox.setFillColor(sf::Color(54, 58, 55));

        target->draw(pawnPromoDialogBox);

        titleFont.loadFromFile("../fonts/inter_bold.ttf");
        titleText.setFont(this->playerFont);

        titleText.setString("Pawn Promotion");
        titleText.setCharacterSize(35);
        titleText.setFillColor(sf::Color::Black);

        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 20.f));
        target->draw(titleText);

        bool clicked;
        char del1, del2;
        float mouseX, mouseY;

        std::ifstream mousePositionFile("../templates/mouse_position.txt");
        mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
        mousePositionFile.close();

        sf::Vector2f clickPosition(mouseX, mouseY);

        // RENDER APPROPRIATE PIECE COLOR ACCORDING TO THE PAWN COLOR
        // EXAMPLE IF BLACK PAWN IS FOR PROMOTION THEN THE PROMOTED PIECE SHOULD ALSO BE BLACK
        if (pawnColor)
        {
            textures[0].loadFromFile("../src/white_queen.png");
            textures[1].loadFromFile("../src/white_rook.png");
            textures[2].loadFromFile("../src/white_bishop.png");
            textures[3].loadFromFile("../src/white_knight.png");
        }
        else
        {
            textures[0].loadFromFile("../src/black_queen.png");
            textures[1].loadFromFile("../src/black_rook.png");
            textures[2].loadFromFile("../src/black_bishop.png");
            textures[3].loadFromFile("../src/black_knight.png");
        }

        for (int i = 0; i < 4; i++)
        {
            textures[i].setSmooth(true);
            sprites[i].setTexture(textures[i]);

            float scaleX = 100.f / sprites[i].getLocalBounds().width;
            float scaleY = 100.f / sprites[i].getLocalBounds().height;

            sprites[i].setScale(scaleX, scaleY);
            if (i < 2)
            {
                sprites[i].setPosition(startXPosition + 50.f + (i * 150.f), startYPosition + 100.f);
            }
            else
            {
                sprites[i].setPosition(startXPosition + 50.f + ((i - 2) * 150.f), startYPosition + 225.f);
            }

            target->draw(sprites[i]);

            if (clicked)
            {
                if (sprites[i].getGlobalBounds().contains(clickPosition))
                {
                    // PAWN IS PROMOTED TO ACCORDING TO THE BUTTON CLICKED IN THE DIALOG BOX
                    std::string promotedPiece;
                    if (i == 0)
                    {
                        promotedPiece = "queen";
                    }
                    else if (i == 1)
                    {
                        promotedPiece = "rook";
                    }
                    else if (i == 2)
                    {
                        promotedPiece = "bishop";
                    }
                    else if (i == 3)
                    {
                        promotedPiece = "knight";
                    }
                    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
                    std::ofstream tempPromoFile("../templates/promoting_piece.txt");
                    std::string infoLine;

                    // TXT FILE STORING PIECE INFO IS UPDATED TO REPLACE PAWN TO PROMOTOED PIECE
                    while (std::getline(currentPositionFile, infoLine))
                    {
                        std::istringstream infoString(infoLine);

                        int row, col;

                        infoString >> row;
                        infoString.ignore(1, ',');

                        infoString >> col;
                        infoString.ignore(1, ',');

                        if (row == pawnX && col == pawnY)
                        {
                            tempPromoFile << row << ',' << col << ',' << promotedPiece << ',' << pawnColor << ',' << "pawn_promoted" << std::endl;
                        }
                        else
                        {
                            tempPromoFile << infoLine << std::endl;
                        }
                    }
                    currentPositionFile.close();
                    tempPromoFile.close();
                    std::filesystem::remove("../templates/current_piece_position.txt");
                    std::filesystem::rename("../templates/promoting_piece.txt", "../templates/current_piece_position.txt");

                    // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
                    std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                    mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                    mousePositionFile_1.close();

                    // PAWN PROMO FLAG IS TURNED OFF AS THE PAWN WAS PROMOTED SUCCESSFULLY
                    std::ofstream pawnPromotionInfoFile_1("../templates/pawn_promotion_info.txt");
                    pawnPromotionInfoFile_1 << 0 << ',' << 0 << ',' << 0 << ',' << 0;
                    pawnPromotionInfoFile_1.close();
                }
            }
        }
    }
}

void MatchState::renderCheckDialog(sf::RenderTarget *target)
{
    bool pieceColor, checkFlag;
    char delimeter;

    std::ifstream checkFlagFile("../templates/check_flag.txt");
    checkFlagFile >> pieceColor >> delimeter >> checkFlag;
    checkFlagFile.close();

    if (checkFlag)
    {
        // IF CHECK FLAG IS ON, THEN THE CHECK DIALOG BOX IS RENDERED
        sf::RectangleShape checkDialogBox;

        sf::Font titleFont;
        sf::Text titleText;

        float startXPosition = 0.f;
        float startYPosition = (target->getSize().y - 150.f) / 2;

        checkDialogBox.setPosition(sf::Vector2f(startXPosition, startYPosition));
        checkDialogBox.setSize(sf::Vector2f(350.f, 150.f));
        checkDialogBox.setFillColor(sf::Color(54, 58, 55));

        target->draw(checkDialogBox);

        titleFont.loadFromFile("../fonts/inter_bold.ttf");
        titleText.setFont(titleFont);

        titleText.setString("Check !!!");
        titleText.setCharacterSize(35);
        titleText.setFillColor(sf::Color::White);

        titleText.setPosition(sf::Vector2f(startXPosition + 100.f, startYPosition + 20.f));
        target->draw(titleText);

        std::string playerShade = pieceColor ? "White" : "Black";

        // INDICATOR MODIFIED ACCORDING TO WHICH KING IS IN CHECK
        titleText.setString(playerShade + " king is in danger.");
        titleText.setCharacterSize(25);
        titleText.setPosition(sf::Vector2f(startXPosition + 35.f, startYPosition + 80.f));
        target->draw(titleText);
    }
}

void MatchState::renderResignDialog(sf::RenderTarget *target)
{
    bool popup;
    std::ifstream resignPopupFile("../templates/resign_popup.txt");
    resignPopupFile >> popup;
    resignPopupFile.close();

    if (popup)
    {
        // IF RESIGN POPUP FLAG IS ON, THEN RESIGN DIALOG BOX IS RENDERED
        sf::RectangleShape resignDialogBox;

        sf::Font titleFont;
        sf::Text titleText;

        float startXPosition = (target->getSize().x - 445.f) / 2;
        float startYPosition = (target->getSize().y - 245.f) / 2;

        resignDialogBox.setPosition(sf::Vector2f(startXPosition, startYPosition));
        resignDialogBox.setSize(sf::Vector2f(445.f, 245.f));
        resignDialogBox.setFillColor(sf::Color(54, 58, 55));

        target->draw(resignDialogBox);

        titleFont.loadFromFile("../fonts/inter_bold.ttf");
        titleText.setFont(titleFont);

        titleText.setString("Do you want to resign");
        titleText.setCharacterSize(35);
        titleText.setFillColor(sf::Color::White);

        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 20.f));
        target->draw(titleText);

        titleText.setString("the match ?");
        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 80.f));
        target->draw(titleText);

        sf::RectangleShape btnBox[2];

        sf::Font btnFont;
        sf::Text btnText[2];

        btnBox[0].setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 160.f));
        btnBox[0].setSize(sf::Vector2f(130.f, 50.f));
        btnBox[0].setFillColor(sf::Color::Black);

        target->draw(btnBox[0]);

        btnFont.loadFromFile("../fonts/inter_bold.ttf");
        btnText[0].setFont(btnFont);
        btnText[1].setFont(btnFont);

        btnText[0].setString("Resign");
        btnText[0].setCharacterSize(20);
        btnText[0].setFillColor(sf::Color::White);

        btnText[0].setPosition(sf::Vector2f(startXPosition + 70.f, startYPosition + 172.f));
        target->draw(btnText[0]);

        btnBox[1].setPosition(sf::Vector2f(startXPosition + 275.f, startYPosition + 160.f));
        btnBox[1].setSize(sf::Vector2f(130.f, 50.f));
        btnBox[1].setFillColor(sf::Color(169, 169, 169));

        target->draw(btnBox[1]);

        btnText[1].setString("Cancel");
        btnText[1].setCharacterSize(20);
        btnText[1].setFillColor(sf::Color::White);

        btnText[1].setPosition(sf::Vector2f(startXPosition + 305.f, startYPosition + 172.f));
        target->draw(btnText[1]);

        bool clicked;
        char del1, del2;
        float mouseX, mouseY;

        std::ifstream mousePositionFile("../templates/mouse_position.txt");
        mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
        mousePositionFile.close();

        sf::Vector2f clickPosition(mouseX, mouseY);

        if (clicked)
        {
            if (btnBox[0].getGlobalBounds().contains(clickPosition))
            {
                // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
                std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                mousePositionFile_1.close();

                // RESIGN FLAG IS TURNED OFF TO PREVENT MULTIPLE RESIGN
                std::ofstream resignPopupFile_1("../templates/resign_popup.txt");
                resignPopupFile_1 << 0;
                resignPopupFile_1.close();

                // CONFIRMATION FLAG IS TURNED ON
                std::ofstream resignConfirmFile("../templates/resign_confirm.txt");
                resignConfirmFile << 1;
                resignConfirmFile.close();
            }

            if (btnBox[1].getGlobalBounds().contains(clickPosition))
            {
                // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
                std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                mousePositionFile_1.close();

                // RESIGN FLAG IS TURNED OFF TO HIDE RESIGN DIALOG BOX
                std::ofstream resignPopupFile_1("../templates/resign_popup.txt");
                resignPopupFile_1 << 0;
                resignPopupFile_1.close();
            }
        }
    }
}

void MatchState::renderResignConfirmDialog(sf::RenderTarget *target)
{
    bool confirm;
    std::ifstream resignConfirmFile("../templates/resign_confirm.txt");
    resignConfirmFile >> confirm;
    resignConfirmFile.close();

    if (confirm)
    {
        // IF CONFIRM FLAG IS ON, THEN CONFIRM DIALOG BOX IS TURNED ON
        bool playerTurn;
        std::ifstream playerTurnFile("../templates/player_turn.txt");
        playerTurnFile >> playerTurn;
        playerTurnFile.close();

        sf::RectangleShape resignConfirmDialogBox;

        sf::Font titleFont;
        sf::Text titleText;

        float startXPosition = (target->getSize().x - 445.f) / 2;
        float startYPosition = (target->getSize().y - 315.f) / 2;

        resignConfirmDialogBox.setPosition(sf::Vector2f(startXPosition, startYPosition));
        resignConfirmDialogBox.setSize(sf::Vector2f(445.f, 315.f));
        resignConfirmDialogBox.setFillColor(sf::Color(54, 58, 55));

        target->draw(resignConfirmDialogBox);

        titleFont.loadFromFile("../fonts/inter_bold.ttf");
        titleText.setFont(titleFont);

        std::string activePlayer = playerTurn ? "White" : "Black";
        std::string dormantPlayer = playerTurn ? "Black" : "White";

        titleText.setString(activePlayer + " King resigned");
        titleText.setCharacterSize(35);
        titleText.setFillColor(sf::Color::White);

        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 20.f));
        target->draw(titleText);

        titleText.setString("the match.");
        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 80.f));
        target->draw(titleText);

        // INDICATOR IS MODIFIED ACCORDING TO THE PLAYER TURN
        titleText.setString(dormantPlayer + " King wins.");
        titleText.setPosition(sf::Vector2f(startXPosition + 40.f, startYPosition + 180.f));
        target->draw(titleText);

        sf::RectangleShape btnBox;

        sf::Font btnFont;
        sf::Text btnText;

        btnBox.setPosition(sf::Vector2f(startXPosition + 275.f, startYPosition + 240.f));
        btnBox.setSize(sf::Vector2f(130.f, 50.f));
        btnBox.setFillColor(sf::Color::Black);

        target->draw(btnBox);

        btnFont.loadFromFile("../fonts/inter_bold.ttf");
        btnText.setFont(btnFont);

        btnText.setString("Okay");
        btnText.setCharacterSize(20);
        btnText.setFillColor(sf::Color::White);

        btnText.setPosition(sf::Vector2f(startXPosition + 310.f, startYPosition + 252.f));
        target->draw(btnText);

        bool clicked;
        char del1, del2;
        float mouseX, mouseY;

        std::ifstream mousePositionFile("../templates/mouse_position.txt");
        mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
        mousePositionFile.close();

        sf::Vector2f clickPosition(mouseX, mouseY);

        if (clicked)
        {
            if (btnBox.getGlobalBounds().contains(clickPosition))
            {
                // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
                std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                mousePositionFile_1.close();

                // FLAG TO REDIRECT TO MAIN MENU IS TURNED ON
                std::ofstream resignFile("../templates/resign.txt");
                resignFile << 1;
                resignFile.close();
            }
        }
    }
}

void MatchState::renderStalemateDialog(sf::RenderTarget *target)
{
    bool stalemate;
    std::ifstream staleMateFile("../templates/stalemate.txt");
    staleMateFile >> stalemate;
    staleMateFile.close();

    if (stalemate)
    {
        // IF STALEMATE FLAG IS ON, THEN STALEMATE DIALOG BOX IS TURNED ON
        sf::RectangleShape stalemateDialogBox;

        sf::Font titleFont;
        sf::Text titleText;

        float startXPosition = (target->getSize().x - 445.f) / 2;
        float startYPosition = (target->getSize().y - 235.f) / 2;

        stalemateDialogBox.setPosition(sf::Vector2f(startXPosition, startYPosition));
        stalemateDialogBox.setSize(sf::Vector2f(445.f, 235.f));
        stalemateDialogBox.setFillColor(sf::Color(54, 58, 55));

        target->draw(stalemateDialogBox);

        titleFont.loadFromFile("../fonts/inter_bold.ttf");
        titleText.setFont(titleFont);

        titleText.setString("Stalemate!!!");
        titleText.setCharacterSize(35);
        titleText.setFillColor(sf::Color::White);

        titleText.setPosition(sf::Vector2f(startXPosition + 125.f, startYPosition + 20.f));
        target->draw(titleText);

        titleText.setString("It's a Draw.");
        titleText.setPosition(sf::Vector2f(startXPosition + 135.f, startYPosition + 100.f));
        target->draw(titleText);

        sf::RectangleShape btnBox;

        sf::Font btnFont;
        sf::Text btnText;

        btnBox.setPosition(sf::Vector2f(startXPosition + 275.f, startYPosition + 160.f));
        btnBox.setSize(sf::Vector2f(130.f, 50.f));
        btnBox.setFillColor(sf::Color::Black);

        target->draw(btnBox);

        btnFont.loadFromFile("../fonts/inter_bold.ttf");
        btnText.setFont(btnFont);

        btnText.setString("Okay");
        btnText.setCharacterSize(20);
        btnText.setFillColor(sf::Color::White);

        btnText.setPosition(sf::Vector2f(startXPosition + 310.f, startYPosition + 172.f));
        target->draw(btnText);

        bool clicked;
        char del1, del2;
        float mouseX, mouseY;

        std::ifstream mousePositionFile("../templates/mouse_position.txt");
        mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
        mousePositionFile.close();

        sf::Vector2f clickPosition(mouseX, mouseY);

        if (clicked)
        {
            if (btnBox.getGlobalBounds().contains(clickPosition))
            {
                // CLICKED FLAG IS TURNED OFF TO PREVENT MULTIPLE CLICK DETECTION
                std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                mousePositionFile_1.close();

                // FLAG TO REDIRECT TO MAIN MENU IS TURNED ON
                std::ofstream resignFile("../templates/resign.txt");
                resignFile << 1;
                resignFile.close();
            }
        }
    }
}

void MatchState::checkForPawnPromotion()
{
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    // TO CHECK IF PAWN HAS REACHED TO THE LAST ROW
    while (std::getline(currentPositionFile, infoLine))
    {
        std::istringstream infoString(infoLine);
        int x, y;
        std::string pisType;
        bool pisColor;
        std::string pisIdentifier;

        infoString >> x;
        infoString.ignore(1, ',');

        infoString >> y;
        infoString.ignore(1, ',');

        std::getline(infoString, pisType, ',');
        if (infoString.fail())
            continue;

        infoString >> pisColor;
        if (infoString.fail())
            continue;
        infoString.ignore(1, ',');

        std::getline(infoString, pisIdentifier);
        if (infoString.fail())
            continue;

        // TO CHECK FOR WHITE PAWN
        if (pisColor && pisType == "pawn" && y == 7)
        {
            std::ofstream pawnPromotionInfoFile_1("../templates/pawn_promotion_info.txt");
            pawnPromotionInfoFile_1 << x << ',' << y << ',' << 1 << ',' << 1;
            pawnPromotionInfoFile_1.close();
            break;
        }
        // TO CHECK FOR BLACK PAWN
        else if (!pisColor && pisType == "pawn" && y == 0)
        {
            std::ofstream pawnPromotionInfoFile_2("../templates/pawn_promotion_info.txt");
            pawnPromotionInfoFile_2 << x << ',' << y << ',' << 0 << ',' << 1;
            pawnPromotionInfoFile_2.close();
            break;
        }
        else
        {
            std::ofstream pawnPromotionInfoFile_3("../templates/pawn_promotion_info.txt");
            pawnPromotionInfoFile_3 << 0 << ',' << 0 << ',' << 0 << ',' << 0;
            pawnPromotionInfoFile_3.close();
        }
    }
    currentPositionFile.close();
}

void MatchState::castle(int initialRow, int initialColumn, int finalRow, int finalColumn)
{
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    // TO CHECK IF CASTLING HAS BEEN DONE OR NOT
    while (std::getline(currentPositionFile, infoLine))
    {
        std::istringstream infoString(infoLine);
        int _x, _y;
        bool _pisColor;
        std::string _pisType, _pisIdentifier;

        infoString >> _x;
        infoString.ignore(1, ',');

        infoString >> _y;
        infoString.ignore(1, ',');

        std::getline(infoString, _pisType, ',');
        if (infoString.fail())
            continue;

        infoString >> _pisColor;
        if (infoString.fail())
            continue;
        infoString.ignore(1, ',');

        std::getline(infoString, _pisIdentifier);
        if (infoString.fail())
            continue;

        if (_x == initialRow && _y == initialColumn)
        {
            // IS KING IS IN SAME Y COORDINATE AS CASTLING OCCURS IN SAME Y COORDINATE
            if (_pisType == "king" && finalColumn == initialColumn)
            {
                // FOR SHORT CASTLING
                if (finalRow == (initialRow + 2))
                {
                    currentPositionFile.close();

                    std::ifstream currentPositionFile_1("../templates/current_piece_position.txt");
                    std::ofstream castlingMoveFile_1("../templates/castling_move.txt");
                    std::string infoLine_1;

                    while (std::getline(currentPositionFile_1, infoLine_1))
                    {
                        std::istringstream infoString_1(infoLine_1);

                        int row, col;

                        infoString_1 >> row;
                        infoString_1.ignore(1, ',');

                        infoString_1 >> col;
                        infoString_1.ignore(1, ',');

                        // REPLACING ROOK FROM INITIAL POSITION TO OPPOSITE SIDE OF KING
                        if ((row == (initialRow + 1)) && col == initialColumn)
                        {
                            castlingMoveFile_1 << row << ',' << col << ',' << "rook" << ',' << _pisColor << ',' << "rook2" << std::endl;
                        }
                        else if ((row == (initialRow + 3)) && col == initialColumn)
                        {
                            castlingMoveFile_1 << row << ',' << col << ',' << ',' << ',' << std::endl;
                        }
                        else
                        {
                            castlingMoveFile_1 << infoLine_1 << std::endl;
                        }
                    }
                    currentPositionFile_1.close();
                    castlingMoveFile_1.close();
                    std::filesystem::remove("../templates/current_piece_position.txt");
                    std::filesystem::rename("../templates/castling_move.txt", "../templates/current_piece_position.txt");
                }

                // FOR LONG CASTLING
                if (finalRow == (initialRow - 2))
                {
                    currentPositionFile.close();

                    std::ifstream currentPositionFile_2("../templates/current_piece_position.txt");
                    std::ofstream castlingMoveFile_2("../templates/castling_move.txt");
                    std::string infoLine_2;

                    while (std::getline(currentPositionFile_2, infoLine_2))
                    {
                        std::istringstream infoString_2(infoLine_2);

                        int row, col;

                        infoString_2 >> row;
                        infoString_2.ignore(1, ',');

                        infoString_2 >> col;
                        infoString_2.ignore(1, ',');

                        // REPLACING ROOK FROM INITIAL POSITION TO OPPOSITE SIDE OF KING
                        if ((row == (initialRow - 1)) && col == initialColumn)
                        {
                            castlingMoveFile_2 << row << ',' << col << ',' << "rook" << ',' << _pisColor << ',' << "rook1" << std::endl;
                        }
                        else if ((row == (initialRow - 4)) && col == initialColumn)
                        {
                            castlingMoveFile_2 << row << ',' << col << ',' << ',' << ',' << std::endl;
                        }
                        else
                        {
                            castlingMoveFile_2 << infoLine_2 << std::endl;
                        }
                    }
                    currentPositionFile_2.close();
                    castlingMoveFile_2.close();
                    std::filesystem::remove("../templates/current_piece_position.txt");
                    std::filesystem::rename("../templates/castling_move.txt", "../templates/current_piece_position.txt");
                }
            }
        }
    }
    currentPositionFile.close();
}

void MatchState::isCheck(sf::RenderTarget *target)
{
    int blackKingCorrd[2];
    int whiteKingCorrd[2];
    std::ifstream currentPositionFile_1("../templates/current_piece_position.txt");
    std::string infoLine_1;

    // TO RETRIEVE CURRENT COORDINATE OF BOTH KINGS
    while (std::getline(currentPositionFile_1, infoLine_1))
    {
        std::istringstream infoString_1(infoLine_1);
        int x, y;
        std::string pisType;
        bool pisColor;
        std::string pisIdentifier;

        infoString_1 >> x;
        infoString_1.ignore(1, ',');

        infoString_1 >> y;
        infoString_1.ignore(1, ',');

        std::getline(infoString_1, pisType, ',');
        if (infoString_1.fail())
            continue;

        infoString_1 >> pisColor;
        if (infoString_1.fail())
            continue;
        infoString_1.ignore(1, ',');

        std::getline(infoString_1, pisIdentifier);
        if (infoString_1.fail())
            continue;

        pisType = pisType.substr(pisType.find_first_not_of(" \t"));
        pisIdentifier = pisIdentifier.substr(pisIdentifier.find_first_not_of(" \t"));

        if (pisType == "king")
        {
            if (pisColor)
            {
                // FOR WHITE KING
                whiteKingCorrd[0] = x;
                whiteKingCorrd[1] = y;
            }
            else
            {
                // FOR BLACK KING
                blackKingCorrd[0] = x;
                blackKingCorrd[1] = y;
            }
        }
    }
    currentPositionFile_1.close();

    std::vector<std::vector<int>> whitePossibleMoves = {};
    std::vector<std::vector<int>> blackPossibleMoves = {};

    std::ifstream currentPositionFile_2("../templates/current_piece_position.txt");
    std::string infoLine_2;

    // RENDERING VIRTUAL BOARD PIECES TO EMULATE THE CURRENT POSITION OF PIECES IN THE REAL BOARD
    while (std::getline(currentPositionFile_2, infoLine_2))
    {
        std::istringstream infoString_2(infoLine_2);
        int x, y;
        std::string pisType;
        bool pisColor;
        std::string pisIdentifier;

        infoString_2 >> x;
        infoString_2.ignore(1, ',');

        infoString_2 >> y;
        infoString_2.ignore(1, ',');

        std::getline(infoString_2, pisType, ',');
        if (infoString_2.fail())
            continue;

        infoString_2 >> pisColor;
        if (infoString_2.fail())
            continue;
        infoString_2.ignore(1, ',');

        std::getline(infoString_2, pisIdentifier);
        if (infoString_2.fail())
            continue;

        std::string imageColor = pisColor ? "white" : "black";
        sf::Color btnColor = sf::Color::White;

        delete this->virtualBoardPieces[x][y];
        if (pisType == "pawn")
        {
            std::string imagePath = "../src/" + imageColor + "_pawn.png";
            this->virtualBoardPieces[x][y] = new Pawn(pisColor, x, y, btnColor, imagePath, target);
        }
        else if (pisType == "bishop")
        {
            std::string imagePath = "../src/" + imageColor + "_bishop.png";
            this->virtualBoardPieces[x][y] = new Bishop(pisColor, x, y, btnColor, imagePath, target);
        }
        else if (pisType == "knight")
        {
            std::string imagePath = "../src/" + imageColor + "_knight.png";
            this->virtualBoardPieces[x][y] = new Knight(pisColor, x, y, btnColor, imagePath, target);
        }
        else if (pisType == "rook")
        {
            std::string imagePath = "../src/" + imageColor + "_rook.png";
            this->virtualBoardPieces[x][y] = new Rook(pisColor, x, y, btnColor, imagePath, target);
        }
        else if (pisType == "queen")
        {
            std::string imagePath = "../src/" + imageColor + "_queen.png";
            this->virtualBoardPieces[x][y] = new Queen(pisColor, x, y, btnColor, imagePath, target);
        }
        else if (pisType == "king")
        {
            std::string imagePath = "../src/" + imageColor + "_king.png";
            this->virtualBoardPieces[x][y] = new King(pisColor, x, y, btnColor, imagePath, target);
        }

        // POSSIBLE MOVE COORDINATES ARE PUSHED TO EACH ARRAY ACCORDING TO THE PIECE COLOR
        if (pisColor)
        {
            this->virtualBoardPieces[x][y]->possibleMoves(x, y, pisColor, whitePossibleMoves);
        }
        else
        {
            this->virtualBoardPieces[x][y]->possibleMoves(x, y, pisColor, blackPossibleMoves);
        }
    }
    currentPositionFile_2.close();

    bool whiteKingCheckFlag = 0;
    bool blackKingCheckFlag = 0;

    // TO CHECK IF ANY BLACK POSSIBLE MOVE COORDINATE COINCIDE WITH CURRENT COORDINATE OF WHITE KING
    for (const auto &bpair : blackPossibleMoves)
    {
        int xMove = bpair[0];
        int yMove = bpair[1];
        if (whiteKingCorrd[0] == xMove && whiteKingCorrd[1] == yMove)
        {
            whiteKingCheckFlag = 1;
        }
    }

    // TO CHECK IF ANY WHITE POSSIBLE MOVE COORDINATE COINCIDE WITH CURRENT COORDINATE OF BLACK KING
    for (const auto &wpair : whitePossibleMoves)
    {
        int xMove = wpair[0];
        int yMove = wpair[1];
        if (blackKingCorrd[0] == xMove && blackKingCorrd[1] == yMove)
        {
            blackKingCheckFlag = 1;
        }
    }

    // CURRENT PLAYER TURN IS RETRIEVED
    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    this->playerTurn = !playerTurn;
    this->whiteKingCheckFlag = whiteKingCheckFlag;
    this->blackKingCheckFlag = blackKingCheckFlag;

    // TO CHECK IF CHECK FLAG IS ON
    if ((whiteKingCheckFlag) || (blackKingCheckFlag))
    {
        char deli;
        bool whoseTurn, prevFlag;

        std::ifstream checkFlagFile("../templates/check_flag.txt");
        checkFlagFile >> whoseTurn >> deli >> prevFlag;
        checkFlagFile.close();

        // IF FLAG WAS ALREADY ON WHICH MEANS THE USER DID AN INVALID MOVE AS THE KING IS STILL IN CHECK
        if (prevFlag)
        {
            // THE MOVE IS RETRACTED BACK TO PREVIOUS MOVESET
            std::ifstream tempPositionFile_3("../templates/temp_piece_position.txt");
            std::ofstream currentPositionFile_3("../templates/current_piece_position.txt");
            std::string infoLine_3;

            while (std::getline(tempPositionFile_3, infoLine_3))
            {
                currentPositionFile_3 << infoLine_3 << std::endl;
            }
            tempPositionFile_3.close();
            currentPositionFile_3.close();

            // TURN IS INVERSED AS THE INVALID MOVE SHOULD NOT WASTE A PLAYER'S TURN
            bool turnNum, inverseTurn;
            std::ifstream playerTurnFile_1("../templates/player_turn.txt");
            std::ofstream inversePlayerTurnFile("../templates/inverse_player_turn.txt");

            playerTurnFile_1 >> turnNum;
            inverseTurn = !turnNum;
            inversePlayerTurnFile << inverseTurn;

            playerTurnFile_1.close();
            inversePlayerTurnFile.close();
            std::filesystem::remove("../templates/player_turn.txt");
            std::filesystem::rename("../templates/inverse_player_turn.txt", "../templates/player_turn.txt");
        }
        else
        {
            // THE POSITION INFO FILE IS UPDATED ACCORDINGLY IF THE CHECK FLAG WAS JUST TURNED ON
            std::ofstream checkFlagFile_1("../templates/check_flag.txt");
            checkFlagFile_1 << !playerTurn << ',' << 1;
            checkFlagFile_1.close();

            std::ifstream currentPositionFile_4("../templates/current_piece_position.txt");
            std::ofstream tempPositionFile_4("../templates/temp_piece_position.txt");
            std::string infoLine_4;

            while (std::getline(currentPositionFile_4, infoLine_4))
            {
                tempPositionFile_4 << infoLine_4 << std::endl;
            }
            currentPositionFile_4.close();
            tempPositionFile_4.close();

            // TO CHECK POSSIBLE CHECKMATE
            if (whiteKingCheckFlag)
            {
                this->isCheckmate(1, blackPossibleMoves);
            }
            else if (blackKingCheckFlag)
            {
                this->isCheckmate(0, whitePossibleMoves);
            }

            if (this->checkmate)
            {
                // END GAME
            }
        }
    }
    else
    {
        std::ofstream checkFlagFile_2("../templates/check_flag.txt");
        checkFlagFile_2 << 0 << ',' << 0;
        checkFlagFile_2.close();

        std::ifstream currentPositionFile_5("../templates/current_piece_position.txt");
        std::ofstream tempPositionFile_5("../templates/temp_piece_position.txt");
        std::string infoLine_5;

        while (std::getline(currentPositionFile_5, infoLine_5))
        {
            tempPositionFile_5 << infoLine_5 << std::endl;
        }
        currentPositionFile_5.close();
        tempPositionFile_5.close();
    }

    if ((this->playerTurn && !this->whiteKingCheckFlag && whitePossibleMoves.empty()) || (!this->playerTurn && !this->blackKingCheckFlag && blackPossibleMoves.empty()))
    {
        std::ofstream staleMateFile("../templates/stalemate.txt");
        staleMateFile << 1;
        staleMateFile.close();
    }
}

void MatchState::isCheckmate(bool shade, std::vector<std::vector<int>> &oppMoveArray)
{
    std::vector<std::vector<int>> kingposMoves = {};

    std::ifstream currentPositionFile_2("../templates/current_piece_position.txt");
    std::string infoLine_2;

    // LOOPING OVER EACH PIECE TO IDENTIFY KING
    while (std::getline(currentPositionFile_2, infoLine_2))
    {
        std::istringstream infoString_2(infoLine_2);
        int x, y;
        std::string pisType;
        bool pisColor;
        std::string pisIdentifier;

        infoString_2 >> x;
        infoString_2.ignore(1, ',');

        infoString_2 >> y;
        infoString_2.ignore(1, ',');

        std::getline(infoString_2, pisType, ',');
        if (infoString_2.fail())
            continue;

        infoString_2 >> pisColor;
        if (infoString_2.fail())
            continue;
        infoString_2.ignore(1, ',');

        std::getline(infoString_2, pisIdentifier);
        if (infoString_2.fail())
            continue;

        // IF PIECE IS KING AND COLOR MATCHES TO THE PASSED COLOR
        if (pisColor == shade && pisType == "king")
        {
            // ALL POSSIBLE MOVE OF THE KING IS CHECKED IF IT TURNS OFF THE CHECK OFF
            // IF IT CANNOT THEN IT IS CHECKMATE
            this->virtualBoardPieces[x][y]->possibleMoves(x, y, pisColor, kingposMoves);
            for (const auto &kpair : kingposMoves)
            {
                int kxMove = kpair[0];
                int kyMove = kpair[1];

                int isNotSafe = 0;

                for (const auto &bpair : oppMoveArray)
                {
                    int bxMove = bpair[0];
                    int byMove = bpair[1];

                    if (kxMove == bxMove && kyMove == byMove)
                    {
                        isNotSafe++;
                    }
                }

                if (isNotSafe == 0)
                {
                    this->checkmate = false;
                    return;
                }
            }
            this->checkmate = true;
        }
    }
    currentPositionFile_2.close();
}