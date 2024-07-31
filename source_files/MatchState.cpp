#include "../header_files/MatchState.h"

MatchState::MatchState(sf::RenderWindow *window) : State(window)
{
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(54, 58, 55));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->boardPieces[i][j] = nullptr;
        }
    }

    for (int i = 0; i < 30; i++)
    {
        this->btns[i] = nullptr;
    }
}

MatchState::~MatchState()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; j++)
        {
            delete this->boardPieces[i][j];
            this->boardPieces[i][j] = nullptr;
        }
    }

    for (int i = 0; i < 30; i++)
    {
        delete this->btns[i];
        this->btns[i] = nullptr;
    }
}

void MatchState::update(const float &deltaTime)
{
    this->updateMousePositions();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->boardPieces[i][j] != nullptr)
            {
                this->boardPieces[i][j]->update();
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        if (this->btns[i] != nullptr)
        {
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

    target->draw(this->stateBackground);
    this->renderBoard(target);
    this->renderPieces(target);

    this->renderPawnPromoDialog(target);
}

void MatchState::endState()
{
}

void MatchState::renderBoard(sf::RenderTarget *target)
{
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
            square.setFillColor(boardColors[(i + j) % 2]);

            target->draw(square);
        }
    }

    this->labelFont.loadFromFile("../fonts/inter_regular.ttf");

    this->xtileLabel.setFont(this->labelFont);
    this->ytileLabel.setFont(this->labelFont);

    char colLabels[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char rowLabels[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    for (int i = 0; i < 8; i++)
    {
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
}

void MatchState::renderPieces(sf::RenderTarget *target)
{
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    std::ifstream activeTileInfoFile("../templates/active_tile_info.txt");
    std::string activeLineInfo;

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
                std::vector<std::vector<int>> moveArray = {};
                this->boardPieces[row][col]->possibleMoves(row, col, pieceColor, moveArray);

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

            delete this->boardPieces[row][col];
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

    int blackKingCorrd[2];
    int whiteKingCorrd[2];
    std::ifstream currentPositionFile_1("../templates/current_piece_position.txt");
    std::string infoLine_1;

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
                whiteKingCorrd[0] = x;
                whiteKingCorrd[1] = y;
            }
            else
            {
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

        if (pisColor)
        {
            this->boardPieces[x][y]->possibleMoves(x, y, pisColor, whitePossibleMoves);
        }
        else
        {
            this->boardPieces[x][y]->possibleMoves(x, y, pisColor, blackPossibleMoves);
        }
    }
    currentPositionFile_2.close();

    bool whiteKingCheckFlag = 0;
    bool blackKingCheckFlag = 0;

    for (const auto &bpair : blackPossibleMoves)
    {
        int xMove = bpair[0];
        int yMove = bpair[1];
        if (whiteKingCorrd[0] == xMove && whiteKingCorrd[1] == yMove)
        {
            whiteKingCheckFlag = 1;
        }
    }

    for (const auto &wpair : whitePossibleMoves)
    {
        int xMove = wpair[0];
        int yMove = wpair[1];
        if (blackKingCorrd[0] == xMove && blackKingCorrd[1] == yMove)
        {
            blackKingCheckFlag = 1;
        }
    }

    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurn = !playerTurn;
    playerTurnFile.close();

    if ((playerTurn && whiteKingCheckFlag) || (!playerTurn && blackKingCheckFlag))
    {
        std::ifstream tempPositionFile_3("../templates/temp_piece_position.txt");
        std::ofstream currentPositionFile_3("../templates/current_piece_position.txt");
        std::string infoLine_3;

        while (std::getline(tempPositionFile_3, infoLine_3))
        {
            currentPositionFile_3 << infoLine_3 << std::endl;
        }
        tempPositionFile_3.close();
        currentPositionFile_3.close();

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

    std::ifstream currentPositionFile_4("../templates/current_piece_position.txt");
    std::ofstream tempPositionFile_4("../templates/temp_piece_position.txt");
    std::string infoLine_4;

    while (std::getline(currentPositionFile_4, infoLine_4))
    {
        tempPositionFile_4 << infoLine_4 << std::endl;
    }
    currentPositionFile_4.close();
    tempPositionFile_4.close();

    std::ifstream isButtonClickedFile("../templates/is_button_clicked.txt");
    std::string coordInfoLine;

    while (std::getline(isButtonClickedFile, coordInfoLine))
    {
        std::istringstream coordInfoString(coordInfoLine);

        int initialRow, initialColumn, finalRow, finalColumn, moveFlag;
        char delimiter1, delimiter2, delimiter3, delimiter4;

        coordInfoString >> initialRow >> delimiter1 >> initialColumn >> delimiter2 >> finalRow >> delimiter3 >> finalColumn >> delimiter4 >> moveFlag;
        if (moveFlag)
        {
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

                if ((playerTurn && !whiteKingCheckFlag) || (!playerTurn && !blackKingCheckFlag))
                {
                    this->castle(initialRow, initialColumn, finalRow, finalColumn);
                }

                this->boardPieces[initialRow][initialColumn]->movePiece(initialRow, initialColumn, finalRow, finalColumn);
                this->checkForPawnPromotion();

                delete this->boardPieces[initialRow][initialColumn];
                this->boardPieces[initialRow][initialColumn] = nullptr;

                for (int i = 0; i < 30; i++)
                {
                    delete this->btns[i];
                    this->btns[i] = nullptr;
                }

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

                    std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                    mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                    mousePositionFile_1.close();

                    std::ofstream pawnPromotionInfoFile_1("../templates/pawn_promotion_info.txt");
                    pawnPromotionInfoFile_1 << 0 << ',' << 0 << ',' << 0 << ',' << 0;
                    pawnPromotionInfoFile_1.close();
                }
            }
        }
    }
}

void MatchState::checkForPawnPromotion()
{
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

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

        if (pisColor && pisType == "pawn" && y == 7)
        {
            std::ofstream pawnPromotionInfoFile_1("../templates/pawn_promotion_info.txt");
            pawnPromotionInfoFile_1 << x << ',' << y << ',' << 1 << ',' << 1;
            pawnPromotionInfoFile_1.close();
            break;
        }
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
            if (_pisType == "king" && finalColumn == initialColumn)
            {
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