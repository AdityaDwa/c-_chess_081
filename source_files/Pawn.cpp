#include "../header_files/Pawn.h"

Pawn::Pawn(bool pieceColor, int row, int column, sf::RenderTarget *target) : Piece(pieceColor, row, column, target)
{
    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    if (pieceColor)
    {
        this->texture.loadFromFile("../src/white_pawn.png"); // handle error
    }
    else
    {
        this->texture.loadFromFile("../src/black_pawn.png");
    }

    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 120.f / this->sprite.getLocalBounds().width;
    float scaleY = 120.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);

    this->isClicked = false;
}

Pawn::~Pawn()
{
}

void Pawn::update(const sf::Vector2f mousePos)
{
    // if (this->buttonShape.getGlobalBounds().contains(mousePos)) {
    //     // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //         this->buttonShape.setFillColor(sf::Color(169, 169, 169));
    //         this->isClicked = true;
        // }
        // else {
            // this->isClicked = false;
        // }
    // }
    static bool wasPressed = false;
    static int clickCount = 0;

    if (this->buttonShape.getGlobalBounds().contains(mousePos))
    {
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (isPressed && !wasPressed)
        {
            clickCount++;
            this->isClicked = (clickCount % 2 == 1);
            this->buttonShape.setFillColor(isClicked ? sf::Color(169, 169, 169) : sf::Color(0, 0, 0, 0));
        }
        wasPressed = isPressed;
    }
    else
    {
        wasPressed = false;
    }
}

void Pawn::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}