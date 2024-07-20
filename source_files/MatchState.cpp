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

            ss >> std::boolalpha >> pieceColor;
            if (ss.fail() || ss.peek() != ',')
                continue;
            ss.ignore(1, ',');

            std::getline(ss, pieceIdentifier);
            if (ss.fail())
                continue;

            pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
            pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

            sscoord >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3;

            sf::Color color = num3 ? sf::Color(169, 169, 169) : sf::Color(0, 0, 0, 0); 
            if (num3)
            {
                // delete this->boardPieces[3][3];
                // this->boardPieces[3][3] = new Pawn(true, 3, 3, color, target);
                // this->boardPieces[3][3]->render(target);
                this->boardPieces[i][j]->move(i, j, 4, 4);
            }
            

            delete this->boardPieces[i][j];
            if (pieceType == "pawn")
            {
                this->boardPieces[i][j] = new Pawn(pieceColor, row, col, color, target);
            }
            else if (pieceType == "bishop")
            {
                this->boardPieces[i][j] = new Bishop(pieceColor, row, col, color, target);
            }
            else if (pieceType == "knight")
            {
                this->boardPieces[i][j] = new Knight(pieceColor, row, col, color, target);
            }
            else if (pieceType == "rook")
            {
                this->boardPieces[i][j] = new Rook(pieceColor, row, col, color, target);
            }
            else if (pieceType == "queen")
            {
                this->boardPieces[i][j] = new Queen(pieceColor, row, col, color, target);
            }
            else
            {
                this->boardPieces[i][j] = new King(pieceColor, row, col, color, target);
            }

            this->boardPieces[i][j]->render(target);
        }
    }

    file.close();
    sourceFile.close();
}