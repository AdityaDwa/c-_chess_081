#include "../header_files/MainMenuState.h"

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("../fonts/Roboto-Black.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initBtns()
{
    this->btns["black_pawn_a8"] = new Button(((this->window->getSize().x - 960.f) / 2), ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_b8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 120.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_c8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 240.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_d8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 360.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_e8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 480.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_f8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 600.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_g8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 720.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");
    this->btns["black_pawn_h8"] = new Button(((this->window->getSize().x - 960.f) / 2) + 840.f, ((this->window->getSize().y - 960.f) / 2) - 20.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/black_pawn.png");

    this->btns["white_pawn_a1"] = new Button(((this->window->getSize().x - 960.f) / 2), ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_b1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 120.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_c1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 240.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_d1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 360.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_e1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 480.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_f1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 600.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_g1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 720.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
    this->btns["white_pawn_h1"] = new Button(((this->window->getSize().x - 960.f) / 2) + 840.f, ((this->window->getSize().y - 960.f) / 2) + 820.f, 120, 120, &this->font, "", sf::Color(0, 0, 0, 0), sf::Color(169, 169, 169), "../images/white_pawn.png");
}

MainMenuState::MainMenuState(sf::RenderWindow *window) : State(window)
{
    this->initFonts();
    this->initBtns();

    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color(119, 149, 86));
}

MainMenuState::~MainMenuState()
{
    auto btnPair = this->btns.begin();
    for (btnPair = this->btns.begin(); btnPair != this->btns.end(); ++btnPair)
    {
        delete btnPair->second;
    }
}

void MainMenuState::endState()
{
    std::cout << "end State";
}

void MainMenuState::updateInput(const float &deltaTime)
{
    this->checkForQuit();
}

void MainMenuState::updateBtns()
{
    for (auto &btn : this->btns)
    {
        btn.second->update(this->mousePosView);
    }

    if (this->btns["white_pawn_a1"]->isClicked)
    {
        this->btns["move1"] = new Button(((this->window->getSize().x - 960.f) / 2), ((this->window->getSize().y - 960.f) / 2) + 720.f, 120, 120, &this->font, "", sf::Color(169, 169, 169), sf::Color(169, 169, 169), "../images/white_pawn.png");
        this->btns["move2"] = new Button(((this->window->getSize().x - 960.f) / 2), ((this->window->getSize().y - 960.f) / 2) + 600.f, 120, 120, &this->font, "", sf::Color(169, 169, 169), sf::Color(169, 169, 169), "../images/white_pawn.png");
    }
}

void MainMenuState::update(const float &deltaTime)
{
    this->updateMousePositions();
    this->updateInput(deltaTime);

    this->updateBtns();
}

void MainMenuState::renderBtns(sf::RenderTarget *target)
{
    for (auto &btn : this->btns)
    {
        btn.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->background);

    const int numSquares = 8;                                                 // NUMBER OF SQUARES PER ROW/COLUMN
    const float squareSize = 120.f;                                           // PIXEL SIZE OF EACH SQUARE
    sf::Color colors[2] = {sf::Color(235, 236, 220), sf::Color(139, 85, 19)}; // Color(139, 85, 19)(119, 149, 86)

    // CALCULATING BOARDSIZE (LENGTH/WIDTH)
    float boardSize = numSquares * squareSize;

    // CALCULATING START POSITION TO CENTER ALIGN THE BOARD
    float startXPosition = (this->window->getSize().x - boardSize) / 2;
    float startYPosition = (this->window->getSize().y - boardSize) / 2;

    // DRAWING CHESSBOARD
    for (int i = 0; i < numSquares; i++)
    {
        for (int j = 0; j < numSquares; j++)
        {
            // CALCULATING POSITON FOR SQUARE
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(startXPosition + (i * squareSize), startYPosition + (j * squareSize));

            // ALTERNATING COLOR BASED ON ROW/COLUMN
            square.setFillColor(colors[(i + j) % 2]);

            // DRAWING THE SQUARE
            target->draw(square);
        }
    }

    this->renderBtns(target);
}