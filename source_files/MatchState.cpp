#include "../header_files/MatchState.h"

MatchState::MatchState(sf::RenderWindow *window) : State(window)
{
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(119, 149, 86));
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
                this->boardPieces[i][j]->update(this->mousePosView);
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        if (this->btns[i] != nullptr)
        {
            this->btns[i]->update(this->mousePosView);
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
}

void MatchState::renderPieces(sf::RenderTarget *target)
{
    std::ifstream file("../pieces_info.txt");
    std::string line;

    std::ifstream sourceFile("../active_tiles.txt");
    std::string linecoord;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::getline(file, line);
            std::istringstream ss(line);

            std::getline(sourceFile, linecoord);
            std::istringstream sscoord(linecoord);

            int row, col;
            std::string pieceType;
            bool pieceColor;
            std::string pieceIdentifier;

            int num1, num2, num3;
            char delimiter1, delimiter2;

            ss >> row;
            ss.ignore(1, ',');

            ss >> col;
            ss.ignore(1, ',');

            std::getline(ss, pieceType, ',');
            if (ss.fail())
                continue;

            ss >> pieceColor;
            if (ss.fail())
                continue;
            ss.ignore(1, ',');

            std::getline(ss, pieceIdentifier);
            if (ss.fail())
                continue;

            pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
            pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

            sscoord >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3;

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
            else
            {
                std::string imagePath = "../src/" + imageColor + "_king.png";
                this->boardPieces[row][col] = new King(pieceColor, row, col, btnColor, imagePath, target);
            }

            this->boardPieces[row][col]->render(target);
        }
    }

    file.close();
    sourceFile.close();

    std::ifstream filegone("../isClickedOn.txt");
    std::string liner;
    while (std::getline(filegone, liner))
    {
        std::istringstream jss(liner);
        int initialRow, initialColumn, finalRow, finalColumn, moveFlag;
        char delimiter1, delimiter2, delimiter3, delimiter4;
        jss >> initialRow >> delimiter1 >> initialColumn >> delimiter2 >> finalRow >> delimiter3 >> finalColumn >> delimiter4 >> moveFlag;
        if (moveFlag)
        {
            // std::ofstream test("../logs/templog.txt");
            // test << "i am working" << r << c << f;
            // test.close();

            if (this->boardPieces[initialRow][initialColumn] != nullptr)
            {
                this->boardPieces[initialRow][initialColumn]->movePiece(initialRow, initialColumn, finalRow, finalColumn);
                delete this->boardPieces[initialRow][initialColumn];
                this->boardPieces[initialRow][initialColumn] = nullptr;
                
                for (int i = 0; i < 30; i++)
                {
                    delete this->btns[i];
                    this->btns[i] = nullptr;
                }

                bool turnNum, inverseTurn;
                std::ifstream filler("../turn.txt");
                std::ofstream turnChangeptr("../tempturn.txt");
                
                filler >> turnNum;
                inverseTurn = !turnNum;
                turnChangeptr << inverseTurn;

                filler.close();
                turnChangeptr.close();
                std::filesystem::remove("../turn.txt");
                std::filesystem::rename("../tempturn.txt", "../turn.txt");
            }
        }
    }
    filegone.close();

    std::ofstream vacancy("../isClickedOn.txt");
    vacancy.close();
}