#include "../header_files/MatchState.h"

MatchState::MatchState(sf::RenderWindow *window) : State(window)
{
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(119, 149, 86));
    for (int i = 0; i < 32; i++)
    {
        this->boardPieces[i] = nullptr;
    }
}

MatchState::~MatchState()
{
    for (int i = 0; i < 32; ++i)
    {
        delete this->boardPieces[i];
        this->boardPieces[i] = nullptr;
    }

    // auto btnPair = this->btns.begin();
    // for (btnPair = this->btns.begin(); btnPair != this->btns.end(); ++btnPair)
    // {
    //     delete btnPair->second;
    // }
}

void MatchState::update(const float &deltaTime)
{
    this->updateMousePositions();
    for (int i = 0; i < 32; i++)
    {
        if (this->boardPieces[i] != nullptr)
        {
            this->boardPieces[i]->update(this->mousePosView);
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

    int i = 0;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);

        std::string pieceType;
        bool pieceColor;
        int row, col;
        std::string pieceIdentifier;

        std::getline(ss, pieceType, ',');
        ss >> std::boolalpha >> pieceColor;
        ss.ignore(1, ',');
        ss >> row;
        ss.ignore(1, ',');
        ss >> col;
        ss.ignore(1, ',');
        std::getline(ss, pieceIdentifier);

        pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
        pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

        if (pieceType == "pawn")
        {
            this->boardPieces[i] = new Pawn(pieceColor, row, col, target);
            this->boardPieces[i]->render(target);
        }
        else
        {
            this->boardPieces[i] = new Knight(pieceColor, row, col, target);
            this->boardPieces[i]->render(target);
        }
        // else{
        //     this->boardPieces[i] = nullptr;
        // }

        i++;
    }

    file.close();
}